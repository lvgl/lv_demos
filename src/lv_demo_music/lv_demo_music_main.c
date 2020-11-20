/**
 * @file lv_demo_music_main.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_music_main.h"
#include "assets/spectrum.h"

/*********************
 *      DEFINES
 *********************/
#define TRACK_CNT 5

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void spectrum_anim_cb(void * a, lv_anim_value_t v);
static lv_design_res_t spectrum_design_cb(lv_obj_t * obj, const lv_area_t * mask, lv_design_mode_t mode);
static lv_obj_t * album_img_create(lv_obj_t * parent);
static void album_event_cb(lv_obj_t * img, lv_event_t event);
static void play_event_cb(lv_obj_t * img, lv_event_t event);
static void timer_cb(lv_task_t * t);
static void track_load(uint32_t id);
static void wave_create(bool bottom, bool rev, lv_coord_t x);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * main_cont;
static lv_obj_t * spectrum_obj;
static lv_obj_t * title_obj;
static lv_obj_t * artist_obj;
static lv_obj_t * genre_obj;
static lv_obj_t * time_obj;
static lv_obj_t * album_img_obj;
static lv_obj_t * slider_obj;
static uint32_t spectrum_i = 0;
static uint32_t spectrum_i_pause = 0;
static uint32_t spectrum_lane_ofs = 0;
static uint32_t spectrum_lane_ofs_start = 0;
static uint32_t spectrum_lane_rot = 0;
static uint32_t time;
static lv_task_t *  time_task;
static lv_font_t * font_small;
static lv_font_t * font_medium;
static lv_font_t * font_large;
static uint32_t track_id;
static bool playing;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_demo_music_main_create(lv_obj_t * parent)
{
    LV_FONT_DECLARE(lv_demo_music_font_16_bold);
    font_small = &lv_font_montserrat_12;
    font_medium = &lv_font_montserrat_14;
    font_large = &lv_demo_music_font_16_bold;

    /*Create an empty white main container*/
    main_cont = lv_obj_create(parent, NULL);
    lv_obj_set_size(main_cont, LV_HOR_RES, LV_VER_RES + 30);
    lv_obj_set_style_local_bg_color(main_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_set_style_local_radius(main_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 15);
    lv_obj_set_style_local_border_width(main_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_clip_corner(main_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, true);
    lv_page_glue_obj(main_cont, true);
    lv_obj_add_protect(main_cont, LV_PROTECT_PRESS_LOST);

    wave_create(true, false, -90);
    wave_create(true, false, 160);
    wave_create(true, false, 300);

    wave_create(true, true, -20);
    wave_create(true, true, 230);


    wave_create(false, false, -90);
    wave_create(false, false, 160);

    wave_create(false, true, -20);
    wave_create(false, true, 230);

    /*Create the titles*/
    lv_obj_t * title_box = lv_cont_create(main_cont, NULL);
    lv_obj_clean_style_list(title_box, LV_CONT_PART_MAIN);
    lv_cont_set_layout(title_box, LV_LAYOUT_COLUMN_MID);
    lv_cont_set_fit2(title_box, LV_FIT_NONE, LV_FIT_TIGHT);
#if LV_DEMO_MUSIC_LANDSCAPE
    lv_obj_set_width(title_box, LV_HOR_RES / 2);
    lv_obj_align(title_box, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 15);
#else
    lv_obj_set_width(title_box, LV_HOR_RES - 20);
    lv_obj_align(title_box, NULL, LV_ALIGN_IN_TOP_MID, 0, 15);
#endif

    title_obj = lv_label_create(title_box, NULL);
    lv_obj_set_style_local_text_font(title_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_large);
    lv_obj_set_style_local_text_color(title_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x504d6d));
    lv_obj_set_style_local_margin_top(title_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_label_set_text(title_obj, _lv_demo_music_get_title(track_id));

    artist_obj = lv_label_create(title_box, NULL);
    lv_obj_set_style_local_text_font(artist_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_small);
    lv_obj_set_style_local_text_color(artist_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x504d6d));
    lv_obj_set_style_local_margin_top(artist_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 5);
    lv_label_set_text(artist_obj, _lv_demo_music_get_artist(track_id));

    genre_obj = lv_label_create(title_box, NULL);
    lv_obj_set_style_local_text_font(genre_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_small);
    lv_obj_set_style_local_text_color(genre_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x8a86b8));
    lv_label_set_text(genre_obj, _lv_demo_music_get_genre(track_id));

    /*Create the icons*/
    lv_obj_t * icon_box = lv_cont_create(main_cont, NULL);
    lv_obj_clean_style_list(icon_box, LV_CONT_PART_MAIN);
    lv_obj_set_width(icon_box, 176);
    lv_cont_set_fit2(icon_box, LV_FIT_NONE, LV_FIT_TIGHT);
    lv_cont_set_layout(icon_box, LV_LAYOUT_PRETTY_MID);

    lv_obj_t * icon;
    LV_IMG_DECLARE(img_lv_demo_music_icon_1);
    LV_IMG_DECLARE(img_lv_demo_music_icon_2);
    LV_IMG_DECLARE(img_lv_demo_music_icon_3);
    LV_IMG_DECLARE(img_lv_demo_music_icon_4);
    icon = lv_img_create(icon_box, NULL);
    lv_img_set_src(icon, &img_lv_demo_music_icon_1);
    icon = lv_img_create(icon_box, NULL);
    lv_img_set_src(icon, &img_lv_demo_music_icon_2);
    icon = lv_img_create(icon_box, NULL);
    lv_img_set_src(icon, &img_lv_demo_music_icon_3);
    icon = lv_img_create(icon_box, NULL);
    lv_img_set_src(icon, &img_lv_demo_music_icon_4);

#if LV_DEMO_MUSIC_LANDSCAPE
    lv_obj_align(icon_box, title_box, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
#else
    lv_obj_align(icon_box, NULL, LV_ALIGN_IN_TOP_MID, 0, 100);
#endif

    /*Create the spectrum visualizer*/
    spectrum_obj = lv_obj_create(main_cont, NULL);
    lv_obj_set_design_cb(spectrum_obj, spectrum_design_cb);
    lv_obj_set_click(spectrum_obj, false);
#if LV_DEMO_MUSIC_LANDSCAPE
    lv_obj_set_size(spectrum_obj, LV_HOR_RES / 2, LV_VER_RES);
    lv_obj_align(spectrum_obj, NULL, LV_ALIGN_IN_RIGHT_MID, 0, -10);
#else
    lv_obj_set_size(spectrum_obj, lv_obj_get_width(lv_scr_act()), 300);
    lv_obj_align(spectrum_obj, NULL, LV_ALIGN_CENTER, 0, -10);
#endif

    LV_IMG_DECLARE(img_lv_demo_music_cover_bg);
    lv_obj_t * cover_bg = lv_img_create(spectrum_obj, NULL);
    lv_img_set_src(cover_bg, &img_lv_demo_music_cover_bg);
#if LV_DEMO_MUSIC_LANDSCAPE
    lv_obj_align(cover_bg, NULL, LV_ALIGN_CENTER, 0, 0);
#else
    lv_obj_align(cover_bg, NULL, LV_ALIGN_CENTER, 0, 0);
#endif

    album_img_obj = album_img_create(spectrum_obj);

    /*Create the control box*/
    lv_obj_t * ctrl_box = lv_cont_create(main_cont, NULL);
    lv_obj_clean_style_list(ctrl_box, LV_CONT_PART_MAIN);
    lv_obj_set_click(ctrl_box, false);
#if LV_DEMO_MUSIC_LANDSCAPE
    lv_obj_set_size(ctrl_box, (LV_HOR_RES / 2) - 20, 140);
    lv_obj_align(ctrl_box, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 10, -15);
#else
    lv_obj_set_size(ctrl_box, LV_HOR_RES - 10, 140);
    lv_obj_align(ctrl_box, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -15);
#endif

    LV_IMG_DECLARE(img_lv_demo_music_btn_loop);
    LV_IMG_DECLARE(img_lv_demo_music_btn_rnd);
    LV_IMG_DECLARE(img_lv_demo_music_btn_next);
    LV_IMG_DECLARE(img_lv_demo_music_btn_prev);
    LV_IMG_DECLARE(img_lv_demo_music_btn_play);
    LV_IMG_DECLARE(img_lv_demo_music_btn_pause);

    icon = lv_img_create(ctrl_box, NULL);
    lv_img_set_src(icon, &img_lv_demo_music_btn_rnd);
    lv_obj_align(icon, NULL, LV_ALIGN_IN_TOP_MID, -95, 27);

    icon = lv_img_create(ctrl_box, NULL);
    lv_img_set_src(icon, &img_lv_demo_music_btn_loop);
    lv_obj_align(icon, NULL, LV_ALIGN_IN_TOP_MID, 95, 27);

    icon = lv_img_create(ctrl_box, NULL);
    lv_img_set_src(icon, &img_lv_demo_music_btn_prev);
    lv_obj_align(icon, NULL, LV_ALIGN_IN_TOP_MID, -45, 7);

    icon = lv_imgbtn_create(ctrl_box, NULL);
    lv_imgbtn_set_src(icon, LV_BTN_STATE_RELEASED, &img_lv_demo_music_btn_play);
    lv_imgbtn_set_src(icon, LV_BTN_STATE_CHECKED_RELEASED, &img_lv_demo_music_btn_pause);
    lv_imgbtn_set_checkable(icon, true);
    lv_obj_align(icon, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_set_event_cb(icon, play_event_cb);

    icon = lv_img_create(ctrl_box, NULL);
    lv_img_set_src(icon, &img_lv_demo_music_btn_next);
    lv_obj_align(icon, NULL, LV_ALIGN_IN_TOP_MID, 45, 7);

    LV_IMG_DECLARE(img_lv_demo_music_slider_knob);
    slider_obj = lv_slider_create(ctrl_box, NULL);
    lv_slider_set_anim_time(slider_obj, 1000);

#if LV_DEMO_MUSIC_LANDSCAPE
    lv_obj_set_size(slider_obj, lv_obj_get_width(ctrl_box) - 50, 3);
    lv_obj_align(slider_obj, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 75);
#else
    lv_obj_set_size(slider_obj, 210, 3);
    lv_obj_align(slider_obj, NULL, LV_ALIGN_IN_TOP_MID, -10, 75);
#endif
    lv_obj_set_style_local_pattern_image(slider_obj, LV_SLIDER_PART_KNOB, LV_STATE_DEFAULT, &img_lv_demo_music_slider_knob);
    lv_obj_set_style_local_bg_opa(slider_obj, LV_SLIDER_PART_KNOB, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_obj_set_style_local_pad_all(slider_obj, LV_SLIDER_PART_KNOB, LV_STATE_DEFAULT, 20);
    lv_obj_set_style_local_bg_grad_dir(slider_obj, LV_SLIDER_PART_INDIC, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
    lv_obj_set_style_local_bg_color(slider_obj, LV_SLIDER_PART_INDIC, LV_STATE_DEFAULT, lv_color_hex(0x569af8));
    lv_obj_set_style_local_bg_grad_color(slider_obj, LV_SLIDER_PART_INDIC, LV_STATE_DEFAULT, lv_color_hex(0xa666f1));
    lv_obj_set_style_local_outline_width(slider_obj, LV_SLIDER_PART_BG, LV_STATE_DEFAULT, 0);

    time_obj = lv_label_create(ctrl_box, NULL);
    lv_obj_set_style_local_text_font(time_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_small);
    lv_obj_set_style_local_text_color(time_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x8a86b8));
    lv_label_set_text(time_obj, "0:00");
    lv_obj_align(time_obj, NULL, LV_ALIGN_IN_TOP_RIGHT, -1, 67);

    /*A handle to scroll to the track list*/
    lv_obj_t * label = lv_label_create(main_cont, NULL);
    lv_label_set_text(label, "ALL TRACKS");
    lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_small);
    lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x8a86b8));
    lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -35);

    lv_obj_t * handle = lv_obj_create(main_cont, NULL);
    lv_obj_set_size(handle, 20, 2);
    lv_obj_align(handle, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -30);
    lv_obj_set_style_local_bg_color(handle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x8a86b8));
    lv_obj_set_style_local_border_width(handle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);

    time_task = lv_task_create(timer_cb, 1000, LV_TASK_PRIO_OFF, NULL);

    return main_cont;
}

