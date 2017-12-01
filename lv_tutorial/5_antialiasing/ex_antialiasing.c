/**
 * @file ex_antialiasing.h
 *
 */

/*
 * The graphics library support 2 types of anti aliasing:
 * 1. Full screen anti aliasing:
 *   - Everything is rendered in double size and the filtered (smoothed) to the real size
 *   - It results smooth image but need more computation resources and memory (VDB)
 *   - Only available in buffered mode (lv_conf.h   LV_VDB_SIZE != 0)
 *   - You can enable it in lv_conf.h: LV_ANTIALIAS    1
 *   - You have to use double sizes in your GUI because the filtering will downscale everithing
 *      - E.g. lv_obj_set_width(obj, 100) will result an 50 px wide object
 *   - Use the LV_AA macro to compensate this effect
 *      - E.g. lv_obj_set_width(obj, 100 << LV_AA) will result an 100 px wide object
 *                                                 independently from anti aliasing
 *   - The style parameters are also reduced (border width, radius, letter space etc.)
 *      - E.g. style.body.bolder.width = 5 << LV_AA
 *   - The font are reduced as well. To get a 20 px font you have to use 40 px ones
 *
 *
 * 2. Font anti aliasing
 *   - It smoothes only the fonts.
 *   - Works in buffered and unbuffered mode as well, but makes much better result with buffering
 *   - Needs only a little extra computation resource
 *   - Only the fonts has to be doubled
 *   - You can enable it in lv_conf.h: LV_FONT_ANTIALIAS    1
 *   - Don not enable LV_ANTIALIAS and LV_FONT_ANTIALIAS at the same time because
 *     it will result quarter sized letters
 *
 *
 * Try the example by hanging the anti aliasing modes in lv_conf.h
 */

/*********************
 *      INCLUDES
 *********************/
#include "ex_antialiasing.h"
#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create object to see how they change from the anti aliasing
 * Modify LV_ANTIALIAS and LV_FONT_ANTIALIAS to see what is changing
 */
void ex_antialiasing(void)
{
    lv_obj_t *label;


    static lv_style_t style1;
    lv_style_copy(&style1, &lv_style_btn_rel);
    style1.body.radius = 20;
    style1.body.border.width = 8;


    lv_obj_t *btn1;
    btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_pos(btn1, 10, 10);
    lv_obj_set_size(btn1, 160, 80);
    lv_btn_set_style(btn1, LV_BTN_STYLE_REL, &style1);

    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Reduce");

    static lv_style_t style2;
    lv_style_copy(&style2, &lv_style_btn_rel);
    style2.body.radius = 20 << LV_AA;
    style2.body.border.width = 8 << LV_AA;

    lv_obj_t *btn2;
    btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_align(btn2, btn1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);
    lv_obj_set_size(btn2, 160 << LV_AA, 80 << LV_AA);
    lv_btn_set_style(btn2, LV_BTN_STYLE_REL, &style2);

    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "Upscale");


}

/**********************
 *   STATIC FUNCTIONS
 **********************/
