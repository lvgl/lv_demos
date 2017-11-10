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
    //lv_obj_set_style(scr, th->bg);

    lv_obj_t *tv = lv_tabview_create(scr, NULL);
    lv_btnm_set_style_btn(lv_tabview_get_tabs(tv), th->tabview.tab.rel, th->tabview.tab.pr,
                                                   th->tabview.tab.trel, th->tabview.tab.tpr, NULL);
    lv_obj_set_style(lv_tabview_get_indic(tv), th->tabview.indic);
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
    lv_btn_set_style(btn, th->btn.sm.rel, th->btn.sm.pr, th->btn.sm.trel, th->btn.sm.tpr, th->btn.sm.ina);
    lv_btn_set_fit(btn, true, true);
    lv_btn_set_toggle(btn, true);
    lv_obj_t *btn_label = lv_label_create(btn, NULL);
    lv_label_set_text(btn_label, "Small");

    btn = lv_btn_create(h, btn);
    lv_btn_toggle(btn);
    btn_label = lv_label_create(btn, NULL);
    lv_label_set_text(btn_label, "Toggled");

    btn = lv_btn_create(h, btn);
    lv_btn_set_state(btn, LV_BTN_STATE_INACTIVE);
    btn_label = lv_label_create(btn, NULL);
    lv_label_set_text(btn_label, "Inactive");

    btn = lv_btn_create(h, btn);
    lv_btn_set_state(btn, LV_BTN_STATE_RELEASED);
    lv_btn_set_style(btn, th->btn.md.rel, th->btn.md.pr, th->btn.md.trel, th->btn.md.tpr, th->btn.md.ina);
    btn_label = lv_label_create(btn, NULL);
    lv_label_set_text(btn_label, "Medium");

    btn = lv_btn_create(h, btn);
    lv_btn_set_style(btn, th->btn.lg.rel, th->btn.lg.pr, th->btn.lg.trel, th->btn.lg.tpr, th->btn.lg.ina);
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

    lv_obj_t *sw = lv_sw_create(h, NULL);
    lv_sw_set_style(sw, th->sw.bg, th->sw.indic, th->sw.knob_off, th->sw.knob_on);

    sw = lv_sw_create(h, sw);
    lv_sw_set_on(sw);

    lv_obj_t *bar = lv_bar_create(h, NULL);
    lv_bar_set_style(bar, th->bar.bg, th->bar.indic);
    lv_bar_set_value(bar, 70);

    lv_obj_t *slider = lv_slider_create(h, NULL);
    lv_slider_set_style(slider, th->slider.bg, th->slider.indic, th->slider.knob);
    lv_obj_set_height(slider, LV_DPI / 2);
    lv_bar_set_value(slider, 70);

    lv_obj_t *ta = lv_ta_create(h, NULL);
    lv_obj_set_style(ta, th->ta.oneline);
    lv_ta_set_text(ta, "Some text");
    lv_ta_set_one_line(ta, true);

    lv_obj_t *cb = lv_cb_create(h, NULL);
    lv_cb_set_style_bullet(cb, th->cb.bullet.rel, th->cb.bullet.pr, th->cb.bullet.trel, th->cb.bullet.tpr, th->cb.bullet.ina);
    lv_cb_set_style(cb, th->cb.bg);
    cb = lv_cb_create(h, cb);
    lv_btn_set_state(cb, LV_BTN_STATE_TGL_RELEASED);


    lv_obj_t *ddlist = lv_ddlist_create(h, NULL);
    lv_ddlist_set_style(ddlist, th->ddlist.bg, th->ddlist.sb, th->ddlist.sel);

    h = lv_cont_create(tab1, h);

    lv_obj_t * list = lv_list_create(h, NULL);
    lv_list_set_style_btn(list, th->list.btn.rel, th->list.btn.pr, th->list.btn.trel, th->list.btn.tpr, th->list.btn.ina);
    lv_page_set_style(list, th->list.bg, &lv_style_transp_tight, th->list.sb);
    lv_list_add(list, SYMBOL_GPS, "GPS", NULL);
    lv_list_add(list, SYMBOL_WIFI, "WiFi", NULL);
    lv_list_add(list, SYMBOL_CALL, "Call", NULL);
    lv_list_add(list, SYMBOL_BELL, "Bell", NULL);
    lv_list_add(list, SYMBOL_FILE, "File", NULL);
    lv_list_add(list, SYMBOL_EDIT, "Edit", NULL);
    lv_list_add(list, SYMBOL_CUT, "Cut", NULL);
    lv_list_add(list, SYMBOL_COPY, "Copy", NULL);


    lv_obj_t *roller = lv_roller_create(h, NULL);
    lv_ddlist_set_style(roller, th->roller.bg, NULL, th->roller.sel);
    lv_ddlist_set_options(roller, "Monday\nTuesday\nWednesday\nThursday\nFriday\nSaturday\nSunday");
    lv_obj_set_height(roller, LV_DPI);

    return;

    static const char *btnm_str[] = {"1", "2", "3", "\n", "4", "5", "6", "\n", "7", "8", "9", "\n", SYMBOL_CLOSE, "0", SYMBOL_OK, ""};

    lv_obj_t *kb = lv_btnm_create(tab1, NULL);
    lv_obj_set_size(kb, LV_HOR_RES / 3, LV_VER_RES / 2);
    lv_btnm_set_map(kb, btnm_str);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/
