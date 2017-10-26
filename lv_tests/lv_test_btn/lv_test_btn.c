/**
 * @file lv_test_btn.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_btn.h"

#if USE_LV_BTN != 0

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
    lv_obj_align_scale(btn2, btn1, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_btn_set_state(btn2, LV_BTN_STATE_ON_RELEASED);

    /* Default toggle button
     * GOAL: A button which van be toggled */
    lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_align_scale(btn3, btn2, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_btn_set_toggle(btn3, true);

    /* Test actions
     * GOAL: Press: increase width, Release: decrease width, Long press: delete */
    lv_obj_t * btn4 = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_align_scale(btn4, btn1, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
    lv_btn_set_action(btn4, LV_BTN_ACTION_PRESS, width_inc);
    lv_btn_set_action(btn4, LV_BTN_ACTION_RELEASE, width_dec);
    lv_btn_set_action(btn4,  LV_BTN_ACTION_LONG_PRESS, lv_obj_del);

    /* Test styles and copy
     * GOAL: Same as 'btn4' but different style in states */
    static lv_style_t style_rel;
    lv_style_copy(&style_rel, lv_style_get(LV_STYLE_PRETTY));
    style_rel.body.color_main = COLOR_ORANGE;
    style_rel.body.color_gradient = COLOR_BLACK;
    style_rel.body.border.color = COLOR_RED;
    style_rel.body.shadow.color = COLOR_MARRON;
    style_rel.body.shadow.width = 10 << LV_ANTIALIAS;

    static lv_style_t style_pr;
    lv_style_copy(&style_pr,  lv_style_get(LV_STYLE_PRETTY));
    style_pr.body.empty = 1;
    style_pr.body.border.color = COLOR_RED;
    style_pr.body.border.width = 4 << LV_ANTIALIAS;

    /*Skip 'tpr' because it will be let the same*/

    static lv_style_t style_tpr;
    lv_style_copy(&style_tpr, lv_style_get(LV_STYLE_PRETTY));
    style_tpr.body.empty = 1;
    style_tpr.body.border.color = COLOR_RED;
    style_tpr.body.border.width = 4 << LV_ANTIALIAS;

    static lv_style_t style_ina;
    lv_style_copy(&style_ina, lv_style_get(LV_STYLE_PRETTY));
    style_ina.body.color_main = COLOR_SILVER;
    style_ina.body.color_gradient = COLOR_GRAY;
    style_ina.body.border.color = COLOR_RED;

    lv_obj_t * btn5 = lv_btn_create(lv_scr_act(), btn4);
    lv_obj_align_scale(btn5, btn4, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_btn_set_style(btn5, LV_BTN_STATE_OFF_RELEASED, &style_rel);
    lv_btn_set_style(btn5, LV_BTN_STATE_OFF_PRESSED, &style_pr);
    lv_btn_set_style(btn5, LV_BTN_STATE_ON_PRESSED, &style_tpr);
    lv_btn_set_style(btn5, LV_BTN_STATE_INACTIVE, &style_ina);
    lv_btn_set_toggle(btn5, true);

    /* Test style copy and inactive state
     * GOAL: Non-default inactive style and no actions called*/
    lv_obj_t * btn6 = lv_btn_create(lv_scr_act(), btn5);
    lv_obj_align_scale(btn6, btn5, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_btn_set_state(btn6, LV_BTN_STATE_INACTIVE);
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

#endif /*USE_LV_BTN*/
