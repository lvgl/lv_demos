/**
 * @file lv_test_group.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_group.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_res_t win_btn_acion(lv_obj_t *btn);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_group_t *g;
static lv_obj_t *win;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create base groups to test their functionalities
 */
void lv_test_group_1(void)
{

    g = lv_group_create();

    /*Create a window to hold all the objects*/
    static lv_style_t win_style;
    lv_style_copy(&win_style, &lv_style_transp);
    win_style.body.padding.hor = LV_DPI / 4;
    win_style.body.padding.ver = LV_DPI / 4;
    win_style.body.padding.inner = LV_DPI / 4;


    win = lv_win_create(lv_scr_act(), NULL);
    lv_win_set_title(win, "Group test");
    lv_win_set_layout(win, LV_LAYOUT_PRETTY);
    lv_win_set_style(win, LV_WIN_STYLE_CONTENT_SCRL, &win_style);

    lv_obj_t *win_btn = lv_win_add_btn(win, SYMBOL_RIGHT, win_btn_acion);
    lv_obj_set_free_num(win_btn, LV_GROUP_KEY_RIGHT);

    win_btn = lv_win_add_btn(win, SYMBOL_NEXT, win_btn_acion);
    lv_obj_set_free_num(win_btn, LV_GROUP_KEY_NEXT);

    win_btn = lv_win_add_btn(win, SYMBOL_OK, win_btn_acion);
    lv_obj_set_free_num(win_btn, LV_GROUP_KEY_ENTER);

    win_btn = lv_win_add_btn(win, SYMBOL_PREV, win_btn_acion);
    lv_obj_set_free_num(win_btn, LV_GROUP_KEY_PREV);

    win_btn = lv_win_add_btn(win, SYMBOL_LEFT, win_btn_acion);
    lv_obj_set_free_num(win_btn, LV_GROUP_KEY_LEFT);

    win_btn = lv_win_add_btn(win, "a", win_btn_acion);
    lv_obj_set_free_num(win_btn, 'a');


    lv_obj_t *obj;

    obj = lv_obj_create(win, NULL);
    lv_group_add_obj(g, obj);

    obj = lv_label_create(win, NULL);
    lv_group_add_obj(g, obj);

    obj = lv_btn_create(win, NULL);
    lv_group_add_obj(g, obj);
    obj = lv_label_create(obj, NULL);
    lv_label_set_text(obj, "Button");

    obj = lv_cb_create(win, NULL);
    lv_group_add_obj(g, obj);

    obj = lv_bar_create(win, NULL);
    lv_bar_set_value(obj, 60);
    lv_group_add_obj(g, obj);

    obj = lv_slider_create(win, NULL);
    lv_group_add_obj(g, obj);

    obj = lv_sw_create(win, NULL);
    lv_group_add_obj(g, obj);

    obj = lv_ddlist_create(win, NULL);
    lv_group_add_obj(g, obj);

    obj = lv_roller_create(win, NULL);
    lv_group_add_obj(g, obj);

    obj = lv_btnm_create(win, NULL);
    lv_obj_set_size(obj, LV_HOR_RES / 4, LV_VER_RES / 6);
    lv_group_add_obj(g, obj);

    lv_obj_t *ta = lv_ta_create(win, NULL);
    lv_group_add_obj(g, ta);

    obj = lv_kb_create(win, NULL);
    lv_obj_set_size(obj, LV_HOR_RES / 2, LV_VER_RES / 4);
    lv_kb_set_ta(obj, ta);
    lv_group_add_obj(g, obj);

    static const char *mbox_btns[] = {"Yes", "No", ""};
    obj = lv_mbox_create(win, NULL);
    lv_mbox_add_btns(obj, mbox_btns, NULL);
    lv_group_add_obj(g, obj);

    obj = lv_list_create(win, NULL);
    lv_list_add(obj, SYMBOL_FILE, "File 1", NULL);
    lv_list_add(obj, SYMBOL_FILE, "File 2", NULL);
    lv_list_add(obj, SYMBOL_FILE, "File 3", NULL);
    lv_list_add(obj, SYMBOL_FILE, "File 4", NULL);
    lv_list_add(obj, SYMBOL_FILE, "File 5", NULL);
    lv_list_add(obj, SYMBOL_FILE, "File 6", NULL);
    lv_group_add_obj(g, obj);


    obj = lv_page_create(win, NULL);
    lv_obj_set_size(obj, 2 * LV_DPI, LV_DPI);
    lv_group_add_obj(g, obj);
    obj = lv_label_create(obj, NULL);
    lv_label_set_text(obj, "I'm a page");

    obj = lv_lmeter_create(win, NULL);
    lv_lmeter_set_value(obj, 60);
    lv_group_add_obj(g, obj);

    static color_t needle_color[] = {COLOR_RED};
    obj = lv_gauge_create(win, NULL);
    lv_gauge_set_needle_count(obj, 1, needle_color);
    lv_gauge_set_value(obj, 0, 80);
    lv_group_add_obj(g, obj);

    obj = lv_chart_create(win, NULL);
    lv_chart_series_t * ser = lv_chart_add_series(obj, COLOR_RED);
    lv_chart_set_next(obj, ser, 40);
    lv_chart_set_next(obj, ser, 30);
    lv_chart_set_next(obj, ser, 35);
    lv_chart_set_next(obj, ser, 50);
    lv_chart_set_next(obj, ser, 60);
    lv_chart_set_next(obj, ser, 75);
    lv_chart_set_next(obj, ser, 80);
    lv_group_add_obj(g, obj);

    obj = lv_led_create(win, NULL);
    lv_group_add_obj(g, obj);

    obj = lv_tabview_create(win, NULL);
    lv_obj_set_size(obj, LV_HOR_RES / 2, LV_VER_RES / 2);
    lv_tabview_add_tab(obj, "Tab 1");
    lv_tabview_add_tab(obj, "Tab 2");
    lv_group_add_obj(g, obj);
}


/**********************
 *   STATIC FUNCTIONS
 **********************/


static lv_res_t win_btn_acion(lv_obj_t *btn)
{
    uint8_t c = lv_obj_get_free_num(btn);

    if(c == LV_GROUP_KEY_NEXT) {
        lv_group_focus_next(g);
        lv_win_focus(win, lv_group_get_focused(g), 200);
        return LV_RES_OK;
    }

    if(c == LV_GROUP_KEY_PREV) {
        lv_group_focus_prev(g);
        lv_win_focus(win, lv_group_get_focused(g), 200);
        return LV_RES_OK;
    }


    lv_group_send(g, c);


    return LV_RES_OK;
}
