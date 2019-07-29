/**
 * @file lv_examples.h
 *
 */

#ifndef LV_EXAMPLES_H
#define LV_EXAMPLES_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/
/*Test  lvgl version*/
#define LV_EXAMPLES_LVGL_REQ_MAJOR  6
#define LV_EXAMPLES_LVGL_REQ_MINOR  0
#define LV_EXAMPLES_LVGL_REQ_PATCH  0

#if LV_EXAMPLES_LVGL_REQ_MAJOR != LVGL_VERSION_MAJOR
#error "lv_examples: Wrong lvgl major version"
#endif

#if LV_EXAMPLES_LVGL_REQ_MINOR > LVGL_VERSION_MINOR
#error "lv_examples: Wrong lvgl minor version"
#endif

#if LV_EXAMPLES_LVGL_REQ_PATCH > LVGL_VERSION_PATCH
#error "lv_examples: Wrong lvgl bug fix version"
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_ex_arc_1(void);
void lv_ex_arc_2(void);
void lv_ex_bar_1(void);
void lv_ex_btn_1(void);
void lv_ex_btnm_1(void);
void lv_ex_calendar_1(void);
void lv_ex_canvas_1(void);
void lv_ex_cb_1(void);
void lv_ex_chart_1(void);
void lv_ex_cont_1(void);
void lv_ex_ddlist_1(void);
void lv_ex_gauge_1(void);
void lv_ex_img_1(void);
void lv_ex_img_2(void);
void lv_ex_imgbtn_1(void);
void lv_ex_kb_1(void);
void lv_ex_label_1(void);
void lv_ex_label_2(void);
void lv_ex_label_3(void);
void lv_ex_led_1(void);
void lv_ex_line_1(void);
void lv_ex_list_1(void);
void lv_ex_lmeter_1(void);
void lv_ex_mbox_1(void);
void lv_ex_mbox_2(void);
void lv_ex_misc_1(void);
void lv_ex_obj_1(void);
void lv_ex_page_1(void);
void lv_ex_preload_1(void);
void lv_ex_roller_1(void);
void lv_ex_slider_1(void);
void lv_ex_slider_2(void);
void lv_ex_spinbox_1(void);
void lv_ex_sw_1(void);
void lv_ex_ta_1(void);
void lv_ex_ta_2(void);
void lv_ex_table_1(void);
void lv_ex_tabview_1(void);
void lv_ex_tileview_1(void);
void lv_ex_win_1(void);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_EXAMPLES_H*/
