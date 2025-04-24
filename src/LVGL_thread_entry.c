#include <lvgl_thread.h>
#include "lvgl.h"
#include "port/lv_port_disp.h"
#include "port/lv_port_indev.h"
#include "lvgl/demos/lv_demos.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include <stdio.h>

#include "ui/ui.h"

static uint32_t idle_time_sum;
static uint32_t non_idle_time_sum;
static uint32_t task_switch_timestamp;
static bool idle_task_running;

void vApplicationMallocFailedHook( void );
uint32_t lv_os_get_idle_percent(void);

extern fsp_vector_t g_vector_table[];


// empty definitions to prevent "undefined reference to ..." linker errors
void __dso_handle() {}
void _fini(void) {}
//


void lv_freertos_task_switch_in(const char * name)
{
    if(strcmp(name, "IDLE")) idle_task_running = false;
    else idle_task_running = true;

    task_switch_timestamp = lv_tick_get();
}

void lv_freertos_task_switch_out(void)
{
    uint32_t elaps = lv_tick_elaps(task_switch_timestamp);
    if(idle_task_running) idle_time_sum += elaps;
    else non_idle_time_sum += elaps;
}

uint32_t lv_os_get_idle_percent(void)
{
    if(non_idle_time_sum + idle_time_sum == 0) {
        LV_LOG_WARN("Not enough time elapsed to provide idle percentage");
        return 0;
    }

    uint32_t pct = (idle_time_sum * 100) / (idle_time_sum + non_idle_time_sum);

    non_idle_time_sum = 0;
    idle_time_sum = 0;

    return pct;
}

void timer_tick_callback(timer_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    lv_tick_inc(1);
}

void vApplicationMallocFailedHook( void )
{
    __BKPT(0);
}

/* New Thread entry function */
/* pvParameters contains TaskHandle_t */
void LVGL_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);
    fsp_err_t err;

    lv_init();

    lv_port_disp_init();

    lv_port_indev_init();

    ui_init();

#if (1 == LV_USE_DEMO_BENCHMARK)
    // lv_demo_benchmark();
#endif

#if (1 == LV_USE_DEMO_MUSIC)
    lv_demo_music();
#endif

#if (1 == LV_USE_DEMO_KEYPAD_AND_ENCODER)
    lv_demo_keypad_encoder();

#endif

#if (1 == LV_USE_DEMO_STRESS)
    lv_demo_stress();
#endif

#if (1 == LV_USE_DEMO_WIDGETS && 0 == LV_USE_DEMO_BENCHMARK)
    lv_demo_widgets();
#endif

    err = R_GTM_Open(&g_timer1_ctrl, &g_timer1_cfg);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0);
    }

    err = R_GTM_Start(&g_timer1_ctrl);
    if (FSP_SUCCESS != err)
    {
        __BKPT(0);
    }

    /* TODO: add your own code here */
    while (1)
    {
        uint32_t time_till_next = lv_timer_handler();
        ui_tick();
        vTaskDelay (pdMS_TO_TICKS(time_till_next));
    }
}
