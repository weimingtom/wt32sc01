#include "lvgl_esp32_drivers/myconfig.h"

/***
* author:xnby
* platform: esp
* version: 1.0.0
* UIResolution: 240*320
*/

#include "qm_ui_entry.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include "lv_8ms_blockly.h"
#include "wtctrl.h"

typedef struct
{
    char *name;
    lv_obj_t **id;
} lv_widget_t;

typedef struct
{
    char *name;
    lv_obj_t **id;
    lv_widget_t *wids;
    int len;
} lv_screen_t;

void lvgl_blockly_loop();
void lvgl_blockly_init();
    /*
    * includes
    */
    /*
    * declear main_screen
    */
lv_obj_t * main_screen;
lv_obj_t * label_109c;

lv_widget_t g_main_screen_ids[]=
{
    {"label_109c",&label_109c},
};

lv_screen_t g_screens[] =
{
    {"main_screen", &main_screen, g_main_screen_ids, (sizeof(g_main_screen_ids) / sizeof(g_main_screen_ids[0]))},
};

LV_FONT_DECLARE(ali_font_16);


    void show_screen_main_screen();
    /*
    * keyboard
    */
    lv_obj_t * g_kb = NULL;

    static void g_kb_event_cb(lv_obj_t * event_kb, lv_event_t event)
    {
    /* Just call the regular event handler */
    if(event == LV_EVENT_APPLY) {
    lv_obj_set_hidden(event_kb, true);
    } else if(event == LV_EVENT_CANCEL) {
    lv_obj_set_hidden(event_kb, true);
    } else {
    lv_keyboard_def_event_cb(event_kb, event);
    }
    }
    static void g_create_kb_ifneeded() {
    if(g_kb == NULL) {
    g_kb = lv_keyboard_create(main_screen, NULL);
    lv_obj_set_pos(g_kb, 5, 90);
    lv_obj_set_event_cb(g_kb, g_kb_event_cb); /* Setting a custom event handler stops the keyboard from closing automatically */
    lv_obj_set_size(g_kb,  LV_HOR_RES - 10, 140);
    lv_keyboard_set_cursor_manage(g_kb, true); /* Automatically show/hide cursors on text areas */
    lv_obj_set_hidden(g_kb, true);
    }
    }
static void g_show_kb() 
{
    g_create_kb_ifneeded();
    lv_obj_set_parent(g_kb, lv_scr_act());
    lv_obj_set_hidden(g_kb, false);
    lv_obj_align(g_kb,NULL,LV_ALIGN_IN_BOTTOM_MID,0,0);
}

    /**
    *开机启动屏相关
    */
    static lv_style_t style_star, style_black, style_url;
    //LV_IMG_DECLARE(img_8ms_png);
    //LV_IMG_DECLARE(img_star);
    lv_obj_t * logo;
    lv_obj_t * logo_star;
    lv_obj_t * url_label;
    lv_obj_t * url_mask;
    lv_obj_t * mask_layer;
    int timer_cnt = 0;
    /****
    * 临时变量用于数据传输
    */
    char _tmpbuf[32];

  

    
    /*
    * declear codes
    */



#ifndef LV_8MS_PRESET_UART_QUEUE
void lv_8ms_uart_queue_ana(uint8_t* data,int size){   
    printf("ana:%s\n",wtctrl_json_parse((char *)data));
}
#endif
#ifndef CUSTOM_MQTT_PARSE
void lv_8ms_mqtt_received(const char* data)
{
    printf("custom:%s\n",data);
}
#endif
/*
 * callback functions begins
 */
/*
 * callback functions ends
 */
    /*
    * init codes
    */
