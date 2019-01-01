/**
 * @file lv_test_tileview.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_tileview.h"
#if USE_LV_TILEVIEW && USE_LV_BTN && USE_LV_LABEL && USE_LV_LIST

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

/**
 * Create a tileview to test their functionalities
 */
void lv_test_tileview_1(void)
{
    static const lv_point_t vp[] = {
                   {1,0},          /*First row: only the middle tile*/
            {0,1}, {1,1}, {1,2},   /*Second row: all tree tiles */
                   {2,1}, {2,2},   /*Third row: middle and right tile*/
            {LV_COORD_MIN, LV_COORD_MIN}};

    lv_obj_t * t;
    t = lv_tileview_create(lv_scr_act(), NULL);
    lv_tileview_set_valid_positions(t, vp);
    lv_tileview_set_edge_flash(t, true);

    lv_obj_t * label;

    /*x0, y1 container*/
    lv_obj_t * p01 = lv_obj_create(t, NULL);
    lv_obj_set_click(p01, true);
    lv_obj_set_style(p01, &lv_style_pretty_color);
    lv_obj_set_size(p01, lv_obj_get_width(t), lv_obj_get_height(t));
    lv_tileview_add_element(p01);

    /*Add a  button at x0, y1*/
    lv_obj_t * b01 = lv_btn_create(p01, NULL);
    lv_tileview_add_element(b01);
    lv_obj_align(b01, NULL, LV_ALIGN_CENTER, 0, 50);
    label = lv_label_create(b01, NULL);
    lv_label_set_text(label, "Button");

    /*Add a label to indicate the position*/
    label = lv_label_create(p01, NULL);
    lv_label_set_text(label, "x0, y1");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    /*x1, y1 container*/
    lv_obj_t * p11 = lv_obj_create(t, p01);
    lv_obj_align(p11, p01, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_tileview_add_element(p11);

    /*Add a label to indicate the position*/
    label = lv_label_create(p11, NULL);
    lv_label_set_text(label, "x1, y1");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    /*x1, y2 list*/
    lv_obj_t * list12 = lv_list_create(t, NULL);
    lv_obj_set_size(list12, LV_HOR_RES, LV_VER_RES);
    lv_obj_align(list12, p11, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_list_set_scroll_propagation(list12, true);
    lv_tileview_add_element(list12);

    lv_obj_t * list_btn;
    list_btn = lv_list_add(list12, NULL, "One", NULL);
    lv_tileview_add_element(list_btn);

    list_btn = lv_list_add(list12, NULL, "Two", NULL);
    lv_tileview_add_element(list_btn);

    list_btn = lv_list_add(list12, NULL, "Three", NULL);
    lv_tileview_add_element(list_btn);

    list_btn = lv_list_add(list12, NULL, "Four", NULL);
    lv_tileview_add_element(list_btn);

    list_btn = lv_list_add(list12, NULL, "Five", NULL);
    lv_tileview_add_element(list_btn);

    list_btn = lv_list_add(list12, NULL, "Six", NULL);
    lv_tileview_add_element(list_btn);

    list_btn = lv_list_add(list12, NULL, "Seven", NULL);
    lv_tileview_add_element(list_btn);

    /*x1, y0 container*/
    lv_obj_t * p10 = lv_obj_create(t, p01);
    lv_tileview_add_element(p10);

    /*Add a label to indicate the position*/
    label = lv_label_create(p10, NULL);
    lv_label_set_text(label, "x1, y0");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(p10, p11, LV_ALIGN_OUT_TOP_MID, 0, 0);

    /*x2, y1 container*/
    lv_obj_t * p21 = lv_obj_create(t, p01);
    lv_tileview_add_element(p21);
    lv_obj_align(p21, p11, LV_ALIGN_OUT_RIGHT_MID, 0, 0);

    /*Add a label to indicate the position*/
    label = lv_label_create(p21, NULL);
    lv_label_set_text(label, "x2, y1");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    /*x2, y1 container*/
    lv_obj_t * p22 = lv_obj_create(t, p01);
    lv_tileview_add_element(p22);
    lv_obj_align(p22, p21, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    /*Add a label to indicate the position*/
    label = lv_label_create(p22, NULL);
    lv_label_set_text(label, "x2, y2");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    /*Focus on a tile (the list)*/
    lv_tileview_set_tile_act(t, 1, 2, true);

}


/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /*USE_LV_TILEVIEW && USE_LV_TESTS*/
