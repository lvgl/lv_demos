/**
 * @file lv_test_gauge.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_gauge.h"

#if USE_LV_GAUGE != 0

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
void lv_test_gauge_1(void)
{
    /* Create a default object*/
    lv_obj_t *gauge1 = lv_gauge_create(lv_scr_act(), NULL);
    lv_obj_set_pos_scale(gauge1, 10, 10);
    lv_gauge_set_value(gauge1, 0, 75);

    /*Copy the previous gauge and set smaller size for it*/
    lv_obj_t *gauge2 = lv_gauge_create(lv_scr_act(), gauge1);
    lv_obj_set_size(gauge2, 2 * lv_obj_get_width(gauge1) / 3,  2 * lv_obj_get_height(gauge1) / 3);
    lv_obj_align_scale(gauge2, gauge1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    /*Copy the first gauge add more needles and set new style*/
    static color_t needle_colors[3] = {COLOR_BLUE, COLOR_PURPLE, COLOR_TEAL};

    /*Create a styled gauge*/
    static lv_style_t style3;
    lv_style_copy(&style3, &lv_style_pretty);
    style3.body.color_main = COLOR_GREEN;
    style3.body.color_gradient = COLOR_RED;
    style3.body.padding.hor = 4 << LV_ANTIALIAS;
    style3.body.padding.inner = 10 << LV_ANTIALIAS;
    style3.body.padding.ver = 8 << LV_ANTIALIAS;
    style3.body.border.color= COLOR_GRAY;
    style3.line.width = 2 << LV_ANTIALIAS;

    lv_obj_t *gauge3 = lv_gauge_create(lv_scr_act(), gauge1);
    lv_obj_align_scale(gauge3, gauge1, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
    lv_obj_set_style(gauge3, &style3);
    lv_gauge_set_scale(gauge3, 270, 41, 5);
    lv_gauge_set_needle_count(gauge3, 3, needle_colors);
    lv_gauge_set_value(gauge3, 0, 20);
    lv_gauge_set_value(gauge3, 1, 40);
    lv_gauge_set_value(gauge3, 2, 60);

    /*Copy the modified 'gauge3' and set a smaller size for it*/
    lv_obj_t *gauge4 = lv_gauge_create(lv_scr_act(), gauge3);
    lv_obj_set_size_scale(gauge4, 100, 100);
    lv_obj_align_scale(gauge4, gauge3, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /*USE_LV_GAUGE*/

