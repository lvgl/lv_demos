/**
 * @file lv_test_cb.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_cb.h"

#if USE_LV_CB != 0

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
 * Create a default object and test the basic functions
 */
void lv_test_cb_1(void)
{
    /* Create a default object*/
    lv_obj_t * cb1 = lv_cb_create(lv_scr_act(), NULL);


    /*Create an other check box and set its text*/
    lv_obj_t * cb2 = lv_cb_create(lv_scr_act(), NULL);
#if TXT_UTF8 == 0
    lv_cb_set_text(cb2, "New text");
#else
    lv_cb_set_text(cb2, "UTF8-text: üŰ öŐ íÍ");
#endif
    lv_obj_align_scale(cb2, cb1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);


    /*Create styles for a round bullet*/
    static lv_style_t cb3_styles[LV_BTN_STATE_NUM];
    lv_style_copy(&cb3_styles[LV_BTN_STATE_OFF_RELEASED], lv_style_get(LV_STYLE_PLAIN));
    cb3_styles[LV_BTN_STATE_OFF_RELEASED].body.radius = LV_RADIUS_CIRCLE;
    cb3_styles[LV_BTN_STATE_OFF_RELEASED].body.border.width = 1 << LV_ANTIALIAS;
    cb3_styles[LV_BTN_STATE_OFF_RELEASED].body.border.color = COLOR_GRAY;
    cb3_styles[LV_BTN_STATE_OFF_RELEASED].body.color_main = COLOR_WHITE;
    cb3_styles[LV_BTN_STATE_OFF_RELEASED].body.color_gradient = COLOR_SILVER;

    lv_style_copy(&cb3_styles[LV_BTN_STATE_OFF_PRESSED], &cb3_styles[LV_BTN_STATE_OFF_RELEASED]);
    cb3_styles[LV_BTN_STATE_OFF_PRESSED].body.color_main = COLOR_SILVER;
    cb3_styles[LV_BTN_STATE_OFF_PRESSED].body.color_gradient = COLOR_GRAY;

    lv_style_copy(&cb3_styles[LV_BTN_STATE_ON_RELEASED], &cb3_styles[LV_BTN_STATE_OFF_RELEASED]);
    cb3_styles[LV_BTN_STATE_ON_RELEASED].body.border.width = 4 << LV_ANTIALIAS;
    cb3_styles[LV_BTN_STATE_ON_RELEASED].body.border.color = COLOR_WHITE;
    cb3_styles[LV_BTN_STATE_ON_RELEASED].body.border.opa = OPA_70;
    cb3_styles[LV_BTN_STATE_ON_RELEASED].body.color_main = COLOR_GRAY;
    cb3_styles[LV_BTN_STATE_ON_RELEASED].body.color_gradient = COLOR_BLACK;

    lv_style_copy(&cb3_styles[LV_BTN_STATE_ON_PRESSED], &cb3_styles[LV_BTN_STATE_ON_RELEASED]);
    cb3_styles[LV_BTN_STATE_ON_PRESSED].body.border.color = COLOR_SILVER;
    cb3_styles[LV_BTN_STATE_ON_PRESSED].body.border.opa = OPA_70;
    cb3_styles[LV_BTN_STATE_ON_PRESSED].body.color_main = COLOR_GRAY;
    cb3_styles[LV_BTN_STATE_ON_PRESSED].body.color_gradient = COLOR_BLACK;

    lv_style_copy(&cb3_styles[LV_BTN_STATE_INACTIVE], &cb3_styles[LV_BTN_STATE_ON_RELEASED]);
    cb3_styles[LV_BTN_STATE_INACTIVE].body.border.width = 1 << LV_ANTIALIAS;
    cb3_styles[LV_BTN_STATE_INACTIVE].body.border.color = COLOR_GRAY;
    cb3_styles[LV_BTN_STATE_INACTIVE].body.color_main = COLOR_SILVER;
    cb3_styles[LV_BTN_STATE_INACTIVE].body.color_gradient = COLOR_SILVER;


    /*Copy the previous check box and apply the new styles*/
    lv_obj_t *cb3 = lv_cb_create(lv_scr_act(), cb2);
    lv_obj_t *bullet3 = lv_cb_get_bullet(cb3);
    lv_btn_set_style(bullet3, LV_BTN_STATE_OFF_RELEASED, &cb3_styles[LV_BTN_STATE_OFF_RELEASED]);
    lv_btn_set_style(bullet3, LV_BTN_STATE_OFF_PRESSED, &cb3_styles[LV_BTN_STATE_OFF_PRESSED]);
    lv_btn_set_style(bullet3, LV_BTN_STATE_ON_RELEASED, &cb3_styles[LV_BTN_STATE_ON_RELEASED]);
    lv_btn_set_style(bullet3, LV_BTN_STATE_ON_PRESSED, &cb3_styles[LV_BTN_STATE_ON_PRESSED]);
    lv_btn_set_style(bullet3, LV_BTN_STATE_INACTIVE, &cb3_styles[LV_BTN_STATE_INACTIVE]);
    lv_obj_align_scale(cb3, cb2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    /*Copy the previous check box and set it to INACTIVE*/
    lv_obj_t *cb4 = lv_cb_create(lv_scr_act(), cb3);
    lv_obj_align_scale(cb4, cb3, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
    lv_btn_set_state(cb4, LV_BTN_STATE_INACTIVE);

}


/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /*USE_LV_VB*/
