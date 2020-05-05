/**
 * @file lv_demo_priner_scr.c
 * Screen templates
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_printer_scr.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
void anim_bg_color_cb(lv_anim_t * a, lv_anim_value_t v);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * bg_top;
static lv_obj_t * bg_bottom;
static lv_style_t style_bg_top;
static lv_style_t style_bg_bottom;
static lv_style_t style_box;
static lv_style_t style_title;
static lv_style_t style_back;
static lv_style_t style_icon;
static lv_color_t bg_color_prev;
static lv_color_t bg_color_act;
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize some styles
 */
void lv_demo_printer_scr_init(void)
{
    bg_color_prev = LV_DEMO_PRINTER_BLUE;
    bg_color_act = LV_DEMO_PRINTER_BLUE;
    lv_style_init(&style_bg_top);
    lv_style_set_bg_opa(&style_bg_top, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&style_bg_top, LV_STATE_DEFAULT, LV_DEMO_PRINTER_BLUE);

    lv_style_init(&style_bg_bottom);
    lv_style_set_bg_opa(&style_bg_bottom, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&style_bg_bottom, LV_STATE_DEFAULT, LV_DEMO_PRINTER_LIGHT);

    lv_style_init(&style_box);
    lv_style_set_bg_opa(&style_box, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_radius(&style_box, LV_STATE_DEFAULT, 10);

    lv_style_init(&style_title);
    lv_style_set_bg_color(&style_title, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    lv_style_init(&style_icon);
    lv_style_set_value_align(&style_icon, LV_STATE_DEFAULT, LV_ALIGN_OUT_BOTTOM_MID);
    lv_style_set_value_ofs_y(&style_icon, LV_STATE_DEFAULT, LV_VER_RES / 30);
    lv_style_set_value_ofs_y(&style_icon, LV_STATE_PRESSED, LV_VER_RES / 20);
    lv_style_set_value_color(&style_icon, LV_STATE_DEFAULT, LV_DEMO_PRINTER_GRAY);
    lv_style_set_transform_zoom(&style_icon, LV_STATE_PRESSED, 350);
    lv_style_set_transition_time(&style_icon, LV_STATE_DEFAULT, 300);
    lv_style_set_transition_delay(&style_icon, LV_STATE_PRESSED, 0);
    lv_style_set_transition_delay(&style_icon, LV_STATE_DEFAULT, 300);
    lv_style_set_transition_prop_1(&style_icon, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_ZOOM);
    lv_style_set_transition_prop_2(&style_icon, LV_STATE_DEFAULT, LV_STYLE_VALUE_OFS_Y);

    bg_bottom = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_clean_style_list(bg_bottom, LV_OBJ_PART_MAIN);
    lv_obj_add_style(bg_bottom, LV_OBJ_PART_MAIN, &style_bg_bottom);
    lv_obj_set_size(bg_bottom, LV_HOR_RES, LV_VER_RES);

    bg_top = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_clean_style_list(bg_top, LV_OBJ_PART_MAIN);
    lv_obj_add_style(bg_top, LV_OBJ_PART_MAIN, &style_bg_top);
    lv_obj_set_size(bg_top, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_y(bg_top, LV_DEMO_PRINTER_BG_NONE);
}

/**
 * Create a simple box
 * @param scr a screen
 * @return
 */
lv_obj_t * lv_demo_printer_scr_add_box(void)
{
    lv_obj_t * box = lv_cont_create(lv_scr_act(), NULL);
    lv_obj_clean_style_list(box, LV_CONT_PART_MAIN);
    lv_obj_add_style(box, LV_CONT_PART_MAIN, &style_box);

    return box;
}

/**
 * Add a title
 * @param scr a screen
 * @return
 */
lv_obj_t * lv_demo_printer_scr_add_title(const char * txt)
{
    lv_obj_t * title = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(title, txt);
    return title;
}

/**
 * Create a simple box
 * @param scr a screen
 * @return
 */
lv_obj_t * lv_demo_printer_scr_add_back(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);

    return btn;
}

/**
 * Create add icon
 * @param parent pointer to parent (screen or box)
 * @return
 */
lv_obj_t * lv_demo_printer_scr_add_icon(lv_obj_t * parent, const void * src, const char * txt)
{
    lv_obj_t * icon = lv_img_create(parent, NULL);
    lv_obj_clean_style_list(icon, LV_OBJ_PART_MAIN);
    lv_obj_add_style(icon, LV_OBJ_PART_MAIN, &style_icon);
    lv_img_set_src(icon, src);
    lv_obj_set_click(icon, true);

    lv_obj_set_style_local_value_str(icon, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, txt);

    return icon;
}

void lv_demo_printer_anim_bg(uint32_t delay, lv_color_t color, uint32_t y)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, bg_top);
    lv_anim_set_time(&a, LV_DEMO_PRINTER_ANIM_TIME_BG);
    lv_anim_set_delay(&a, delay);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_values(&a, lv_obj_get_y(bg_top), y);
    lv_anim_start(&a);

    bg_color_prev = bg_color_act;
    bg_color_act = color;

    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)anim_bg_color_cb);
    lv_anim_set_values(&a, 0, 255);
    lv_anim_start(&a);


}

