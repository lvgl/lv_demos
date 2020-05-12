/**
 * @file lv_demo_priner.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_printer_scr.h"
#include "lv_demo_printer_theme.h"

/*********************
 *      DEFINES
 *********************/
/*Bg positions*/
#define LV_DEMO_PRINTER_BG_NONE (-LV_VER_RES)
#define LV_DEMO_PRINTER_BG_FULL 0
#define LV_DEMO_PRINTER_BG_NORMAL (-2 * (LV_VER_RES / 3))

/*Sizes*/
#define LV_DEMO_PRINTER_BTN_H   (LV_VER_RES / 10)
#define LV_DEMO_PRINTER_BTN_W   (LV_HOR_RES / 5)

/*Animations*/
#define LV_DEMO_PRINTER_ANIM_Y (LV_VER_RES / 20)
#define LV_DEMO_PRINTER_ANIM_DELAY (40)
#define LV_DEMO_PRINTER_ANIM_TIME  (150)
#define LV_DEMO_PRINTER_ANIM_TIME_BG  (200)

/*Padding*/
#define LV_DEMO_PRINTER_TITLE_PAD (LV_VER_RES / 20)

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void home_open(uint32_t delay);
static void print_open(uint32_t delay);
static void usb_open(uint32_t delay);
static void mobile_open(uint32_t delay);
static void internet_open(uint32_t delay);
static void scan1_open(uint32_t delay);
static void scan2_open(uint32_t delay);

LV_EVENT_CB_DECLARE(copy_icon_event_cb);
LV_EVENT_CB_DECLARE(scan_icon_event_cb);
LV_EVENT_CB_DECLARE(scan_next_event_cb);
LV_EVENT_CB_DECLARE(usb_icon_event_cb);
LV_EVENT_CB_DECLARE(mobile_icon_event_cb);
LV_EVENT_CB_DECLARE(mobile_cancel_event_cb);
LV_EVENT_CB_DECLARE(internet_icon_event_cb);
LV_EVENT_CB_DECLARE(internet_cancel_event_cb);

static lv_obj_t * add_icon(lv_obj_t * parent, const void * src,
        const char * txt);
static lv_obj_t * add_title(const char * txt);

static void lv_demo_printer_anim_bg(uint32_t delay, lv_color_t color,
        uint32_t y);
