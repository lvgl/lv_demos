/**
 * @file lv_templ.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_widgets.h"
#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void controls_create(lv_obj_t * parent);
static void visuals_create(lv_obj_t * parent);
static void selectors_create(lv_obj_t * parent);
static void lv_ta_event_cb(lv_obj_t * ta, lv_event_t e);
static void lv_kb_event_cb(lv_obj_t * ta, lv_event_t e);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * tv;
static lv_obj_t * t1;
static lv_obj_t * t2;
static lv_obj_t * t3;
static lv_obj_t * kb;

static lv_style_t style_box;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_widget(void)
{
    tv = lv_tabview_create(lv_scr_act(), NULL);
    lv_obj_set_style_int(tv, LV_TABVIEW_PART_TAB_BG, LV_STYLE_PAD_LEFT, LV_HOR_RES / 2);
    t1 = lv_tabview_add_tab(tv, "Controls");
    t2 = lv_tabview_add_tab(tv, "Visuals");
    t3 = lv_tabview_add_tab(tv, "Selectors");

    lv_style_init(&style_box);
    lv_style_set_value_align(&style_box, LV_STATE_NORMAL, LV_ALIGN_OUT_TOP_LEFT);
    lv_style_set_value_ofs_y(&style_box, LV_STATE_NORMAL, 0);
    lv_style_set_pad_inner(&style_box, LV_STATE_NORMAL, LV_DPI / 4);

    controls_create(t1);
    visuals_create(t2);
    selectors_create(t3);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


static void controls_create(lv_obj_t * parent)
{
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY);

    static const char * btns[] = {"Cancel", "Ok", ""};

    lv_obj_t * m = lv_msgbox_create(lv_scr_act(), NULL);
    lv_msgbox_add_btns(m, btns);
    lv_obj_t * btnm = lv_msgbox_get_btnm(m);
    lv_btnmatrix_set_btn_ctrl(btnm, 1, LV_BTNMATRIX_CTRL_CHECK_STATE);

    lv_obj_t * h = lv_cont_create(parent, NULL);
    lv_cont_set_layout(h, LV_LAYOUT_COLUMN_LEFT);
    lv_obj_add_style(h, LV_CONT_PART_MAIN, &style_box);
    lv_obj_set_drag_parent(h, true);

    lv_obj_set_style_value_str(h, LV_CONT_PART_MAIN, LV_STATE_NORMAL, "Basics");

    lv_cont_set_fit2(h, LV_FIT_TIGHT, LV_FIT_TIGHT);

    lv_obj_t * btn = lv_btn_create(h, NULL);
    lv_btn_set_fit(btn, LV_FIT_TIGHT);
    lv_obj_t * label = lv_label_create(btn, NULL);
    lv_label_set_text(label ,"Button");

    lv_checkbox_create(h, NULL);
    lv_switch_create(h, NULL);

    lv_obj_t * slider = lv_slider_create(h, NULL);
    lv_bar_set_value(slider, 40, LV_ANIM_OFF);

    slider = lv_slider_create(h, NULL);
    lv_slider_set_type(slider, LV_SLIDER_TYPE_RANGE);
    lv_slider_set_value(slider, 70, LV_ANIM_OFF);
    lv_slider_set_left_value(slider, 30, LV_ANIM_OFF);


    h = lv_cont_create(parent, h);
    lv_obj_set_style_value_str(h, LV_CONT_PART_MAIN, LV_STATE_NORMAL, "Text input");

    lv_obj_t * ta = lv_textarea_create(h, NULL);
    lv_textarea_set_text(ta, "");
    lv_textarea_set_placeholder_text(ta, "E-mail address");
    lv_textarea_set_one_line(ta, true);
    lv_textarea_set_cursor_hidden(ta, true);
    lv_obj_set_event_cb(ta, lv_ta_event_cb);
    lv_theme_apply(ta, LV_THEME_TEXTAREA_ONELINE);

    ta = lv_textarea_create(h, ta);
    lv_textarea_set_pwd_mode(ta, true);
    lv_textarea_set_placeholder_text(ta, "Password");

    ta = lv_textarea_create(h, NULL);
    lv_textarea_set_text(ta, "");
    lv_textarea_set_placeholder_text(ta, "Message");
    lv_textarea_set_cursor_hidden(ta, true);
    lv_obj_set_event_cb(ta, lv_ta_event_cb);
}

static void visuals_create(lv_obj_t * parent)
{
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY);

    lv_obj_t * chart = lv_chart_create(parent, NULL);
    lv_chart_set_div_line_count(chart, 3, 0);
    lv_chart_set_point_count(chart, 8);
    lv_obj_set_style_int(chart, LV_CHART_PART_BG, LV_STYLE_PAD_LEFT, 50);
    lv_obj_set_style_int(chart, LV_CHART_PART_BG, LV_STYLE_PAD_BOTTOM, 30);
    lv_chart_set_y_tick_length(chart, 0, 0);
    lv_chart_set_x_tick_length(chart, 0, 0);
    lv_chart_set_y_tick_texts(chart, "600\n500\n400\n300\n200", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
    lv_chart_set_x_tick_texts(chart, "Jan\nFeb\nMar\nApr\nMay\nJun\nJul\nAug", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_series_t * s1 = lv_chart_add_series(chart, lv_color_hex(0xae7af8));
    lv_chart_series_t * s2 = lv_chart_add_series(chart, lv_color_hex(0x0080ff));

    lv_chart_set_next(chart, s1, 10);
    lv_chart_set_next(chart, s1, 90);
    lv_chart_set_next(chart, s1, 30);
    lv_chart_set_next(chart, s1, 60);
    lv_chart_set_next(chart, s1, 10);
    lv_chart_set_next(chart, s1, 90);
    lv_chart_set_next(chart, s1, 30);
    lv_chart_set_next(chart, s1, 60);
    lv_chart_set_next(chart, s1, 10);
    lv_chart_set_next(chart, s1, 90);

    lv_chart_set_next(chart, s2, 32);
    lv_chart_set_next(chart, s2, 66);
    lv_chart_set_next(chart, s2, 5);
    lv_chart_set_next(chart, s2, 47);
    lv_chart_set_next(chart, s2, 32);
    lv_chart_set_next(chart, s2, 32);
    lv_chart_set_next(chart, s2, 66);
    lv_chart_set_next(chart, s2, 5);
    lv_chart_set_next(chart, s2, 47);
    lv_chart_set_next(chart, s2, 66);
    lv_chart_set_next(chart, s2, 5);
    lv_chart_set_next(chart, s2, 47);

    lv_obj_t * chart2 = lv_chart_create(parent, chart);
    lv_chart_set_type(chart2, LV_CHART_TYPE_COLUMN);

    s1 = lv_chart_add_series(chart2, lv_color_hex(0xae7af8));
    s2 = lv_chart_add_series(chart2, lv_color_hex(0x0080ff));

    lv_chart_set_next(chart2, s1, 10);
    lv_chart_set_next(chart2, s1, 90);
    lv_chart_set_next(chart2, s1, 30);
    lv_chart_set_next(chart2, s1, 60);
    lv_chart_set_next(chart2, s1, 10);
    lv_chart_set_next(chart2, s1, 90);
    lv_chart_set_next(chart2, s1, 30);
    lv_chart_set_next(chart2, s1, 60);
    lv_chart_set_next(chart2, s1, 10);
    lv_chart_set_next(chart2, s1, 90);

    lv_chart_set_next(chart2, s2, 32);
    lv_chart_set_next(chart2, s2, 66);
    lv_chart_set_next(chart2, s2, 5);
    lv_chart_set_next(chart2, s2, 47);
    lv_chart_set_next(chart2, s2, 32);
    lv_chart_set_next(chart2, s2, 32);
    lv_chart_set_next(chart2, s2, 66);
    lv_chart_set_next(chart2, s2, 5);
    lv_chart_set_next(chart2, s2, 47);
    lv_chart_set_next(chart2, s2, 66);
    lv_chart_set_next(chart2, s2, 5);
    lv_chart_set_next(chart2, s2, 47);

    lv_obj_t * page = lv_page_create(parent ,NULL);
    lv_obj_set_size(page, LV_HOR_RES / 3, LV_DPI * 2);
    lv_page_set_scroll_propagation(page, true);
    lv_cont_set_fit2(page, LV_FIT_TIGHT, LV_FIT_NONE);
    lv_page_set_scrl_fit(page, LV_FIT_TIGHT);

    lv_obj_t * table1 = lv_table_create(page, NULL);
    lv_obj_set_click(table1, false);
    lv_table_set_col_cnt(table1, 4);
    lv_table_set_row_cnt(table1, 7);
    lv_table_set_col_width(table1, 0, 30);
    lv_table_set_col_width(table1, 1, 150);
    lv_table_set_col_width(table1, 2, 150);
    lv_table_set_col_width(table1, 3, 150);

    lv_table_set_cell_value(table1, 0, 0, "#");
    lv_table_set_cell_value(table1, 0, 1, "FIRST NAME");
    lv_table_set_cell_value(table1, 0, 2, "LAST NAME");
    lv_table_set_cell_value(table1, 0, 3, "USER NAME");

    lv_table_set_cell_value(table1, 1, 0, "1");
    lv_table_set_cell_value(table1, 1, 1, "Mark");
    lv_table_set_cell_value(table1, 1, 2, "Otto");
    lv_table_set_cell_value(table1, 1, 3, "@mdo");

    lv_table_set_cell_value(table1, 2, 0, "2");
    lv_table_set_cell_value(table1, 2, 1, "Jacob");
    lv_table_set_cell_value(table1, 2, 2, "Thoronton");
    lv_table_set_cell_value(table1, 2, 3, "@fat");

    lv_table_set_cell_value(table1, 3, 0, "3");
    lv_table_set_cell_value(table1, 3, 1, "John");
    lv_table_set_cell_value(table1, 3, 2, "Doe");
    lv_table_set_cell_value(table1, 3, 3, "@j_doe");

    lv_table_set_cell_value(table1, 4, 0, "4");
    lv_table_set_cell_value(table1, 4, 1, "Emily");
    lv_table_set_cell_value(table1, 4, 2, "Smith");
    lv_table_set_cell_value(table1, 4, 3, "@e.smith");

    lv_table_set_cell_value(table1, 5, 0, "5");
    lv_table_set_cell_value(table1, 5, 1, "Samantha");
    lv_table_set_cell_value(table1, 5, 2, "Taylor");
    lv_table_set_cell_value(table1, 5, 3, "@staylor");

    lv_table_set_cell_value(table1, 6, 0, "6");
    lv_table_set_cell_value(table1, 6, 1, "George");
    lv_table_set_cell_value(table1, 6, 2, "Black");
    lv_table_set_cell_value(table1, 6, 3, "@black-g1");

    lv_obj_t * arc = lv_arc_create(parent, NULL);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_arc_set_angles(arc, 270, 30);
    lv_obj_set_size(arc, LV_DPI * 2, LV_DPI * 2);

    lv_obj_t * lmeter = lv_linemeter_create(parent, NULL);
    lv_obj_set_size(lmeter, LV_DPI * 2, LV_DPI * 2);
    lv_linemeter_set_value(lmeter, 50);

    lv_obj_t * gauge = lv_gauge_create(parent, NULL);
}


static void selectors_create(lv_obj_t * parent)
{
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY);

    lv_obj_t * list = lv_list_create(parent, NULL);

    const char * txts[] = {LV_SYMBOL_SAVE, "Save", LV_SYMBOL_CUT, "Cut", LV_SYMBOL_COPY, "Copy",
            LV_SYMBOL_OK, "Apply", LV_SYMBOL_EDIT, "Edit", LV_SYMBOL_WIFI, "Wifi",
            LV_SYMBOL_BLUETOOTH, "Bluetooth",  LV_SYMBOL_GPS, "GPS", LV_SYMBOL_USB, "USB",
            LV_SYMBOL_SD_CARD, "SD card", LV_SYMBOL_CLOSE, "Close", NULL};

    uint32_t i;
    lv_obj_t * btn;
    for(i = 0; txts[i] != NULL; i += 2) {
        btn = lv_list_add_btn(list, txts[i], txts[i + 1]);
        lv_btn_set_checkable(btn, true);

        /*Make button disabled*/
        if(i == 4) {
            lv_btn_set_state(btn, LV_BTN_STATE_DISABLED);
        }
    }

    lv_obj_t * cal = lv_calendar_create(parent, NULL);

    static lv_calendar_date_t hl[] = {
            {.year = 2020, .month = 1, .day = 5},
            {.year = 2020, .month = 1, .day = 9},
    };

    lv_calendar_set_highlighted_dates(cal, hl, 2);

    lv_obj_t * dd = lv_dropdown_create(parent, NULL);
    lv_obj_set_width(dd, 150);
    lv_dropdown_set_options(dd, "Alpha\nBravo\nCharlie\nDelta\nEcho\nFoxtrot\nGolf\nHotel\nIndia\nJuliette\nKilo\nLima\nMike\nNovember\n"
            "Oscar\nPapa\nQuebec\nRomeo\nSierra\nTango\nUniform\nVictor\nWhiskey\nXray\nYankee\nZulu");

}

