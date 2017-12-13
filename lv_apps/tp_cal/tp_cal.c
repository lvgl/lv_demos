/**
 * @file tp_cal.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include "stdio.h"

/*********************
 *      DEFINES
 *********************/
#define CIRCLE_SIZE     20

/**********************
 *      TYPEDEFS
 **********************/
typedef enum {
    TP_CAL_STATE_INIT,
    TP_CAL_STATE_WIAT_COORD1,
    TP_CAL_STATE_WIAT_COORD2,
    TP_CAL_STATE_WIAT_LEAVE,
    TP_CAL_STATE_READY,
}tp_cal_state_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static lv_res_t scr_click_action(lv_obj_t *scr);

/**********************
 *  STATIC VARIABLES
 **********************/
static tp_cal_state_t state;
static lv_point_t p1;
static lv_point_t p2;
static lv_obj_t *big_btn;
static lv_obj_t *label_main;
static lv_obj_t *circ_area;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a touchpad calibration screen
 */
void tp_cal_create(void)
{
    state = TP_CAL_STATE_INIT;

    /*Create a big transparent button screen to receive clicks*/
    big_btn = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_size(big_btn, LV_HOR_RES, LV_VER_RES);
    lv_btn_set_style(big_btn, LV_BTN_STYLE_REL, &lv_style_transp);
    lv_btn_set_style(big_btn, LV_BTN_STYLE_PR, &lv_style_transp);
    lv_btn_set_action(big_btn, LV_BTN_ACTION_REL, scr_click_action);
    lv_btn_set_layout(big_btn, LV_LAYOUT_OFF);

    label_main = lv_label_create(big_btn, NULL);
    lv_label_set_text(label_main, "Click the circle in\n"
                                  "top left-hand corner");
    lv_obj_align(label_main, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_align(label_main, LV_LABEL_ALIGN_CENTER);


    static lv_style_t style_circ;
    lv_style_copy(&style_circ, &lv_style_pretty_color);
    style_circ.body.radius = LV_RADIUS_CIRCLE;

    circ_area = lv_obj_create(big_btn, NULL);
    lv_obj_set_size(circ_area, CIRCLE_SIZE, CIRCLE_SIZE);
    lv_obj_set_style(circ_area, &style_circ);
    lv_obj_set_click(circ_area, false);

    lv_anim_t a;
    a.var = circ_area;
    a.start = LV_HOR_RES / 2;
    a.end = 0;
    a.fp = (lv_anim_fp_t)lv_obj_set_x;
    a.path = lv_anim_get_path(LV_ANIM_PATH_LIN);
    a.end_cb = NULL;
    a.act_time = -500;
    a.time = 200;
    a.playback = 0;
    a.playback_pause = 0;
    a.repeat = 0;
    a.repeat_pause = 0;
    lv_anim_create(&a);

    a.start = LV_VER_RES / 2;
    a.end = 0;
    a.fp = (lv_anim_fp_t)lv_obj_set_y;
    a.end_cb = NULL;
    a.time = 200;
    lv_anim_create(&a);

    state = TP_CAL_STATE_WIAT_COORD1;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static lv_res_t scr_click_action(lv_obj_t *scr)
{
    if(state == TP_CAL_STATE_WIAT_COORD1) {
        lv_indev_t *indev = lv_indev_get_act();
        lv_indev_get_point(indev, &p1);

        char buf[64];
        sprintf(buf, "x: %d\ny: %d", p1.x, p1.y);
        lv_obj_t *label_coord = lv_label_create(big_btn, NULL);
        lv_label_set_text(label_coord, buf);

        lv_label_set_text(label_main, "Click the circle in\n"
                                      "lower right-hand corner");

        lv_anim_t a;
        a.var = circ_area;
        a.start = 0;
        a.end = LV_HOR_RES - CIRCLE_SIZE;
        a.fp = (lv_anim_fp_t)lv_obj_set_x;
        a.path = lv_anim_get_path(LV_ANIM_PATH_LIN);
        a.end_cb = NULL;
        a.act_time = 0;
        a.time = 200;
        a.playback = 0;
        a.playback_pause = 0;
        a.repeat = 0;
        a.repeat_pause = 0;
        lv_anim_create(&a);

        a.start = 0;
        a.end = LV_VER_RES - CIRCLE_SIZE;
        a.fp = (lv_anim_fp_t)lv_obj_set_y;
        a.end_cb = NULL;
        a.time = 200;
        lv_anim_create(&a);

        state = TP_CAL_STATE_WIAT_COORD2;
    }
    else if(state == TP_CAL_STATE_WIAT_COORD2) {
        lv_indev_t *indev = lv_indev_get_act();
        lv_indev_get_point(indev, &p2);

        lv_label_set_text(label_main, "Click the screen\n"
                                      "to leave calibration");

        char buf[64];
        sprintf(buf, "x: %d\ny: %d", p2.x, p2.y);
        lv_obj_t *label_coord = lv_label_create(big_btn, NULL);
        lv_label_set_text(label_coord, buf);
        lv_obj_align(label_coord, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);

        lv_obj_del(circ_area);

        state = TP_CAL_STATE_WIAT_LEAVE;
    }
    else if(state == TP_CAL_STATE_WIAT_LEAVE) {
        lv_obj_del(big_btn);
        state = TP_CAL_STATE_READY;


    }
    else if(state == TP_CAL_STATE_READY) {
        /*Process 'p1' and 'p2' here*/
    }

    return LV_RES_OK;
}
