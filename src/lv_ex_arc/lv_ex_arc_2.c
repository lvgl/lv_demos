#include "lvgl/lvgl.h" 

/**
 * An `lv_task` to call periodically to set the angles of the arc
 * @param t
 */
static void arc_loader(lv_task_t * t)
{
    static int16_t a = 0;

    a+=5;
    if(a >= 359) a = 359;

    if(a < 180) lv_arc_set_angles(t->user_data, 180-a ,180);
    else lv_arc_set_angles(t->user_data, 540-a ,180);

    if(a == 359) {
        lv_task_del(t);
        return;
    }
}

/**
 * Create an arc which acts as a loader.
 */
void lv_ex_arc_2(void)
{
  /*Create style for the Arcs*/
  static lv_style_t style;
  lv_style_copy(&style, &lv_style_plain);
  style.line.color = LV_COLOR_NAVY;           /*Arc color*/
  style.line.width = 8;                       /*Arc width*/

  /*Create an Arc*/
  lv_obj_t * arc = lv_arc_create(lv_scr_act(), NULL);
  lv_arc_set_angles(arc, 180, 180);
  lv_arc_set_style(arc, LV_ARC_STYLE_MAIN, &style);
  lv_obj_align(arc, NULL, LV_ALIGN_CENTER, 0, 0);

  /* Create an `lv_task` to update the arc.
   * Store the `arc` in the user data*/
  lv_task_create(arc_loader, 20, LV_TASK_PRIO_LOWEST, arc);

}
