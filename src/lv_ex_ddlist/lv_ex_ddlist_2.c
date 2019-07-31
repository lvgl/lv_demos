#include "lvgl/lvgl.h"
#include <stdio.h>

/**
 * Create a drop UP list by applying auto realign
 */
void lv_ex_ddlist_2(void)
{

    /*Create a drop down list*/
    lv_obj_t * ddlist = lv_ddlist_create(lv_scr_act(), NULL);
    lv_ddlist_set_options(ddlist, "Apple\n"
            "Banana\n"
            "Orange\n"
            "Melon\n"
            "Grape\n"
            "Raspberry");

    lv_ddlist_set_fix_width(ddlist, 150);
    lv_ddlist_set_fix_height(ddlist, 150);
    lv_ddlist_set_draw_arrow(ddlist, true);

    /* Enable auto-realign when the size changes.
     * It will keep the bottom of the ddlist fixed*/
    lv_obj_set_auto_realign(ddlist, true);

    /*It will be called automatically when the size changes*/
    lv_obj_align(ddlist, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -20);
}
