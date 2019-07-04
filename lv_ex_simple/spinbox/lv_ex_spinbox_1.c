#include "lvgl/lvgl.h"
#include <stdio.h>

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        printf("Value: %d\n", lv_spinbox_get_value(obj));
    }
    else if(event == LV_EVENT_CLICKED) {
        /*For simple test: Click the spinbox to increment its value*/
        lv_spinbox_increment(obj);
    }
}

void lv_ex_spinbox_1(void)
{
    lv_obj_t * spinbox;
    spinbox = lv_spinbox_create(lv_scr_act(), NULL);
    lv_spinbox_set_digit_format(spinbox, 5, 3);
    lv_spinbox_step_prev(spinbox);
    lv_obj_set_width(spinbox, 100);
    lv_obj_align(spinbox, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_event_cb(spinbox, event_handler);
}