void lv_demo_music_album_next(bool next)
{
    uint32_t id = track_id;
    if(next) {
        id++;
        if(id >= TRACK_CNT) id = 0;
    } else {
        if(id == 0) {
            id = TRACK_CNT - 1;
        } else {
            id--;
        }
    }

    if(playing) {
        lv_demo_music_play(id);
    } else {
        track_load(id);
    }

}

void lv_demo_music_play(uint32_t id)
{
    track_load(id);

    lv_demo_music_resume();
}

void lv_demo_music_resume(void)
{
    playing = true;
    spectrum_i = spectrum_i_pause;
    uint32_t record_cnt = sizeof(spectrum) / sizeof(spectrum[0]);
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_values(&a, spectrum_i, sizeof(spectrum) / sizeof(spectrum[0]) - 1);
    lv_anim_set_exec_cb(&a, spectrum_anim_cb);
    lv_anim_set_var(&a, spectrum_obj);
    lv_anim_set_time(&a, ((record_cnt - spectrum_i) * 1000) / 30);
    lv_anim_set_playback_time(&a, 0);
    lv_anim_start(&a);

    lv_task_set_prio(time_task, LV_TASK_PRIO_MID);
    lv_slider_set_range(slider_obj, 0, _lv_demo_music_get_track_length(track_id));
}

