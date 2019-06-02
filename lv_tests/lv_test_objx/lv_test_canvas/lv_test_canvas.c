/**
 * @file lv_test_canvas.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_canvas.h"

#if LV_USE_CANVAS && LV_USE_TESTS

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
    static lv_style_t style;
    lv_style_copy(&style, &lv_style_plain);
    style.body.main_color = LV_COLOR_RED;
    style.body.grad_color = LV_COLOR_MAROON;
    style.body.radius = 4;
    style.body.border.width = 2;
    style.body.border.color = LV_COLOR_WHITE;
    style.body.shadow.color = LV_COLOR_WHITE;
    style.body.shadow.width = 4;
    style.line.width = 2;
    style.line.color = LV_COLOR_BLACK;
    style.text.color = LV_COLOR_BLUE;

    lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
    lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(200, 300)];
    lv_canvas_set_buffer(canvas, cbuf, 200, 300, LV_IMG_CF_TRUE_COLOR);
    lv_obj_set_pos(canvas, 10, 20);
    lv_canvas_fill_bg(canvas, LV_COLOR_LIGHT_GRAY);

    lv_canvas_draw_rect(canvas, 50, 20, 100, 60, &style);

    lv_canvas_draw_text(canvas, 80, 100, 110, &style, "Long text on the right!", LV_LABEL_ALIGN_RIGHT);

    const lv_point_t points[] = {{50, 180}, {130, 190}, {110, 260}, {60, 280}, {50, 180}};

    lv_canvas_draw_polygon(canvas, points, 5, &style);
    lv_canvas_draw_line(canvas, points, 5, &style);

    lv_canvas_draw_arc(canvas, 40, 120, 30, 20, 250, &style);

    lv_color_t cbuf_tmp[200 * 300];
    memcpy(cbuf_tmp, cbuf, sizeof(cbuf_tmp));
    lv_img_dsc_t img;
    img.data = (void *)cbuf_tmp;
    img.header.cf = LV_IMG_CF_TRUE_COLOR;
    img.header.w = 200;
    img.header.h = 300;

    lv_canvas_fill_bg(canvas, LV_COLOR_LIGHT_GRAY);
    lv_canvas_rotate(canvas, &img, 40, 0, 0, 100, 150);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /*LV_USE_CANVAS && LV_USE_TESTS*/
