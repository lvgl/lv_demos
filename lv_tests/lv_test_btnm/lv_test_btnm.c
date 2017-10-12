/**
 * @file lv_test_btnm.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_btnm.h"
#include <stdio.h>  /*For printf in the action*/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_action_res_t btnm_action(lv_obj_t * btnm, uint16_t id);

/**********************
 *  STATIC VARIABLES
 **********************/
#if TXT_UTF8 != 0
static const char * btnm_map[] = {"One line", "\n", "\212", "\204üŰöŐ", "\221éÉ","\n", "\214", "\202Left", ""};
#else
static const char * btnm_map[] = {"One line", "\n", "\212", "\204long", "\221short","\n", "\214", "\202Left", ""};
#endif
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a default object and test the basic functions
 */
void lv_test_btnm_1(void)
{
    /* Default object
     * GOAL: A button matrix with default buttons */
    lv_obj_t * btnm1 = lv_btnm_create(lv_scr_act(), NULL);

    /* Test map, size and position. Also try some features.
     * GOAL: A button matrix with default buttons.  */
    static lv_style_t rel;
    lv_style_get(LV_STYLE_BTN_REL, &rel);
    rel.mcolor = COLOR_RED;
    rel.gcolor = COLOR_BLACK;
    rel.ccolor = COLOR_YELLOW;

    static lv_style_t pr;
    lv_style_get(LV_STYLE_BTN_REL, &pr);
    pr.mcolor = COLOR_ORANGE;
    pr.gcolor = COLOR_BLACK;
    pr.ccolor = COLOR_WHITE;


    lv_obj_t * btnm2 = lv_btnm_create(lv_scr_act(), NULL);
    lv_btnm_set_map(btnm2, btnm_map);
    lv_obj_set_size_us(btnm2, 200, 100);
    lv_obj_align(btnm2, btnm1, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_btnm_set_tgl(btnm2, true, 2);
    lv_btnm_set_action(btnm2, btnm_action);
    lv_btnm_set_styles_btn(btnm2, &rel, &pr,  NULL,  NULL,  NULL);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static lv_action_res_t btnm_action(lv_obj_t * btnm, uint16_t id)
{
    /* On PC
     * printf("%s\n", btnm_map[id]);
     */

    return LV_ACTION_RES_OK;
}
