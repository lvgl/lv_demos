#include "lvgl/lvgl.h"
#if LV_USE_IMGBTN


void lv_ex_imgbtn_1(void)
{
    LV_IMG_DECLARE(imgbtn_green);
    LV_IMG_DECLARE(imgbtn_blue);

    /*Darken the button when pressed*/
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_image_recolor_opa(&style, LV_STYLE_STATE_PRESSED, LV_OPA_30);
    lv_style_set_image_recolor(&style, LV_STYLE_STATE_PRESSED, LV_COLOR_BLACK);

    /*Create an Image button*/
    lv_obj_t * imgbtn1 = lv_imgbtn_create(lv_scr_act(), NULL);
    lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_REL, &imgbtn_green);
    lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_PR, &imgbtn_green);
    lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_TGL_REL, &imgbtn_blue);
    lv_imgbtn_set_src(imgbtn1, LV_BTN_STATE_TGL_PR, &imgbtn_blue);
    lv_imgbtn_set_toggle(imgbtn1, true);
    lv_obj_add_style(imgbtn1, LV_IMGBTN_PART_MAIN, &style);
    lv_obj_align(imgbtn1, NULL, LV_ALIGN_CENTER, 0, -40);

    /*Create a label on the Image button*/
    lv_obj_t * label = lv_label_create(imgbtn1, NULL);
    lv_label_set_text(label, "Button");
}

#endif
