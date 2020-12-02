/**
 * @file lv_demo_keypad_encoder.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_examples.h"
#include "lv_demo_keypad_encoder.h"
#if LV_EX_KEYBOARD
#include "lv_drivers/indev/keyboard.h"
#endif
#if LV_EX_MOUSEWHEEL
#include "lv_drivers/indev/mousewheel.h"
#endif

#if LV_USE_DEMO_KEYPAD_AND_ENCODER

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void selectors_create(lv_obj_t * parent);
static void text_input_create(lv_obj_t * parent);
static void msgbox_create(void);

static void msgbox_event_cb(lv_obj_t * msgbox, lv_event_t e);
static void tv_event_cb(lv_obj_t * ta, lv_event_t e);
static void ta_event_cb(lv_obj_t * ta, lv_event_t e);
static void kb_event_cb(lv_obj_t * kb, lv_event_t e);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_group_t*  g;
static lv_obj_t * tv;
static lv_obj_t * t1;
static lv_obj_t * t2;

struct {
    lv_obj_t * btn;
    lv_obj_t * cb;
    lv_obj_t * slider;
    lv_obj_t * sw;
    lv_obj_t * spinbox;
    lv_obj_t * dropdown;
    lv_obj_t * roller;
    lv_obj_t * list_btn[7];
}selector_objs;

struct {
    lv_obj_t * ta1;
    lv_obj_t * ta2;
    lv_obj_t * kb;
}textinput_objs;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

LV_EVENT_CB_DECLARE(dd_enc)
{
    if(e == LV_EVENT_VALUE_CHANGED) {
        printf("chg\n");
    }
}

void lv_demo_keypad_encoder(void)
{
    g = lv_group_create();

#if LV_EX_KEYBOARD
    lv_indev_drv_t kb_drv;
    lv_indev_drv_init(&kb_drv);
    kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    kb_drv.read_cb = keyboard_read;
    lv_indev_t * kb_indev = lv_indev_drv_register(&kb_drv);
    lv_indev_set_group(kb_indev, g);
#endif

#if LV_EX_MOUSEWHEEL
    lv_indev_drv_t enc_drv;
    lv_indev_drv_init(&enc_drv);
    enc_drv.type = LV_INDEV_TYPE_ENCODER;
    enc_drv.read_cb = mousewheel_read;
    lv_indev_t * enc_indev = lv_indev_drv_register(&enc_drv);
    lv_indev_set_group(enc_indev, g);
#endif

    tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, LV_DPI / 2);
    lv_obj_set_event_cb(tv, tv_event_cb);

    t1 = lv_tabview_add_tab(tv, "Selectors");
    t2 = lv_tabview_add_tab(tv, "Text input");

    lv_group_add_obj(g, lv_tabview_get_tab_btns(tv));

    selectors_create(t1);
    text_input_create(t2);

    msgbox_create();
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void selectors_create(lv_obj_t * parent)
{
    lv_obj_set_flex_dir(parent, LV_FLEX_DIR_COLUMN);
    lv_obj_set_flex_place(parent, LV_FLEX_PLACE_START, LV_FLEX_PLACE_CENTER);
    lv_obj_set_flex_gap(parent, LV_DPI / 4);

    selector_objs.btn = lv_calendar_create(parent, NULL);
    lv_obj_set_flex_item_place(selector_objs.btn, LV_FLEX_PLACE_CENTER);

    lv_obj_t * label = lv_label_create(selector_objs.btn, NULL);
    lv_label_set_text(label, "Button");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    selector_objs.cb = lv_checkbox_create(parent, NULL);
    lv_obj_set_flex_item_place(selector_objs.cb, LV_FLEX_PLACE_CENTER);

    selector_objs.slider = lv_slider_create(parent, NULL);
    lv_obj_set_flex_item_place(selector_objs.slider, LV_FLEX_PLACE_CENTER);
    lv_slider_set_range(selector_objs.slider, 0, 10);

    selector_objs.sw = lv_switch_create(parent, NULL);
    lv_obj_set_flex_item_place(selector_objs.sw, LV_FLEX_PLACE_CENTER);

    selector_objs.spinbox = lv_spinbox_create(parent);
    lv_obj_set_flex_item_place(selector_objs.spinbox, LV_FLEX_PLACE_CENTER);

    selector_objs.dropdown = lv_dropdown_create(parent, NULL);
    lv_obj_set_flex_item_place(selector_objs.dropdown, LV_FLEX_PLACE_CENTER);
    lv_obj_set_event_cb(selector_objs.dropdown, dd_enc);

    selector_objs.roller = lv_roller_create(parent, NULL);
    lv_obj_set_flex_item_place(selector_objs.roller, LV_FLEX_PLACE_CENTER);

    lv_obj_t * list = lv_list_create(parent);
    lv_obj_set_flex_item_place(list, LV_FLEX_PLACE_CENTER);
    if(lv_obj_get_height(list) > lv_obj_get_height_fit(parent)) {
        lv_obj_set_height(list, lv_obj_get_height_fit(parent));
    }
    selector_objs.list_btn[0] = lv_list_add_btn(list, LV_SYMBOL_OK, "Apply", NULL);
    lv_group_add_obj(g, selector_objs.list_btn[0]);
    selector_objs.list_btn[1] = lv_list_add_btn(list, LV_SYMBOL_CLOSE, "Close", NULL);
    lv_group_add_obj(g, selector_objs.list_btn[1]);
    selector_objs.list_btn[2] = lv_list_add_btn(list, LV_SYMBOL_EYE_OPEN, "Show", NULL);
    lv_group_add_obj(g, selector_objs.list_btn[2]);
    selector_objs.list_btn[3] = lv_list_add_btn(list, LV_SYMBOL_EYE_CLOSE, "Hide", NULL);
    lv_group_add_obj(g, selector_objs.list_btn[3]);
    selector_objs.list_btn[4] = lv_list_add_btn(list, LV_SYMBOL_TRASH, "Delete", NULL);
    lv_group_add_obj(g, selector_objs.list_btn[4]);
    selector_objs.list_btn[5] = lv_list_add_btn(list, LV_SYMBOL_COPY, "Copy", NULL);
    lv_group_add_obj(g, selector_objs.list_btn[5]);
    selector_objs.list_btn[6] = lv_list_add_btn(list, LV_SYMBOL_PASTE, "Paste", NULL);
    lv_group_add_obj(g, selector_objs.list_btn[6]);
}

static void text_input_create(lv_obj_t * parent)
{
    textinput_objs.ta1 = lv_textarea_create(parent, NULL);
    lv_obj_set_event_cb(textinput_objs.ta1, ta_event_cb);
    lv_obj_set_width(textinput_objs.ta1, 400);
    lv_obj_align(textinput_objs.ta1, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 20);
    lv_textarea_set_one_line(textinput_objs.ta1, true);
    lv_textarea_set_cursor_hidden(textinput_objs.ta1, true);
    lv_textarea_set_placeholder_text(textinput_objs.ta1, "Type something");
    lv_textarea_set_text(textinput_objs.ta1, "");

    textinput_objs.ta2 = lv_textarea_create(parent, textinput_objs.ta1);
    lv_obj_align(textinput_objs.ta2, textinput_objs.ta1, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI / 20);

    textinput_objs.kb = NULL;
}

static void msgbox_create(void)
{
    static const char * btns[] = {"Ok", "Cancel", ""};
    lv_obj_t * mbox = lv_msgbox_create("Hi", "Welcome to the keyboard and encoder demo", btns, false);
    lv_obj_set_event_cb(mbox, msgbox_event_cb);
    lv_group_add_obj(g, lv_msgbox_get_btns(mbox));
    lv_group_focus_obj(lv_msgbox_get_btns(mbox));
#if LV_EX_MOUSEWHEEL
    lv_group_set_editing(g, true);
#endif
    lv_group_focus_freeze(g, true);

    lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * bg = lv_obj_get_parent(mbox);
    lv_obj_set_style_local_bg_opa(bg, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_70);
    lv_obj_set_style_local_bg_color(bg, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GRAY);
}


static void msgbox_event_cb(lv_obj_t * msgbox, lv_event_t e)
{
    if(e == LV_EVENT_CLICKED) {
        const char * txt = lv_msgbox_get_active_btn_text(msgbox);
        if(txt) {
            lv_msgbox_close(msgbox);
            lv_group_focus_freeze(g, false);
            lv_event_send(tv, LV_EVENT_REFRESH, NULL);
            lv_obj_scroll_to(t1, 0, 0, LV_ANIM_OFF);
        }
    }
}

static void tv_event_cb(lv_obj_t * ta, lv_event_t e)
{
    if(e == LV_EVENT_VALUE_CHANGED || e == LV_EVENT_REFRESH) {
        lv_group_remove_all_objs(g);

        uint16_t tab = lv_tabview_get_tab_act(tv);
        size_t size = 0;
        lv_obj_t ** objs = NULL;
        if(tab == 0) {
            size = sizeof(selector_objs);
            objs = (lv_obj_t**) &selector_objs;
        }
        else if(tab == 1) {
            size = sizeof(textinput_objs);
            objs = (lv_obj_t**) &textinput_objs;
        }

        lv_group_add_obj(g, lv_tabview_get_tab_btns(tv));

        uint32_t i;
        for(i = 0; i < size / sizeof(lv_obj_t *); i++) {
            if(objs[i] == NULL) continue;
            lv_group_add_obj(g, objs[i]);
        }

    }
}

static void ta_event_cb(lv_obj_t * ta, lv_event_t e)
{
    /*Create a virtual keyboard for the encoders*/
    lv_indev_t * indev = lv_indev_get_act();
    if(indev == NULL) return;
    lv_indev_type_t indev_type = lv_indev_get_type(indev);

    if(e == LV_EVENT_FOCUSED) {
        lv_textarea_set_cursor_hidden(ta, false);
        if(lv_group_get_editing(g)) {
            if(textinput_objs.kb == NULL) {
                textinput_objs.kb = lv_keyboard_create(lv_scr_act());
                lv_group_add_obj(g, textinput_objs.kb);
                lv_obj_set_event_cb(textinput_objs.kb, kb_event_cb);
                lv_obj_set_height(tv, LV_VER_RES - lv_obj_get_height(textinput_objs.kb));
            }

            lv_keyboard_set_textarea(textinput_objs.kb, ta);
            lv_group_focus_obj(textinput_objs.kb);
            lv_group_set_editing(g, true);
            lv_obj_scroll_to_obj(t2, ta, LV_ANIM_ON);
        }
    }
    else if(e == LV_EVENT_DEFOCUSED) {
        if(indev_type == LV_INDEV_TYPE_ENCODER) {
            if(textinput_objs.kb == NULL) {
                lv_textarea_set_cursor_hidden(ta, true);
            }
        } else {
            lv_textarea_set_cursor_hidden(ta, true);
        }
    }
}

static void kb_event_cb(lv_obj_t * kb, lv_event_t e)
{
    lv_keyboard_def_event_cb(kb, e);

    if(e == LV_EVENT_APPLY || e == LV_EVENT_CANCEL) {
        lv_group_focus_obj(lv_keyboard_get_textarea(kb));
        lv_obj_del(kb);
        textinput_objs.kb = NULL;
        lv_obj_set_height(tv, LV_VER_RES);
    }
}

#endif