static void lv_demo_printer_anim_in(lv_obj_t * obj, uint32_t delay);
static void lv_demo_printer_anim_out(lv_obj_t * obj, uint32_t delay);
static void lv_demo_printer_anim_out_all(lv_obj_t * obj, uint32_t delay);
static void lv_demo_printer_anim_in_all(lv_obj_t * obj, uint32_t delay);
static void anim_bg_color_cb(lv_anim_t * a, lv_anim_value_t v);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * bg_top;
static lv_obj_t * bg_bottom;
static lv_obj_t * scan_img;
static lv_color_t bg_color_prev;
static lv_color_t bg_color_act;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_printer(void) {

    bg_color_prev = LV_DEMO_PRINTER_BLUE;
    bg_color_act = LV_DEMO_PRINTER_BLUE;

    lv_theme_t * th = lv_demo_printer_theme_init(LV_COLOR_BLACK, LV_COLOR_BLACK,
            0, &lv_font_montserrat_14, &lv_font_montserrat_20,
            &lv_font_montserrat_24, &lv_font_montserrat_30);
    lv_theme_set_act(th);

    lv_obj_t * scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);

    bg_top = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_clean_style_list(bg_top, LV_OBJ_PART_MAIN);
    lv_obj_set_style_local_bg_opa(bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,
            LV_OPA_COVER);
    lv_obj_set_style_local_bg_color(bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,
            LV_DEMO_PRINTER_BLUE);
    lv_obj_set_size(bg_top, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_y(bg_top, LV_DEMO_PRINTER_BG_NONE);

    home_open(0);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void home_open(uint32_t delay) {
    lv_obj_t * title = add_title("22 April 2020 15:36");
    lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_RIGHT, -LV_DEMO_PRINTER_TITLE_PAD,
            LV_DEMO_PRINTER_TITLE_PAD);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in_all(title, delay);

    lv_coord_t box_w = (LV_HOR_RES * 9) / 10;
    lv_obj_t * box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(box, box_w, LV_VER_RES / 2);
    lv_obj_align(box, NULL, LV_ALIGN_CENTER, 0, 0);

    LV_IMG_DECLARE(lv_demo_printer_img_scan);

    lv_obj_t * icon;

    icon = add_icon(box, &lv_demo_printer_img_scan, "COPY");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 1 * box_w / 8, 0);
    lv_obj_set_event_cb(icon, copy_icon_event_cb);

    icon = add_icon(box, &lv_demo_printer_img_scan, "SCAN");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 3 * box_w / 8, 0);
    lv_obj_set_event_cb(icon, scan_icon_event_cb);

    icon = add_icon(box, &lv_demo_printer_img_scan, "PRINT");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 5 * box_w / 8, 0);
    lv_obj_set_event_cb(icon, copy_icon_event_cb);

    icon = add_icon(box, &lv_demo_printer_img_scan, "SETUP");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 7 * box_w / 8, 0);
    lv_obj_set_event_cb(icon, copy_icon_event_cb);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in_all(box, delay);

    box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(box, LV_HOR_RES * 6 / 10, LV_VER_RES / 6);
    lv_obj_align(box, NULL, LV_ALIGN_IN_BOTTOM_LEFT, LV_HOR_RES / 20,
            - LV_HOR_RES / 40);
    lv_obj_set_style_local_value_str(box, LV_CONT_PART_MAIN, LV_STATE_DEFAULT,
            "What do you want to do today?");

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in_all(box, delay);

    box = lv_obj_create(lv_scr_act(), NULL);
    box_w = LV_HOR_RES / 4;
    lv_obj_set_size(box, LV_HOR_RES / 4, LV_VER_RES / 6);
    lv_obj_align(box, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, - LV_HOR_RES / 20,
            - LV_HOR_RES / 40);

    lv_obj_t * bar = lv_bar_create(box, NULL);
    lv_obj_set_style_local_bg_color(bar, LV_BAR_PART_INDIC, LV_STATE_DEFAULT,
            lv_color_hex(0x00ffff));
    lv_obj_set_size(bar, LV_HOR_RES / 30, LV_VER_RES / 10);
    lv_obj_align_origo(bar, NULL, LV_ALIGN_IN_LEFT_MID, 1 * box_w / 8, 0);
    lv_bar_set_value(bar, 60, LV_ANIM_ON);

    bar = lv_bar_create(box, NULL);
    lv_obj_set_style_local_bg_color(bar, LV_BAR_PART_INDIC, LV_STATE_DEFAULT,
            lv_color_hex(0xff00ff));
    lv_obj_set_size(bar, LV_HOR_RES / 30, LV_VER_RES / 10);
    lv_obj_align_origo(bar, NULL, LV_ALIGN_IN_LEFT_MID, 3 * box_w / 8, 0);
    lv_bar_set_value(bar, 30, LV_ANIM_ON);

    bar = lv_bar_create(box, NULL);
    lv_obj_set_style_local_bg_color(bar, LV_BAR_PART_INDIC, LV_STATE_DEFAULT,
            lv_color_hex(0xffff00));
    lv_obj_set_size(bar, LV_HOR_RES / 30, LV_VER_RES / 10);
    lv_obj_align_origo(bar, NULL, LV_ALIGN_IN_LEFT_MID, 5 * box_w / 8, 0);
    lv_bar_set_value(bar, 80, LV_ANIM_ON);

    bar = lv_bar_create(box, NULL);
    lv_obj_set_style_local_bg_color(bar, LV_BAR_PART_INDIC, LV_STATE_DEFAULT,
            LV_COLOR_BLACK);
    lv_obj_set_size(bar, LV_HOR_RES / 30, LV_VER_RES / 10);
    lv_obj_align_origo(bar, NULL, LV_ALIGN_IN_LEFT_MID, 7 * box_w / 8, 0);
    lv_bar_set_value(bar, 20, LV_ANIM_ON);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in_all(box, delay);

    lv_demo_printer_anim_bg(0, LV_DEMO_PRINTER_BLUE, LV_DEMO_PRINTER_BG_NORMAL);
}

