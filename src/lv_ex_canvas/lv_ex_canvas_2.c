#include "lvgl/lvgl.h"

#define CANVAS_WIDTH  50
#define CANVAS_HEIGHT  50

/**
 * Create a transparent canvas with Chrome keying with indexed color format (palette).
 */
void lv_ex_canvas_2(void)
{
    /*Create a button to better see the transparency*/
    lv_btn_create(lv_scr_act(), NULL);

    /*Create a buffer for the canvas*/
    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_INDEXED_2BIT(CANVAS_WIDTH, CANVAS_HEIGHT)];

    /*Create a canvas and initialize its the palette*/
    lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
    lv_canvas_set_buffer(canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_INDEXED_2BIT);
    lv_canvas_set_palette(canvas, 0, LV_COLOR_TRANSP);
    lv_canvas_set_palette(canvas, 1, LV_COLOR_RED);
    lv_canvas_set_palette(canvas, 2, LV_COLOR_GREEN);
    lv_canvas_set_palette(canvas, 3, LV_COLOR_BLUE);

    /*Create colors with the indices of the palette*/
    lv_color_t c0;
    lv_color_t c1;
    lv_color_t c2;
    lv_color_t c3;

    c0.full = 0;
    c1.full = 1;
    c2.full = 2;
    c3.full = 3;

    /*Transparent background*/
    lv_canvas_fill_bg(canvas, c0);

    /*Draw three lines with the colors*/
    uint32_t i;
    for( i = 0; i < 20; i++) {
        lv_canvas_set_px(canvas, 5 + i, 10, c1);
        lv_canvas_set_px(canvas, 10 + i, 20, c2);
        lv_canvas_set_px(canvas, 15 + i, 30, c3);
    }

}
