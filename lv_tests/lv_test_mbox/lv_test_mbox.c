/**
 * @file lv_test_mbox.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>  /*For printf in the action*/

#include "lv_test_mbox.h"

#if USE_LV_MBOX != 0

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_res_t mbox_action(lv_obj_t *btn);

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
void lv_test_mbox_1(void)
{
    /* Default object */
    lv_obj_t *mbox1 = lv_mbox_create(lv_scr_act(), NULL);
    lv_obj_set_pos_scale(mbox1, 10, 10);

    /*Add buttons and modify text*/
    lv_obj_t *mbox2 = lv_mbox_create(lv_scr_act(), NULL);
    lv_mbox_add_btn(mbox2, "Ok", mbox_action);
    lv_mbox_add_btn(mbox2, "Cancel", lv_mbox_close_action);
    lv_mbox_set_text(mbox2, "Message");
    lv_obj_align_scale(mbox2, mbox1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);


    /*Add styles*/
    static lv_style_t bg;
    static lv_style_t btnh;
    lv_style_copy(&bg, &lv_style_pretty);
    lv_style_copy(&btnh, &lv_style_pretty);
    bg.body.padding.hor = 20 << LV_ANTIALIAS;
    bg.body.padding.ver = 20 << LV_ANTIALIAS;
    bg.body.padding.inner = 20 << LV_ANTIALIAS;
    bg.body.color_main = COLOR_BLACK;
    bg.body.color_gradient = COLOR_MARRON;
    bg.text.color = COLOR_WHITE;

    btnh.body.padding.hor = 10 << LV_ANTIALIAS;
    btnh.body.padding.ver = 20 << LV_ANTIALIAS;
    btnh.body.padding.inner = 40 << LV_ANTIALIAS;
    btnh.body.empty = 1;
    btnh.body.border.color = COLOR_WHITE;
    btnh.text.color = COLOR_WHITE;

    static lv_style_t btn_rel;
    lv_style_copy(&btn_rel, &lv_style_btn_off_released);
    btn_rel.body.empty = 1;
    btn_rel.body.border.color = COLOR_WHITE;

    lv_obj_t *mbox3 = lv_mbox_create(lv_scr_act(), mbox2);
    lv_mbox_set_style(mbox3, &bg, &btnh);
    lv_mbox_set_style_btn(mbox3, &btn_rel, NULL);

    lv_obj_align_scale(mbox3, mbox2, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

    /*Copy with styles and set button width*/
    lv_obj_t *mbox4 = lv_mbox_create(lv_scr_act(), mbox3);
    lv_mbox_set_text(mbox4, "A quite long message text which is\n"
                            "manually broken into multiple lines");

    lv_mbox_set_btn_width(mbox4, LV_DPI);
    lv_mbox_add_btn(mbox4, "Third", NULL);
    lv_obj_align_scale(mbox4, mbox3, LV_ALIGN_OUT_BOTTOM_MID, 0, 40);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static lv_res_t mbox_action(lv_obj_t *btn)
{
    lv_obj_t *mbox = lv_mbox_get_from_btn(btn);

    lv_mbox_set_text(mbox, "Short text");

    return LV_RES_OK;
}

#endif /*USE_LV_MBOX*/