static void lv_ta_event_cb(lv_obj_t * ta, lv_event_t e)
{
    if(e == LV_EVENT_FOCUSED) {
        lv_obj_set_height(tv, LV_VER_RES / 2);
        kb = lv_keyboard_create(lv_scr_act(), NULL);
        lv_keyboard_set_ta(kb, ta);
        lv_obj_set_event_cb(kb, lv_kb_event_cb);
        lv_page_focus(t1, ta, LV_ANIM_ON);
    }
}


static void lv_kb_event_cb(lv_obj_t * kb, lv_event_t e)
{
    lv_keyboard_def_event_cb(kb, e);

    if(e == LV_EVENT_CANCEL) {
        lv_obj_set_height(tv, LV_VER_RES);
        lv_obj_del(kb);
    }
}

//
//  lv_obj_t * arc = lv_arc_create(cont, NULL);
//  lv_obj_set_size(arc, 200, 200);
//
//#if 1
//
//  static const char * btnm_map[] = {"Previous", "1", "2", "3", "Next", ""};
//
//
//  lv_obj_t * btnm = lv_btnmatrix_create(cont, NULL);
//  lv_group_add_obj(g1, btnm);
//  lv_coord_t btnm_h = 18 * LV_DPI / 50;
//  lv_obj_set_size(btnm, 7 * btnm_h, btnm_h);
//  lv_btnmatrix_set_map(btnm, btnm_map);
//  lv_btnmatrix_set_btn_ctrl_all(btnm, LV_BTNMATRIX_CTRL_CHECKABLE);
//  lv_btnmatrix_set_one_toggle(btnm, true);
//  lv_btnmatrix_set_btn_width(btnm, 0, 2);
//  lv_btnmatrix_set_btn_width(btnm, 4, 2);
//  lv_btnmatrix_set_btn_ctrl(btnm, 0, LV_BTNMATRIX_CTRL_INACTIVE);
//
//
//  lv_obj_t * h2 = lv_cont_create(t1, h);
//  subtitle = lv_label_create(h2, subtitle);
//  lv_label_set_text(subtitle, "Scrolling");
//
//  lv_obj_t * page = lv_page_create(t1 ,NULL);
//  lv_obj_set_size(page, LV_HOR_RES / 3,lv_obj_get_height(cont));
//  lv_page_set_scroll_propagation(page, true);
//
//  label = lv_label_create(page, NULL);
//  lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
//  lv_obj_set_width(label, lv_page_get_fit_width(page));
//  lv_label_set_text(label ,"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam eu quam lacus. Praesent rhoncus et orci sed vehicula. Etiam ut euismod metus. Etiam consequat orci ac mi dapibus, sed lacinia quam molestie. Cras convallis eros ut est fermentum, non fringilla velit placerat. In hac habitasse platea dictumst. Aliquam nec imperdiet elit, ut euismod orci. Morbi venenatis mattis sem, a lacinia massa ultricies non. Phasellus nec egestas justo. Duis quam mauris, congue vel ultricies vel, eleifend nec arcu. Vivamus ut accumsan purus.");
//
//
//
//
//
//     cont = lv_cont_create(t2, NULL);
//     lv_obj_set_drag(cont, true);
//     lv_cont_set_fit(cont, LV_FIT_TIGHT);
//
//
//
////     lv_group_add_obj(g, btn2);
//#endif
////
//     lv_obj_set_drag(dd, true);
////     lv_group_add_obj(g1, dd);
//
////     lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), NULL);
////     lv_obj_set_pos(btn2, 200, 200);
////     lv_obj_set_drag(btn2, true);
//
//     lv_obj_t * win = lv_win_create(t2, NULL);
//     lv_win_add_btn(win, LV_SYMBOL_CLOSE);
//     lv_win_add_btn(win, LV_SYMBOL_OK);
//
//
//#if 1
//
//     LV_IMG_DECLARE(icon_color);
//     lv_obj_t * img = lv_img_create(t1, NULL);
//     lv_img_set_src(img, &icon_color);
//     lv_theme_apply(img, LV_THEME_CONT);
////     lv_obj_set_style_int(img, LV_IMG_PART_MAIN, LV_STYLE_PAD_LEFT, 0);
////     lv_obj_set_style_int(img, LV_IMG_PART_MAIN, LV_STYLE_PAD_RIGHT, -20);
////     lv_obj_set_style_int(img, LV_IMG_PART_MAIN, LV_STYLE_PAD_TOP, 0);
////     lv_obj_set_style_int(img, LV_IMG_PART_MAIN, LV_STYLE_PAD_BOTTOM, -20);
////     lv_obj_set_style_int(img, LV_IMG_PART_MAIN, LV_STYLE_CLIP_CORNER, 1);
////     lv_obj_set_style_int(img, LV_IMG_PART_MAIN, LV_STYLE_RADIUS, 200);
//
//
////     lv_obj_t * kb = lv_keyboard_create(lv_scr_act(), NULL);
////     lv_group_add_obj(g1, kb);
////     lv_group_focus_obj(kb);
////     lv_spinner_create(lv_scr_act(), NULL);
//
//     lv_gauge_create(win, NULL);
//
//
//     #endif
//
//
//
////     lv_test_tileview_1();
////
////  volatile uint32_t t1 = lv_tick_get();
////   lv_obj_t * cont = lv_cont_create(lv_scr_act(), NULL);
////   lv_obj_set_size(cont, 220, 300);
////   lv_obj_align(cont, NULL, LV_ALIGN_CENTER, 0, 0);
////   lv_cont_set_layout(cont, LV_LAYOUT_PRETTY);
////
////
////    lv_style_t s;
////    lv_style_init(&s);
////
////    lv_style_set_color(&s, LV_STYLE_BORDER_COLOR, LV_COLOR_GREEN);
////    lv_style_set_int(&s, LV_STYLE_LINE_WIDTH, 3);
////    lv_style_set_int(&s, LV_STYLE_LINE_BLEND_MODE, 1);
////    lv_style_set_color(&s, LV_STYLE_LINE_COLOR, LV_COLOR_BLUE);
////    lv_style_set_color(&s, LV_STYLE_BORDER_COLOR, LV_COLOR_GREEN);
////
////    uint16_t i;
////   lv_obj_t * b ;
////   lv_obj_t * l;
////   for(i = 0; i < 40; i++) {
////       b= lv_btn_create(cont, NULL);
//////   lv_obj_set_style_bg_color(b, LV_BTN_PART_MAIN, LV_STYLE_STATE_NORMAL, LV_COLOR_RED);
////   lv_obj_set_style_value_str(b, LV_BTN_PART_MAIN, LV_STYLE_STATE_NORMAL, "xy");
////   lv_obj_set_style_value_ofs_y(b, LV_BTN_PART_MAIN, LV_STYLE_STATE_NORMAL, 0);
//////   lv_obj_set_style_value_ofs_y(b, LV_BTN_PART_MAIN, LV_STYLE_STATE_PRESSED, -15);
//////   lv_obj_set_style_value_ofs_x(b, LV_BTN_PART_MAIN, LV_STYLE_STATE_NORMAL, 0);
//////   lv_obj_set_style_value_ofs_x(b, LV_BTN_PART_MAIN, LV_STYLE_STATE_PRESSED, 10);
////   lv_obj_set_style_value_ofs_y(b, LV_BTN_PART_MAIN, LV_STYLE_STATE_FOCUS, -5);
////   lv_obj_set_style_value_align(b, LV_BTN_PART_MAIN, LV_STYLE_STATE_FOCUS, LV_ALIGN_OUT_TOP_LEFT);
//////        lv_obj_set_size(b, 50, 30);
//////        lv_obj_set_pos(b, (i%3) * 60 + 10, (i/3) * 40  + 10);
////       lv_btn_set_fit(b, LV_FIT_TIGHT);
//////        lv_obj_add_style_class(b, LV_BTN_PART_MAIN, &s);
////
////
////
////        l = lv_label_create(b, NULL);
////       lv_label_set_text_fmt(l, "    ");
////   }
//
////
////   lv_obj_t * l = lv_label_create(lv_scr_act(), NULL);
////   lv_obj_set_style_bg_color(l, LV_LABEL_PART_MAIN, LV_OBJ_STATE_NORMAL,LV_COLOR_RED);
////   lv_obj_set_style_bg_opa(l, LV_LABEL_PART_MAIN, LV_OBJ_STATE_NORMAL,LV_OPA_COVER);
////   lv_obj_set_style_pad_top(l, LV_LABEL_PART_MAIN, LV_OBJ_STATE_NORMAL,50);
////   lv_obj_set_style_pad_bottom(l, LV_LABEL_PART_MAIN, LV_OBJ_STATE_NORMAL,10);
////   lv_obj_set_style_pad_left(l, LV_LABEL_PART_MAIN, LV_OBJ_STATE_NORMAL,20);
////   lv_obj_set_style_pad_right(l, LV_LABEL_PART_MAIN, LV_OBJ_STATE_NORMAL,30);
////   lv_label_set_long_mode(l, LV_LABEL_LONG_CROP);
////   lv_obj_set_width(l, 100);
////   lv_label_set_text(l, "heje huja fogadom");

