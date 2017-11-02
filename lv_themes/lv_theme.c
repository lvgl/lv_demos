/**
 * @file lv_theme.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include "examples/lv_themes/lv_theme.h"

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
void lv_theme_create_test_screen(lv_theme_t *th)
{

    static lv_style_t h_style;
    lv_style_copy(&h_style, &lv_style_transp);
    h_style.body.padding.inner = LV_DPI / 4;
    h_style.body.padding.hor = LV_DPI / 4;
    h_style.body.padding.ver = LV_DPI / 6;

    lv_obj_t *scr = lv_cont_create(NULL, NULL);
    lv_scr_load(scr);
    //lv_obj_set_style(scr, th->bg);

    lv_obj_t *tv = lv_tabview_create(scr, NULL);
    lv_btnm_set_button_style(lv_tabview_get_tabs(tv), th->tab.rel, th->tab.pr, th->tab.trel, th->tab.tpr, NULL);
    lv_obj_set_style(lv_tabview_get_indic(tv), th->tab.indic);
    lv_obj_set_style(tv, th->bg);
    lv_obj_set_size(tv, LV_HOR_RES, LV_VER_RES);
    lv_obj_t *tab1 = lv_tabview_add_tab(tv, "Tab 1");
    lv_obj_set_style(tab1, &h_style);
    lv_cont_set_layout(lv_page_get_scrl(tab1), LV_CONT_LAYOUT_PRETTY);

    lv_tabview_add_tab(tv, "Tab 2");
    lv_tabview_add_tab(tv, "Tab 3");

    lv_obj_t *h = lv_cont_create(tab1, NULL);
    lv_obj_set_style(h, &h_style);
    lv_cont_set_fit(h, true, true);
    lv_cont_set_layout(h, LV_CONT_LAYOUT_COL_M);

    lv_obj_t *btn = lv_btn_create(h, NULL);
    lv_btn_set_styles(btn, th->btn.sm.rel, th->btn.sm.pr, th->btn.sm.trel, th->btn.sm.tpr, th->btn.sm.ina);
    lv_cont_set_fit(btn, true, true);
    lv_obj_t *btn_label = lv_label_create(btn, NULL);
    lv_label_set_text(btn_label, "Small");

    btn = lv_btn_create(h, btn);
    lv_btn_set_styles(btn, th->btn.md.rel, th->btn.md.pr, th->btn.md.trel, th->btn.md.tpr, th->btn.md.ina);
    btn_label = lv_label_create(btn, NULL);
    lv_label_set_text(btn_label, "Medium");

    btn = lv_btn_create(h, btn);
    lv_btn_set_styles(btn, th->btn.lg.rel, th->btn.lg.pr, th->btn.lg.trel, th->btn.lg.tpr, th->btn.lg.ina);
    btn_label = lv_label_create(btn, NULL);
    lv_label_set_text(btn_label, "Large");

    lv_obj_t *label = lv_label_create(h, NULL);
    lv_label_set_text(label, "Small");
    lv_obj_set_style(label, th->label.sm);

    label = lv_label_create(h, NULL);
    lv_label_set_text(label, "Medium");
    lv_obj_set_style(label, th->label.md);

    label = lv_label_create(h, NULL);
    lv_label_set_text(label, "Large");
    lv_obj_set_style(label, th->label.lg);
    lv_obj_set_protect(label, LV_PROTECT_FOLLOW);

   // lv_obj_align_scale(kb, NULL, LV_ALIGN_IN_TOP_RIGHT, 10, 10);

//    lv_obj_t *cb = lv_cb_create(scr, NULL);
//    lv_btn_set_styles(lv_cb_get_bullet(cb), th->cb);

    h = lv_cont_create(tab1, h);
    lv_obj_t *sw = lv_sw_create(h, NULL);
    lv_obj_set_style(sw, th->sw.bg);
    lv_bar_set_indicator_style(sw, th->sw.indic);
    lv_slider_set_knob_style(sw, th->sw.knob);

    sw = lv_sw_create(h, sw);
    lv_bar_set_value(sw, 1);

    lv_obj_t *bar = lv_bar_create(h, NULL);
    lv_obj_set_style(bar, th->bar.bg);
    lv_bar_set_indicator_style(bar, th->bar.indic);
    lv_bar_set_value(bar, 70);

    lv_obj_t *slider = lv_slider_create(h, NULL);
    lv_obj_set_style(slider, th->slider.bg);
    lv_bar_set_indicator_style(slider, th->slider.indic);
    lv_slider_set_knob_style(slider, th->slider.knob);
    lv_obj_set_height(slider, LV_DPI / 2);
    lv_bar_set_value(slider, 70);

    lv_obj_t *ta = lv_ta_create(h, NULL);
    lv_obj_set_style(ta, th->ta.oneline);
    lv_ta_set_text(ta, "Some text");
    lv_ta_set_one_line(ta, true);

    lv_obj_t *cb = lv_cb_create(h, NULL);
    lv_btn_set_styles(lv_cb_get_bullet(cb), th->cb.bullet.rel, th->cb.bullet.pr, th->cb.bullet.trel, th->cb.bullet.tpr, th->cb.bullet.ina);
    lv_btn_set_styles(cb, th->cb.bg, th->cb.bg, th->cb.bg, th->cb.bg, th->cb.bg);
    cb = lv_cb_create(h, cb);
    lv_btn_set_state(cb, LV_BTN_STATE_TGL_RELEASED);


    lv_obj_t * list = lv_list_create(tab1, NULL);
    lv_list_set_btn_styles(list, th->list.rel, th->list.pr, th->list.trel, th->list.tpr, th->list.ina);
    lv_obj_set_style(lv_page_get_scrl(list), &lv_style_transp_tight);
    lv_page_set_style_sb(list, th->list.sb);
    lv_list_add(list, symbol_gps, "GPS", NULL);
    lv_list_add(list, symbol_wifi, "WiFi", NULL);
    lv_list_add(list, symbol_call, "Call", NULL);
    lv_list_add(list, symbol_bell, "Bell", NULL);
    lv_list_add(list, symbol_file, "File", NULL);
    lv_list_add(list, symbol_edit, "Edit", NULL);
    lv_list_add(list, symbol_cut, "Cut", NULL);
    lv_list_add(list, symbol_copy, "Copy", NULL);



    static const char *btnm_str[] = {"1", "2", "3", "\n", "4", "5", "6", "\n", "7", "8", "9", "\n", symbol_close, "0", symbol_ok, ""};

    lv_obj_t *kb = lv_btnm_create(tab1, NULL);
    lv_obj_set_size(kb, LV_HOR_RES / 3, LV_VER_RES / 2);
    lv_btnm_set_map(kb, btnm_str);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/