LV_EVENT_CB_DECLARE(copy_icon_event_cb)
{
    if(e == LV_EVENT_CLICKED) {
       lv_demo_printer_anim_out_all(lv_scr_act(), 0);
       print_open(200);
    }
}


LV_EVENT_CB_DECLARE(scan_icon_event_cb) {
    if (e == LV_EVENT_CLICKED) {
        lv_demo_printer_anim_out_all(lv_scr_act(), 0);
        scan1_open(200);
    }
}

static void print_open(uint32_t delay) {
    lv_obj_t * title = add_title("PRINT MENU");
    lv_demo_printer_anim_in_all(title, delay);

    lv_coord_t box_w = (LV_HOR_RES * 9) / 10;
    lv_obj_t * box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(box, box_w, LV_VER_RES / 2);
    lv_obj_align(box, NULL, LV_ALIGN_CENTER, 0, 0);

    LV_IMG_DECLARE(lv_demo_printer_img_scan);

    lv_obj_t * icon;

    icon = add_icon(box, &lv_demo_printer_img_scan, "USB");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 1 * box_w / 6, 0);
    lv_obj_set_event_cb(icon, usb_icon_event_cb);

    icon = add_icon(box, &lv_demo_printer_img_scan, "MOBILE");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 3 * box_w / 6, 0);
    lv_obj_set_event_cb(icon, mobile_icon_event_cb);

    icon = add_icon(box, &lv_demo_printer_img_scan, "INTERNET");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 5 * box_w / 6, 0);
    lv_obj_set_event_cb(icon, internet_icon_event_cb);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in_all(box, delay);

    box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(box, box_w, LV_VER_RES / 6);
    lv_obj_align(box, NULL, LV_ALIGN_IN_BOTTOM_LEFT, LV_HOR_RES / 20,
            - LV_HOR_RES / 40);
    lv_obj_set_style_local_value_str(box, LV_CONT_PART_MAIN, LV_STATE_DEFAULT,
            "From where do you want to print?");

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in_all(box, delay);

    lv_demo_printer_anim_bg(0, LV_DEMO_PRINTER_BLUE, LV_DEMO_PRINTER_BG_NORMAL);
}

LV_EVENT_CB_DECLARE(usb_icon_event_cb)
{
    if (e == LV_EVENT_CLICKED) {
        lv_demo_printer_anim_out_all(lv_scr_act(), 0);
        usb_open(200);
    }
}


