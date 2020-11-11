/**
 * @file lv_demo_music_main.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_music_main.h"
#include "spectrum.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void spectrum_anim_cb(void * a, lv_anim_value_t v);
static lv_design_res_t spectrum_design_cb(lv_obj_t * obj, const lv_area_t * mask, lv_design_mode_t mode);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * spectrum_obj;
static lv_obj_t * title_obj;
static lv_obj_t * subtitle_obj;
static lv_obj_t * genre_obj;
static lv_obj_t * time_obj;
static uint32_t spectrum_i = 0;
static uint32_t spectrum_lane_ofs = 0;
static uint32_t spectrum_lane_ofs_start = 0;
static uint32_t spectrum_lane_rot = 0;
static uint32_t time;
static lv_font_t * font_small;
static lv_font_t * font_medium;
static lv_font_t * font_large;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_music_main_create(void)
{
    font_small = &lv_font_montserrat_12;
    font_medium = &lv_font_montserrat_14;
    font_large = &lv_font_montserrat_16;

    /*Create an empty white main container*/
    lv_obj_t * parent = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(parent, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_style_local_bg_color(parent, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    /*Create the titles*/
    lv_obj_t * title_box = lv_cont_create(parent, NULL);
    lv_obj_clean_style_list(title_box, LV_CONT_PART_MAIN);
    lv_cont_set_fit2(title_box, LV_FIT_PARENT, LV_FIT_TIGHT);
    lv_cont_set_layout(title_box, LV_LAYOUT_COLUMN_MID);

    title_obj = lv_label_create(title_box, NULL);
    lv_obj_set_style_local_text_font(title_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_large);
    lv_obj_set_style_local_text_color(title_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x504d6d));
    lv_obj_set_style_local_margin_top(title_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 10);

    subtitle_obj = lv_label_create(title_box, NULL);
    lv_obj_set_style_local_text_font(subtitle_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_small);
    lv_obj_set_style_local_text_color(subtitle_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x504d6d));
    lv_obj_set_style_local_margin_top(subtitle_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 5);

    genre_obj = lv_label_create(title_box, NULL);
    lv_obj_set_style_local_text_font(genre_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_small);
    lv_obj_set_style_local_text_color(genre_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x8a86b8));

    lv_demo_music_set_text("Future of natural", "Oceans Ate Alaska", "Metal • 2015");

    /*Create the icons*/
    lv_obj_t * icon_box = lv_cont_create(parent, NULL);
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

    lv_obj_align(icon_box, NULL, LV_ALIGN_IN_TOP_MID, 0, 90);

    /*Create the spectrum visualizer*/
    spectrum_obj = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(spectrum_obj, lv_obj_get_width(lv_scr_act()), 300);
    lv_obj_set_design_cb(spectrum_obj, spectrum_design_cb);
    lv_obj_align(spectrum_obj, NULL, LV_ALIGN_CENTER, 0, 0);

    /*Create the control box*/
    lv_obj_t * ctrl_box = lv_cont_create(parent, NULL);
    lv_obj_set_size(ctrl_box, LV_HOR_RES - 10, 140);
    lv_obj_align(ctrl_box, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_obj_clean_style_list(ctrl_box, LV_CONT_PART_MAIN);

    LV_IMG_DECLARE(img_lv_demo_music_btn_loop);
    LV_IMG_DECLARE(img_lv_demo_music_btn_rnd);
    LV_IMG_DECLARE(img_lv_demo_music_btn_next);
    LV_IMG_DECLARE(img_lv_demo_music_btn_prev);
    LV_IMG_DECLARE(img_lv_demo_music_btn_play);

    icon = lv_img_create(ctrl_box, NULL);
    lv_img_set_src(icon, &img_lv_demo_music_btn_rnd);
    lv_obj_align(icon, NULL, LV_ALIGN_IN_TOP_MID, -95, 27);

    icon = lv_img_create(ctrl_box, NULL);
    lv_img_set_src(icon, &img_lv_demo_music_btn_loop);
    lv_obj_align(icon, NULL, LV_ALIGN_IN_TOP_MID, 95, 27);

    icon = lv_img_create(ctrl_box, NULL);
    lv_img_set_src(icon, &img_lv_demo_music_btn_prev);
    lv_obj_align(icon, NULL, LV_ALIGN_IN_TOP_MID, -45, 7);

    icon = lv_img_create(ctrl_box, NULL);
    lv_img_set_src(icon, &img_lv_demo_music_btn_play);
    lv_obj_align(icon, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

    icon = lv_img_create(ctrl_box, NULL);
    lv_img_set_src(icon, &img_lv_demo_music_btn_next);
    lv_obj_align(icon, NULL, LV_ALIGN_IN_TOP_MID, 45, 7);

    LV_IMG_DECLARE(img_lv_demo_music_slider_knob);
    lv_obj_t * slider = lv_slider_create(ctrl_box, NULL);
    lv_obj_set_size(slider, 210, 3);
    lv_obj_align(slider, NULL, LV_ALIGN_IN_TOP_MID, -10, 75);
    lv_obj_set_style_local_pattern_image(slider, LV_SLIDER_PART_KNOB, LV_STATE_DEFAULT, &img_lv_demo_music_slider_knob);
    lv_obj_set_style_local_bg_opa(slider, LV_SLIDER_PART_KNOB, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_obj_set_style_local_pad_all(slider, LV_SLIDER_PART_KNOB, LV_STATE_DEFAULT, 20);
    lv_obj_set_style_local_bg_grad_dir(slider, LV_SLIDER_PART_INDIC, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
    lv_obj_set_style_local_bg_color(slider, LV_SLIDER_PART_INDIC, LV_STATE_DEFAULT, lv_color_hex(0x569af8));
    lv_obj_set_style_local_bg_grad_color(slider, LV_SLIDER_PART_INDIC, LV_STATE_DEFAULT, lv_color_hex(0xa666f1));
    lv_obj_set_style_local_outline_width(slider, LV_SLIDER_PART_BG, LV_STATE_DEFAULT, 0);

    time_obj = lv_label_create(ctrl_box, NULL);
    lv_obj_set_style_local_text_font(time_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_small);
    lv_obj_set_style_local_text_color(time_obj, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x8a86b8));
    lv_label_set_text(time_obj, "0:00");
    lv_obj_align(time_obj, NULL, LV_ALIGN_IN_TOP_RIGHT, -1, 67);

    lv_obj_t * label = lv_label_create(ctrl_box, NULL);
    lv_label_set_text(label, "ALL TRACKS");
    lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_medium);
    lv_obj_set_style_local_text_color(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x8a86b8));
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 100);

    lv_obj_t * handle = lv_obj_create(ctrl_box, NULL);
    lv_obj_set_size(handle, 40, 2);
    lv_obj_align(handle, NULL, LV_ALIGN_IN_TOP_MID, 0, 120);
    lv_obj_set_style_local_bg_color(handle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x8a86b8));
    lv_obj_set_style_local_border_width(handle, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);

}

