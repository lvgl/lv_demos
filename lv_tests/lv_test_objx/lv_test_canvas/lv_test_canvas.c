/**
 * @file lv_test_canvas.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_canvas.h"

#if USE_LV_CANVAS && USE_LV_TESTS

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
 * Create canvas to test its functionalities
 */
void lv_test_canvas_1(void)
{
    /*Create a buffer for the canvas set its pixels to gray*/
    static lv_color_t cbuf[sizeof(lv_color_t) * 100 * 80];
    uint32_t i;
    for(i = 0; i < sizeof(cbuf) / sizeof(cbuf[0]); i++) {
        cbuf[i] = LV_COLOR_GRAY;
    }

    /*Create the canvas object*/
    lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);

    /*Assign the buffer to the canvas*/
    lv_canvas_set_buffer(canvas, cbuf, 100, 80, LV_IMG_CF_TRUE_COLOR);

    /*Set some pixels*/
    lv_canvas_set_px(canvas, 1,1, LV_COLOR_RED);
    lv_canvas_set_px(canvas, 2,5, LV_COLOR_BLUE);

    /*Create a pattern to copy to the canvas*/
    lv_color_t pbuf[2][2] = {LV_COLOR_RED, LV_COLOR_GREEN, LV_COLOR_BLUE, LV_COLOR_AQUA};

    /*Copy the pattern to teh canvas*/
    lv_canvas_copy_to_buf(canvas, pbuf, 2, 2, 6, 10);
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /*USE_LV_CANVAS && USE_LV_TESTS*/
