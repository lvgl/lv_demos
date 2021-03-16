/**
 * @file lv_demo_keypad_encoder.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <lv_examples/lv_demo.h>
#include "lv_demo_keypad_encoder.h"

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
static void ta_event_cb(lv_obj_t * ta, lv_event_t e);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_group_t*  g;
static lv_obj_t * tv;
static lv_obj_t * t1;
static lv_obj_t * t2;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_keypad_encoder(void)
{
    g = lv_group_create();

    lv_indev_t* cur_drv = NULL;
    for (;;) {
        cur_drv = lv_indev_get_next(cur_drv);
        if (!cur_drv) {
            break;
        }

#if LV_EX_KEYBOARD
        if (cur_drv->driver.type == LV_INDEV_TYPE_KEYPAD) {
            lv_indev_set_group(cur_drv, g);
        }
#endif

#if LV_EX_MOUSEWHEEL
        if (cur_drv->driver.type == LV_INDEV_TYPE_ENCODER) {
            lv_indev_set_group(cur_drv, g);
        }
#endif
    }

    tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, LV_DPI_DEF / 3);
//    lv_obj_set_event_cb(tv, tv_event_cb);

    t1 = lv_tabview_add_tab(tv, "Selectors");
    t2 = lv_tabview_add_tab(tv, "Text input");

//    lv_group_add_obj(g, lv_tabview_get_tab_btns(tv));

    selectors_create(t1);
    text_input_create(t2);

    msgbox_create();
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void selectors_create(lv_obj_t * parent)
{
<<<<<<< HEAD
    lv_page_set_scrl_layout(parent, LV_LAYOUT_COLUMN_MID);

   selector_objs.btn = lv_btn_create(parent, NULL);

   lv_obj_t * label = lv_label_create(selector_objs.btn, NULL);
   lv_label_set_text(label, "Button");

   selector_objs.cb = lv_checkbox_create(parent, NULL);

   selector_objs.slider = lv_slider_create(parent, NULL);
   lv_slider_set_range(selector_objs.slider, 0, 10);
   lv_slider_set_type(selector_objs.slider, LV_SLIDER_TYPE_RANGE);

   selector_objs.sw = lv_switch_create(parent, NULL);

   selector_objs.spinbox = lv_spinbox_create(parent, NULL);

   selector_objs.dropdown = lv_dropdown_create(parent, NULL);
   lv_obj_set_event_cb(selector_objs.dropdown, dd_enc);

   selector_objs.roller = lv_roller_create(parent, NULL);

   selector_objs.list = lv_list_create(parent, NULL);
   if(lv_obj_get_height(selector_objs.list) > lv_page_get_height_fit(parent)) {
       lv_obj_set_height(selector_objs.list, lv_page_get_height_fit(parent));
   }
   lv_obj_t * bt;

  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_OK, "1");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_CLOSE, "2");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_EYE_CLOSE, "3");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_TRASH, "4");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_COPY, "5");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_COPY, "6");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_OK, "7");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_CLOSE, "8");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_EYE_CLOSE, "9");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_TRASH, "10");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_COPY, "11");lv_group_add_obj(g,bt);
  bt=lv_list_add_btn(selector_objs.list, LV_SYMBOL_COPY, "12");lv_group_add_obj(g,bt);


=======
    lv_obj_set_layout(parent, &lv_flex_vertical_list);

    lv_obj_t * obj;

    obj = lv_table_create(parent, NULL);
    lv_table_set_cell_value(obj, 0, 0, "00");
    lv_table_set_cell_value(obj, 0, 1, "01");
    lv_table_set_cell_value(obj, 1, 0, "10");
    lv_table_set_cell_value(obj, 1, 1, "11");
    lv_table_set_cell_value(obj, 2, 0, "20");
    lv_table_set_cell_value(obj, 2, 1, "21");
    lv_table_set_cell_value(obj, 3, 0, "30");
    lv_table_set_cell_value(obj, 3, 1, "31");
    lv_group_add_obj(g, obj);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_calendar_create(parent);
    lv_group_add_obj(g, obj);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_btnmatrix_create(parent, NULL);
    lv_group_add_obj(g, obj);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_checkbox_create(parent, NULL);
    lv_group_add_obj(g, obj);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_slider_create(parent, NULL);
    lv_slider_set_range(obj, 0, 10);
    lv_group_add_obj(g, obj);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_switch_create(parent, NULL);
    lv_group_add_obj(g, obj);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_spinbox_create(parent);
    lv_group_add_obj(g, obj);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_dropdown_create(parent, NULL);
    lv_group_add_obj(g, obj);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    obj = lv_roller_create(parent, NULL);
    lv_group_add_obj(g, obj);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    lv_obj_t * list = lv_list_create(parent);
    if(lv_obj_get_height(list) > lv_obj_get_height_fit(parent)) {
        lv_obj_set_height(list, lv_obj_get_height_fit(parent));
    }

    obj = lv_list_add_btn(list, LV_SYMBOL_OK, "Apply", NULL);
    lv_group_add_obj(g, obj);
    obj = lv_list_add_btn(list, LV_SYMBOL_CLOSE, "Close", NULL);
    lv_group_add_obj(g, obj);
    obj = lv_list_add_btn(list, LV_SYMBOL_EYE_OPEN, "Show", NULL);
    lv_group_add_obj(g, obj);
    obj = lv_list_add_btn(list, LV_SYMBOL_EYE_CLOSE, "Hide", NULL);
    lv_group_add_obj(g, obj);
    obj= lv_list_add_btn(list, LV_SYMBOL_TRASH, "Delete", NULL);
    lv_group_add_obj(g, obj);
    obj = lv_list_add_btn(list, LV_SYMBOL_COPY, "Copy", NULL);
    lv_group_add_obj(g, obj);
    obj = lv_list_add_btn(list, LV_SYMBOL_PASTE, "Paste", NULL);
    lv_group_add_obj(g, obj);
>>>>>>> dev
}

static void text_input_create(lv_obj_t * parent)
{
    lv_obj_set_layout(parent, &lv_flex_vertical_list);

    lv_obj_t * ta1 = lv_textarea_create(parent, NULL);
    lv_obj_set_width(ta1, LV_SIZE_PCT(100));
    lv_textarea_set_one_line(ta1, true);
    lv_textarea_set_placeholder_text(ta1, "Click with an encoder to show a keyboard");
    lv_group_add_obj(g, ta1);

    lv_obj_t * ta2 = lv_textarea_create(parent, NULL);
    lv_obj_set_width(ta2, LV_SIZE_PCT(100));
    lv_textarea_set_one_line(ta2, true);
    lv_textarea_set_placeholder_text(ta2, "Type something");
    lv_group_add_obj(g, ta2);

    lv_obj_t *kb = lv_keyboard_create(lv_scr_act());
    lv_group_add_obj(g, kb);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_event_cb(ta1, ta_event_cb, kb);
    lv_obj_add_event_cb(ta2, ta_event_cb, kb);
}

static void msgbox_create(void)
{
    static const char * btns[] = {"Ok", "Cancel", ""};
    lv_obj_t * mbox = lv_msgbox_create("Hi", "Welcome to the keyboard and encoder demo", btns, false);
    lv_obj_add_event_cb(mbox, msgbox_event_cb, NULL);
    lv_group_add_obj(g, lv_msgbox_get_btns(mbox));
    lv_group_focus_obj(lv_msgbox_get_btns(mbox));
#if LV_EX_MOUSEWHEEL
    lv_group_set_editing(g, true);
#endif
    lv_group_focus_freeze(g, true);

    lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * bg = lv_obj_get_parent(mbox);
    lv_obj_set_style_bg_opa(bg, LV_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_70);
    lv_obj_set_style_bg_color(bg, LV_PART_MAIN, LV_STATE_DEFAULT, lv_color_grey());
}


static void msgbox_event_cb(lv_obj_t * msgbox, lv_event_t e)
{
    if(e == LV_EVENT_VALUE_CHANGED) {
        const char * txt = lv_msgbox_get_active_btn_text(msgbox);
        if(txt) {
            lv_msgbox_close(msgbox);
            lv_group_focus_freeze(g, false);
            lv_group_focus_obj(lv_obj_get_child(t1, 0));
            lv_obj_scroll_to(t1, 0, 0, LV_ANIM_OFF);

        }
    }
}

static void ta_event_cb(lv_obj_t * ta, lv_event_t e)
{
    lv_indev_t * indev = lv_indev_get_act();
    if(indev == NULL) return;
    lv_indev_type_t indev_type = lv_indev_get_type(indev);

    lv_obj_t * kb = lv_event_get_user_data();
    lv_obj_align(kb, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    if(e == LV_EVENT_CLICKED && indev_type == LV_INDEV_TYPE_ENCODER) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_group_focus_obj(kb);
        lv_obj_set_height(tv, LV_VER_RES / 2);
    }

    if(e == LV_EVENT_READY) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_height(tv, LV_VER_RES);
    }
}

#endif
