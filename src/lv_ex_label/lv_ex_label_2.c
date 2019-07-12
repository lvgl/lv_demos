/**
 * @file lv_ex_templ.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

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

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_ex_label_2(void)
{
    /* Create the first label */
    lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "A simple method to create shadows on text\n\tIt even works with newlines       and spaces.");
    
    
    /* Create the second label for a shadow */
    lv_obj_t * second_label = lv_label_create(lv_scr_act(), label);
    
    /* Create a style */
    static lv_style_t label_style;
    
    lv_style_copy(&label_style, &lv_style_plain);
    label_style.text.opa = LV_OPA_50;
    
    lv_label_set_style(second_label, LV_LABEL_STYLE_MAIN, &label_style);
    
    /* Position the label */
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
    
    /* Shift the second label down and to the right by 1 pixel */
    lv_obj_align(second_label, NULL, LV_ALIGN_CENTER, 1, 1);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
