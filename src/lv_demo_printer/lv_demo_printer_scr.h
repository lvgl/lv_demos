/**
 * @file lv_demo_printer_scr.h
 *
 */

#ifndef LV_DEMO_PRINTER_SCR_H
#define LV_DEMO_PRINTER_SCR_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_printer.h"

/*********************
 *      DEFINES
 *********************/

/*Colors*/
#define LV_DEMO_PRINTER_WHITE   lv_color_hex(0xffffff)
#define LV_DEMO_PRINTER_LIGHT   lv_color_hex(0xf3f8fe)
#define LV_DEMO_PRINTER_GRAY    lv_color_hex(0x8a8a8a)
#define LV_DEMO_PRINTER_BLUE    lv_color_hex(0x006fb6)
#define LV_DEMO_PRINTER_GREEN   lv_color_hex(0x4cb242)

/*Bg positions*/
#define LV_DEMO_PRINTER_BG_NONE (-LV_VER_RES)
#define LV_DEMO_PRINTER_BG_FULL 0
#define LV_DEMO_PRINTER_BG_NORMAL (-2 * (LV_VER_RES / 3))

/*Animations*/
#define LV_DEMO_PRINTER_ANIM_Y (LV_VER_RES / 20)
#define LV_DEMO_PRINTER_ANIM_DELAY (50)
#define LV_DEMO_PRINTER_ANIM_TIME  (200)
#define LV_DEMO_PRINTER_ANIM_TIME_BG  (350)

/*Fonts*/
LV_FONT_DECLARE(lv_font_montserrat_20);
LV_FONT_DECLARE(lv_font_montserrat_28);
#define LV_DEMO_PRINTER_FONT_NORMAL &lv_font_montserrat_20
#define LV_DEMO_PRINTER_FONT_BIG &lv_font_montserrat_28

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_demo_printer_scr_init(void);


lv_obj_t * lv_demo_printer_scr_add_box(void);

/**
 * Add a title
 * @param scr a screen
 * @return
 */
lv_obj_t * lv_demo_printer_scr_add_title( const char * txt);

/**
 * Create a simple box
 * @param scr a screen
 * @return
 */
lv_obj_t * lv_demo_printer_scr_add_back(void);

/**
 * Create add icon
 * @param parent pointer to parent (screen or box)
 * @return
 */
lv_obj_t * lv_demo_printer_scr_add_icon(lv_obj_t * parent, const void * src, const char * txt);

void lv_demo_printer_anim_bg(uint32_t delay, lv_color_t color, uint32_t y);

void lv_demo_printer_anim_in(lv_obj_t * obj, uint32_t delay);

void lv_demo_printer_anim_out(lv_obj_t * obj, uint32_t delay);

void lv_demo_printer_anim_out_all(lv_obj_t * obj, uint32_t delay);

void lv_demo_printer_anim_in_all(lv_obj_t * obj, uint32_t delay);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DEMO_PRINTER_SCR_H*/
