/**
 * @file lv_test_btn.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_btn.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void width_inc(lv_obj_t * btn);
static void width_dec(lv_obj_t * btn);

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
 * Create a default object and test the basic functions
 */
void lv_test_btn_1(void)
{
    /* Default object
     * GOAL: A button which looks well */
    lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);

    /* Default button manually set to toggles state
     * GOAL: A button in toggle released state */
    lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_align_us(btn2, btn1, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_btn_set_state(btn2, LV_BTN_STATE_TREL);

    /* Default toggle button
     * GOAL: A button which van be toggled */
    lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_align_us(btn3, btn2, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_btn_set_tgl(btn3, true);


    /* Test actions
     * GOAL: Press: increase width, Release: decrease width, Long press: delete */
    lv_obj_t * btn4 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_align_us(btn4, btn1, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
    lv_btn_set_pr_action(btn4, width_inc);
    lv_btn_set_rel_action(btn4, width_dec);
    lv_btn_set_lpr_action(btn4, lv_obj_del);

    /* Test styles and copy
     * GOAL: Same as 'btn4' but different style in states */
    static lv_style_t style_rel;
    lv_style_get(LV_STYLE_PRETTY, &style_rel);
    style_rel.mcolor = COLOR_ORANGE;
    style_rel.gcolor = COLOR_BLACK;
    style_rel.bcolor = COLOR_RED;
    style_rel.scolor = COLOR_MARRON;
    style_rel.swidth = 10 << LV_ANTIALIAS;

    static lv_style_t style_pr;
    lv_style_get(LV_STYLE_PRETTY, &style_pr);
    style_pr.empty = 1;
    style_pr.bcolor = COLOR_RED;
    style_pr.bwidth = 4 << LV_ANTIALIAS;

    /*Skip 'tpr' because it will be let the same*/

    static lv_style_t style_tpr;
    lv_style_get(LV_STYLE_PRETTY, &style_tpr);
    style_tpr.empty = 1;
    style_tpr.bcolor = COLOR_RED;
    style_tpr.bwidth = 4 << LV_ANTIALIAS;

    static lv_style_t style_ina;
    lv_style_get(LV_STYLE_PRETTY, &style_ina);
    style_ina.mcolor = COLOR_SILVER;
    style_ina.gcolor = COLOR_GRAY;
    style_ina.bcolor = COLOR_RED;

    lv_obj_t * btn5 = lv_btn_create(lv_scr_act(), btn4);
    lv_obj_align_us(btn5, btn4, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_btn_set_styles(btn5, &style_rel, &style_pr, NULL, &style_tpr, &style_ina);
    lv_btn_set_tgl(btn5, true);

    /* Test style copy and inactive state
     * GOAL: Non-default inactive style and no actions called*/
    lv_obj_t * btn6 = lv_btn_create(lv_scr_act(), btn5);
    lv_obj_align_us(btn6, btn5, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_btn_set_state(btn6, LV_BTN_STATE_INA);
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Increase the width of the button.
 * @param btn pointer to a button object
 */
static void width_inc(lv_obj_t * btn)
{
    lv_obj_set_width(btn, lv_obj_get_width(btn) + 10);
}

/**
 * Decrease the width of the button.
 * @param btn pointer to a button object
 */
static void width_dec(lv_obj_t * btn)
{
    lv_obj_set_width(btn, lv_obj_get_width(btn) - 10);
}
