#include "lvgl_esp32_drivers/myconfig.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "nvs_flash.h"

/* Littlevgl specific */
#include "lvgl/lvgl.h"
#include "lvgl_helpers.h"
#include "qm_ui_entry.h"
#include "wtctrl.h"
#include "lv_demo_widgets.h"

/*********************
 *      DEFINES
 *********************/
#define TAG "main"
#define LV_TICK_PERIOD_MS 10

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_tick_task(void *arg);
void guiTask(void *pvParameter);

/**********************
 *   APPLICATION MAIN
 **********************/
static void user_nvs_init()
{
    esp_err_t ret;
    // Initialize NVS
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

void app_main()
{
    user_nvs_init();
    xTaskCreatePinnedToCore(guiTask, "gui", 4096 * 2, NULL, 0, NULL, 1);

#ifdef LV_8MS_UART_CTRL
    lv_8ms_uart_ctrl_init(UART_NUM_0);
#endif
}

static void lv_tick_task(void *arg)
{
    (void)arg;
    lv_tick_inc(LV_TICK_PERIOD_MS);
}

extern void lv_8ms_init(void);

//Creates a semaphore to handle concurrent call to lvgl stuff
//If you wish to call *any* lvgl function from other threads/tasks
//you should lock on the very same semaphore!
SemaphoreHandle_t xGuiSemaphore;

//-----------------------
//test blink
#define BLINK_GPIO 23 //LCD_LED==23 //CONFIG_BLINK_GPIO
void test()
{
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1) {
        /* Blink off (output low) */
        printf("Turning off the LED\n");
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        /* Blink on (output high) */
        printf("Turning on the LED\n");
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
//---------------------


void guiTask(void *pvParameter)
{

    (void)pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    lv_init();

    /* Initialize SPI or I2C bus used by the drivers */
    lvgl_driver_init();

    //test();
	static lv_color_t buf1[DISP_BUF_SIZE];
#ifndef CONFIG_LVGL_TFT_DISPLAY_MONOCHROME
    static lv_color_t buf2[DISP_BUF_SIZE];
#endif
    static lv_disp_buf_t disp_buf;
	//test();
	
    uint32_t size_in_px = DISP_BUF_SIZE;

#if defined CONFIG_LVGL_TFT_DISPLAY_CONTROLLER_IL3820
    /* Actual size in pixel, not bytes and use single buffer */
    size_in_px *= 8;
    lv_disp_buf_init(&disp_buf, buf1, NULL, size_in_px);
#elif defined CONFIG_LVGL_TFT_DISPLAY_MONOCHROME
    lv_disp_buf_init(&disp_buf, buf1, NULL, size_in_px);
#else
    lv_disp_buf_init(&disp_buf, buf1, buf2, size_in_px);
#endif
	//test();

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_driver_flush;

#ifdef CONFIG_LVGL_TFT_DISPLAY_MONOCHROME
    disp_drv.rounder_cb = disp_driver_rounder;
    disp_drv.set_px_cb = disp_driver_set_px;
#endif

    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

#if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.read_cb = touch_driver_read;
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register(&indev_drv);
#endif

    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

    lv_8ms_init();
//test();

    //lv_qm_ui_entry();
lv_demo_widgets();
    while (1)
    {
        vTaskDelay(10 / portTICK_PERIOD_MS);
        //Try to lock the semaphore, if success, call lvgl stuff
        //printf("Turning on the LED\n");
        if (xSemaphoreTake(xGuiSemaphore, (TickType_t)10) == pdTRUE)
        {
            lv_qm_ui_loop();
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
        }
    }

    //A task should NEVER return
    vTaskDelete(NULL);
}
