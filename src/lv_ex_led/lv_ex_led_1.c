#include "lvgl/lvgl.h"
#if LV_USE_LED

void lv_ex_led_1(void)
{
    /*Create a style for the LED*/
    static lv_style_t style_led;
    lv_style_copy(&style_led, &lv_style_pretty_color);
    style_led.body.radius = LV_RADIUS_CIRCLE;
    style_led.body.main_color = LV_COLOR_MAKE(0xb5, 0x0f, 0x04);
    style_led.body.grad_color = LV_COLOR_MAKE(0x50, 0x07, 0x02);
    style_led.body.border.color = LV_COLOR_MAKE(0xfa, 0x0f, 0x00);
    style_led.body.border.width = 3;
    style_led.body.border.opa = LV_OPA_30;
    style_led.body.shadow.color = LV_COLOR_MAKE(0xb5, 0x0f, 0x04);
    style_led.body.shadow.width = 5;

    /*Create a LED and switch it OFF*/
    lv_obj_t * led1  = lv_led_create(lv_scr_act(), NULL);
    lv_led_set_style(led1, LV_LED_STYLE_MAIN, &style_led);
    lv_obj_align(led1, NULL, LV_ALIGN_CENTER, -80, 0);
    lv_led_off(led1);

    /*Copy the previous LED and set a brightness*/
    lv_obj_t * led2  = lv_led_create(lv_scr_act(), led1);
    lv_obj_align(led2, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_led_set_bright(led2, 190);

    /*Copy the previous LED and switch it ON*/
    lv_obj_t * led3  = lv_led_create(lv_scr_act(), led1);
    lv_obj_align(led3, NULL, LV_ALIGN_CENTER, 80, 0);
    lv_led_on(led3);
}

#endif
