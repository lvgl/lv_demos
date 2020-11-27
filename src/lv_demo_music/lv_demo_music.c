/**
 * @file lv_demo_music.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_music_main.h"
#include "lv_demo_music_list.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void auto_step_cb(lv_task_t * task);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * ctrl;
static lv_obj_t * list;

static const char * title_list[] = {
    "Waiting for true love",
    "Title 2",
    "Title 3",
    "Title 4",
    "Title 5",
    "Title 6",
    "Title 7",
    "Title 8",
    "Title 9",
    "Title 10",
};

static const char * artist_list[] = {
    "John Smith",
    "Artist 2",
    "Artist 3",
    "Artist 4",
    "Artist 5",
    "Artist 6",
    "Artist 7",
    "Artist 8",
    "Artist 9",
    "Artist 10",
};

static const char * genre_list[] = {
    "Pop • 2015",
    "Metal • 2015",
    "Metal • 2015",
    "Metal • 2015",
    "Metal • 2015",
    "Metal • 2015",
    "Metal • 2015",
    "Metal • 2015",
    "Metal • 2015",
    "Metal • 2015",
};

static const uint32_t time_list[] = {
    2*60 + 34,
    2*60 + 34,
    2*60 + 34,
    2*60 + 34,
    2*60 + 34,
    2*60 + 34,
    2*60 + 34,
    2*60 + 34,
    2*60 + 34,
    2*60 + 34,
};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_music(void)
{
    lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x343247));

    list = lv_demo_music_list_create(lv_scr_act());
    ctrl = lv_demo_music_main_create(lv_scr_act());

//    lv_task_create(auto_step_cb, 1000, LV_TASK_PRIO_MID, NULL);
}

const char * _lv_demo_music_get_title(uint32_t track_id)
{
    if(track_id >= sizeof(title_list) / sizeof(title_list[0])) return NULL;
    return title_list[track_id];
}

const char * _lv_demo_music_get_artist(uint32_t track_id)
{
    if(track_id >= sizeof(artist_list) / sizeof(artist_list[0])) return NULL;
    return artist_list[track_id];
}

const char * _lv_demo_music_get_genre(uint32_t track_id)
{
    if(track_id >= sizeof(genre_list) / sizeof(genre_list[0])) return NULL;
    return genre_list[track_id];
}

uint32_t _lv_demo_music_get_track_length(uint32_t track_id)
{
    if(track_id >= sizeof(time_list) / sizeof(time_list[0])) return 0;
    return time_list[track_id];
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void auto_step_cb(lv_task_t * task)
{
    static uint32_t state = 0;
    lv_anim_t a;
    lv_obj_t * obj;;

    switch(state) {
    case 5:
        lv_demo_music_album_next(true);
        break;
    case 6:
        lv_demo_music_album_next(true);
        break;
    case 7:
        lv_demo_music_album_next(true);
        break;
        break;
    case 8:
        lv_demo_music_play(0);
        break;
    case 9:
        lv_anim_init(&a);
        lv_anim_set_var(&a, ctrl);
        lv_anim_set_values(&a, lv_obj_get_y(ctrl), -lv_obj_get_height(ctrl) + LV_DEMO_LIST_CTRL_OVERLAP);
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_y);
        lv_anim_set_time(&a, 500);
        lv_anim_start(&a);
        break;
    case 10:
        obj = lv_page_get_scrl(list);
        lv_anim_init(&a);
        lv_anim_set_var(&a, obj);
        lv_anim_set_values(&a, lv_obj_get_y(obj), -lv_obj_get_height(obj) + LV_DEMO_LIST_CTRL_OVERLAP);
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_y);
        lv_anim_set_time(&a, 1000);
        lv_anim_set_playback_time(&a, 1000);
        lv_anim_set_playback_delay(&a, 200);
        lv_anim_start(&a);
        break;
    case 13:
        lv_demo_music_play(1);
        break;
    case 14:
        lv_anim_init(&a);
        lv_anim_set_var(&a, ctrl);
        lv_anim_set_values(&a, lv_obj_get_y(ctrl), -15);
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_y);
        lv_anim_set_time(&a, 500);
        lv_anim_start(&a);
        break;
    }


    state++;

}
