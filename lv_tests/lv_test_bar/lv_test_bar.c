/**
 * @file lv_test_bar.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_bar.h"

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
void lv_test_bar_1(void)
{
    /* Default object
     * GOAL: A bar which looks well */
    lv_obj_t * bar1 = lv_bar_create(lv_scr_act(), NULL);

    /* Modify the basic attributes
     * GOAL: size and position modified, indicator at 75 % */
    lv_obj_t * bar2 = lv_bar_create(lv_scr_act(), NULL);
    lv_obj_set_size(bar2, 200, 50);
    lv_obj_align_us(bar2, bar1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);
    lv_bar_set_range(bar2, -50, 50);
    lv_bar_set_value(bar2, 25);

    /* Copy 'bar2' but set its size to be vertical
     * GOAL: indicator at 75 % but the bar is vertical*/
    lv_obj_t * bar3 = lv_bar_create(lv_scr_act(), bar2);
    lv_obj_set_size(bar3, 50, 200);
    lv_obj_align_us(bar3, bar2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);


    /* Copy 'bar2' and set new style for it
     * GOAL: like 'bar2' on its left but dark bg, thin red indicator with big light*/
    static lv_style_t bar_bg;
    lv_style_get(LV_STYLE_PRETTY, &bar_bg);
    bar_bg.mcolor = COLOR_BLACK;

    static lv_style_t bar_indic;
    lv_style_get(LV_STYLE_PRETTY, &bar_indic);
    bar_indic.mcolor = COLOR_RED;
    bar_indic.gcolor = COLOR_MARRON;
    bar_indic.scolor = COLOR_RED;
    bar_indic.swidth = 20 << LV_ANTIALIAS;
    bar_indic.vpad = 10 << LV_ANTIALIAS;       /*Make the indicator thinner*/

    lv_obj_t * bar4 = lv_bar_create(lv_scr_act(), bar2);
    lv_obj_align_us(bar4, bar2, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
    lv_obj_set_style(bar4, &bar_bg);
    lv_bar_set_style_indic(bar4, &bar_indic);

    /* Copy 'bar4' but set its size to be vertical
     * GOAL: same es the styles 'bar4' but vertical*/
    lv_obj_t * bar5 = lv_bar_create(lv_scr_act(), bar4);
    lv_obj_set_size(bar5, 50, 200);
    lv_obj_align_us(bar5, bar4, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);

}


/**********************
 *   STATIC FUNCTIONS
 **********************/
