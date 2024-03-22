#include <stdbool.h>
#include "lvgl_esp32_drivers/myconfig.h"

extern void st7796s_enable_backlight(bool backlight);

void lv_8ms_init(void)
{
	st7796s_enable_backlight(true);
}

