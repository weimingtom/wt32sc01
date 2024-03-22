idf_component_register(SRC_DIRS "."
					SRC_DIRS "lvgl/src/lv_core"
					SRC_DIRS "lvgl/src/lv_draw"
					SRC_DIRS "lvgl/src/lv_font"
					SRC_DIRS "lvgl/src/lv_gpu"
					SRC_DIRS "lvgl/src/lv_hal"
					SRC_DIRS "lvgl/src/lv_misc"
					SRC_DIRS "lvgl/src/lv_themes"
					SRC_DIRS "lvgl/src/lv_widgets"
					SRC_DIRS "lvgl_esp32_drivers"
					SRC_DIRS "lvgl_esp32_drivers/lvgl_tft"
					SRC_DIRS "lvgl_esp32_drivers/lvgl_touch"
					INCLUDE_DIRS "lvgl"
					INCLUDE_DIRS "lvgl_esp32_drivers"
                    INCLUDE_DIRS ".")


# SRCS "blink.c"
# link to libmain.a
# output to build\esp-idf\main\CMakeFiles\__idf_main.dir\lvgl\src\lv_core