static void usb_open(uint32_t delay) {
    lv_obj_t * title = add_title("PRINTING FROM USB DRIVE");
    lv_demo_printer_anim_in_all(title, delay);

    lv_coord_t box_w = (LV_HOR_RES * 5) / 10;
    lv_obj_t * list = lv_list_create(lv_scr_act(), NULL);
    lv_obj_set_size(list, box_w, LV_VER_RES / 2);
    lv_obj_align(list, NULL, LV_ALIGN_IN_TOP_LEFT, LV_HOR_RES / 20, LV_VER_RES / 5);

    const char * dummy_file_list[] = { "File 1", "File 1", "File 1", "File 1",
                                    "File 1", "File 1", "File 1", "File 1", "File 1", "File 1",
                                    "File 1", "File 1", "File 1", "File 1", "File 1", "File 1",
                                    "File 1", "File 1", "File 1", "File 10" };


    uint32_t i;
    for(i = 0; i < sizeof(dummy_file_list) / sizeof(dummy_file_list[0]); i++) {
        lv_obj_t * btn = lv_list_add_btn(list, LV_SYMBOL_FILE, dummy_file_list[i]);
        lv_btn_set_checkable(btn, true);
    }

    lv_obj_t * dropdown_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(dropdown_box, box_w, LV_VER_RES / 5);
    lv_obj_align(dropdown_box, list, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_HOR_RES / 30);

    lv_obj_t * dropdown = lv_dropdown_create(dropdown_box, NULL);
    lv_obj_align(dropdown, NULL, LV_ALIGN_IN_LEFT_MID, LV_HOR_RES / 60, 0);
    lv_dropdown_set_max_height(dropdown, LV_VER_RES / 3);
    lv_dropdown_set_options_static(dropdown, "High quality\nNormal quality\nDraft");
    lv_obj_set_width(dropdown, (box_w - 3 * LV_HOR_RES / 60) / 2);

    dropdown = lv_dropdown_create(dropdown_box, dropdown);
    lv_obj_align(dropdown, NULL, LV_ALIGN_IN_RIGHT_MID, - LV_HOR_RES / 60, 0);
    lv_dropdown_set_options_static(dropdown, "100 DPI\n200 DPI\n300 DPI\n400 DPI\n500 DPI\n1500 DPI");

    box_w = (LV_HOR_RES * 4) / 10 - LV_HOR_RES / 20;
    lv_obj_t * settings_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(settings_box, box_w, LV_VER_RES / 2);
    lv_obj_align(settings_box, list, LV_ALIGN_OUT_RIGHT_TOP, LV_HOR_RES / 20, 0);

    lv_obj_t * numbox = lv_cont_create(settings_box, NULL);
    lv_theme_apply(numbox, LV_DEMO_PRINTER_THEME_BOX_BORDER);
    lv_obj_set_size(numbox, LV_HOR_RES / 7, LV_HOR_RES / 13);
    lv_obj_align(numbox, settings_box, LV_ALIGN_IN_TOP_MID, 0, LV_VER_RES / 10);
    lv_obj_set_style_local_value_str(numbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, "Copies");
    lv_obj_set_style_local_value_align(numbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_ALIGN_OUT_TOP_MID);
    lv_obj_set_style_local_value_ofs_y(numbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, - LV_VER_RES / 50);
    lv_obj_set_style_local_value_font(numbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_subtitle());
    lv_cont_set_layout(numbox, LV_LAYOUT_CENTER);

    lv_obj_t * copytxt = lv_label_create(numbox, NULL);
    lv_label_set_text(copytxt, "12");
    lv_obj_set_style_local_text_font(copytxt, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());

    lv_obj_t * btn = lv_btn_create(settings_box, NULL);
    lv_obj_set_size(btn, LV_HOR_RES / 13, LV_HOR_RES / 13);
    lv_obj_align(btn, numbox, LV_ALIGN_OUT_LEFT_MID, - LV_VER_RES / 60, 0);
    lv_obj_set_style_local_value_str(btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_DOWN);

    lv_obj_t * sw = lv_switch_create(settings_box, NULL);
    lv_obj_set_size(sw, LV_HOR_RES / 10, LV_VER_RES / 12);
    lv_obj_align(sw, btn, LV_ALIGN_OUT_BOTTOM_LEFT, LV_HOR_RES / 50, LV_VER_RES / 7);
    lv_obj_set_style_local_value_ofs_y(sw, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, - LV_VER_RES / 50);
    lv_obj_set_style_local_value_align(sw, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_ALIGN_OUT_TOP_MID);
    lv_obj_set_style_local_value_str(sw, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, "Color");
    lv_obj_set_style_local_value_font(sw, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_subtitle());

    btn = lv_btn_create(settings_box, btn);
    lv_obj_align(btn, numbox, LV_ALIGN_OUT_RIGHT_MID, LV_VER_RES / 60, 0);
    lv_obj_set_style_local_value_str(btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_UP);

    sw = lv_switch_create(settings_box, sw);
    lv_obj_align(sw, btn, LV_ALIGN_OUT_BOTTOM_RIGHT, - LV_HOR_RES / 50, LV_VER_RES / 7);
    lv_obj_set_style_local_value_str(sw, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, "Vertical");

    lv_obj_t * print_btn = lv_btn_create(lv_scr_act(), NULL);
    lv_theme_apply(print_btn, LV_DEMO_PRINTER_THEME_BTN_CIRCLE);
    lv_obj_set_width(print_btn, box_w);

    lv_coord_t btn_ofs_y = (lv_obj_get_height(dropdown_box) - lv_obj_get_height(print_btn)) / 2;
    lv_obj_align(print_btn, settings_box, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_HOR_RES / 30 + btn_ofs_y);
    lv_obj_set_style_local_value_str(print_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, "START PRINTING");
    lv_obj_set_style_local_value_font(print_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_subtitle());

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in(list, delay);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in(settings_box, delay);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in(dropdown_box, delay);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in(print_btn, delay);

    lv_demo_printer_anim_bg(0, LV_DEMO_PRINTER_BLUE, LV_DEMO_PRINTER_BG_NORMAL);

}

