#include "lvgl/lvgl.h"
#include <stdio.h>
#if LV_USE_DDLIST


/**
 * Create a drop LEFT menu
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

    lv_ddlist_set_dir(ddlist, LV_DDLIST_DIR_LEFT);
    lv_ddlist_set_symbol(ddlist, NULL);
    lv_ddlist_set_show_selected(ddlist, false);
    lv_ddlist_set_text(ddlist, "Fruits");
    /*It will be called automatically when the size changes*/
    lv_obj_align(ddlist, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 20);

    /*Copy the drop LEFT list*/
    ddlist = lv_ddlist_create(lv_scr_act(), ddlist);
    lv_obj_align(ddlist, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 100);
}

#endif
