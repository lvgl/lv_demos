#include "lvgl/lvgl.h"
#if LV_USE_LMETER

void lv_ex_lmeter_1(void)
{
    /*Create a line meter */
    lv_obj_t * lmeter;
    lmeter = lv_lmeter_create(lv_scr_act(), NULL);
    lv_lmeter_set_range(lmeter, 0, 100);                   /*Set the range*/
    lv_lmeter_set_value(lmeter, 80);                       /*Set the current value*/
    lv_lmeter_set_scale(lmeter, 240, 31);                  /*Set the angle and number of lines*/
    lv_obj_set_size(lmeter, 150, 150);
    lv_obj_align(lmeter, NULL, LV_ALIGN_CENTER, 0, 0);
}

#endif
