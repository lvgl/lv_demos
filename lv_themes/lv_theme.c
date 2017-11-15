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

/**
 * Create a test screen with a lot objects and apply the given theme on them
 * @param th pointer to a theme
 */
void lv_theme_create_test_screen(lv_theme_t *th)
{

    static lv_style_t h_style;
    lv_style_copy(&h_style, &lv_style_transp);
    h_style.body.padding.inner = LV_DPI / 4;
    h_style.body.padding.hor = LV_DPI / 4;
    h_style.body.padding.ver = LV_DPI / 6;

    lv_obj_t *scr = lv_cont_create(NULL, NULL);
    lv_scr_load(scr);
    lv_cont_set_style(scr, th->bg);

    lv_obj_t *tv = lv_tabview_create(scr, NULL);
    lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BG, th->tabview.bg);
    lv_tabview_set_style(tv, LV_TABVIEW_STYLE_INDIC, th->tabview.indic);
    lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_BG, th->tabview.tab.bg);
    lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_REL, th->tabview.tab.rel);
    lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_PR, th->tabview.tab.pr);
    lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_TGL_REL, th->tabview.tab.trel);
    lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_TGL_PR, th->tabview.tab.tpr);

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
    lv_btn_set_style(btn, LV_BTN_STYLE_REL, th->btn.sm.rel);
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, th->btn.sm.pr);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, th->btn.sm.trel);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, th->btn.sm.tpr);
    lv_btn_set_style(btn, LV_BTN_STYLE_INA, th->btn.sm.ina);
    lv_btn_set_fit(btn, true, true);
    lv_btn_set_toggle(btn, true);
    lv_obj_t *btn_label = lv_label_create(btn, NULL);
    lv_label_set_text(btn_label, "Small");

    btn = lv_btn_create(h, btn);
    lv_btn_toggle(btn);
    btn_label = lv_label_create(btn, NULL);
    lv_label_set_text(btn_label, "Toggled");

    btn = lv_btn_create(h, btn);
    lv_btn_set_state(btn, LV_BTN_STATE_INA);
    btn_label = lv_label_create(btn, NULL);
    lv_label_set_text(btn_label, "Inactive");

    btn = lv_btn_create(h, btn);
    lv_btn_set_state(btn, LV_BTN_STATE_REL);
    lv_btn_set_style(btn, LV_BTN_STYLE_REL, th->btn.md.rel);
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, th->btn.md.pr);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, th->btn.md.trel);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, th->btn.md.tpr);
    lv_btn_set_style(btn, LV_BTN_STYLE_INA, th->btn.md.ina);

    btn_label = lv_label_create(btn, NULL);
    lv_label_set_text(btn_label, "Medium");

    btn = lv_btn_create(h, btn);
    lv_btn_set_style(btn, LV_BTN_STYLE_REL, th->btn.lg.rel);
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, th->btn.lg.pr);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, th->btn.lg.trel);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, th->btn.lg.tpr);
    lv_btn_set_style(btn, LV_BTN_STYLE_INA, th->btn.lg.ina);
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

    h = lv_cont_create(tab1, h);

    lv_obj_t *sw_h = lv_cont_create(h, NULL);
    lv_cont_set_style(sw_h, &lv_style_transp);
    lv_cont_set_fit(sw_h, false, true);
    lv_obj_set_width(sw_h, LV_HOR_RES / 4);
    lv_cont_set_layout(sw_h, LV_CONT_LAYOUT_PRETTY);

    lv_obj_t *sw = lv_sw_create(sw_h, NULL);
    lv_sw_set_style(sw, LV_SW_STYLE_BG, th->sw.bg);
    lv_sw_set_style(sw, LV_SW_STYLE_INDIC, th->sw.indic);
    lv_sw_set_style(sw, LV_SW_STYLE_KNOB_OFF, th->sw.knob_off);
    lv_sw_set_style(sw, LV_SW_STYLE_KNOB_ON, th->sw.knob_on);

    sw = lv_sw_create(sw_h, sw);
    lv_sw_set_on(sw);

    lv_obj_t *bar = lv_bar_create(h, NULL);
    lv_bar_set_style(bar, LV_BAR_STYLE_BG, th->bar.bg);
    lv_bar_set_style(bar, LV_BAR_STYLE_INDIC, th->bar.indic);
    lv_bar_set_value(bar, 70);

    lv_obj_t *slider = lv_slider_create(h, NULL);
    lv_slider_set_style(slider, LV_SLIDER_STYLE_BG, th->slider.bg);
    lv_slider_set_style(slider, LV_SLIDER_STYLE_INDIC, th->slider.indic);
    lv_slider_set_style(slider, LV_SLIDER_STYLE_KNOB, th->slider.knob);
    lv_obj_set_height(slider, LV_DPI / 2);
    lv_bar_set_value(slider, 70);

    lv_obj_t *line = lv_line_create(h, NULL);
    static const point_t line_p[] = {{0,0},{LV_HOR_RES / 5, 0}};
    lv_line_set_points(line, line_p, 2);
    lv_line_set_style(line, th->line.decor);


    lv_obj_t *ta = lv_ta_create(h, NULL);
    lv_obj_set_style(ta, th->ta.oneline);
    lv_ta_set_text(ta, "Some text");
    lv_ta_set_one_line(ta, true);

    lv_obj_t *cb = lv_cb_create(h, NULL);
    lv_cb_set_style(cb, LV_CB_STYLE_BG, th->cb.bg);
    lv_cb_set_style(cb, LV_CB_STYLE_RELEASED, th->cb.bullet.rel);
    lv_cb_set_style(cb, LV_CB_STYLE_PRESSED, th->cb.bullet.pr);
    lv_cb_set_style(cb, LV_CB_STYLE_TGL_RELEASED, th->cb.bullet.trel);
    lv_cb_set_style(cb, LV_CB_STYLE_TGL_PRESSED, th->cb.bullet.tpr);
    lv_cb_set_style(cb, LV_CB_STYLE_INACTIVE, th->cb.bullet.ina);

    cb = lv_cb_create(h, cb);
    lv_btn_set_state(cb, LV_BTN_STATE_TGL_REL);


    lv_obj_t *ddlist = lv_ddlist_create(h, NULL);
    lv_ddlist_set_style(ddlist, LV_DDLIST_STYLE_BG, th->ddlist.bg);
    lv_ddlist_set_style(ddlist, LV_DDLIST_STYLE_SELECTED, th->ddlist.sel);
    lv_ddlist_set_style(ddlist, LV_DDLIST_STYLE_SB, th->ddlist.sb);
    lv_ddlist_open(ddlist, false);
    lv_ddlist_set_selected(ddlist, 1);


    static const char *btnm_str[] = {"1", "2", "3", SYMBOL_OK, SYMBOL_CLOSE, ""};

    lv_obj_t *btnm = lv_btnm_create(h, NULL);
    lv_obj_set_size(btnm,LV_HOR_RES / 4, 2 * LV_DPI / 3);
    lv_btnm_set_map(btnm, btnm_str);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BG, th->btnm.bg);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_REL, th->btnm.btn.rel);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_PR, th->btnm.btn.pr);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_TGL_REL, th->btnm.btn.trel);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_TGL_PR, th->btnm.btn.tpr);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_INA, th->btnm.btn.ina);
    ((lv_btnm_ext_t *) btnm->ext_attr)->btn_id_pressed = 3; /*Hack to show a button pressed*/

    h = lv_cont_create(tab1, h);

    lv_obj_t * list = lv_list_create(h, NULL);
    lv_list_set_style(list, LV_LIST_STYLE_BG, th->list.bg);
    lv_list_set_style(list, LV_LIST_STYLE_SCRL, th->list.scrl);
    lv_list_set_style(list, LV_LIST_STYLE_SB, th->list.sb);
    lv_list_set_style(list, LV_LIST_STYLE_BTN_REL, th->list.btn.rel);
    lv_list_set_style(list, LV_LIST_STYLE_BTN_TGL_REL, th->list.btn.pr);
    lv_list_set_style(list, LV_LIST_STYLE_BTN_PR, th->list.btn.trel);
    lv_list_set_style(list, LV_LIST_STYLE_BTN_TGL_PR, th->list.btn.tpr);
    lv_list_set_style(list, LV_LIST_STYLE_BTN_INA, th->list.btn.ina);
    lv_list_add(list, SYMBOL_GPS, "GPS", NULL);
    lv_list_add(list, SYMBOL_WIFI, "WiFi", NULL);
    lv_list_add(list, SYMBOL_CALL, "Call", NULL);
    lv_list_add(list, SYMBOL_BELL, "Bell", NULL);
    lv_list_add(list, SYMBOL_FILE, "File", NULL);
    lv_list_add(list, SYMBOL_EDIT, "Edit", NULL);
    lv_list_add(list, SYMBOL_CUT, "Cut", NULL);
    lv_list_add(list, SYMBOL_COPY, "Copy", NULL);

    lv_obj_t *roller = lv_roller_create(h, NULL);
    lv_roller_set_style(roller, LV_ROLLER_STYLE_BG, th->roller.bg);
    lv_roller_set_style(roller, LV_ROLLER_STYLE_SELECTED, th->roller.sel);
    lv_roller_set_options(roller, "Monday\nTuesday\nWednesday\nThursday\nFriday\nSaturday\nSunday");
    lv_obj_set_height(roller, LV_DPI);

    lv_obj_t *gauge = lv_gauge_create(h, NULL);
    lv_gauge_set_style(gauge, th->gauge.bg);
    lv_gauge_set_value(gauge, 0, 40);
    lv_obj_set_size(gauge, 3 * LV_DPI / 2, 3 * LV_DPI / 2);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/
