///**
// * @file terminal.c
// *
// */
//
///*********************
// *      INCLUDES
// *********************/
//
//#include "terminal.h"
//
//#include "lvgl/lv_objx/lv_btn.h"
//#include "lvgl/lv_objx/lv_label.h"
//#include "lvgl/lv_objx/lv_page.h"
//#include "lvgl/lv_objx/lv_ta.h"
//#include "lvgl/lv_objx/lv_kb.h"
//#include <stdbool.h>
//#include <string.h>
//
///*********************
// *      DEFINES
// *********************/
//#define TERMINAL_ANIM_TIME   100 /*[ms]*/
//#define TERMINAL_NO_INPUT    0   /*Do not create Text are and Keyboard*/
//#define TERMINAL_WIDTH       (LV_HOR_RES / 2)
//#define TERMINAL_HEIGHT      (LV_VER_RES)
//#define TERMINAL_LOG_LENGTH  512        /*Characters*/
//
///**********************
// *      TYPEDEFS
// **********************/
//
///**********************
// *  STATIC PROTOTYPES
// **********************/
//static lv_action_res_t ta_rel_action(lv_obj_t * ta);
//static lv_action_res_t clr_rel_action(lv_obj_t * btn);
//static lv_action_res_t kb_ok_action(lv_obj_t * kb);
//static lv_action_res_t kb_close_action(lv_obj_t * kb);
//static void kb_del(void);
//
///**********************
// *  STATIC VARIABLES
// **********************/
//static lv_obj_t * holder;
//static char txt_log[TERMINAL_LOG_LENGTH + 1];
//static lv_obj_t * label;
//static lv_obj_t * ta;
//static lv_obj_t * clr_btn;
//static lv_obj_t * keyboard;
//static lv_style_t style_bg;
//
///**********************
// *      MACROS
// **********************/
//
///**********************
// *   GLOBAL FUNCTIONS
// **********************/
//
///**
// * Open a terminal
// */
//void terminal_init(void)
//{
//    lv_style_copy(&style_bg, &lv_style_pretty);
//    style_bg.body.main_color = LV_COLOR_MAKE(0x30, 0x30, 0x30);
//    style_bg.body.grad_color = LV_COLOR_MAKE(0x30, 0x30, 0x30);
//    style_bg.body.border.color = LV_COLOR_WHITE;
//    style_bg.text.color = LV_COLOR_MAKE(0xE0, 0xE0, 0xE0);
//
//    holder = lv_page_create(lv_scr_act(), NULL);
//    lv_obj_set_style(holder, &style_bg);
//    lv_obj_set_style(lv_page_get_scrl(holder), &lv_style_transp);
//    lv_obj_set_size(holder, TERMINAL_WIDTH, TERMINAL_HEIGHT);
//    lv_page_set_sb_mode(holder, LV_PAGE_SB_MODE_AUTO);
//
//    /*Make the window content responsive*/
//    lv_cont_set_layout(lv_page_get_scrl(holder), LV_CONT_LAYOUT_PRETTY);
//
//    /*Create a label for the text of the terminal*/
//    label = lv_label_create(holder, NULL);
//    lv_obj_set_style(label, &style_bg);
//    lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
//    lv_obj_set_width(label, lv_obj_get_width(lv_page_get_scrl(holder)));
//    lv_label_set_text_static(label, txt_log);               /*Use the text array directly*/
//
//    /*Create a text area. Text can be added to the terminal using soft keyboard.*/
//    ta = lv_ta_create(holder, NULL);
//    lv_obj_set_size(ta, lv_obj_get_width(lv_page_get_scrl(holder)) , LV_DPI);
//    lv_page_set_rel_action(ta, ta_rel_action);
//    lv_page_glue_obj(ta, true);
//    lv_ta_set_text(ta, "");
//
//    /*Create a clear button*/
//    clr_btn = lv_btn_create(holder, NULL);
//    lv_cont_set_fit(clr_btn, true, true);
//    lv_page_glue_obj(ta, true);
//    lv_btn_set_action(clr_btn, LV_BTN_ACTION_RELEASE, clr_rel_action);
//    lv_obj_t * btn_label = lv_label_create(clr_btn, NULL);
//    lv_label_set_text(btn_label, "Clear");
//}
//
///**
// * Add data to the terminal
// * @param txt_in character sting to add to the terminal
// */
//void terminal_add(const char * txt_in)
//{
//       uint16_t txt_len = strlen(txt_in);
//       uint16_t old_len = strlen(txt_log);
//
//       /*If the data is longer then the terminal ax size show the last part of data*/
//       if(txt_len > TERMINAL_LOG_LENGTH) {
//           txt_in += (txt_len - TERMINAL_LOG_LENGTH);
//           txt_len = TERMINAL_LOG_LENGTH;
//           old_len = 0;
//       }
//       /*If the text become too long 'forget' the oldest lines*/
//       else if(old_len + txt_len > TERMINAL_LOG_LENGTH) {
//           uint16_t new_start;
//           for(new_start = 0; new_start < old_len; new_start++) {
//               if(txt_log[new_start] == '\n') {
//                   /*If there is enough space break*/
//                   if(new_start >= txt_len) {
//                       /*Ignore line breaks*/
//                       while(txt_log[new_start] == '\n' || txt_log[new_start] == '\r') new_start++;
//                       break;
//                   }
//               }
//           }
//
//           /* If it wasn't able to make enough space on line breaks
//            * simply forget the oldest characters*/
//           if(new_start == old_len) {
//               new_start = old_len - (TERMINAL_LOG_LENGTH - txt_len);
//           }
//           /*Move the remaining text to the beginning*/
//           uint16_t j;
//           for(j = new_start; j < old_len; j++) {
//               txt_log[j - new_start] = txt_log[j];
//           }
//           old_len = old_len - new_start;
//           txt_log[old_len] = '\0';
//
//       }
//
//       memcpy(&txt_log[old_len], txt_in, txt_len);
//       txt_log[old_len + txt_len] = '\0';
//
//       lv_label_set_text_static(label, txt_log);
//       lv_page_focus(holder, clr_btn, TERMINAL_ANIM_TIME);
//}
//
///**********************
// *   STATIC FUNCTIONS
// **********************/
//
///*--------------------
// * OTHER FUNCTIONS
// ---------------------*/
//
///**
// * Called when the Text area is released to open a keyboard
// * @param ta pointer to the text area
// * @return LV_ACTION_RES_OK because the text area is not deleted
// */
//static lv_action_res_t ta_rel_action(lv_obj_t * ta)
//{
//    /*Create a keyboard if not created yet*/
//    if(keyboard == NULL) {
//        keyboard = lv_kb_create(lv_scr_act(), NULL);
//        lv_kb_set_ta(keyboard, ta);
//        lv_kb_set_ok_action(keyboard, kb_ok_action);
//        lv_kb_set_close_action(keyboard, kb_close_action);
//        lv_obj_set_height(holder, LV_VER_RES / 2);
//        lv_obj_align(holder, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
//        lv_page_focus(holder, clr_btn, 0);
//    }
//
//    return LV_ACTION_RES_OK;
//}
//
///**
// * Called when the Clear button is released to clear the text of the terminal
// * @param btn pointer to the clear button
// * @return LV_ACTION_RES_OK because the button is not deleted
// */
//static lv_action_res_t clr_rel_action(lv_obj_t * btn)
//{
//    txt_log[0] = '\0';
//    lv_label_set_text_static(label, txt_log);   /*Refresh the text*/
//
//    return LV_ACTION_RES_OK;
//}
//
///**
// * Called when the 'Ok' button of the keyboard in the window
// * is pressed to write to the Terminal
// * @param kb pointer to the Keyboard
// * @return LV_ACTION_RES_INV because the keyboard is deleted
// */
//static lv_action_res_t kb_ok_action(lv_obj_t * kb)
//{
//    const char * ta_txt = lv_ta_get_txt(ta);
//    if(txt_log[0] != '\0') terminal_add("\n");
//    terminal_add(ta_txt);
//    lv_ta_set_text(ta, "");
//    kb_del();
//
//    return LV_ACTION_RES_INV;
//}
//
///**
// * Called when the 'Close' button of the keyboard is pressed
// * @param kb pointer to the Keyboard
// * @return LV_ACTION_RES_INV because the keyboard is deleted
// */
//static lv_action_res_t kb_close_action(lv_obj_t * kb)
//{
//    lv_ta_set_text(ta, "");
//    kb_del();
//
//    return LV_ACTION_RES_INV;
//}
//
///**
// * Delete the soft keyboard and restore the
// */
//static void kb_del(void)
//{
//    lv_obj_del(keyboard);
//    keyboard = NULL;
//    lv_obj_set_height(holder, LV_VER_RES);
//    lv_page_focus(holder, clr_btn, TERMINAL_ANIM_TIME);
//}
//