LV_EVENT_CB_DECLARE(mobile_icon_event_cb)
{
    if (e == LV_EVENT_CLICKED) {
        lv_demo_printer_anim_out_all(lv_scr_act(), 0);
        mobile_open(200);
    }
}

static void mobile_open(uint32_t delay)
{
    lv_demo_printer_anim_bg(0, LV_DEMO_PRINTER_BLUE, LV_DEMO_PRINTER_BG_FULL);

    lv_obj_t * txt = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(txt, "Put you phone near to the printer");
    lv_theme_apply(txt, LV_DEMO_PRINTER_THEME_LABEL_WHITE);
    lv_obj_align(txt, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);
    lv_theme_apply(btn, LV_DEMO_PRINTER_THEME_BTN_BORDER);
    lv_obj_set_size(btn, LV_DEMO_PRINTER_BTN_W, LV_DEMO_PRINTER_BTN_H);
    lv_obj_align(btn, txt, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_VER_RES / 20);
    lv_obj_set_style_local_value_str(btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
            "Cancel");
    lv_obj_set_event_cb(btn, mobile_cancel_event_cb);

    lv_demo_printer_anim_in_all(txt, delay);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in_all(btn, delay);
}

LV_EVENT_CB_DECLARE(mobile_cancel_event_cb) {
    if (e == LV_EVENT_CLICKED) {
        lv_demo_printer_anim_out_all(lv_scr_act(), 0);
        print_open(200);
    }
}

LV_EVENT_CB_DECLARE(internet_icon_event_cb) {
    if (e == LV_EVENT_CLICKED) {
        lv_demo_printer_anim_out_all(lv_scr_act(), 0);
        internet_open(200);
    }
}

static void internet_open(uint32_t delay) {
    lv_demo_printer_anim_bg(0, LV_DEMO_PRINTER_RED, LV_DEMO_PRINTER_BG_FULL);

    lv_obj_t * txt = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(txt, "No internet connection");
    lv_theme_apply(txt, LV_DEMO_PRINTER_THEME_LABEL_WHITE);
    lv_obj_align(txt, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);
    lv_theme_apply(btn, LV_DEMO_PRINTER_THEME_BTN_BORDER);
    lv_obj_set_size(btn, LV_DEMO_PRINTER_BTN_W, LV_DEMO_PRINTER_BTN_H);
    lv_obj_align(btn, txt, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_VER_RES / 20);
    lv_obj_set_style_local_value_str(btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT,
            "Cancel");
    lv_obj_set_event_cb(btn, internet_cancel_event_cb);

    lv_demo_printer_anim_in_all(txt, delay);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in_all(btn, delay);
}

LV_EVENT_CB_DECLARE(internet_cancel_event_cb) {
    if (e == LV_EVENT_CLICKED) {
        lv_demo_printer_anim_out_all(lv_scr_act(), 0);
        print_open(200);
    }
}


