#include "../../../lv_examples.h"
#include <stdio.h>
#if LV_USE_LIST

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        printf("Clicked: %s\n", lv_list_get_btn_text(obj));
    }
}

void lv_ex_list_1(void)
{
    /*Create a list*/
    lv_obj_t * list1 = lv_list_create(lv_scr_act());
    lv_obj_set_size(list1, 160, 200);
    lv_obj_align(list1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_flex_cont(list1, LV_FLEX_DIR_NONE, LV_FLEX_START);


    printf("start\n");
    uint32_t t = lv_tick_get();
    uint32_t i;
    for(i=0; i <= 50; i++) {
//        if(i%100 == 0)
//            printf("btn: %d\n", i);
        lv_list_add_btn(list1, LV_SYMBOL_FILE, "New", event_handler);
//        lv_list_add_text(list1, LV_SYMBOL_FILE "New");

    }

    lv_obj_set_flex_cont(list1, LV_FLEX_DIR_COLUMN, LV_FLEX_START);
    printf("time: %d\n", lv_tick_elaps(t));



    /*Add buttons to the list*/
    lv_list_add_btn(list1, LV_SYMBOL_FILE, "New", event_handler);
    lv_list_add_btn(list1, LV_SYMBOL_DIRECTORY, "Open", event_handler);
    lv_list_add_btn(list1, LV_SYMBOL_CLOSE, "Delete", event_handler);
    lv_list_add_btn(list1, LV_SYMBOL_EDIT, "Edit", event_handler);
    lv_list_add_btn(list1, LV_SYMBOL_SAVE, "Save", event_handler);
    lv_list_add_btn(list1, LV_SYMBOL_BELL, "Notify", event_handler);
    lv_list_add_btn(list1, LV_SYMBOL_BATTERY_FULL, "Battery", event_handler);
}

#endif
