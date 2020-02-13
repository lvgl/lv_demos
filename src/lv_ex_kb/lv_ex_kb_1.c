#include "lvgl/lvgl.h"
#if LV_USE_KB

void lv_ex_kb_1(void)
{
    /*Create a keyboard and apply the styles*/
    lv_obj_t *kb = lv_kb_create(lv_scr_act(), NULL);
    lv_kb_set_cursor_manage(kb, true);

    /*Create a text area. The keyboard will write here*/
    lv_obj_t *ta = lv_ta_create(lv_scr_act(), NULL);
    lv_obj_align(ta, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);
    lv_ta_set_text(ta, "");

    /*Assign the text area to the keyboard*/
    lv_kb_set_ta(kb, ta);
}
#endif
