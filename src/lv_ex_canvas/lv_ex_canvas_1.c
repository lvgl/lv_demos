#include "lvgl/lvgl.h"
#if LV_USE_CANVAS


#define CANVAS_WIDTH  200
#define CANVAS_HEIGHT  150

void lv_ex_canvas_1(void)
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

    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_WIDTH, CANVAS_HEIGHT)];

    lv_obj_t * canvas = lv_canvas_create(lv_scr_act(), NULL);
    lv_canvas_set_buffer(canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);
    lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_canvas_fill_bg(canvas, LV_COLOR_SILVER);

    lv_canvas_draw_rect(canvas, 70, 60, 100, 70, &style);

    lv_canvas_draw_text(canvas, 40, 20, 100, &style, "Some text on text canvas", LV_LABEL_ALIGN_LEFT);

    /* Test the rotation. It requires an other buffer where the orignal image is stored.
     * So copy the current image to buffer and rotate it to the canvas */
    lv_color_t cbuf_tmp[CANVAS_WIDTH * CANVAS_HEIGHT];
    memcpy(cbuf_tmp, cbuf, sizeof(cbuf_tmp));
    lv_img_dsc_t img;
    img.data = (void *)cbuf_tmp;
    img.header.cf = LV_IMG_CF_TRUE_COLOR;
    img.header.w = CANVAS_WIDTH;
    img.header.h = CANVAS_HEIGHT;

    lv_canvas_fill_bg(canvas, LV_COLOR_SILVER);
    lv_canvas_rotate(canvas, &img, 30, 0, 0, CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2);
}

#endif