void lv_demo_music_pause(void)
{
    playing = false;
    spectrum_i_pause = spectrum_i;
    spectrum_i = 0;
    lv_anim_del(spectrum_obj, spectrum_anim_cb);
    lv_obj_invalidate(spectrum_obj);
    lv_img_set_zoom(album_img_obj, LV_IMG_ZOOM_NONE);
    lv_task_set_prio(time_task, LV_TASK_PRIO_OFF);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void track_load(uint32_t id)
{

    bool next = false;
    if((track_id+1) % TRACK_CNT == id) next = true;

    lv_demo_music_list_btn_check(track_id, false);

    track_id = id;

    lv_demo_music_list_btn_check(id, true);

    lv_label_set_text(title_obj, _lv_demo_music_get_title(track_id));
    lv_label_set_text(artist_obj, _lv_demo_music_get_artist(track_id));
    lv_label_set_text(genre_obj, _lv_demo_music_get_genre(track_id));

    spectrum_i = 0;
    time = 0;
    spectrum_i_pause = 0;
    lv_slider_set_value(slider_obj, 0, LV_ANIM_OFF);

    spectrum_i_pause = 0;

    lv_obj_fade_out(album_img_obj, 500, 0);

    lv_anim_path_t path;
    lv_anim_path_init(&path);
    lv_anim_path_set_cb(&path, lv_anim_path_ease_out);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, album_img_obj);
    lv_anim_set_time(&a, 500);
    lv_anim_set_path(&a, &path);
#if LV_DEMO_MUSIC_LANDSCAPE
    if(next) {
        lv_anim_set_values(&a, lv_obj_get_x(album_img_obj), lv_obj_get_x(album_img_obj) - LV_HOR_RES / 7);
    } else {
        lv_anim_set_values(&a, lv_obj_get_x(album_img_obj), lv_obj_get_x(album_img_obj) + LV_HOR_RES / 7);
    }
#else
    if(next) {
        lv_anim_set_values(&a, lv_obj_get_x(album_img_obj), lv_obj_get_x(album_img_obj) - LV_HOR_RES / 2);
    } else {
        lv_anim_set_values(&a, lv_obj_get_x(album_img_obj), lv_obj_get_x(album_img_obj) + LV_HOR_RES / 2);
    }
#endif
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_x);
    lv_anim_set_ready_cb(&a, lv_obj_del_anim_ready_cb);
    lv_anim_start(&a);

    lv_anim_path_set_cb(&path, lv_anim_path_linear);
    lv_anim_set_path(&a, &path);
    lv_anim_set_var(&a, album_img_obj);
    lv_anim_set_time(&a, 500);
    lv_anim_set_values(&a, LV_IMG_ZOOM_NONE, LV_IMG_ZOOM_NONE / 2);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_img_set_zoom);
    lv_anim_set_ready_cb(&a, NULL);
    lv_anim_start(&a);

    album_img_obj = album_img_create(spectrum_obj);

    lv_obj_fade_in(album_img_obj, 500, 0);

    lv_anim_path_set_cb(&path, lv_anim_path_overshoot);
    lv_anim_set_path(&a, &path);
    lv_anim_set_var(&a, album_img_obj);
    lv_anim_set_time(&a, 500);
    lv_anim_set_values(&a, LV_IMG_ZOOM_NONE / 4, LV_IMG_ZOOM_NONE);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_img_set_zoom);
    lv_anim_set_ready_cb(&a, NULL);
    lv_anim_start(&a);
}

