/*******************************************************************************************************************//**
 * Back light driver for ISL97671A
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "../inc/isl97671a.h"
#include "../../i2c/inc/i2c_ctrl.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define DUTY_MAX                            (100)
#define DUTY_MIN                            (0)
#define BL_EVENT_FLAG_I2C_ABRT              (0x00000001UL)
#define BL_EVENT_FLAG_I2C_RXCP              (0x00000002UL)
#define BL_EVENT_FLAG_I2C_TXCP              (0x00000004UL)
#define BL_EVENT_FLAG_I2C_ERR               (0x00000008UL)
#define BL_EVENT_FLAG_I2C_MASK              (BL_EVENT_FLAG_I2C_ABRT|BL_EVENT_FLAG_I2C_RXCP|BL_EVENT_FLAG_I2C_TXCP|BL_EVENT_FLAG_I2C_ERR)
#define MTU3_MAX_PERCENT                    (100)
#define ISL97671A_I2C_DEVCTRL_REG           (0x01)
#define ISL97671A_I2C_PWMCTRL_REG           (0x00)
#define ISL97671A_I2C_DEVCTRL_DATA_MTD1     (0x05)
#define ISL97671A_I2C_DEVCTRL_DATA_MTD2     (0x03)
#define ISL97671A_I2C_DEVCTRL_DATA_BLOFF    (0x00)
#define ISL97671A_I2C_WAIT                  (500)
#define ISL97671A_I2C_SLV_ADDR              (0x2C)      /* ISL97671A slave address */
#define TX_SUCCESS                          (0x00)

/***********************************************************************************************************************
 * Private constants
 **********************************************************************************************************************/
//static TX_EVENT_FLAGS_GROUP event_flag;

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void _isl87671a_callback( i2c_master_callback_args_t *p_arg );
static void _isl87671a_i2c_open(i2c_master_instance_t *p_i2c);
static void _isl87671a_i2c_close(i2c_master_instance_t *p_i2c);
static uint32_t _isl87671a_i2c_wait_cb(i2c_master_event_t *p_event);
static fsp_err_t _isl87671a_i2c_backlight_method_set(i2c_master_instance_t *p_i2c, led_method_type method);
static fsp_err_t _isl87671a_i2c_backlight_duty_set(i2c_master_instance_t *p_i2c, uint32_t duty);
static void _isl87671a_mtu3_backlight_duty_set(timer_instance_t *p_mtu3, uint32_t duty);
static volatile i2c_master_event_t g_i2c_event = I2C_MASTER_EVENT_ABORTED;
volatile static uint32_t g_counter = 0;

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/


/*******************************************************************************************************************//**
 * @addtogroup ISL97671A
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * global Functions
 **********************************************************************************************************************/

void isl87671a_ctrl_func(timer_instance_t *p_mtu3, led_method_type method, uint32_t duty)
{
    uint32_t status;
    i2c_master_instance_t *p_i2c;

    // Get I2C instance
    p_i2c = &g_i2c_master1;

    // I2C Open
    _isl87671a_i2c_open(p_i2c);

    // Set LED method to register
    status = _isl87671a_i2c_backlight_method_set(p_i2c, method);
    if( status != FSP_SUCCESS )
    {
        printf("[ISL97671A] _isl87671a_i2c_backlight_method_set is failed(%d).\r\n", status);
        goto BL_END;
    }

    // Set duty
    switch( method )
    {
        case LED_METHOD_1:
            _isl87671a_i2c_backlight_duty_set(p_i2c, duty);
            break;
        case LED_METHOD_2:
            if( p_mtu3 != NULL )
            {
                _isl87671a_mtu3_backlight_duty_set(p_mtu3, duty);
            }
            break;
        default:
            printf("[BL] Method is UNKNOWN (%d)\r\n", method);
            break;
    }

BL_END:
    // I2C Close
    _isl87671a_i2c_close(p_i2c);

    return;
}

/***********************************************************************************************************************
 * static Functions
 **********************************************************************************************************************/
static void _isl87671a_callback( i2c_master_callback_args_t *p_arg )
{
	g_counter++;
	g_i2c_event = p_arg->event;
}

static void _isl87671a_i2c_open(i2c_master_instance_t *p_i2c)
{
    fsp_err_t err;

    err = p_i2c->p_api->open(p_i2c->p_ctrl, p_i2c->p_cfg);
    if(FSP_SUCCESS != err)
    {
        printf("[ISL97671A] I2C open failed.(%d)\r\n", err);
        return;
    }

    err = p_i2c->p_api->callbackSet(p_i2c->p_ctrl, _isl87671a_callback, NULL, NULL);
    if(FSP_SUCCESS != err)
    {
        printf("[ISL97671A] I2C open failed.(%d)\r\n", err);
        return;
    }

    err = p_i2c->p_api->slaveAddressSet( p_i2c->p_ctrl, ISL97671A_I2C_SLV_ADDR, I2C_MASTER_ADDR_MODE_7BIT );
    if( FSP_SUCCESS != err )
    {
        printf("[ISL97671A] I2C slaveAddressSet failed.(%d)\r\n", err);
    }
}

static void _isl87671a_i2c_close(i2c_master_instance_t *p_i2c)
{
    fsp_err_t err;

    // I2C Close
    err = p_i2c->p_api->close(p_i2c->p_ctrl);
    if(FSP_SUCCESS != err)
    {
        printf("[ISL97671A] I2C close failed.(%d)\r\n", err);
    }
}

static uint32_t _isl87671a_i2c_wait_cb( i2c_master_event_t *p_event )
{
    while (!g_counter) {
    	;
    }

    *p_event = g_i2c_event;
    g_counter = 0;

    return TX_SUCCESS;
}