static void scan1_open(uint32_t delay)
{
    lv_obj_t * title = add_title("SCANNING IMAGE");
    lv_demo_printer_anim_in(title, delay);

    LV_IMG_DECLARE(wp1);
    lv_coord_t box_w = (LV_HOR_RES * 5) / 10;
    scan_img = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(scan_img, &wp1);
    lv_obj_align(scan_img, NULL, LV_ALIGN_IN_TOP_LEFT, 40, 100);
    lv_obj_set_style_local_image_recolor_opa(scan_img, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 170);
    lv_obj_set_style_local_radius(scan_img, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_local_clip_corner(scan_img, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, true);

    box_w = (LV_HOR_RES * 2) / 10;
    lv_obj_t * settings_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(settings_box, box_w, 225);
    lv_obj_align(settings_box, scan_img, LV_ALIGN_OUT_RIGHT_TOP, 40, 0);

    lv_obj_t * next_btn = lv_btn_create(lv_scr_act(), NULL);
    lv_theme_apply(next_btn, LV_DEMO_PRINTER_THEME_BTN_CIRCLE);
    lv_obj_set_width(next_btn, box_w);
    lv_obj_set_event_cb(next_btn, scan_next_event_cb);
    lv_obj_align(next_btn, settings_box, LV_ALIGN_OUT_BOTTOM_MID, 0, 40);
    lv_obj_set_style_local_value_str(next_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, "NEXT");
    lv_obj_set_style_local_value_font(next_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_subtitle());

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in(scan_img, delay);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in(settings_box, delay);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in(next_btn, delay);

    lv_demo_printer_anim_bg(0, LV_DEMO_PRINTER_BLUE, LV_DEMO_PRINTER_BG_NORMAL);

}

LV_EVENT_CB_DECLARE(scan_next_event_cb)
{
    if (e == LV_EVENT_CLICKED) {
        lv_demo_printer_anim_out_all(lv_scr_act(), 0);
        scan2_open(400);
    }
}

static void scan2_open(uint32_t delay)
{
    lv_obj_t * title = add_title("SCANNING IMAGE");
    lv_demo_printer_anim_in_all(title, delay);

    lv_coord_t box_w = 400;
    lv_img_set_pivot(scan_img, 0, 0);
    lv_img_set_antialias(scan_img, false);
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, scan_img);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_img_set_zoom);
    lv_anim_set_values(&a, LV_IMG_ZOOM_NONE, 190);
    lv_anim_set_time(&a, 200);
    lv_anim_set_delay(&a, 200);
    lv_anim_start(&a);
    scan_img = NULL;    /*To allow anim out*/

    lv_obj_t * dropdown_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(dropdown_box, box_w, LV_VER_RES / 5);
    lv_obj_align(dropdown_box, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 40, -20);

    lv_obj_t * dropdown = lv_dropdown_create(dropdown_box, NULL);
    lv_obj_align(dropdown, NULL, LV_ALIGN_IN_LEFT_MID, LV_HOR_RES / 60, 0);
    lv_dropdown_set_max_height(dropdown, LV_VER_RES / 3);
    lv_dropdown_set_options_static(dropdown, "High quality\nNormal quality\nDraft");
    lv_obj_set_width(dropdown, (box_w - 3 * LV_HOR_RES / 60) / 2);

    dropdown = lv_dropdown_create(dropdown_box, dropdown);
    lv_obj_align(dropdown, NULL, LV_ALIGN_IN_RIGHT_MID, - LV_HOR_RES / 60, 0);
    lv_dropdown_set_options_static(dropdown, "100 DPI\n200 DPI\n300 DPI\n400 DPI\n500 DPI\n1500 DPI");

    box_w = (LV_HOR_RES * 4) / 10 - LV_HOR_RES / 20;
    lv_obj_t * settings_box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(settings_box, box_w, LV_VER_RES / 2);
    lv_obj_align(settings_box, NULL, LV_ALIGN_IN_TOP_RIGHT, -LV_HOR_RES / 20, LV_VER_RES / 5);

    lv_obj_t * numbox = lv_cont_create(settings_box, NULL);
    lv_theme_apply(numbox, LV_DEMO_PRINTER_THEME_BOX_BORDER);
    lv_obj_set_size(numbox, LV_HOR_RES / 7, LV_HOR_RES / 13);
    lv_obj_align(numbox, settings_box, LV_ALIGN_IN_TOP_MID, 0, LV_VER_RES / 10);
    lv_obj_set_style_local_value_str(numbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, "Copies");
    lv_obj_set_style_local_value_align(numbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_ALIGN_OUT_TOP_MID);
    lv_obj_set_style_local_value_ofs_y(numbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, - LV_VER_RES / 50);
    lv_obj_set_style_local_value_font(numbox, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_subtitle());
    lv_cont_set_layout(numbox, LV_LAYOUT_CENTER);

    lv_obj_t * copytxt = lv_label_create(numbox, NULL);
    lv_label_set_text(copytxt, "12");
    lv_obj_set_style_local_text_font(copytxt, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());

    lv_obj_t * btn = lv_btn_create(settings_box, NULL);
    lv_obj_set_size(btn, LV_HOR_RES / 13, LV_HOR_RES / 13);
    lv_obj_align(btn, numbox, LV_ALIGN_OUT_LEFT_MID, - LV_VER_RES / 60, 0);
    lv_obj_set_style_local_value_str(btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_DOWN);

    lv_obj_t * sw = lv_switch_create(settings_box, NULL);
    lv_obj_set_size(sw, LV_HOR_RES / 10, LV_VER_RES / 12);
    lv_obj_align(sw, btn, LV_ALIGN_OUT_BOTTOM_LEFT, LV_HOR_RES / 50, LV_VER_RES / 7);
    lv_obj_set_style_local_value_ofs_y(sw, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, - LV_VER_RES / 50);
    lv_obj_set_style_local_value_align(sw, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_ALIGN_OUT_TOP_MID);
    lv_obj_set_style_local_value_str(sw, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, "Color");
    lv_obj_set_style_local_value_font(sw, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_subtitle());

    btn = lv_btn_create(settings_box, btn);
    lv_obj_align(btn, numbox, LV_ALIGN_OUT_RIGHT_MID, LV_VER_RES / 60, 0);
    lv_obj_set_style_local_value_str(btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_UP);

    sw = lv_switch_create(settings_box, sw);
    lv_obj_align(sw, btn, LV_ALIGN_OUT_BOTTOM_RIGHT, - LV_HOR_RES / 50, LV_VER_RES / 7);
    lv_obj_set_style_local_value_str(sw, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, "Vertical");

    lv_obj_t * print_btn = lv_btn_create(lv_scr_act(), NULL);
    lv_theme_apply(print_btn, LV_DEMO_PRINTER_THEME_BTN_CIRCLE);
    lv_obj_set_width(print_btn, box_w);
    lv_coord_t btn_ofs_y = (lv_obj_get_height(dropdown_box) - lv_obj_get_height(print_btn)) / 2;
    lv_obj_align(print_btn, settings_box, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_HOR_RES / 30 + btn_ofs_y);
    lv_obj_set_style_local_value_str(print_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, "START PRINTING");
    lv_obj_set_style_local_value_font(print_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_subtitle());