static lv_design_res_t spectrum_design_cb(lv_obj_t * obj, const lv_area_t * mask, lv_design_mode_t mode)
{
    if(mode == LV_DESIGN_COVER_CHK) {
        return LV_DESIGN_RES_NOT_COVER;
    }
    if(mode == LV_DESIGN_DRAW_MAIN) {
        lv_point_t tri[3];
        tri[0].x = obj->coords.x1 + lv_obj_get_width(obj) / 2;
        tri[0].y = obj->coords.y1 + lv_obj_get_height(obj) / 2;

        lv_draw_rect_dsc_t draw_dsc;
        lv_draw_rect_dsc_init(&draw_dsc);
        draw_dsc.bg_opa = LV_OPA_COVER;

        uint16_t r[64];
        uint32_t i;

        int32_t all_lane_cnt = 20;
        uint32_t sector_cnt = sizeof(spectrum[0]) / sizeof(spectrum[0][0]);
        for(i = 0; i < all_lane_cnt; i++) r[i] = 98;

        uint32_t s;
        for(s = 0; s < 4; s++) {
            uint32_t f;
            uint32_t sublane_cnt = 0;
            switch(s) {
            case 0:
                sublane_cnt = 20;
                break;
            case 1:
                sublane_cnt = 8;
                break;
            case 2:
                sublane_cnt = 4;
                break;
            case 3:
                sublane_cnt = 2;
                break;
            }
            for(f = 0; f < sublane_cnt; f++) {
                uint32_t amain = spectrum[spectrum_i][s];

                float amod = (2 - (cos(((float)f / (float)sublane_cnt) * 2 * 3.1415f) + 1)) / 2;
                uint32_t l = (all_lane_cnt / sector_cnt);
                int32_t t = l * s - sublane_cnt / 2 + f;
                if(t < 0) t = all_lane_cnt + t;
                if(t >= all_lane_cnt) t = t - all_lane_cnt;
                r[t] += amain * amod * 0.5;

            }
        }

        uint32_t deg_space = 6;
        uint32_t deg_step = 180/all_lane_cnt;

        static uint8_t rnd[10] = {15, 3, 40, 9, 24, 33, 15, 23, 6, 18};

        uint32_t amax = 20;
        int32_t animv = spectrum_i - spectrum_lane_ofs_start;
        if(animv > amax) animv = amax;
        for(i = 0; i < all_lane_cnt; i++) {
            uint32_t deg = i * deg_step + 90;
            uint32_t j =  (i + spectrum_lane_rot + rnd[spectrum_lane_ofs %10]) % all_lane_cnt;
            uint32_t k = (i + spectrum_lane_rot + rnd[(spectrum_lane_ofs + 1) % 10]) % all_lane_cnt;

            uint32_t v = (r[k] * animv + r[j] * (amax - animv)) / amax;
            float d;

            lv_color_t c1 = lv_color_hex(0xb15ff0);
            lv_color_t c2 = lv_color_hex(0x48a3f9);
            int min = 100;
            int max= 130;
            if(v < min) draw_dsc.bg_color = c1;
            else if(v > max) draw_dsc.bg_color = c2;
            else draw_dsc.bg_color = lv_color_mix(c2, c1, ((v - min) * 255) / (max-min));

            uint32_t di = deg + deg_space / 2;
            d = (float)(di)/(float)180.0 * 3.1415f;
            int32_t x1 = (cos(d) * v);
            tri[1].x = tri[0].x + x1;
            tri[1].y = tri[0].y + (sin(d) * v);

            di += deg_step - deg_space;

            d = (float)(di)/(float)180.0 * 3.1415f;
            int32_t x2 = (cos(d) * v);
            tri[2].x = tri[0].x + x2;
            tri[2].y = tri[0].y + (sin(d) * v);


            lv_point_t mask_in;
            int32_t mx = (cos(d) * 90);
            mask_in.x = tri[0].x + mx;
            mask_in.y = tri[0].y + (sin(d) * 90);

            lv_area_t mask2;
            mask2.x1 = LV_MATH_MIN3(tri[1].x, tri[2].x, mask_in.x) - 5;
            mask2.y1 = LV_MATH_MIN3(tri[1].y, tri[2].y, mask_in.y) - 5;
            mask2.x2 = LV_MATH_MAX3(tri[1].x, tri[2].x, mask_in.x) + 5;
            mask2.y2 = LV_MATH_MAX3(tri[1].y, tri[2].y, mask_in.y) + 5;

            if(_lv_area_intersect(&mask2, &mask2, mask)) {
                lv_draw_triangle(tri, &mask2, &draw_dsc);
            }

            tri[1].x = tri[0].x - x1;
            tri[2].x = tri[0].x - x2;
            mask_in.x = tri[0].x - mx;
            mask2.x1 = LV_MATH_MIN3(tri[1].x, tri[2].x, mask_in.x) - 5;
            mask2.y1 = LV_MATH_MIN3(tri[1].y, tri[2].y, mask_in.y) - 5;
            mask2.x2 = LV_MATH_MAX3(tri[1].x, tri[2].x, mask_in.x) + 5;
            mask2.y2 = LV_MATH_MAX3(tri[1].y, tri[2].y, mask_in.y) + 5;
            if(_lv_area_intersect(&mask2, &mask2, mask)) {
                lv_draw_triangle(tri, &mask2, &draw_dsc);
            }

        }
    }
    return LV_DESIGN_RES_OK;
}

