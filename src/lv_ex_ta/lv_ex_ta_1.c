#include "lvgl/lvgl.h"
#include <stdio.h>

lv_obj_t * ta1;

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        printf("Value: %s\n", lv_ta_get_text(obj));
    }
    else if(event == LV_EVENT_LONG_PRESSED_REPEAT) {
        /*For simple test: Long press the Text are to add the text below*/
        const char  * txt = "\n\nYou can scroll it if the text is long enough.\n";
        static uint16_t i = 0;
        if(txt[i] != '\0') {
            lv_ta_add_char(ta1, txt[i]);
            i++;
        }
    }
}


void lv_ex_ta_1(void)
{
    ta1 = lv_ta_create(lv_scr_act(), NULL);
    lv_obj_set_size(ta1, 200, 100);
    lv_obj_align(ta1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_ta_set_cursor_type(ta1, LV_CURSOR_BLOCK);
    lv_ta_set_text(ta1, "A text in a Text Area");    /*Set an initial text*/
    lv_obj_set_event_cb(ta1, event_handler);
}
