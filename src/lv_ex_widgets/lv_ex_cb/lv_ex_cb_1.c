#include "lvgl/lvgl.h"
#include <stdio.h>
#if LV_USE_CB

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        printf("State: %s\n", lv_cb_is_checked(obj) ? "Checked" : "Unchecked");
    }
}

void lv_ex_cb_1(void)
{
    lv_obj_t * cb = lv_cb_create(lv_scr_act(), NULL);
    lv_cb_set_text(cb, "I agree to terms and conditions.");
    lv_obj_align(cb, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_event_cb(cb, event_handler);
}

#endif
