/**
 * @file lv_ex_img_2.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/

#define SLIDER_WIDTH 40
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

LV_IMG_DECLARE(cogwheel);

static void slider_event_cb(lv_obj_t * slider, lv_event_t event);

/**********************
 *  STATIC VARIABLES
 **********************/

static lv_obj_t * red_slider, * green_slider, * blue_slider, * intense_slider;

static lv_obj_t * img1;

static lv_style_t img_style;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_ex_img_2(void)
{
    /* This example uses the default theme */
    
    lv_theme_t *th = lv_theme_get_current();
    
    lv_theme_set_current(lv_theme_default_init(210, NULL));
    
    /* Create a set of RGB sliders */
    /* Use the red one as a base for all the settings */
    red_slider = lv_slider_create(lv_scr_act(), NULL);
    lv_slider_set_range(red_slider, 0, 255);
    lv_obj_set_size(red_slider, SLIDER_WIDTH, 200); /* Be sure it's a vertical slider */
    
    lv_obj_set_event_cb(red_slider, slider_event_cb);
    
    /* Create the intensity slider first, as it does not use any custom styles */
    
    intense_slider = lv_slider_create(lv_scr_act(), red_slider);
    lv_slider_set_range(intense_slider, LV_OPA_TRANSP, LV_OPA_COVER);
    
    
    
    /* Create the slider knob and fill styles */
    /* Fill styles are initialized with a gradient between black and the slider's respective color. */
    /* Knob styles are simply filled with the slider's respective color. */
    static lv_style_t slider_red_fill_style, slider_red_knob_style;
    
    lv_style_copy(&slider_red_fill_style, lv_slider_get_style(red_slider, LV_SLIDER_STYLE_INDIC));
    lv_style_copy(&slider_red_knob_style, lv_slider_get_style(red_slider, LV_SLIDER_STYLE_KNOB));
    
    slider_red_fill_style.body.main_color = lv_color_make(255, 0, 0);
    slider_red_fill_style.body.grad_color = LV_COLOR_BLACK;
    
    slider_red_knob_style.body.main_color = slider_red_knob_style.body.grad_color = slider_red_fill_style.body.main_color;
    
    static lv_style_t slider_green_fill_style, slider_green_knob_style;
    lv_style_copy(&slider_green_fill_style, &slider_red_fill_style);
    lv_style_copy(&slider_green_knob_style, &slider_red_knob_style);
    
    slider_green_fill_style.body.main_color = lv_color_make(0, 255, 0);
    
    slider_green_knob_style.body.main_color = slider_green_knob_style.body.grad_color = slider_green_fill_style.body.main_color;
    
    static lv_style_t slider_blue_fill_style, slider_blue_knob_style;
    lv_style_copy(&slider_blue_fill_style, &slider_red_fill_style);
    lv_style_copy(&slider_blue_knob_style, &slider_red_knob_style);
    
    slider_blue_fill_style.body.main_color = lv_color_make(0, 0, 255);
    
    slider_blue_knob_style.body.main_color = slider_blue_knob_style.body.grad_color = slider_blue_fill_style.body.main_color;
    
    /* Setup the red slider */
    lv_slider_set_style(red_slider, LV_SLIDER_STYLE_INDIC, &slider_red_fill_style);
    lv_slider_set_style(red_slider, LV_SLIDER_STYLE_KNOB, &slider_red_knob_style);
    
    /* Copy it for the other two sliders */
    green_slider = lv_slider_create(lv_scr_act(), red_slider);
    lv_slider_set_style(green_slider, LV_SLIDER_STYLE_INDIC, &slider_green_fill_style);
    lv_slider_set_style(green_slider, LV_SLIDER_STYLE_KNOB, &slider_green_knob_style);
    
    blue_slider = lv_slider_create(lv_scr_act(), red_slider);
    lv_slider_set_style(blue_slider, LV_SLIDER_STYLE_INDIC, &slider_blue_fill_style);
    lv_slider_set_style(blue_slider, LV_SLIDER_STYLE_KNOB, &slider_blue_knob_style);
    
    lv_obj_align(red_slider, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0);
    
    lv_obj_align(green_slider, red_slider, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    
    lv_obj_align(blue_slider, green_slider, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    
    lv_obj_align(intense_slider, blue_slider, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    
    /* Now create the actual image */
    img1 = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img1, &cogwheel);
    lv_obj_align(img1, blue_slider, LV_ALIGN_OUT_RIGHT_MID, 70, 0);
    
    /* Create a message box for information */
    
    static const char * btns[] ={"OK", ""};
    
    lv_obj_t * mbox = lv_mbox_create(lv_scr_act(), NULL);
    
    lv_mbox_set_text(mbox, "Welcome to the image recoloring demo!\nThe first three sliders control the RGB value of the recoloring.\nThe last slider controls the intensity.");
    lv_mbox_add_btns(mbox, btns);
    lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);
    
    /* Save the image's style so the sliders can modify it */
    lv_style_copy(&img_style, lv_img_get_style(img1, LV_IMG_STYLE_MAIN));
    
    if(th != NULL)
        lv_theme_set_current(th);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void slider_event_cb(lv_obj_t * slider, lv_event_t event) {
    if(event == LV_EVENT_VALUE_CHANGED) {
	/* Recolor the image based on the sliders' values */
        img_style.image.color = lv_color_make(lv_slider_get_value(red_slider), lv_slider_get_value(green_slider), lv_slider_get_value(blue_slider));
        img_style.image.intense = lv_slider_get_value(intense_slider);
        lv_img_set_style(img1, LV_IMG_STYLE_MAIN, &img_style);
    }
}
