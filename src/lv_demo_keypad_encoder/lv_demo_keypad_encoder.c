/**
 * @file lv_demo_keypad_encoder.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_examples.h"
#include "lvgl/lvgl.h"
#include "lv_demo_keypad_encoder.h"
#if LV_USE_KEYBOARD
#include "lv_drivers/indev/keyboard.h"
#endif

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
static void containers_create(lv_obj_t * parent);

static void focus_cb(lv_group_t * g);
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
static lv_obj_t * t3;

struct {
    lv_obj_t * btn;
    lv_obj_t * cb;
    lv_obj_t * slider;
    lv_obj_t * sw;
    lv_obj_t * spinbox;
    lv_obj_t * dropdown;
    lv_obj_t * roller;
    lv_obj_t * cpicker;
    lv_obj_t * list;
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

void lv_demo_keypad_encoder(void)
{
    g = lv_group_create();
    lv_group_set_focus_cb(g, focus_cb);

#if LV_USE_KEYBOARD
    lv_indev_drv_t kb_drv;
    lv_indev_drv_init(&kb_drv);
    kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    kb_drv.read_cb = keyboard_read;
    lv_indev_t * kb_indev = lv_indev_drv_register(&kb_drv);
    lv_indev_set_group(kb_indev, g);
#endif

    tv = lv_tabview_create(lv_scr_act(), NULL);
    lv_obj_set_event_cb(tv, tv_event_cb);
    lv_group_add_obj(g, tv);

    t1 = lv_tabview_add_tab(tv, "Selectors");
    t2 = lv_tabview_add_tab(tv, "Text input");
    t3 = lv_tabview_add_tab(tv, "Containers");

    selectors_create(t1);
    text_input_create(t2);
    containers_create(t3);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void selectors_create(lv_obj_t * parent)
{
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY_TOP);


   selector_objs.btn = lv_btn_create(parent, NULL);
   lv_group_add_obj(g, selector_objs.btn);

   lv_obj_t * label = lv_label_create(selector_objs.btn, NULL);
   lv_label_set_text(label, "Button");

   selector_objs.cb = lv_checkbox_create(parent, NULL);
   lv_group_add_obj(g, selector_objs.cb);

   selector_objs.slider = lv_slider_create(parent, NULL);
   lv_slider_set_range(selector_objs.slider, 0, 10);
   lv_group_add_obj(g, selector_objs.slider);

   selector_objs.sw = lv_switch_create(parent, NULL);
   lv_group_add_obj(g, selector_objs.sw);

   selector_objs.spinbox = lv_spinbox_create(parent, NULL);
   lv_group_add_obj(g, selector_objs.spinbox);

   selector_objs.dropdown = lv_dropdown_create(parent, NULL);
   lv_group_add_obj(g, selector_objs.dropdown);

   selector_objs.roller = lv_roller_create(parent, NULL);
   lv_group_add_obj(g, selector_objs.roller);

   selector_objs.list = lv_list_create(parent, NULL);
   lv_obj_set_height(selector_objs.list, LV_DPI * 2);
   lv_list_add_btn(selector_objs.list, LV_SYMBOL_OK, "Apply");
   lv_list_add_btn(selector_objs.list, LV_SYMBOL_CLOSE, "Close");
   lv_list_add_btn(selector_objs.list, LV_SYMBOL_EYE_OPEN, "Show");
   lv_list_add_btn(selector_objs.list, LV_SYMBOL_EYE_CLOSE, "Hide");
   lv_list_add_btn(selector_objs.list, LV_SYMBOL_TRASH, "Delete");
   lv_list_add_btn(selector_objs.list, LV_SYMBOL_COPY, "Copy");
   lv_list_add_btn(selector_objs.list, LV_SYMBOL_PASTE, "Paste");
   lv_group_add_obj(g, selector_objs.list);

   selector_objs.cpicker = lv_cpicker_create(parent, NULL);
   lv_group_add_obj(g, selector_objs.cpicker);
}

static void text_input_create(lv_obj_t * parent)
{
    textinput_objs.ta1 = lv_textarea_create(parent, NULL);
    lv_obj_set_event_cb(textinput_objs.ta1, ta_event_cb);
    lv_obj_align(textinput_objs.ta1, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);
    lv_textarea_set_cursor_hidden(textinput_objs.ta1, true);

    textinput_objs.ta2 = lv_textarea_create(parent, textinput_objs.ta1);
    lv_obj_align(textinput_objs.ta2, NULL, LV_ALIGN_IN_TOP_MID, 0, 100);

    textinput_objs.kb = NULL;

}

static void containers_create(lv_obj_t * parent)
{

}

static void focus_cb(lv_group_t * g)
{
    lv_obj_t * obj = lv_group_get_focused(g);
    if(obj != tv) {
        uint16_t tab = lv_tabview_get_tab_act(tv);
        switch(tab) {
        case 0:
            lv_page_focus(t1, obj, LV_ANIM_ON);
            break;
        case 1:
            lv_page_focus(t2, obj, LV_ANIM_ON);
            break;
        case 2:
            lv_page_focus(t3, obj, LV_ANIM_ON);
            break;
        }
    }
}

static void tv_event_cb(lv_obj_t * ta, lv_event_t e)
{
    if(e == LV_EVENT_VALUE_CHANGED) {
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

        lv_group_add_obj(g, tv);

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
        if(indev_type == LV_INDEV_TYPE_ENCODER) {
            if(textinput_objs.kb == NULL) {
                textinput_objs.kb = lv_keyboard_create(lv_scr_act(), NULL);
                lv_group_add_obj(g, textinput_objs.kb);
                lv_obj_set_event_cb(textinput_objs.kb, kb_event_cb);
                lv_obj_set_height(tv, LV_VER_RES - lv_obj_get_height(textinput_objs.kb));
            }

            lv_keyboard_set_textarea(textinput_objs.kb, ta);
            lv_group_focus_obj(textinput_objs.kb);
            lv_page_focus(t2, lv_textarea_get_label(ta), LV_ANIM_ON);
        }
    }
    else if(e == LV_EVENT_DEFOCUSED) {
        lv_textarea_set_cursor_hidden(ta, true);
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
