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
static void lv_slider_event_cb(lv_obj_t * slider, lv_event_t e);
static void lv_ta_event_cb(lv_obj_t * ta, lv_event_t e);
static void lv_kb_event_cb(lv_obj_t * ta, lv_event_t e);
static void bar_anim(lv_task_t * t);

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
    _lv_obj_set_style_int(tv, LV_TABVIEW_PART_TAB_BG, LV_STYLE_PAD_LEFT, LV_HOR_RES / 2);
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
    lv_slider_set_value(slider, 40, LV_ANIM_OFF);
    lv_obj_set_event_cb(slider, lv_slider_event_cb);

    /*Use the knobs style value the display the current value in focused state*/
    lv_obj_set_style_value_font(slider, LV_SLIDER_PART_KNOB, LV_STATE_NORMAL, LV_THEME_DEFAULT_FONT_SMALL);
    lv_obj_set_style_value_ofs_y(slider, LV_SLIDER_PART_KNOB, LV_STATE_NORMAL, 0);
    lv_obj_set_style_value_opa(slider, LV_SLIDER_PART_KNOB, LV_STATE_NORMAL, LV_OPA_TRANSP);
    lv_obj_set_style_value_ofs_y(slider, LV_SLIDER_PART_KNOB, LV_STATE_FOCUSED, -18);
    lv_obj_set_style_value_opa(slider, LV_SLIDER_PART_KNOB, LV_STATE_FOCUSED, LV_OPA_COVER);
    lv_obj_set_style_transition_time(slider, LV_SLIDER_PART_BG, LV_STATE_FOCUSED, 300);

    slider = lv_slider_create(h, NULL);
    lv_slider_set_type(slider, LV_SLIDER_TYPE_RANGE);
    lv_slider_set_value(slider, 70, LV_ANIM_OFF);
    lv_slider_set_left_value(slider, 30, LV_ANIM_OFF);
    lv_obj_set_style_value_font(slider, LV_SLIDER_PART_INDIC, LV_STATE_NORMAL, LV_THEME_DEFAULT_FONT_SMALL);
    lv_obj_set_event_cb(slider, lv_slider_event_cb);
    lv_event_send(slider, LV_EVENT_VALUE_CHANGED, NULL);      /*To refresh the text*/

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
    _lv_obj_set_style_int(chart, LV_CHART_PART_BG, LV_STYLE_PAD_LEFT, 50);
    _lv_obj_set_style_int(chart, LV_CHART_PART_BG, LV_STYLE_PAD_BOTTOM, 30);
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
    lv_table_set_col_cnt(table1, 3);
    lv_table_set_row_cnt(table1, 7);
    lv_table_set_col_width(table1, 0, 30);
    lv_table_set_col_width(table1, 1, 110);
    lv_table_set_col_width(table1, 2, 110);

    lv_table_set_cell_value(table1, 0, 0, "#");
    lv_table_set_cell_value(table1, 0, 1, "FIRST NAME");
    lv_table_set_cell_value(table1, 0, 2, "LAST NAME");
    lv_table_set_cell_value(table1, 0, 3, "USER NAME");

    lv_table_set_cell_value(table1, 1, 0, "1");
    lv_table_set_cell_value(table1, 1, 1, "Mark");
    lv_table_set_cell_value(table1, 1, 2, "Otto");

    lv_table_set_cell_value(table1, 2, 0, "2");
    lv_table_set_cell_value(table1, 2, 1, "Jacob");
    lv_table_set_cell_value(table1, 2, 2, "Thoronton");

    lv_table_set_cell_value(table1, 3, 0, "3");
    lv_table_set_cell_value(table1, 3, 1, "John");
    lv_table_set_cell_value(table1, 3, 2, "Doe");

    lv_table_set_cell_value(table1, 4, 0, "4");
    lv_table_set_cell_value(table1, 4, 1, "Emily");
    lv_table_set_cell_value(table1, 4, 2, "Smith");

    lv_table_set_cell_value(table1, 5, 0, "5");
    lv_table_set_cell_value(table1, 5, 1, "Samantha");
    lv_table_set_cell_value(table1, 5, 2, "Taylor");

    lv_table_set_cell_value(table1, 6, 0, "6");
    lv_table_set_cell_value(table1, 6, 1, "George");
    lv_table_set_cell_value(table1, 6, 2, "Black");

    lv_obj_t * arc = lv_arc_create(parent, NULL);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_arc_set_angles(arc, 270, 30);
    lv_obj_set_size(arc, LV_DPI * 2, LV_DPI * 2);

    lv_obj_t * lmeter = lv_linemeter_create(parent, NULL);
    lv_obj_set_size(lmeter, LV_DPI * 2, LV_DPI * 2);
    lv_linemeter_set_value(lmeter, 50);

    lv_gauge_create(parent, NULL);

    /*Create a bar and use the backgrounds value style property to display the current value*/
    lv_obj_t * bar = lv_bar_create(parent, NULL);
    lv_obj_set_style_value_font(bar, LV_BAR_PART_BG, LV_STATE_NORMAL, LV_THEME_DEFAULT_FONT_SMALL);

    lv_obj_t * h = lv_cont_create(parent, NULL);
    lv_cont_set_layout(h, LV_LAYOUT_ROW_MID);
    lv_cont_set_fit(h, LV_FIT_TIGHT);
    lv_obj_add_style(h, LV_CONT_PART_MAIN, &style_box);
    lv_obj_set_drag_parent(h, true);
    lv_obj_set_style_value_str(h, LV_CONT_PART_MAIN, LV_STATE_NORMAL, "LEDs");

    lv_obj_t * led = lv_led_create(h, NULL);
    lv_led_off(led);

    led = lv_led_create(h, NULL);
    lv_led_on(led);

    lv_task_create(bar_anim, 100, LV_TASK_PRIO_LOW, bar);
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

static void lv_slider_event_cb(lv_obj_t * slider, lv_event_t e)
{
    if(e == LV_EVENT_VALUE_CHANGED) {
        if(lv_slider_get_type(slider) == LV_SLIDER_TYPE_NORMAL) {
            static char buf[16];
            lv_snprintf(buf, sizeof(buf), "%d", lv_slider_get_value(slider));
            lv_obj_set_style_value_str(slider, LV_SLIDER_PART_KNOB, LV_STATE_NORMAL, buf);
        } else {
            static char buf[32];
            lv_snprintf(buf, sizeof(buf), "%d-%d", lv_slider_get_left_value(slider), lv_slider_get_value(slider));
            lv_obj_set_style_value_str(slider, LV_SLIDER_PART_INDIC, LV_STATE_NORMAL, buf);
        }

    }

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


static void bar_anim(lv_task_t * t)
{
    static uint32_t x = 0;
    lv_obj_t * bar = t->user_data;

    static char buf[64];
    lv_snprintf(buf, sizeof(buf), "Copying %d/%d", x, lv_bar_get_max_value(bar));
    lv_obj_set_style_value_str(bar, LV_BAR_PART_BG, LV_STATE_NORMAL, buf);

    lv_bar_set_value(bar, x, LV_ANIM_OFF);
    x++;
    if(x > lv_bar_get_max_value(bar)) x = 0;

}
