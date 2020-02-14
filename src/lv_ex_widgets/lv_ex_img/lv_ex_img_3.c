#include "lvgl/lvgl.h"
#if LV_USE_IMG

LV_IMG_DECLARE(cogwheel);

void lv_ex_img_3(void)
{
    /* Now create the actual image */
    lv_obj_t * img = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img, &cogwheel);
    lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_pivot(img, 0, 50);
    lv_img_set_zoom(img, 512);
    lv_img_set_angle(img, 90);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, img, (lv_anim_exec_xcb_t)lv_img_set_angle);
    lv_anim_set_values(&a, 0, 359);
    lv_anim_set_repeat(&a, 0);
    lv_anim_set_time(&a, 5000, 0);
    lv_anim_create(&a);

//    lv_anim_set_exec_cb(&a, img, (lv_anim_exec_xcb_t)lv_img_set_zoom);
//    lv_anim_set_values(&a, 128, 512);
//    lv_anim_set_playback(&a, 0);
//    lv_anim_create(&a);

}

#endif
