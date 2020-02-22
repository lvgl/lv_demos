#include "lvgl/lvgl.h"
#include <stdio.h>
#if LV_USE_BTN

/**
 * Style a gum-like button
 */
void lv_ex_btn_2(void)
{
    static lv_style_t style_gum;
    lv_style_init(&style_gum);
    lv_style_set_width(&style_gum, LV_STATE_PRESSED, 10);
    lv_style_set_height(&style_gum, LV_STATE_PRESSED, -10);
    lv_style_set_value_letter_space(&style_gum, LV_STATE_PRESSED, 5);
    lv_style_set_trans_path(&style_gum, LV_STATE_DEFAULT, lv_anim_path_overshoot);
    lv_style_set_trans_path(&style_gum, LV_STATE_PRESSED, lv_anim_path_ease_in_out);
    lv_style_set_trans_time(&style_gum, LV_STATE_DEFAULT, 250);
    lv_style_set_trans_delay(&style_gum, LV_STATE_DEFAULT, 100);
    lv_style_set_trans_prop_1(&style_gum, LV_STATE_DEFAULT, LV_STYLE_WIDTH);
    lv_style_set_trans_prop_2(&style_gum, LV_STATE_DEFAULT, LV_STYLE_HEIGHT);
    lv_style_set_trans_prop_3(&style_gum, LV_STATE_DEFAULT, LV_STYLE_VALUE_LETTER_SPACE);

    lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style(btn1, LV_BTN_PART_MAIN, &style_gum);

    /*Instead of creating a label add a values string*/
    lv_obj_set_style_value_str(btn1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, "Button");
}
#endif