void lv_demo_music_set_text(const char * title, const char * subtitle, const char * genre)
{
    lv_label_set_text(title_obj, title);
    lv_label_set_text(subtitle_obj, subtitle);
    lv_label_set_text(genre_obj, genre);
}

void lv_demo_music_play(void)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_values(&a, 0, sizeof(spectrum) / sizeof(spectrum[0]) - 1);
    lv_anim_set_exec_cb(&a, spectrum_anim_cb);
    lv_anim_set_var(&a, spectrum_obj);
    lv_anim_set_time(&a, (sizeof(spectrum) / sizeof(spectrum[0]) * 1000) / 30);
    lv_anim_set_playback_time(&a, 0);
    lv_anim_set_repeat_delay(&a, 300);
    lv_anim_set_delay(&a, 500);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}

void lv_demo_music_stop(void)
{
    lv_anim_del(spectrum_obj, spectrum_anim_cb);
    spectrum_i = 0;
    lv_obj_invalidate(spectrum_obj);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


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
                r[t] += amain * amod * 1.0;

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

            lv_draw_triangle(tri, mask, &draw_dsc);

            tri[1].x = tri[0].x - x1;
            tri[2].x = tri[0].x - x2;
            lv_draw_triangle(tri, mask, &draw_dsc);
        }

        LV_IMG_DECLARE(conver_1);
        lv_draw_img_dsc_t img_dsc;
        lv_draw_img_dsc_init(&img_dsc);
        img_dsc.zoom = 256 + spectrum[spectrum_i][0];
        img_dsc.pivot.x = 100;
        img_dsc.pivot.y = 100;

        lv_area_t a;
        a.x1 = obj->coords.x1 + (lv_obj_get_width(obj) - conver_1.header.w) / 2 + 5;
        a.y1 = obj->coords.y1 + (lv_obj_get_height(obj) - conver_1.header.h) / 2 + 5;
        a.x2 = a.x1 + conver_1.header.w - 1;
        a.y2 = a.y1 + conver_1.header.w - 1;
        lv_draw_img(&a, mask, &conver_1, &img_dsc);
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
}