void lv_demo_printer_anim_in(lv_obj_t * obj, uint32_t delay)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_time(&a, LV_DEMO_PRINTER_ANIM_TIME);
    lv_anim_set_delay(&a, delay);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_values(&a, lv_obj_get_y(obj) - LV_DEMO_PRINTER_ANIM_Y, lv_obj_get_y(obj));
    lv_anim_start(&a);

    lv_obj_fade_in(obj, LV_DEMO_PRINTER_ANIM_TIME, delay);
}

void lv_demo_printer_anim_out(lv_obj_t * obj, uint32_t delay)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_time(&a, LV_DEMO_PRINTER_ANIM_TIME);
    lv_anim_set_delay(&a, delay);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_values(&a, lv_obj_get_y(obj), lv_obj_get_y(obj) + LV_DEMO_PRINTER_ANIM_Y);
    lv_anim_set_ready_cb(&a, lv_obj_del_anim_ready_cb);
    lv_anim_start(&a);

    lv_obj_fade_out(obj, LV_DEMO_PRINTER_ANIM_TIME, delay);
}


void lv_demo_printer_anim_out_all(lv_obj_t * obj, uint32_t delay)
{
    lv_obj_t * child = lv_obj_get_child_back(obj, NULL);
    while(child) {
        lv_demo_printer_anim_out_all(child, delay);
        delay += LV_DEMO_PRINTER_ANIM_DELAY;
        child = lv_obj_get_child_back(obj, child);
    }

    if(obj != bg_top && obj != bg_bottom && obj != lv_scr_act()) {
        lv_demo_printer_anim_out(obj, delay);
        delay += LV_DEMO_PRINTER_ANIM_DELAY;
    }

}

void lv_demo_printer_anim_in_all(lv_obj_t * obj, uint32_t delay)
{
    if(obj != bg_top && obj != bg_bottom && obj != lv_scr_act()) {
        lv_demo_printer_anim_in(obj, delay);
        delay += LV_DEMO_PRINTER_ANIM_DELAY;
    }

    lv_obj_t * child = lv_obj_get_child_back(obj, NULL);

    while(child) {
        delay += LV_DEMO_PRINTER_ANIM_DELAY;
        lv_demo_printer_anim_in_all(child, delay);
        child = lv_obj_get_child_back(obj, child);
    }

}
/**********************
 *   STATIC FUNCTIONS
 **********************/
void anim_bg_color_cb(lv_anim_t * a, lv_anim_value_t v)
{
    lv_color_t c = lv_color_mix(bg_color_act, bg_color_prev, v);
    lv_style_set_bg_color(&style_bg_top, LV_STATE_DEFAULT, c);
    lv_obj_refresh_style(bg_top, LV_STYLE_BG_COLOR);
}