static fsp_err_t _isl87671a_i2c_backlight_method_set(i2c_master_instance_t *p_i2c, led_method_type method)
{
    fsp_err_t err;
    uint32_t status;
    i2c_master_event_t cb_event;
    uint8_t rep_len[2] = {0};

    rep_len[0] = ISL97671A_I2C_DEVCTRL_REG;
    switch(method)
    {
        case LED_METHOD_1:
            rep_len[1] = ISL97671A_I2C_DEVCTRL_DATA_MTD1;
            break;
        case LED_METHOD_2:
            rep_len[1] = ISL97671A_I2C_DEVCTRL_DATA_MTD2;
            break;
        default:
            rep_len[1] = ISL97671A_I2C_DEVCTRL_DATA_BLOFF;
            break;
    }

    err = p_i2c->p_api->write(p_i2c->p_ctrl, rep_len, 2, false);
    if(FSP_SUCCESS == err)
    {
        status = _isl87671a_i2c_wait_cb( &cb_event );
        if(status == TX_SUCCESS)
        {
            switch(cb_event)
            {
            case I2C_MASTER_EVENT_RX_COMPLETE:
            case I2C_MASTER_EVENT_TX_COMPLETE:
                err = FSP_SUCCESS;
                break;
            case I2C_MASTER_EVENT_ABORTED:
            default:
                printf("[W]I2C_MASTER_EVENT_ABORTED or UNKNOWN (%d)\r\n", cb_event);
                err = FSP_ERR_ABORTED;
                break;
            }
        }
        else
        {
            err = FSP_ERR_ABORTED;
        }
    }
    else
    {
        printf("[ISL97671A] I2C write failed.(%d)\r\n", err);
    }

    return err;
}

static fsp_err_t _isl87671a_i2c_backlight_duty_set(i2c_master_instance_t *p_i2c, uint32_t duty)
{
    fsp_err_t err;
    uint8_t rep_len[2] = {0};
    uint8_t duty_val;
    uint32_t status;
    i2c_master_event_t cb_event;

    if( duty > DUTY_MAX )
    {
        printf("[ISL97671A] _isl87671a_i2c_backlight_duty_set : duty is out of range\r\n");
        return FSP_ERR_INVALID_ARGUMENT;
    }

    duty_val = (uint8_t)((255*duty)/100);

    rep_len[0] = ISL97671A_I2C_PWMCTRL_REG;
    rep_len[1] = (uint8_t)duty_val;

    err = p_i2c->p_api->write(p_i2c->p_ctrl, rep_len, 2, false);
    if(FSP_SUCCESS == err)
    {
        status = _isl87671a_i2c_wait_cb( &cb_event );
        if(status == TX_SUCCESS)
        {
            switch(cb_event)
            {
            case I2C_MASTER_EVENT_RX_COMPLETE:
                break;
            case I2C_MASTER_EVENT_TX_COMPLETE:
                err = FSP_SUCCESS;
                break;
            case I2C_MASTER_EVENT_ABORTED:
                break;
            default:
                printf("[W]I2C_MASTER_EVENT_ABORTED or UNKNOWN (%d)\r\n", cb_event);
                err = FSP_ERR_ABORTED;
                break;
            }
        }
        else
        {
            err = FSP_ERR_ABORTED;
        }
    }
    else
    {
        printf("[ISL97671A] I2C write failed.(%d)\r\n", err);
    }

    return err;
}

static void _isl87671a_mtu3_backlight_duty_set(timer_instance_t *p_mtu3, uint32_t duty)
{
    fsp_err_t err = FSP_SUCCESS;
    timer_info_t info;

    if (DUTY_MIN < duty)
    {
        // MTU3 Open
        err = p_mtu3->p_api->open(p_mtu3->p_ctrl, p_mtu3->p_cfg);
        if(FSP_SUCCESS == err)
        {
            R_MTU0->TCR_b.CCLR = 6;     // PWM Clear TCNT on TGRD compare match
            R_MTU0->TMDR1_b.MD = 2;     // PWM mode1 value:2
            R_MTU0->TIORL_b.IOC = 1;    // Compare match is low in the beginning
            R_MTU0->TIORL_b.IOD = 2;    // High in compare match

            err = p_mtu3->p_api->start(p_mtu3->p_ctrl);
            if(FSP_SUCCESS != err)
            {
                printf("[ISL97671A] GTM start failed.(%d)\r\n", err);
            }
        }
        else if(FSP_ERR_ALREADY_OPEN == err)
        {
            // Duty set
            err = p_mtu3->p_api->infoGet(p_mtu3->p_ctrl, &info);
            if(FSP_SUCCESS != err)
            {
                printf("[ISL97671A] GTM infoGet failed.(%d)\r\n", err);
            }
            uint32_t current_period_counts = info.period_counts;

            uint32_t duty_cycle_counts = (current_period_counts * duty) / 100;
            err = p_mtu3->p_api->dutyCycleSet(p_mtu3->p_ctrl, duty_cycle_counts, 0);
            if(FSP_SUCCESS != err)
            {
                printf("[ISL97671A] GTM dutyCycleSet failed.(%d)\r\n", err);
            }
        }
        else
        {
            printf("[ISL97671A] GTM open failed.(%d)\r\n", err);
        }
    }
    else
    {
        // MTU3 Close
        err = p_mtu3->p_api->stop(p_mtu3->p_ctrl);
        if(FSP_SUCCESS != err)
        {
            printf("[ISL97671A] GTM stop failed.(%d)\r\n", err);
        }

        err = p_mtu3->p_api->close(p_mtu3->p_ctrl);
        if(FSP_SUCCESS != err)
        {
            printf("[ISL97671A] GTM close failed.(%d)\r\n", err);
        }
    }
}
