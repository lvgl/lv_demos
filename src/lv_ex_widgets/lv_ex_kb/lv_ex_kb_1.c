#include "lvgl/lvgl.h"
#if LV_USE_KEYBOARD

void lv_ex_kb_1(void)
{
    /*Create a keyboard and apply the styles*/
    lv_obj_t *kb = lv_keyboard_create(lv_scr_act(), NULL);
    lv_keyboard_set_cursor_manage(kb, true);

    /*Create a text area. The keyboard will write here*/
    lv_obj_t *ta = lv_textarea_create(lv_scr_act(), NULL);
    lv_obj_align(ta, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);
    lv_textarea_set_text(ta, "");

    /*Assign the text area to the keyboard*/
    lv_keyboard_set_ta(kb, ta);
}
#endif
