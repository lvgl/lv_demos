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
static lv_res_t main_page_signal_cb(lv_obj_t * scrl, lv_signal_t signal, void * param);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_signal_cb_t ancestor_signal_cb;

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
    lv_obj_t * page = lv_page_create(lv_scr_act(), NULL);
    lv_page_set_scrlbar_mode(page, LV_SCROLLBAR_MODE_OFF);
    lv_page_set_scrollable_fit4(page, LV_FIT_PARENT, LV_FIT_PARENT, LV_FIT_NONE, LV_FIT_TIGHT);
    lv_obj_clean_style_list(page, LV_PAGE_PART_BG);
    lv_obj_clean_style_list(page, LV_PAGE_PART_SCROLLABLE);
    lv_obj_set_style_local_bg_color(page, LV_PAGE_PART_BG, LV_STATE_DEFAULT, lv_color_hex(0x343247));
    lv_obj_set_size(page, LV_HOR_RES, LV_VER_RES);
    ancestor_signal_cb = lv_obj_get_signal_cb(lv_page_get_scrl(page));
    lv_obj_set_signal_cb(lv_page_get_scrl(page), main_page_signal_cb);

    lv_obj_t * list = lv_demo_music_list_create(page);
    lv_obj_set_y(list, LV_VER_RES + 15);

    lv_obj_t * ctrl = lv_demo_music_main_create(page);
    lv_obj_set_y(ctrl, -15);
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
static lv_res_t main_page_signal_cb(lv_obj_t * scrl, lv_signal_t signal, void * param)
{
    lv_res_t res;
    res = ancestor_signal_cb(scrl, signal, param);
    if(res != LV_RES_OK) return res;

    if(signal == LV_SIGNAL_DRAG_THROW_BEGIN) {
        lv_coord_t y = lv_obj_get_y(scrl);
        lv_indev_t * indev = lv_indev_get_act();
        lv_point_t vect;
        lv_indev_get_vect(indev, &vect);
        lv_coord_t y_predict = 0;

        while(vect.y != 0) {
            y_predict += vect.y;
            vect.y = vect.y * (100 - LV_INDEV_DEF_DRAG_THROW) / 100;
        }
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, scrl);
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_y);
        lv_anim_set_time(&a, 300);
        lv_indev_finish_drag(lv_indev_get_act());
        if(y + y_predict > -LV_VER_RES / 2) {
            lv_anim_set_values(&a, y, 0);
        } else {
            lv_anim_set_values(&a, y, -LV_VER_RES);
        }
        lv_anim_start(&a);
    }

    return LV_RES_OK;
}
