/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include "lv_port_indev.h"
#include "LVGL_thread.h"
#include "touch_GT911.h"
#include "arducam.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void touchpad_init(void);
static void touchpad_read(lv_indev_t * indev, lv_indev_data_t * data);
static bool touchpad_is_pressed(void);
static void touchpad_get_xy(int32_t * x, int32_t * y, touch_event_t * touch);

/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t * indev_touchpad;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    /**
     * Here you will find example implementation of input devices supported by LittelvGL:
     *  - Touchpad
     *  - Mouse (with cursor support)
     *  - Keypad (supports GUI usage only with key)
     *  - Encoder (supports GUI usage only with: left, right, push)
     *  - Button (external buttons to press points on the screen)
     *
     *  The `..._read()` function are only examples.
     *  You should shape them according to your hardware
     */


    /*------------------
     * Touchpad
     * -----------------*/

    /*Initialize your touchpad if you have*/
    touchpad_init();

    /*Register a touchpad input device*/
    indev_touchpad = lv_indev_create();
    lv_indev_set_type(indev_touchpad, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_touchpad, touchpad_read);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Touchpad
 * -----------------*/

/*Initialize your touchpad*/
static void touchpad_init(void)
{
    fsp_err_t err;

    /* Need to initialise the Touch Controller before the LCD, as only a Single Reset line shared between them */
    err = R_INTC_IRQ_ExternalIrqOpen(&g_external_irq1_ctrl, &g_external_irq1_cfg);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0); //TODO: Better error handling
    }

    err = R_RIIC_MASTER_Open(&g_i2c_master1_ctrl, &g_i2c_master1_cfg);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0); //TODO: Better error handling
    }

    err = init_ts(&g_i2c_master1_ctrl);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0); //TODO: Better error handling
    }
    err = enable_ts(&g_i2c_master1_ctrl, &g_external_irq1_ctrl);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0); //TODO: Better error handling
    }
}

/*Will be called by the library to read the touchpad*/
static void touchpad_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
    FSP_PARAMETER_NOT_USED(indev_drv);
    static int32_t last_x = 0;
    static int32_t last_y = 0;

    static touch_event_t touch_event = TOUCH_EVENT_NONE;

    /*Save the pressed coordinates and the state*/
    if(touchpad_is_pressed()) {

        touchpad_get_xy(&last_x, &last_y, &touch_event);
        if ((TOUCH_EVENT_DOWN == touch_event) || (TOUCH_EVENT_MOVE == touch_event))
        {
            data->state = LV_INDEV_STATE_PRESSED;
        } else {
            data->state = LV_INDEV_STATE_RELEASED;
        }
    }
    else {
        data->state = LV_INDEV_STATE_RELEASED;
    }

    /*Set the last pressed coordinates*/
    data->point.x = last_x;
    data->point.y = last_y;
}

/*Return true is the touchpad is pressed*/
static bool touchpad_is_pressed(void)
{
    BaseType_t status;
    bool touch_pressed = false;

    status = xSemaphoreTake( g_irq_binary_semaphore, 0 );
    if(pdTRUE == status)
    {
        touch_pressed = true;
    }

    return touch_pressed;
}

/*Get the x and y coordinates if the touchpad is pressed*/
static void touchpad_get_xy(int32_t * x, int32_t * y, touch_event_t * touch_event)
{
    fsp_err_t err;
    uint32_t number_of_coordinates;
    uint8_t read_data[7];

    TouchCordinate_t coordinates[6];
    memset(coordinates, 0, sizeof(TouchCordinate_t));

    err = rdSensorReg16_8(&g_i2c_master1_ctrl, GT911_REG_READ_COORD_ADDR, read_data);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0); //TODO: Better error handling
    }

    if (BUFFER_READY == (BUFFER_READY & read_data[0]))
    {
        number_of_coordinates = (read_data[0] & NUM_TOUCH_POINTS_MASK);
        if (number_of_coordinates != 0)
        {
            for (uint8_t i = 0; i < number_of_coordinates; i++)
            {
                err = rdSensorReg16_Multi(&g_i2c_master1_ctrl, (uint16_t)(GT911_REG_POINT1_X_ADDR + (i * 8)), read_data, 7 );
                if (FSP_SUCCESS != err)
                {
                    __BKPT(0); //TODO: Better error handling
                }

                coordinates[i].x = (uint16_t)((read_data[2] << 8) | read_data[1]);
                coordinates[i].y = (uint16_t)((read_data[4] << 8) | read_data[3]);

            }
            *touch_event = TOUCH_EVENT_DOWN;
        }
        else
        {
            *touch_event = TOUCH_EVENT_UP;
        }

        /* Set status to 0, to wait for next touch event */
        err = wrSensorReg16_8(&g_i2c_master1_ctrl, GT911_REG_READ_COORD_ADDR, 0);
        if (FSP_SUCCESS != err)
        {
            __BKPT(0); //TODO: Better error handling
        }
    }

    if(*touch_event == TOUCH_EVENT_MOVE || *touch_event == TOUCH_EVENT_DOWN)
    {
        /* For EK-RZ/A3M */
        (*x) = coordinates[0].x;
        (*y) = coordinates[0].y;
    }
}
#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