void init_function()
{
#ifdef BLOCKLY_init
    blockly_init();
#endif
    }

    void lv_8ms_label_109c_create()
{
	label_109c = lv_label_create(main_screen, NULL);
	lv_label_set_long_mode(label_109c,LV_LABEL_LONG_BREAK);
	lv_obj_set_size(label_109c, 100, 40);
//set label style
	lv_obj_set_style_local_text_font(label_109c,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,&ali_font_16);

	lv_label_set_text(label_109c, "Label1234");
	lv_label_set_align(label_109c, LV_LABEL_ALIGN_CENTER);
#ifdef BLOCKLY_label_109c_EVENT_HANDLER
	lv_obj_set_event_cb(label_109c, label_109c_event_handler);
#endif
	if(label_109c->coords.x2-label_109c->coords.x1<100)
	{
		int x_offset=(100-(label_109c->coords.x2-label_109c->coords.x1))/2;
		lv_obj_set_style_local_pad_left(label_109c,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
		lv_obj_set_style_local_pad_right(label_109c,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,x_offset);
	}
	if(label_109c->coords.y2-label_109c->coords.y1<40)
	{
		int y_offset=(40-(label_109c->coords.y2-label_109c->coords.y1))/2;
		lv_obj_set_style_local_pad_bottom(label_109c,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
		lv_obj_set_style_local_pad_top(label_109c,LV_LABEL_PART_MAIN,LV_STATE_DEFAULT,y_offset);
	}
		lv_obj_set_pos(label_109c, 70, 140);

}

void show_screen_main_screen()
{
        lv_scr_load(main_screen);
//生成动态页面的style
    
}

int screen_loop_enter = 0;
int _delay = 0;
void lv_qm_ui_loop(void)
{
    #ifdef BLOCKLY_loop
    blockly_loop();
    #endif
}

void lv_qm_ui_entry(void)
{
    
    /*
    * create screens
    */
    main_screen = lv_obj_create(NULL, NULL);
//CREATE STATIC OBJ
    lv_8ms_label_109c_create();
  
    lv_scr_load(main_screen);
    init_function();
}
/**
* @brief blockly initialization
*/

void lvgl_blockly_init()
{
#ifdef WT_WIFI
    blockly_wifi_init();
#endif // DEBUG
#ifdef WT_BLUFI
    blockly_blufi_init();
#endif // DEBUG
#ifdef WT_HTTP_REQUEST
    blockly_http_init();
#endif // WT_HTTP_REQUEST
}

/**
* @brief blockly loop
*/

void lvgl_blockly_loop()
{
#ifdef WT_BLUFI
    blockly_blufi_loop();
#endif // DEBUG
#ifdef WT_WIFI
    blockly_wifi_loop();
#endif // DEBUG
#ifdef WT_HTTP_REQUEST
    blockly_http_loop();
#endif // WT_HTTP_REQUEST
}

void lvgl_device_init(void)
{
#ifdef ESP32_GPIO
    lv_8ms_gpio_setup();
#endif
#ifdef ESP32_TIMER
    lv_8ms_timer_setup();
#endif
#ifdef ESP32_UART
    lv_8ms_uart_setup();
#endif
}

void lvgl_device_loop(void)
{
#ifdef ESP32_GPIO
    lv_8ms_gpio_loop();
#endif
#ifdef ESP32_TIMER
    lv_8ms_timer_loop();
#endif
#ifdef ESP32_UART
    lv_8ms_uart_loop();
#endif
}
lv_obj_t *lv_8ms_get_screen(char *name)
{
    int i = 0;
    for (i = 0; i < (sizeof(g_screens) / sizeof(g_screens[0])); i++)
    {
        if (!strcmp(name, g_screens[i].name))
        {
            return *(g_screens[i].id);
        }
    }
    return NULL;
}

lv_obj_t *lv_8ms_get_widget(char *w_name)
{
    int i = 0, j = 0;

    for (i = 0; i < (sizeof(g_screens) / sizeof(g_screens[0])); i++)
    {
        for (j = 0; j <  g_screens[i].len; j++)
        {
            if (!strcmp(w_name, g_screens[i].wids[j].name))
            {
                return *(g_screens[i].wids[j].id);
            }
        }
    }

    return NULL;
}

const char *lv_8ms_get_obj_name(lv_obj_t *obj)
{
    if (!obj) {
        return NULL;
    }

    int i = 0, j = 0;
    for (i = 0; i < (sizeof(g_screens) / sizeof(g_screens[0])); i++)
    {
        if (*(g_screens[i].id) == obj) {
            return g_screens[i].name;
        }

        for (j = 0; j <  g_screens[i].len; j++)
        {
            if (*(g_screens[i].wids[j].id) == obj)
            {
                return g_screens[i].wids[j].name;
            }
        }
    }

    return NULL;
}