static void spectrum_anim_cb(void * a, lv_anim_value_t v)
{
    lv_obj_t * obj = a;

    spectrum_i = v;
    lv_obj_invalidate(obj);

    static uint32_t bass_cnt = 0;
    static int32_t last_bass = -1000;
    static int32_t dir = 1;
    if(spectrum[spectrum_i][0] > 12) {
        if(spectrum_i-last_bass > 5) {
            bass_cnt++;
            last_bass = spectrum_i;
            if(bass_cnt >= 2) {
                bass_cnt = 0;
                spectrum_lane_ofs_start = spectrum_i;
                spectrum_lane_ofs++;
            }
        }
    }
    if(spectrum[spectrum_i][0] < 4) spectrum_lane_rot+= dir;

    lv_img_set_zoom(album_img_obj, LV_IMG_ZOOM_NONE + spectrum[spectrum_i][0]);
}

static lv_obj_t * album_img_create(lv_obj_t * parent)
{
    LV_IMG_DECLARE(img_lv_demo_music_cover_1);
    LV_IMG_DECLARE(img_lv_demo_music_cover_2);
    LV_IMG_DECLARE(img_lv_demo_music_cover_3);
    LV_IMG_DECLARE(img_lv_demo_music_cover_4);
    LV_IMG_DECLARE(img_lv_demo_music_cover_5);

    lv_obj_t * img;
    img = lv_img_create(parent, NULL);
    LV_IMG_DECLARE(conver_1);

    switch(track_id) {
    case 0:
        lv_img_set_src(img, &img_lv_demo_music_cover_1);
        break;
    case 1:
        lv_img_set_src(img, &img_lv_demo_music_cover_2);
        break;
    case 2:
        lv_img_set_src(img, &img_lv_demo_music_cover_3);
        break;
    case 3:
        lv_img_set_src(img, &img_lv_demo_music_cover_4);
        break;
    case 4:
        lv_img_set_src(img, &img_lv_demo_music_cover_5);
        break;
    }
    lv_img_set_pivot(img, 100, 100);
    lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_event_cb(img, album_event_cb);
    lv_obj_set_gesture_parent(img, false);
    lv_obj_set_click(img, true);

    return img;

}

