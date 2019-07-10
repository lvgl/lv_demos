/**
 * @file lv_ex_mbox_2.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "lvgl/lvgl.h"


/**********************
 *  STATIC PROTOTYPES
 **********************/

static void mbox_event_cb(lv_obj_t *obj, lv_event_t evt);
static void btn_event_cb(lv_obj_t *btn, lv_event_t evt);

/**********************
 *  STATIC VARIABLES
 **********************/

static lv_obj_t *mbox, *info;

static const char welcome_info[] = "Welcome to the modal message box demo!\n"
                                 "Press the button to display the message box.";

static const char in_msg_info[] = "Notice that you cannot touch the button again "
				  "while the message box is open.";

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_ex_mbox_2(void)
{
	/* Create a button, then set its position and event callback */
	lv_obj_t *btn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_size(btn, 200, 60);
	lv_obj_set_event_cb(btn, btn_event_cb);
	lv_obj_align(btn, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);

	/* Create a label on the button */
	lv_obj_t *label = lv_label_create(btn, NULL);
	lv_label_set_text(label, "Display a message box!");

	/* Create an informative label on the screen */
	info = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(info, welcome_info);
	lv_label_set_long_mode(info, LV_LABEL_LONG_BREAK); /* Make sure text will wrap */
	lv_obj_set_width(label, LV_HOR_RES);
	lv_obj_align(info, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 20, -20);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void mbox_event_cb(lv_obj_t *obj, lv_event_t evt)
{
	if(evt == LV_EVENT_DELETE && obj == mbox) {
		/* Delete the parent modal background */
		lv_obj_del_async(lv_obj_get_parent(mbox));
		mbox = NULL; /* happens before object is actually deleted! */
		lv_label_set_text(info, welcome_info);
	} else if(evt == LV_EVENT_VALUE_CHANGED) {
		/* A button was clicked */
		lv_mbox_start_auto_close(mbox, 0);
	}
}

static void btn_event_cb(lv_obj_t *btn, lv_event_t evt)
{
	if(evt == LV_EVENT_CLICKED) {
		static lv_style_t modal_style;
		/* Create a full-screen background */
		lv_style_copy(&modal_style, &lv_style_plain_color);

		/* Set the background's style */
		modal_style.body.main_color = modal_style.body.grad_color = LV_COLOR_BLACK;
		modal_style.body.opa = LV_OPA_50;

		/* Create a base object for the modal background */
		lv_obj_t *obj = lv_obj_create(lv_scr_act(), NULL);
		lv_obj_set_style(obj, &modal_style);
		lv_obj_set_pos(obj, 0, 0);
		lv_obj_set_size(obj, LV_HOR_RES, LV_VER_RES);
		lv_obj_set_opa_scale_enable(obj, true); /* Enable opacity scaling for the animation */

		static const char * btns2[] = {"Ok", "Cancel", ""};

		/* Create the message box as a child of the modal background */
		mbox = lv_mbox_create(obj, NULL);
		lv_mbox_add_btns(mbox, btns2);
		lv_mbox_set_text(mbox, "Hello world!");
		lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);
		lv_obj_set_event_cb(mbox, mbox_event_cb);

		/* Fade the message box in with an animation */
		lv_anim_t a;
		lv_anim_init(&a);
		lv_anim_set_time(&a, 1000, 0);
		lv_anim_set_values(&a, LV_OPA_TRANSP, LV_OPA_COVER);
		lv_anim_set_exec_cb(&a, obj, (lv_anim_exec_xcb_t)lv_obj_set_opa_scale);
		lv_anim_create(&a);
		lv_label_set_text(info, in_msg_info);
	}
}