//    delay += LV_DEMO_PRINTER_ANIM_DELAY;
//    lv_demo_printer_anim_in(img, delay);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in(settings_box, delay);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in(dropdown_box, delay);

    delay += LV_DEMO_PRINTER_ANIM_DELAY;
    lv_demo_printer_anim_in(print_btn, delay);

    lv_demo_printer_anim_bg(0, LV_DEMO_PRINTER_BLUE, LV_DEMO_PRINTER_BG_NORMAL);

}


static lv_obj_t * add_icon(lv_obj_t * parent, const void * src,
        const char * txt) {
    lv_obj_t * icon = lv_img_create(parent, NULL);
    lv_theme_apply(icon, LV_DEMO_PRINTER_THEME_ICON);
    lv_img_set_src(icon, src);
    lv_obj_set_click(icon, true);
    lv_img_set_antialias(icon, false);

    lv_obj_set_style_local_value_str(icon, LV_IMG_PART_MAIN, LV_STATE_DEFAULT,
            txt);

    return icon;
}

static lv_obj_t * add_title(const char * txt) {
    lv_obj_t * title = lv_label_create(lv_scr_act(), NULL);
    lv_theme_apply(title, LV_DEMO_PRINTER_THEME_TITLE);
    lv_label_set_text(title, txt);
    lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 0,
            LV_DEMO_PRINTER_TITLE_PAD);
    return title;
}

