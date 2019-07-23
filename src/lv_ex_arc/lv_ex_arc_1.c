#include "lvgl/lvgl.h" 

void lv_ex_arc_1(void) 
{
  /*Create style for the Arcs*/
  static lv_style_t style;
  lv_style_copy(&style, &lv_style_plain);
  style.line.color = LV_COLOR_BLUE;           /*Arc color*/
  style.line.width = 8;                       /*Arc width*/

  /*Create an Arc*/
  lv_obj_t * arc = lv_arc_create(lv_scr_act(), NULL);
  lv_arc_set_style(arc, LV_ARC_STYLE_MAIN, &style);          /*Use the new style*/
  lv_arc_set_angles(arc, 90, 60);
  lv_obj_set_size(arc, 150, 150);
  lv_obj_align(arc, NULL, LV_ALIGN_CENTER, 0, 0);
}