static void album_event_cb(lv_obj_t * img, lv_event_t event)
{
    if(event == LV_EVENT_GESTURE) {
        lv_gesture_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if(dir == LV_GESTURE_DIR_LEFT) lv_demo_music_album_next(true);
        if(dir == LV_GESTURE_DIR_RIGHT) lv_demo_music_album_next(false);
    }
}

static void play_event_cb(lv_obj_t * img, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        if(lv_imgbtn_get_state(img) == LV_BTN_STATE_RELEASED) {
            lv_demo_music_pause();
        } else {
            lv_demo_music_resume();
        }
    }
}

static void timer_cb(lv_task_t * t)
{
    time++;
    lv_label_set_text_fmt(time_obj, "%d:%02d", time / 60, time % 60);
    lv_slider_set_value(slider_obj, time, LV_ANIM_ON);
}

static void wave_anim_ready_cb(lv_anim_t * a)
{
    lv_obj_t * wave = a->var;

    bool rev;
    if(lv_obj_get_x(wave) < 0) rev = true;
    else rev = false;

    bool bottom = true;
    if(lv_obj_get_y(wave) < LV_VER_RES / 2) bottom = false;

    wave_create(bottom, rev, 0);

    lv_obj_del(wave);
}

static void wave_create(bool bottom, bool rev, lv_coord_t x)
{
    static uint32_t rnd = 123456;

    LV_IMG_DECLARE(img_lv_demo_music_wave_1);
    LV_IMG_DECLARE(img_lv_demo_music_wave_2);
    LV_IMG_DECLARE(img_lv_demo_music_wave_1_top);
    LV_IMG_DECLARE(img_lv_demo_music_wave_2_top);

    lv_obj_t * wave;
    wave = lv_img_create(main_cont, NULL);
    lv_obj_move_background(wave);
    if(rnd & 0x1) lv_img_set_src(wave, bottom ? &img_lv_demo_music_wave_1 : &img_lv_demo_music_wave_1_top);
    else lv_img_set_src(wave, bottom ? &img_lv_demo_music_wave_2 : &img_lv_demo_music_wave_2_top);

    if(bottom) lv_obj_align(wave, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, (rnd % 10));
    else lv_obj_align(wave, NULL, LV_ALIGN_IN_TOP_MID, 0, 15 -(rnd % 10));

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, lv_obj_set_x);
    lv_anim_set_ready_cb(&a, wave_anim_ready_cb);

    if(rev == false) lv_anim_set_values(&a, x - lv_obj_get_width(wave), LV_HOR_RES);
    else lv_anim_set_values(&a, LV_HOR_RES - x,  - lv_obj_get_width(wave));

    lv_anim_set_time(&a, lv_anim_speed_to_time(6 + (rnd % 15), a.start, a.end));
    lv_anim_set_var(&a, wave);
    lv_anim_start(&a);

    if(bottom) {
        lv_anim_set_exec_cb(&a, lv_obj_set_y);
        lv_anim_set_values(&a, lv_obj_get_y(wave), (lv_obj_get_y(wave) + 3 + (rnd % 15)));
        lv_anim_set_time(&a, 3000 + rnd % 3000);
        lv_anim_set_playback_time(&a, 3000 + (rnd % 3000));
        lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
        lv_anim_start(&a);
    }
    rnd *= 4567;
    rnd += 98765;
}