static void lv_demo_printer_anim_bg(uint32_t delay, lv_color_t color, uint32_t y)
{
    lv_color_t act_color = lv_obj_get_style_bg_color(bg_top, LV_OBJ_PART_MAIN);
    if(y == lv_obj_get_y(bg_top) && act_color.full == color.full) return;

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, bg_top);
    lv_anim_set_time(&a, LV_DEMO_PRINTER_ANIM_TIME_BG);
    lv_anim_set_delay(&a, delay);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_y);
    lv_anim_set_values(&a, lv_obj_get_y(bg_top), y);
    lv_anim_start(&a);

    bg_color_prev = bg_color_act;
    bg_color_act = color;

    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) anim_bg_color_cb);
    lv_anim_set_values(&a, 0, 255);
    lv_anim_start(&a);

}

static void lv_demo_printer_anim_in(lv_obj_t * obj, uint32_t delay) {
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_time(&a, LV_DEMO_PRINTER_ANIM_TIME);
    lv_anim_set_delay(&a, delay);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_y);
    lv_anim_set_values(&a, lv_obj_get_y(obj) - LV_DEMO_PRINTER_ANIM_Y,
            lv_obj_get_y(obj));
    lv_anim_start(&a);

    lv_obj_fade_in(obj, LV_DEMO_PRINTER_ANIM_TIME, delay);
}

static void lv_demo_printer_anim_out(lv_obj_t * obj, uint32_t delay) {
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_time(&a, LV_DEMO_PRINTER_ANIM_TIME);
    lv_anim_set_delay(&a, delay);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_y);
    lv_anim_set_values(&a, lv_obj_get_y(obj),
            lv_obj_get_y(obj) + LV_DEMO_PRINTER_ANIM_Y);
    lv_anim_set_ready_cb(&a, lv_obj_del_anim_ready_cb);
    lv_anim_start(&a);

    lv_obj_fade_out(obj, LV_DEMO_PRINTER_ANIM_TIME - 50, delay + 50);
}

static void lv_demo_printer_anim_out_all(lv_obj_t * obj, uint32_t delay) {
    lv_obj_t * child = lv_obj_get_child_back(obj, NULL);
    while(child) {
        if(child != scan_img && child != bg_top && child != bg_bottom && child != lv_scr_act()) {
            lv_demo_printer_anim_out(child, delay);
            delay += LV_DEMO_PRINTER_ANIM_DELAY;
        }
        child = lv_obj_get_child_back(obj, child);
    }
}

static void lv_demo_printer_anim_in_all(lv_obj_t * obj, uint32_t delay) {
    if (obj != bg_top && obj != bg_bottom && obj != lv_scr_act()) {
        lv_demo_printer_anim_in(obj, delay);
        delay += LV_DEMO_PRINTER_ANIM_DELAY;
    }

    lv_obj_t * child = lv_obj_get_child_back(obj, NULL);

    while (child) {
        delay += LV_DEMO_PRINTER_ANIM_DELAY;
        lv_demo_printer_anim_in_all(child, delay);
        child = lv_obj_get_child_back(obj, child);
    }

}

static void anim_bg_color_cb(lv_anim_t * a, lv_anim_value_t v) {
    lv_color_t c = lv_color_mix(bg_color_act, bg_color_prev, v);
    lv_obj_set_style_local_bg_color(bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, c);
}

