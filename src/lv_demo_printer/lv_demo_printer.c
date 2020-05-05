/**
 * @file lv_demo_priner.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_printer_scr.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
LV_EVENT_CB_DECLARE(home_icont_event_cb);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_printer(void)
{
    lv_demo_printer_scr_init();

    lv_demo_printer_scr_add_title("Hello world");

    lv_coord_t box_w = (LV_HOR_RES * 9) / 10;
    lv_obj_t *main_box = lv_demo_printer_scr_add_box();
    lv_obj_set_size(main_box, box_w, LV_VER_RES / 2);
    lv_obj_align(main_box, NULL, LV_ALIGN_CENTER, 0, 0);

    LV_IMG_DECLARE(lv_demo_printer_img_scan);

    lv_obj_t * icon;

    icon = lv_demo_printer_scr_add_icon(main_box, &lv_demo_printer_img_scan, "SCAN");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 1 * box_w / 8, 0);
    lv_obj_set_event_cb(icon, home_icont_event_cb);

    icon = lv_demo_printer_scr_add_icon(main_box, &lv_demo_printer_img_scan, "SCAN");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 3 * box_w / 8, 0);
    icon = lv_demo_printer_scr_add_icon(main_box, &lv_demo_printer_img_scan, "SCAN");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 5 * box_w / 8, 0);
    icon = lv_demo_printer_scr_add_icon(main_box, &lv_demo_printer_img_scan, "SCAN");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 7 * box_w / 8, 0);

    lv_demo_printer_anim_in_all(main_box, 0);
    lv_demo_printer_anim_bg(0, LV_DEMO_PRINTER_BLUE, LV_DEMO_PRINTER_BG_NORMAL);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

LV_EVENT_CB_DECLARE(home_icont_event_cb)
{
    if(e == LV_EVENT_CLICKED) {
       lv_demo_printer_anim_bg(0, LV_DEMO_PRINTER_GREEN, LV_DEMO_PRINTER_BG_FULL);
       lv_demo_printer_anim_out_all(lv_scr_act(), 200);

    }
}
