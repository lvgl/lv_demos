/**
 * @file lv_demo_widgets.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_demo.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef enum {
    DISP_SMALL,
    DISP_MEDIUM,
    DISP_LARGE,
}disp_size_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void profile_create(lv_obj_t * parent);
static void analytics_create(lv_obj_t * parent);
static void shop_create(lv_obj_t * parent);
static void color_changer_create(lv_obj_t * parent);

static lv_obj_t * create_meter_box(lv_obj_t * parent, const char * title, const char * text1, const char * text2, const char * text3);
static lv_obj_t * create_shop_item(lv_obj_t * parent, const void * img_src, const char * name, const char * category, const char * price);

static void color_changer_event_cb(lv_obj_t * obj, lv_event_t e);
static void color_event_cb(lv_obj_t * obj, lv_event_t e);
static void ta_event_cb(lv_obj_t * ta, lv_event_t e);
static void birthday_event_cb(lv_obj_t * ta, lv_event_t e);
static void calendar_event_cb(lv_obj_t * obj, lv_event_t e);
static void slider_event_cb(lv_obj_t * obj, lv_event_t e);
static void chart_event_cb(lv_obj_t * obj, lv_event_t e);
static void shop_chart_event_cb(lv_obj_t * obj, lv_event_t e);
static void meter1_indic1_anim_cb(void * var, int32_t v);
static void meter1_indic2_anim_cb(void * var, int32_t v);
static void meter1_indic3_anim_cb(void * var, int32_t v);
static void meter2_timer_cb(lv_timer_t * timer);
static void meter3_anim_cb(void * var, int32_t v);

/**********************
 *  STATIC VARIABLES
 **********************/
static disp_size_t disp_size;

static lv_obj_t * tv;
static lv_obj_t * calendar;
static lv_obj_t * calendar_header;
static lv_style_t style_text_muted;
static lv_style_t style_title;
static lv_style_t style_subtitle;
static lv_style_t style_icon;
static lv_style_t style_bullet;
static lv_flex_t flex_list;
static lv_flex_t flex_row_wrap_center;
static lv_flex_t flex_column_wrap;

static lv_obj_t * meter1;
static lv_obj_t * meter2;
static lv_obj_t * meter3;

static lv_obj_t * chart1;
static lv_obj_t * chart2;
static lv_obj_t * chart3;

static lv_chart_series_t * ser1;
static lv_chart_series_t * ser2;
static lv_chart_series_t * ser3;
static lv_chart_series_t * ser4;

static const lv_font_t * font_title;
static const lv_font_t * font_icon;
static const lv_font_t * font_subtitle;
static const lv_font_t * font_normal;
static const lv_font_t * font_small;

static uint32_t session_desktop = 1000;
static uint32_t session_tablet = 1000;
static uint32_t session_mobile = 1000;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_widgets(void)
{
    if(LV_HOR_RES <= 320) disp_size = DISP_SMALL;
    else if(LV_HOR_RES < 720) disp_size = DISP_MEDIUM;
    else disp_size = DISP_LARGE;

    lv_coord_t tab_h;
    if(disp_size == DISP_LARGE) {
        tab_h = 70;
        font_title     =  &lv_font_montserrat_28;
        font_icon      =  &lv_font_montserrat_24;
        font_subtitle  =  &lv_font_montserrat_24;
        font_normal    =  &lv_font_montserrat_16;
        font_small     = &lv_font_montserrat_12;
    } else if(disp_size == DISP_MEDIUM) {
        tab_h = 60;
        font_title     =  &lv_font_montserrat_22;
        font_icon      =  &lv_font_montserrat_18;
        font_subtitle  =  &lv_font_montserrat_18;
        font_normal    =  &lv_font_montserrat_14;
        font_small     = &lv_font_montserrat_10;
    } else if(disp_size == DISP_SMALL) {
        tab_h = 50;
        font_title     =  &lv_font_montserrat_22;
        font_icon      =  &lv_font_montserrat_16;
        font_subtitle  =  &lv_font_montserrat_16;
        font_normal    =  &lv_font_montserrat_12;
        font_small     = &lv_font_montserrat_10;
    }

    tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, tab_h);

    lv_obj_set_style_text_font(lv_scr_act(), LV_PART_MAIN, LV_STATE_DEFAULT, font_normal);
    lv_obj_set_style_content_font(lv_scr_act(), LV_PART_MAIN, LV_STATE_DEFAULT, font_normal);

    if(disp_size == DISP_LARGE) {
        lv_obj_set_style_pad_left(lv_tabview_get_tab_btns(tv), LV_PART_MAIN, LV_STATE_DEFAULT, LV_HOR_RES / 2);
    }

    lv_style_init(&style_text_muted);
    lv_style_set_text_opa(&style_text_muted, LV_OPA_50);

    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title, font_title);

    lv_style_init(&style_subtitle);
    lv_style_set_text_font(&style_subtitle, font_subtitle);

    lv_style_init(&style_icon);
    lv_style_set_text_color(&style_icon, lv_theme_get_color_primary(NULL));
    lv_style_set_text_font(&style_icon, font_icon);

    lv_style_init(&style_bullet);
    lv_style_set_content_opa(&style_bullet, LV_OPA_50);
    lv_style_set_content_align(&style_bullet, LV_ALIGN_OUT_RIGHT_MID);
    lv_style_set_content_ofs_x(&style_bullet, LV_DPX(10));
    lv_style_set_border_width(&style_bullet, 0);
    lv_style_set_radius(&style_bullet, LV_RADIUS_CIRCLE);

    lv_flex_init(&flex_list);
    lv_flex_set_flow(&flex_list, LV_FLEX_FLOW_COLUMN);

    lv_flex_init(&flex_row_wrap_center);
    lv_flex_set_flow(&flex_row_wrap_center, LV_FLEX_FLOW_ROW_WRAP);
    lv_flex_set_place(&flex_row_wrap_center, LV_FLEX_PLACE_CENTER, LV_FLEX_PLACE_START, LV_FLEX_PLACE_START);


    lv_flex_init(&flex_column_wrap);
    lv_flex_set_flow(&flex_column_wrap, LV_FLEX_FLOW_COLUMN_WRAP);
    lv_flex_set_place(&flex_column_wrap, LV_FLEX_PLACE_CENTER, LV_FLEX_PLACE_START, LV_FLEX_PLACE_START);


    lv_obj_t * t1 = lv_tabview_add_tab(tv, "Profile");
    lv_obj_t * t2 = lv_tabview_add_tab(tv, "Analytics");
    lv_obj_t * t3 = lv_tabview_add_tab(tv, "Shop");
    profile_create(t1);
    analytics_create(t2);
    shop_create(t3);

    color_changer_create(tv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void profile_create(lv_obj_t * parent)
{
    lv_obj_t * panel1 = lv_obj_create(parent, NULL);
    lv_obj_set_height(panel1, LV_SIZE_CONTENT);

    LV_IMG_DECLARE(img_demo_widgets_avatar);
    lv_obj_t * avatar = lv_img_create(panel1, NULL);
    lv_img_set_src(avatar, &img_demo_widgets_avatar);

    lv_obj_t * name = lv_label_create(panel1, NULL);
    lv_label_set_text(name, "Elena Smith");
    lv_obj_add_style(name, LV_PART_MAIN, LV_STATE_DEFAULT, &style_title);

    lv_obj_t * dsc = lv_label_create(panel1, NULL);
    lv_obj_add_style(dsc, LV_PART_MAIN, LV_STATE_DEFAULT, &style_text_muted);
    lv_label_set_text(dsc, "This is a short description of me. Take a look at my profile!" );
    lv_label_set_long_mode(dsc, LV_LABEL_LONG_WRAP);

    lv_obj_t * email_icn = lv_label_create(panel1, NULL);
    lv_obj_add_style(email_icn, LV_PART_MAIN, LV_STATE_DEFAULT, &style_icon);
    lv_label_set_text(email_icn, LV_SYMBOL_ENVELOPE);

    lv_obj_t * email_label = lv_label_create(panel1, NULL);
    lv_label_set_text(email_label, "elena@smith.com");

    lv_obj_t * call_icn = lv_label_create(panel1, NULL);
    lv_obj_add_style(call_icn, LV_PART_MAIN, LV_STATE_DEFAULT, &style_icon);
    lv_label_set_text(call_icn, LV_SYMBOL_CALL);

    lv_obj_t * call_label = lv_label_create(panel1, NULL);
    lv_label_set_text(call_label, "+79 246 123 4567");

    lv_obj_t * log_out_btn = lv_btn_create(panel1, NULL);
    lv_obj_set_height(log_out_btn, LV_SIZE_CONTENT);

    lv_obj_t * label = lv_label_create(log_out_btn, NULL);
    lv_label_set_text(label, "Log out");

    lv_obj_t * invite_btn = lv_btn_create(panel1, NULL);
    lv_obj_add_state(invite_btn, LV_STATE_DISABLED);
    lv_obj_set_height(invite_btn, LV_SIZE_CONTENT);

    label = lv_label_create(invite_btn, NULL);
    lv_label_set_text(label, "Invite");

    /*Create a keyboard*/
    lv_obj_t * kb = lv_keyboard_create(lv_scr_act());
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

    /*Create the second panel*/
    lv_obj_t * panel2 = lv_obj_create(parent, NULL);
    lv_obj_set_height(panel2, LV_SIZE_CONTENT);

    lv_obj_t * panel2_title = lv_label_create(panel2, NULL);
    lv_label_set_text(panel2_title, "Your profile");
    lv_obj_add_style(panel2_title, LV_PART_MAIN, LV_STATE_DEFAULT, &style_subtitle);

    lv_obj_t * user_name_label = lv_label_create(panel2, NULL);
    lv_label_set_text(user_name_label, "User name");
    lv_obj_add_style(user_name_label, LV_PART_MAIN, LV_STATE_DEFAULT, &style_text_muted);

    lv_obj_t * user_name = lv_textarea_create(panel2, NULL);
    lv_textarea_set_one_line(user_name, true);
    lv_textarea_set_placeholder_text(user_name, "Your name");
    lv_obj_add_event_cb(user_name, ta_event_cb, kb);

    lv_obj_t * password_label = lv_label_create(panel2, NULL);
    lv_label_set_text(password_label, "Password");
    lv_obj_add_style(password_label, LV_PART_MAIN, LV_STATE_DEFAULT, &style_text_muted);

    lv_obj_t * password = lv_textarea_create(panel2, NULL);
    lv_textarea_set_one_line(password, true);
    lv_textarea_set_password_mode(password, true);
    lv_textarea_set_placeholder_text(password, "Min. 8 chars.");
    lv_obj_add_event_cb(password, ta_event_cb, kb);

    lv_obj_t * gender_label = lv_label_create(panel2, NULL);
    lv_label_set_text(gender_label, "Gender");
    lv_obj_add_style(gender_label, LV_PART_MAIN, LV_STATE_DEFAULT, &style_text_muted);

    lv_obj_t * gender = lv_dropdown_create(panel2, NULL);
    lv_dropdown_set_options_static(gender, "Male\nFemale\nOther");

    lv_obj_t * birthday_label = lv_label_create(panel2, NULL);
    lv_label_set_text(birthday_label, "Birthday");
    lv_obj_add_style(birthday_label, LV_PART_MAIN, LV_STATE_DEFAULT, &style_text_muted);

    lv_obj_t * birthdate = lv_textarea_create(panel2, NULL);
    lv_textarea_set_one_line(birthdate, true);
    lv_obj_add_event_cb(birthdate, birthday_event_cb, NULL);

    /*Create the third panel*/
    lv_obj_t * panel3 = lv_obj_create(parent, NULL);
    lv_obj_t * panel3_title = lv_label_create(panel3, NULL);
    lv_label_set_text(panel3_title, "Your skills");
    lv_obj_add_style(panel3_title, LV_PART_MAIN, LV_STATE_DEFAULT, &style_subtitle);

    lv_obj_t * experience_label = lv_label_create(panel3, NULL);
    lv_label_set_text(experience_label, "Experience");
    lv_obj_add_style(experience_label, LV_PART_MAIN, LV_STATE_DEFAULT, &style_text_muted);

    lv_obj_t * slider1 = lv_slider_create(panel3, NULL);
    lv_obj_set_width(slider1, LV_SIZE_PCT(95));
    lv_obj_add_event_cb(slider1, slider_event_cb, NULL);
    lv_obj_refresh_ext_draw_size(slider1);

    lv_obj_t * team_player_label = lv_label_create(panel3, NULL);
    lv_label_set_text(team_player_label, "Team player");
    lv_obj_add_style(team_player_label, LV_PART_MAIN, LV_STATE_DEFAULT, &style_text_muted);

    lv_obj_t * sw1 = lv_switch_create(panel3, NULL);

    lv_obj_t * hard_working_label = lv_label_create(panel3, NULL);
    lv_label_set_text(hard_working_label, "Hard-working");
    lv_obj_add_style(hard_working_label, LV_PART_MAIN, LV_STATE_DEFAULT, &style_text_muted);

    lv_obj_t * sw2 = lv_switch_create(panel3, NULL);

    if(disp_size == DISP_LARGE) {
        static lv_grid_t grid_main;
        lv_grid_init(&grid_main);

        static lv_coord_t grid_main_col_dsc[2] = {LV_GRID_FR(1), LV_GRID_FR(1)};
        static lv_coord_t grid_main_row_dsc[2] = {LV_GRID_CONTENT, LV_GRID_CONTENT};
        lv_grid_set_template(&grid_main, grid_main_col_dsc, 2, grid_main_row_dsc, 2);

        /*Create the top panel*/
        static lv_coord_t grid_1_col_dsc[6] = {LV_GRID_CONTENT, 5, LV_GRID_CONTENT, LV_GRID_FR(2), LV_GRID_FR(1), LV_GRID_FR(1)};
        static lv_coord_t grid1_1_dsc[5] = {LV_GRID_CONTENT, LV_GRID_CONTENT, 10, LV_GRID_CONTENT, LV_GRID_CONTENT};
        static lv_grid_t grid_1;
        lv_grid_init(&grid_1);
        lv_grid_set_template(&grid_1, grid_1_col_dsc, 6, grid1_1_dsc, 5);

        static lv_coord_t grid_2_col_dsc[2] = {LV_GRID_FR(1), LV_GRID_FR(1)};
        static lv_coord_t grid_2_row_dsc[7] = {
                LV_GRID_CONTENT,  /*Title*/
                5,                /*Separator*/
                LV_GRID_CONTENT,  /*Box title*/
                30,               /*Boxes*/
                5,                /*Separator*/
                LV_GRID_CONTENT,  /*Box title*/
                30,               /*Boxes*/
        };

        static lv_grid_t grid_2;
        lv_grid_init(&grid_2);
        lv_grid_set_template(&grid_2, grid_2_col_dsc, 2, grid_2_row_dsc, 7);

        lv_obj_set_layout(parent, &grid_main);

        lv_obj_set_grid_cell(panel1, LV_GRID_STRETCH, 0, 2, LV_GRID_CENTER, 0, 1);

        lv_obj_set_layout(panel1, &grid_1);
        lv_obj_set_grid_cell(avatar, LV_GRID_CENTER, 0, 1, LV_GRID_CENTER, 0, 5);
        lv_obj_set_grid_cell(name, LV_GRID_START, 2, 2, LV_GRID_CENTER, 0, 1);
        lv_obj_set_grid_cell(dsc, LV_GRID_STRETCH, 2, 4, LV_GRID_START, 1, 1);
        lv_obj_set_grid_cell(email_icn, LV_GRID_CENTER, 2, 1, LV_GRID_CENTER, 3, 1);
        lv_obj_set_grid_cell(email_label, LV_GRID_START, 3, 1, LV_GRID_CENTER, 3, 1);
        lv_obj_set_grid_cell(call_icn, LV_GRID_CENTER, 2, 1, LV_GRID_CENTER, 4, 1);
        lv_obj_set_grid_cell(call_label, LV_GRID_START, 3, 1, LV_GRID_CENTER, 4, 1);
        lv_obj_set_grid_cell(log_out_btn, LV_GRID_STRETCH, 4, 1, LV_GRID_CENTER, 3, 2);
        lv_obj_set_grid_cell(invite_btn, LV_GRID_STRETCH, 5, 1, LV_GRID_CENTER, 3, 2);

        lv_obj_set_grid_cell(panel2, LV_GRID_STRETCH, 0, 1, LV_GRID_START, 1, 1);
        lv_obj_set_layout(panel2, &grid_2);
        lv_obj_set_grid_cell(panel2_title, LV_GRID_START, 0, 2, LV_GRID_CENTER, 0, 1);
        lv_obj_set_grid_cell(user_name, LV_GRID_STRETCH, 0, 1, LV_GRID_CENTER, 3, 1);
        lv_obj_set_grid_cell(user_name_label, LV_GRID_START, 0, 1, LV_GRID_START, 2, 1);
        lv_obj_set_grid_cell(password, LV_GRID_STRETCH, 1, 1, LV_GRID_CENTER, 3, 1);
        lv_obj_set_grid_cell(password_label, LV_GRID_START, 1, 1, LV_GRID_START, 2, 1);
        lv_obj_set_grid_cell(birthdate, LV_GRID_STRETCH, 1, 1, LV_GRID_CENTER, 6, 1);
        lv_obj_set_grid_cell(birthday_label, LV_GRID_START, 1, 1, LV_GRID_START, 5, 1);
        lv_obj_set_grid_cell(gender, LV_GRID_STRETCH, 0, 1, LV_GRID_CENTER, 6, 1);
        lv_obj_set_grid_cell(gender_label, LV_GRID_START, 0, 1, LV_GRID_START, 5, 1);


        lv_obj_set_grid_cell(panel3, LV_GRID_STRETCH, 1, 1, LV_GRID_STRETCH, 1, 1);
        lv_obj_set_layout(panel3, &grid_2);
        lv_obj_set_grid_cell(panel3_title, LV_GRID_START, 0, 2, LV_GRID_CENTER, 0, 1);
        lv_obj_set_grid_cell(slider1, LV_GRID_CENTER, 0, 2, LV_GRID_CENTER, 3, 1);
        lv_obj_set_grid_cell(experience_label, LV_GRID_START, 0, 1, LV_GRID_START, 2, 1);
        lv_obj_set_grid_cell(sw2, LV_GRID_START, 1, 1, LV_GRID_CENTER, 6, 1);
        lv_obj_set_grid_cell(hard_working_label, LV_GRID_START, 0, 1, LV_GRID_START, 5, 1);
        lv_obj_set_grid_cell(sw1, LV_GRID_START, 0, 1, LV_GRID_CENTER, 6, 1);
        lv_obj_set_grid_cell(team_player_label, LV_GRID_START, 1, 1, LV_GRID_START, 5, 1);
    }
    else if(disp_size == DISP_MEDIUM) {
        static lv_grid_t grid_main;
        lv_grid_init(&grid_main);

        static lv_coord_t grid_main_col_dsc[2] = {LV_GRID_FR(1), LV_GRID_FR(1)};
        static lv_coord_t grid_main_row_dsc[2] = {LV_GRID_CONTENT, LV_GRID_CONTENT};
        lv_grid_set_template(&grid_main, grid_main_col_dsc, 2, grid_main_row_dsc, 2);


        /*Create the top panel*/
        static lv_coord_t grid_1_col_dsc[4] = {LV_GRID_CONTENT, 1, LV_GRID_CONTENT, LV_GRID_FR(1)};
        static lv_coord_t grid_1_row_dsc[6] = {
                LV_GRID_CONTENT, /*Name*/
                LV_GRID_CONTENT, /*Description*/
                LV_GRID_CONTENT, /*Email*/
                -20,
                LV_GRID_CONTENT, /*Phone*/
                LV_GRID_CONTENT}; /*Buttons*/
        static lv_grid_t grid_1;
        lv_grid_init(&grid_1);
        lv_grid_set_template(&grid_1, grid_1_col_dsc, 4, grid_1_row_dsc, 6);


        static lv_coord_t grid_2_col_dsc[2] = {LV_GRID_FR(1), LV_GRID_FR(1)};
        static lv_coord_t grid_2_row_dsc[10] = {
                LV_GRID_CONTENT,  /*Title*/
                5,                /*Separator*/
                LV_GRID_CONTENT,  /*Box title*/
                40,               /*Box*/
                LV_GRID_CONTENT,  /*Box title*/
                40,               /*Box*/
                LV_GRID_CONTENT,  /*Box title*/
                40,               /*Box*/
                LV_GRID_CONTENT,  /*Box title*/
                40,               /*Box*/
        };

        static lv_grid_t grid_2;
        lv_grid_init(&grid_2);
        lv_grid_set_template(&grid_2, grid_2_col_dsc, 2, grid_2_row_dsc, 10);

        lv_obj_set_layout(parent, &grid_main);
        lv_obj_set_grid_cell(panel1, LV_GRID_STRETCH, 0, 2, LV_GRID_CENTER, 0, 1);

        lv_obj_set_width(log_out_btn, 120);
        lv_obj_set_width(invite_btn, 120);

        lv_obj_set_layout(panel1, &grid_1);
        lv_obj_set_grid_cell(avatar, LV_GRID_CENTER, 0, 1, LV_GRID_START, 0, 4);
        lv_obj_set_grid_cell(name, LV_GRID_START, 2, 2, LV_GRID_CENTER, 0, 1);
        lv_obj_set_grid_cell(dsc, LV_GRID_STRETCH, 2, 2, LV_GRID_START, 1, 1);
        lv_obj_set_grid_cell(email_label, LV_GRID_START, 3, 1, LV_GRID_CENTER, 2, 1);
        lv_obj_set_grid_cell(email_icn, LV_GRID_CENTER, 2, 1, LV_GRID_CENTER, 2, 1);
        lv_obj_set_grid_cell(call_icn, LV_GRID_CENTER, 2, 1, LV_GRID_CENTER, 4, 1);
        lv_obj_set_grid_cell(call_label, LV_GRID_START, 3, 1, LV_GRID_CENTER, 4, 1);
        lv_obj_set_grid_cell(log_out_btn, LV_GRID_START, 1, 1, LV_GRID_CENTER, 5, 1);
        lv_obj_set_grid_cell(invite_btn, LV_GRID_END, 3, 1, LV_GRID_CENTER, 5, 1);

        lv_obj_set_grid_cell(panel2, LV_GRID_STRETCH, 0, 1, LV_GRID_START, 1, 1);
        lv_obj_set_layout(panel2, &grid_2);
        lv_obj_set_grid_cell(panel2_title, LV_GRID_START, 0, 2, LV_GRID_CENTER, 0, 1);
        lv_obj_set_grid_cell(user_name_label, LV_GRID_START, 0, 2, LV_GRID_START, 2, 1);
        lv_obj_set_grid_cell(user_name, LV_GRID_STRETCH, 0, 2, LV_GRID_START, 3, 1);
        lv_obj_set_grid_cell(password_label, LV_GRID_START, 0, 2, LV_GRID_START, 4, 1);
        lv_obj_set_grid_cell(password, LV_GRID_STRETCH, 0, 2, LV_GRID_START, 5, 1);
        lv_obj_set_grid_cell(birthday_label, LV_GRID_START, 0, 2, LV_GRID_START, 6, 1);
        lv_obj_set_grid_cell(birthdate, LV_GRID_STRETCH, 0, 2, LV_GRID_START, 7, 1);
        lv_obj_set_grid_cell(gender_label, LV_GRID_START, 0, 2, LV_GRID_START, 8, 1);
        lv_obj_set_grid_cell(gender, LV_GRID_STRETCH, 0, 2, LV_GRID_START, 9, 1);

        lv_obj_set_grid_cell(panel3, LV_GRID_STRETCH, 1, 1, LV_GRID_STRETCH, 1, 1);
        lv_obj_set_layout(panel3, &grid_2);
        lv_obj_set_grid_cell(panel3_title, LV_GRID_START, 0, 2, LV_GRID_CENTER, 0, 1);
        lv_obj_set_grid_cell(slider1, LV_GRID_CENTER, 0, 2, LV_GRID_CENTER, 3, 1);
        lv_obj_set_grid_cell(experience_label, LV_GRID_START, 0, 1, LV_GRID_START, 2, 1);
        lv_obj_set_grid_cell(hard_working_label, LV_GRID_START, 0, 1, LV_GRID_START, 4, 1);
        lv_obj_set_grid_cell(sw2, LV_GRID_START, 0, 1, LV_GRID_START, 5, 1);
        lv_obj_set_grid_cell(team_player_label, LV_GRID_START, 0, 1, LV_GRID_START, 6, 1);
        lv_obj_set_grid_cell(sw1, LV_GRID_START, 0, 1, LV_GRID_START, 7, 1);
    }
    else if(disp_size == DISP_SMALL) {
        static lv_grid_t grid_main;
        lv_grid_init(&grid_main);

        static lv_coord_t grid_main_col_dsc[1] = {LV_GRID_FR(1)};
        static lv_coord_t grid_main_row_dsc[3] = {LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_CONTENT};
        lv_grid_set_template(&grid_main, grid_main_col_dsc, 1, grid_main_row_dsc, 3);


        /*Create the top panel*/
        static lv_coord_t grid_1_col_dsc[2] = {LV_GRID_CONTENT, LV_GRID_FR(1)};
        static lv_coord_t grid_1_row_dsc[7] = {LV_GRID_CONTENT, /*Avatar*/
                                               LV_GRID_CONTENT, /*Name*/
                                               LV_GRID_CONTENT, /*Description*/
                                               LV_GRID_CONTENT, /*Email*/
                                               LV_GRID_CONTENT, /*Phone number*/
                                               LV_GRID_CONTENT, /*Button1*/
                                               LV_GRID_CONTENT};/*Button2*/
        static lv_grid_t grid_1;
        lv_grid_init(&grid_1);
        lv_grid_set_template(&grid_1, grid_1_col_dsc, 2, grid_1_row_dsc, 7);


        static lv_coord_t grid_2_col_dsc[2] = {LV_GRID_FR(1), LV_GRID_FR(1)};
        static lv_coord_t grid_2_row_dsc[10] = {
                LV_GRID_CONTENT,  /*Title*/
                5,                /*Separator*/
                LV_GRID_CONTENT,  /*Box title*/
                40,               /*Box*/
                LV_GRID_CONTENT,  /*Box title*/
                40,               /*Box*/
                LV_GRID_CONTENT,  /*Box title*/
                40,               /*Box*/
                LV_GRID_CONTENT,  /*Box title*/
                40,               /*Box*/
        };

        static lv_grid_t grid_2;
        lv_grid_init(&grid_2);
        lv_grid_set_template(&grid_2, grid_2_col_dsc, 2, grid_2_row_dsc, 10);

        lv_obj_set_layout(parent, &grid_main);

        lv_obj_set_grid_cell(panel1, LV_GRID_STRETCH, 0, 1, LV_GRID_CENTER, 0, 1);

        lv_obj_set_style_text_align(dsc, LV_PART_MAIN, LV_STATE_DEFAULT, LV_TEXT_ALIGN_CENTER);

        lv_obj_set_layout(panel1, &grid_1);
        lv_obj_set_grid_cell(avatar, LV_GRID_CENTER, 0, 2, LV_GRID_CENTER, 0, 1);
        lv_obj_set_grid_cell(name, LV_GRID_CENTER, 0, 2, LV_GRID_CENTER, 1, 1);
        lv_obj_set_grid_cell(dsc, LV_GRID_STRETCH, 0, 2, LV_GRID_START, 2, 1);
        lv_obj_set_grid_cell(email_icn, LV_GRID_CENTER, 0, 1, LV_GRID_CENTER, 3, 1);
        lv_obj_set_grid_cell(email_label, LV_GRID_START, 1, 1, LV_GRID_CENTER, 3, 1);
        lv_obj_set_grid_cell(call_icn, LV_GRID_CENTER, 0, 1, LV_GRID_CENTER, 4, 1);
        lv_obj_set_grid_cell(call_label, LV_GRID_START, 1, 1, LV_GRID_CENTER, 4, 1);
        lv_obj_set_grid_cell(log_out_btn, LV_GRID_STRETCH, 0, 2, LV_GRID_CENTER, 5, 1);
        lv_obj_set_grid_cell(invite_btn, LV_GRID_STRETCH, 0, 2, LV_GRID_CENTER, 6, 1);

        lv_obj_set_grid_cell(panel2, LV_GRID_STRETCH, 0, 1, LV_GRID_START, 1, 1);
        lv_obj_set_layout(panel2, &grid_2);
        lv_obj_set_grid_cell(panel2_title, LV_GRID_START, 0, 2, LV_GRID_CENTER, 0, 1);
        lv_obj_set_grid_cell(user_name_label, LV_GRID_START, 0, 2, LV_GRID_START, 2, 1);
        lv_obj_set_grid_cell(user_name, LV_GRID_STRETCH, 0, 2, LV_GRID_START, 3, 1);
        lv_obj_set_grid_cell(password_label, LV_GRID_START, 0, 2, LV_GRID_START, 4, 1);
        lv_obj_set_grid_cell(password, LV_GRID_STRETCH, 0, 2, LV_GRID_START, 5, 1);
        lv_obj_set_grid_cell(birthday_label, LV_GRID_START, 0, 2, LV_GRID_START, 6, 1);
        lv_obj_set_grid_cell(birthdate, LV_GRID_STRETCH, 0, 2, LV_GRID_START, 7, 1);
        lv_obj_set_grid_cell(gender_label, LV_GRID_START, 0, 2, LV_GRID_START, 8, 1);
        lv_obj_set_grid_cell(gender, LV_GRID_STRETCH, 0, 2, LV_GRID_START, 9, 1);

        lv_obj_set_height(panel3, LV_SIZE_CONTENT);
        lv_obj_set_grid_cell(panel3, LV_GRID_STRETCH, 0, 1, LV_GRID_START, 2, 1);
        lv_obj_set_layout(panel3, &grid_2);
        lv_obj_set_grid_cell(panel3_title, LV_GRID_START, 0, 2, LV_GRID_CENTER, 0, 1);
        lv_obj_set_grid_cell(experience_label, LV_GRID_START, 0, 1, LV_GRID_START, 2, 1);
        lv_obj_set_grid_cell(slider1, LV_GRID_CENTER, 0, 2, LV_GRID_CENTER, 3, 1);
        lv_obj_set_grid_cell(hard_working_label, LV_GRID_START, 0, 1, LV_GRID_START, 4, 1);
        lv_obj_set_grid_cell(sw1, LV_GRID_START, 0, 1, LV_GRID_START, 5, 1);
        lv_obj_set_grid_cell(team_player_label, LV_GRID_START, 1, 1, LV_GRID_START, 4, 1);
        lv_obj_set_grid_cell(sw2, LV_GRID_START, 1, 1, LV_GRID_START, 5, 1);
    }
}


static void analytics_create(lv_obj_t * parent)
{
    lv_obj_set_layout(parent, &flex_row_wrap_center);

    static lv_coord_t grid_chart_row_dsc[3] = {LV_GRID_CONTENT, LV_GRID_FR(1), 10};
    static lv_coord_t grid_chart_col_dsc[2] = {20, LV_GRID_FR(1)};
    static lv_grid_t grid_chart;
    lv_grid_init(&grid_chart);
    lv_grid_set_template(&grid_chart, grid_chart_col_dsc, 2, grid_chart_row_dsc, 3);

    lv_obj_t * chart1_cont = lv_obj_create(parent, NULL);
    lv_obj_set_flex_grow(chart1_cont, 1);
    lv_obj_set_layout(chart1_cont, &grid_chart);

    if(disp_size <= DISP_MEDIUM) {
        lv_coord_t h = lv_obj_get_height_visible(chart1_cont);
        lv_obj_set_height(chart1_cont, LV_MIN(h, 300));
    }
    else lv_obj_set_height(chart1_cont, 300);

    lv_obj_t * title = lv_label_create(chart1_cont, NULL);
    lv_label_set_text(title, "Unique visitors");
    lv_obj_add_style(title, LV_PART_MAIN, LV_STATE_DEFAULT, &style_subtitle);
    lv_obj_set_grid_cell(title, LV_GRID_START, 0, 2, LV_GRID_START, 0, 1);

    chart1 = lv_chart_create(chart1_cont, NULL);
    lv_obj_set_grid_cell(chart1, LV_GRID_STRETCH, 1, 1, LV_GRID_STRETCH, 1, 1);
    lv_chart_set_axis_tick(chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 0, 5, 1, true, 80);
    lv_chart_set_axis_tick(chart1, LV_CHART_AXIS_X, 0, 0, 12, 1, true, 50);
    lv_chart_set_div_line_count(chart1, 0, 12);
    lv_chart_set_point_count(chart1, 12);
    lv_obj_add_event_cb(chart1, chart_event_cb, NULL);
    if(disp_size == DISP_SMALL) lv_chart_set_zoom_x(chart1, 256 * 3);
    else if(disp_size == DISP_MEDIUM) lv_chart_set_zoom_x(chart1, 256 * 2);

    lv_obj_set_style_border_side(chart1, LV_PART_MAIN, LV_STATE_DEFAULT, LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_BOTTOM);
    lv_obj_set_style_radius(chart1, LV_PART_MAIN, LV_STATE_DEFAULT, 0);

    ser1 = lv_chart_add_series(chart1, lv_theme_get_color_primary(chart1), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));
    lv_chart_set_next_value(chart1, ser1, lv_rand(10, 80));

    lv_obj_t * chart2_cont = lv_obj_create(parent, NULL);
    lv_obj_add_flag(chart2_cont, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    lv_obj_set_flex_grow(chart2_cont, 1);

    if(disp_size <= DISP_MEDIUM) {
        lv_coord_t h = lv_obj_get_height_visible(chart1_cont);
        lv_obj_set_height(chart2_cont, LV_MIN(h, 300));
    }
    else lv_obj_set_height(chart2_cont, 300);

    lv_obj_set_layout(chart2_cont, &grid_chart);

    title = lv_label_create(chart2_cont, NULL);
    lv_label_set_text(title, "Monthly revenue");
    lv_obj_add_style(title, LV_PART_MAIN, LV_STATE_DEFAULT, &style_subtitle);
    lv_obj_set_grid_cell(title, LV_GRID_START, 0, 2, LV_GRID_START, 0, 1);

    chart2 = lv_chart_create(chart2_cont, NULL);
    lv_obj_set_grid_cell(chart2, LV_GRID_STRETCH, 1, 1, LV_GRID_STRETCH, 1, 1);
    lv_chart_set_axis_tick(chart2, LV_CHART_AXIS_PRIMARY_Y, 0, 0, 5, 1, true, 80);
    lv_chart_set_axis_tick(chart2, LV_CHART_AXIS_X, 0, 0, 12, 1, true, 50);
    lv_obj_set_size(chart2, LV_SIZE_PCT(100), LV_SIZE_PCT(100));
    lv_chart_set_type(chart2, LV_CHART_TYPE_BAR);
    lv_chart_set_div_line_count(chart2, 6, 0);
    lv_chart_set_point_count(chart2, 12);
    lv_obj_add_event_cb(chart2, chart_event_cb, NULL);
    lv_chart_set_zoom_x(chart2, 256 * 2);
    lv_obj_set_style_border_side(chart2, LV_PART_MAIN, LV_STATE_DEFAULT, LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_BOTTOM);
    lv_obj_set_style_radius(chart2, LV_PART_MAIN, LV_STATE_DEFAULT, 0);

    if(disp_size == DISP_SMALL) {
        lv_obj_set_style_pad_gap(chart2, LV_PART_ITEMS, LV_STATE_DEFAULT, 0);
        lv_obj_set_style_pad_gap(chart2, LV_PART_MAIN, LV_STATE_DEFAULT, 2);
    }
    else if(disp_size == DISP_LARGE) {
        lv_obj_set_style_pad_gap(chart2, LV_PART_MAIN, LV_STATE_DEFAULT, 16);
    }

    ser2 = lv_chart_add_series(chart2, lv_color_grey_lighten_1(), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_next_value(chart2, ser2, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser2, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser2, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser2, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser2, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser2, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser2, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser2, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser2, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser2, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser2, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser2, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser2, lv_rand(10, 80));

    ser3 = lv_chart_add_series(chart2, lv_theme_get_color_primary(chart1), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_next_value(chart2, ser3, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser3, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser3, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser3, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser3, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser3, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser3, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser3, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser3, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser3, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser3, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser3, lv_rand(10, 80));
    lv_chart_set_next_value(chart2, ser3, lv_rand(10, 80));

    lv_meter_scale_t * scale;
    lv_meter_indicator_t *indic;
    meter1 = create_meter_box(parent, "Monthly Target", "Revenue: 63%", "Sales: 44%", "Costs: 58%");
    lv_obj_add_flag(lv_obj_get_parent(meter1), LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    scale = lv_meter_add_scale(meter1);
    lv_meter_set_scale_range(meter1, scale, 0, 100, 270, 90);
    lv_meter_set_scale_ticks(meter1, scale, 0, 0, 0, lv_color_black());

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_values(&a, 20, 100);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);

    indic = lv_meter_add_arc(meter1, scale, 15, lv_color_blue(), 0);
    lv_anim_set_exec_cb(&a, meter1_indic1_anim_cb);
    lv_anim_set_var(&a, indic);
    lv_anim_set_time(&a, 4100);
    lv_anim_set_playback_time(&a, 2700);
    lv_anim_start(&a);

    indic = lv_meter_add_arc(meter1, scale, 15, lv_color_red(), -20);
    lv_anim_set_exec_cb(&a, meter1_indic2_anim_cb);
    lv_anim_set_var(&a, indic);
    lv_anim_set_time(&a, 2600);
    lv_anim_set_playback_time(&a, 3200);
    a.user_data = indic;
    lv_anim_start(&a);

    indic = lv_meter_add_arc(meter1, scale, 15, lv_color_green(), -40);
    lv_anim_set_exec_cb(&a, meter1_indic3_anim_cb);
    lv_anim_set_var(&a, indic);
    lv_anim_set_time(&a, 2800);
    lv_anim_set_playback_time(&a, 1800);
    lv_anim_start(&a);

    meter2 = create_meter_box(parent, "Sessions", "Desktop: ", "Tablet: ", "Mobile: ");
    if(disp_size < DISP_LARGE) lv_obj_add_flag(lv_obj_get_parent(meter2), LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    scale = lv_meter_add_scale(meter2);
    lv_meter_set_scale_range(meter2, scale, 0, 100, 360, 90);
    lv_meter_set_scale_ticks(meter2, scale, 0, 0, 0, lv_color_black());

    static lv_meter_indicator_t * meter2_indic[3];
    meter2_indic[0] = lv_meter_add_arc(meter2, scale, 20, lv_color_red(), -10);
    lv_meter_set_indicator_start_value(meter2, meter2_indic[0], 0);
    lv_meter_set_indicator_end_value(meter2, meter2_indic[0], 39);

    meter2_indic[1] = lv_meter_add_arc(meter2, scale, 30, lv_color_blue(), 0);
    lv_meter_set_indicator_start_value(meter2, meter2_indic[1], 40);
    lv_meter_set_indicator_end_value(meter2, meter2_indic[1], 69);

    meter2_indic[2] = lv_meter_add_arc(meter2, scale, 10, lv_color_green(), -20);
    lv_meter_set_indicator_start_value(meter2, meter2_indic[2], 70);
    lv_meter_set_indicator_end_value(meter2, meter2_indic[2], 99);

    lv_timer_create(meter2_timer_cb, 100, meter2_indic);

    meter3 = create_meter_box(parent, "Network Speed", "Low speed", "Normal Speed", "High Speed");
    if(disp_size < DISP_LARGE) lv_obj_add_flag(lv_obj_get_parent(meter3), LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    lv_obj_set_style_pad_hor(meter3, LV_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_size(meter2, LV_PART_INDICATOR, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_radius(meter3, LV_PART_INDICATOR, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
    lv_obj_set_style_bg_opa(meter3, LV_PART_INDICATOR, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_obj_set_style_bg_color(meter3, LV_PART_INDICATOR, LV_STATE_DEFAULT, lv_color_grey_darken_4());
    lv_obj_set_style_outline_color(meter3, LV_PART_INDICATOR, LV_STATE_DEFAULT, lv_color_white());
    lv_obj_set_style_outline_width(meter3, LV_PART_INDICATOR, LV_STATE_DEFAULT, 3);
    lv_obj_set_style_text_color(meter3, LV_PART_TICKS, LV_STATE_DEFAULT, lv_color_grey_darken_1());

    scale = lv_meter_add_scale(meter3);
    lv_meter_set_scale_range(meter3, scale, 10, 60, 220, 360 - 220);
    lv_meter_set_scale_ticks(meter3, scale, 21, 3, 17, lv_color_white());
    lv_meter_set_scale_major_ticks(meter3, scale, 4, 4, 22, lv_color_white(), 15);

    indic = lv_meter_add_arc(meter3, scale, 10, lv_color_red(), 0);
    lv_meter_set_indicator_start_value(meter3, indic, 0);
    lv_meter_set_indicator_end_value(meter3, indic, 20);

    indic = lv_meter_add_scale_lines(meter3, scale, lv_color_red_darken_3(), lv_color_red_darken_3(), true, 0);
    lv_meter_set_indicator_start_value(meter3, indic, 0);
    lv_meter_set_indicator_end_value(meter3, indic, 20);

    indic = lv_meter_add_arc(meter3, scale, 12, lv_color_blue(), 0);
    lv_meter_set_indicator_start_value(meter3, indic, 20);
    lv_meter_set_indicator_end_value(meter3, indic, 40);

    indic = lv_meter_add_scale_lines(meter3, scale, lv_color_blue_darken_3(), lv_color_blue_darken_3(), true, 0);
    lv_meter_set_indicator_start_value(meter3, indic, 20);
    lv_meter_set_indicator_end_value(meter3, indic, 40);

    indic = lv_meter_add_arc(meter3, scale, 10, lv_color_green(), 0);
    lv_meter_set_indicator_start_value(meter3, indic, 40);
    lv_meter_set_indicator_end_value(meter3, indic, 60);

    indic = lv_meter_add_scale_lines(meter3, scale, lv_color_green_darken_3(), lv_color_green_darken_3(), true, 0);
    lv_meter_set_indicator_start_value(meter3, indic, 40);
    lv_meter_set_indicator_end_value(meter3, indic, 60);

    indic = lv_meter_add_needle_line(meter3, scale, 4, lv_color_grey_darken_4(), -25);

    lv_obj_t * mbps_label = lv_label_create(meter3, NULL);
    lv_label_set_text(mbps_label, "-");
    lv_obj_add_style(mbps_label, LV_PART_MAIN, LV_STATE_DEFAULT, &style_title);

    lv_obj_t * mbps_unit_label = lv_label_create(meter3, NULL);
    lv_label_set_text(mbps_unit_label, "Mbps");

    lv_anim_init(&a);
    lv_anim_set_values(&a, 10, 60);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_exec_cb(&a, meter3_anim_cb);
    lv_anim_set_var(&a, indic);
    lv_anim_set_time(&a, 4100);
    lv_anim_set_playback_time(&a, 800);
    lv_anim_start(&a);

    lv_obj_update_layout(parent);
    if(disp_size == DISP_MEDIUM) {
        lv_obj_set_size(meter1, 200, 200);
        lv_obj_set_size(meter2, 200, 200);
        lv_obj_set_size(meter3, 200, 200);
    } else {
        lv_coord_t meter_w = lv_obj_get_width(meter1);
        lv_obj_set_height(meter1, meter_w);
        lv_obj_set_height(meter2, meter_w);
        lv_obj_set_height(meter3, meter_w);
    }

    lv_obj_align(mbps_label, NULL, LV_ALIGN_IN_TOP_MID, 10, 4 * lv_obj_get_height(meter3) / 8 + 10);
    lv_obj_align(mbps_unit_label, mbps_label, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, 0);
}
void shop_create(lv_obj_t * parent)
{
    lv_obj_set_layout(parent, &flex_row_wrap_center);

    lv_obj_t * panel1 = lv_obj_create(parent, NULL);
    lv_obj_set_size(panel1, LV_SIZE_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_style_pad_bottom(panel1, LV_PART_MAIN, LV_STATE_DEFAULT, 30);

    lv_obj_t * title = lv_label_create(panel1, NULL);
    lv_label_set_text(title, "Monthly Summary");
    lv_obj_add_style(title, LV_PART_MAIN, LV_STATE_DEFAULT, &style_subtitle);

    lv_obj_t * date = lv_label_create(panel1, NULL);
    lv_label_set_text(date, "8-15 July, 2021");
    lv_obj_add_style(date, LV_PART_MAIN, LV_STATE_DEFAULT, &style_text_muted);

    lv_obj_t * amount = lv_label_create(panel1, NULL);
    lv_label_set_text(amount, "$27,123.25");
    lv_obj_add_style(amount, LV_PART_MAIN, LV_STATE_DEFAULT, &style_title);

    lv_obj_t * hint = lv_label_create(panel1, NULL);
    lv_label_set_text(hint, LV_SYMBOL_UP" 17% growth this week");
    lv_obj_set_style_text_color(hint, LV_PART_MAIN, LV_STATE_DEFAULT, lv_color_green());

    chart3 = lv_chart_create(panel1, NULL);
    lv_chart_set_axis_tick(chart3, LV_CHART_AXIS_PRIMARY_Y, 0, 0, 6, 1, true, 80);
    lv_chart_set_axis_tick(chart3, LV_CHART_AXIS_X, 0, 0, 7, 1, true, 50);
    lv_chart_set_type(chart3, LV_CHART_TYPE_BAR);
    lv_chart_set_div_line_count(chart3, 6, 0);
    lv_chart_set_point_count(chart3, 7);
    lv_obj_add_event_cb(chart3, shop_chart_event_cb, NULL);

    ser4 = lv_chart_add_series(chart3, lv_theme_get_color_primary(chart3), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_next_value(chart3, ser4, lv_rand(60, 90));
    lv_chart_set_next_value(chart3, ser4, lv_rand(60, 90));
    lv_chart_set_next_value(chart3, ser4, lv_rand(60, 90));
    lv_chart_set_next_value(chart3, ser4, lv_rand(60, 90));
    lv_chart_set_next_value(chart3, ser4, lv_rand(60, 90));
    lv_chart_set_next_value(chart3, ser4, lv_rand(60, 90));
    lv_chart_set_next_value(chart3, ser4, lv_rand(60, 90));
    lv_chart_set_next_value(chart3, ser4, lv_rand(60, 90));
    lv_chart_set_next_value(chart3, ser4, lv_rand(60, 90));
    lv_chart_set_next_value(chart3, ser4, lv_rand(60, 90));
    lv_chart_set_next_value(chart3, ser4, lv_rand(60, 90));
    lv_chart_set_next_value(chart3, ser4, lv_rand(60, 90));

    if(disp_size == DISP_LARGE) {
        static lv_coord_t grid1_col_dsc[2] = {LV_GRID_FR(1), LV_GRID_FR(1)};
        static lv_coord_t grid1_row_dsc[5] = {
            LV_GRID_CONTENT,  /*Title*/
            LV_GRID_CONTENT,  /*Sub title*/
            20,               /*Spacer*/
            LV_GRID_CONTENT,  /*Amount*/
            LV_GRID_CONTENT,  /*Hint*/
        };
        static lv_grid_t grid1;
        lv_grid_init(&grid1);
        lv_grid_set_template(&grid1, grid1_col_dsc, 2, grid1_row_dsc, 5);

        lv_obj_set_size(chart3, LV_SIZE_PCT(100), LV_SIZE_PCT(100));
        lv_obj_set_style_pad_column(chart3, LV_PART_MAIN, LV_STATE_DEFAULT, LV_DPX(30));

        lv_obj_set_layout(panel1, &grid1);
        lv_obj_set_grid_cell(title, LV_GRID_START, 0, 1, LV_GRID_START, 0, 1);
        lv_obj_set_grid_cell(date, LV_GRID_START, 0, 1, LV_GRID_START, 1, 1);
        lv_obj_set_grid_cell(amount, LV_GRID_START, 0, 1, LV_GRID_START, 3, 1);
        lv_obj_set_grid_cell(hint, LV_GRID_START, 0, 1, LV_GRID_START, 4, 1);
        lv_obj_set_grid_cell(chart3, LV_GRID_STRETCH, 1, 1, LV_GRID_STRETCH, 0, 5);
    } else if(disp_size == DISP_MEDIUM) {
        static lv_coord_t grid1_col_dsc[2] = {LV_GRID_FR(1), LV_GRID_FR(1)};
        static lv_coord_t grid1_row_dsc[3] = {
                LV_GRID_CONTENT,  /*Title + Date*/
                LV_GRID_CONTENT,  /*Amount + Hint*/
                200,              /*Chart*/
        };
        static lv_grid_t grid1;
        lv_grid_init(&grid1);
        lv_grid_set_template(&grid1, grid1_col_dsc, 2, grid1_row_dsc, 3);

        lv_obj_set_width(chart3, lv_obj_get_width_fit(panel1) - 20);
        lv_obj_set_style_pad_column(chart3, LV_PART_MAIN, LV_STATE_DEFAULT, LV_DPX(30));

        lv_obj_set_layout(panel1, &grid1);
        lv_obj_set_grid_cell(title, LV_GRID_START, 0, 1, LV_GRID_CENTER, 0, 1);
        lv_obj_set_grid_cell(date, LV_GRID_START, 1, 1, LV_GRID_CENTER, 0, 1);
        lv_obj_set_grid_cell(amount, LV_GRID_START, 0, 1, LV_GRID_CENTER, 1, 1);
        lv_obj_set_grid_cell(hint, LV_GRID_START, 1, 1, LV_GRID_CENTER, 1, 1);
        lv_obj_set_grid_cell(chart3, LV_GRID_END, 0, 2, LV_GRID_STRETCH, 2, 1);
    } else if(disp_size == DISP_SMALL) {
        static lv_coord_t grid1_col_dsc[1] = {LV_GRID_FR(1)};
        static lv_coord_t grid1_row_dsc[5] = {
                LV_GRID_CONTENT,  /*Title*/
                LV_GRID_CONTENT,  /*Date*/
                LV_GRID_CONTENT,  /*Amount*/
                LV_GRID_CONTENT,  /*Hint*/
                LV_GRID_CONTENT,  /*Chart*/
        };
        static lv_grid_t grid1;
        lv_grid_init(&grid1);
        lv_grid_set_template(&grid1, grid1_col_dsc, 1, grid1_row_dsc, 5);

        lv_obj_set_width(chart3, lv_obj_get_width_fit(panel1) - 20);
        lv_obj_set_height(chart3, lv_obj_get_height_visible(chart3) - 20);
        lv_chart_set_zoom_x(chart3, 512);

        lv_obj_set_layout(panel1, &grid1);
        lv_obj_set_grid_cell(title, LV_GRID_START, 0, 1, LV_GRID_START, 0, 1);
        lv_obj_set_grid_cell(date, LV_GRID_START, 0, 1, LV_GRID_START, 1, 1);
        lv_obj_set_grid_cell(amount, LV_GRID_START, 0, 1, LV_GRID_START, 2, 1);
        lv_obj_set_grid_cell(hint, LV_GRID_START, 0, 1, LV_GRID_START, 3, 1);
        lv_obj_set_grid_cell(chart3, LV_GRID_END, 0, 1, LV_GRID_START, 4, 1);
    }


    lv_obj_t * list = lv_obj_create(parent, NULL);
    if(disp_size == DISP_SMALL) {
        lv_obj_add_flag(list, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
        lv_obj_set_height(list, lv_obj_get_height_visible(panel1));
    } else if(disp_size == DISP_MEDIUM) {
        lv_coord_t h = lv_obj_get_height_visible(panel1);
        lv_obj_set_height(list, LV_MIN(h, 300));
    } else {
        lv_obj_set_height(list, 300);
    }

    lv_obj_set_layout(list, &flex_list);
    lv_obj_set_flex_grow(list, 1);
    lv_obj_add_flag(list, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);

    title = lv_label_create(list, NULL);
    lv_label_set_text(title, "Top products");
    lv_obj_add_style(title, LV_PART_MAIN, LV_STATE_DEFAULT, &style_subtitle);

    LV_IMG_DECLARE(img_clothes);
    create_shop_item(list, &img_clothes, "Blue jeans", "Clothes", "$722");
    create_shop_item(list, &img_clothes, "Blue jeans", "Clothes", "$411");
    create_shop_item(list, &img_clothes, "Blue jeans", "Clothes", "$917");
    create_shop_item(list, &img_clothes, "Blue jeans", "Clothes", "$64");
    create_shop_item(list, &img_clothes, "Blue jeans", "Clothes", "$805");

    lv_obj_t * notifications = lv_obj_create(parent, NULL);
    if(disp_size == DISP_SMALL) {
        lv_obj_add_flag(notifications, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
        lv_obj_set_height(notifications, lv_obj_get_height_visible(panel1));
    } else if(disp_size == DISP_MEDIUM) {
        lv_coord_t h = lv_obj_get_height_visible(panel1);
        lv_obj_set_height(notifications, LV_MIN(h, 300));
    } else {
        lv_obj_set_height(notifications, 300);
    }

    lv_obj_set_layout(notifications, &flex_list);
    lv_obj_set_flex_grow(notifications, 1);

    title = lv_label_create(notifications, NULL);
    lv_label_set_text(title, "Notification");
    lv_obj_add_style(title, LV_PART_MAIN, LV_STATE_DEFAULT, &style_subtitle);

    lv_obj_t * cb;
    cb = lv_checkbox_create(notifications, NULL);
    lv_checkbox_set_text(cb, "Item purchased");

    cb = lv_checkbox_create(notifications, NULL);
    lv_checkbox_set_text(cb, "New connection");

    cb = lv_checkbox_create(notifications, NULL);
    lv_checkbox_set_text(cb, "New subscriber");
    lv_obj_add_state(cb, LV_STATE_CHECKED);

    cb = lv_checkbox_create(notifications, NULL);
    lv_checkbox_set_text(cb, "New message");
    lv_obj_add_state(cb, LV_STATE_DISABLED);

    cb = lv_checkbox_create(notifications, NULL);
    lv_checkbox_set_text(cb, "Milestone reached");
    lv_obj_add_state(cb, LV_STATE_CHECKED | LV_STATE_DISABLED);

    cb = lv_checkbox_create(notifications, NULL);
    lv_checkbox_set_text(cb, "Out of stock");


}

static void color_changer_create(lv_obj_t * parent)
{

    static lv_color_palette_t palette[] = {
            LV_COLOR_PALETTE_BLUE, LV_COLOR_PALETTE_GREEN, LV_COLOR_PALETTE_BLUE_GREY,  LV_COLOR_PALETTE_ORANGE,
            LV_COLOR_PALETTE_RED, LV_COLOR_PALETTE_PURPLE, LV_COLOR_PALETTE_TEAL, _LV_COLOR_PALETTE_LAST };

    static lv_flex_t flex_even_nowrap;
    lv_flex_init(&flex_even_nowrap);
    lv_flex_set_flow(&flex_even_nowrap, LV_FLEX_FLOW_ROW);
    lv_flex_set_place(&flex_even_nowrap, LV_FLEX_PLACE_SPACE_EVENLY, LV_FLEX_PLACE_CENTER, LV_FLEX_PLACE_CENTER);

    lv_obj_t * color_cont = lv_obj_create(parent, NULL);
    lv_obj_set_layout(color_cont, &flex_even_nowrap);
    lv_obj_add_flag(color_cont, LV_OBJ_FLAG_FLOATING);
    lv_obj_remove_style_all(color_cont);
    lv_obj_set_style_bg_color(color_cont, LV_PART_MAIN, LV_STATE_DEFAULT, lv_color_white());
    lv_obj_set_style_pad_right(color_cont, LV_PART_MAIN, LV_STATE_DEFAULT, disp_size == DISP_SMALL ? LV_DPX(47) : LV_DPX(55));
    lv_obj_set_style_bg_opa(color_cont, LV_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_obj_set_style_radius(color_cont, LV_PART_MAIN, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);

    if(disp_size == DISP_SMALL) lv_obj_set_size(color_cont, LV_DPX(52), LV_DPX(52));
    else lv_obj_set_size(color_cont, LV_DPX(60), LV_DPX(60));

    lv_obj_align(color_cont, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, - LV_DPX(10),  - LV_DPX(10));

    uint32_t i;
    for(i = 0; palette[i] != _LV_COLOR_PALETTE_LAST; i++) {
        lv_obj_t * c = lv_btn_create(color_cont, NULL);
        lv_obj_set_style_bg_color(c, LV_PART_MAIN, LV_STATE_DEFAULT, lv_color_get_palette_main(palette[i]));
        lv_obj_set_style_radius(c, LV_PART_MAIN, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
        lv_obj_set_style_opa(c, LV_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
        lv_obj_set_size(c, 20, 20);
        lv_obj_add_event_cb(c, color_event_cb, &palette[i]);
    }

    lv_obj_t * btn = lv_btn_create(parent, NULL);


    lv_obj_add_flag(btn, LV_OBJ_FLAG_FLOATING | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_bg_color(btn, LV_PART_MAIN, LV_STATE_CHECKED, lv_color_white());
    lv_obj_set_style_pad_all(btn, LV_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_radius(btn, LV_PART_MAIN, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
    lv_obj_add_event_cb(btn, color_changer_event_cb, color_cont);
    lv_obj_set_style_shadow_width(btn, LV_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_content_text(btn, LV_PART_MAIN, LV_STATE_DEFAULT, LV_SYMBOL_TINT);
//    lv_obj_set_style_content_font(btn, LV_PART_MAIN, LV_STATE_DEFAULT, font_title);

    if(disp_size == DISP_SMALL) {
         lv_obj_set_size(btn, LV_DPX(42), LV_DPX(42));
         lv_obj_align(btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -LV_DPX(15), -LV_DPX(15));
     } else {
         lv_obj_set_size(btn, LV_DPX(50), LV_DPX(50));
         lv_obj_align(btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -LV_DPX(15), -LV_DPX(15));
     }
}

static void color_changer_anim_cb(void * var, int32_t v)
{
    lv_obj_t * obj = var;
    lv_coord_t max_w = lv_obj_get_width(lv_obj_get_parent(obj)) - LV_DPX(20);
    lv_coord_t w;

    if(disp_size == DISP_SMALL) {
        w = lv_map(v, 0, 256, LV_DPX(52), max_w);
        lv_obj_set_width(obj, w);
        lv_obj_align(obj, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, - LV_DPX(10),  - LV_DPX(10));
    } else {
        w = lv_map(v, 0, 256, LV_DPX(60), max_w);
        lv_obj_set_width(obj, w);
        lv_obj_align(obj, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, - LV_DPX(10),  - LV_DPX(10));
    }

    if(v > LV_OPA_COVER) v = LV_OPA_COVER;

    uint32_t i;
    for(i = 0; i < lv_obj_get_child_cnt(obj); i++) {
        lv_obj_set_style_opa(lv_obj_get_child(obj, i), LV_PART_MAIN, LV_STATE_DEFAULT, v);
    }

}

static void color_changer_event_cb(lv_obj_t * obj, lv_event_t e)
{
    LV_UNUSED(obj);

    if(e == LV_EVENT_CLICKED) {
        lv_obj_t * color_cont = lv_event_get_user_data();
        if(lv_obj_get_width(color_cont) < LV_HOR_RES / 2) {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, color_cont);
            lv_anim_set_exec_cb(&a, color_changer_anim_cb);
            lv_anim_set_values(&a, 0, 256);
            lv_anim_set_time(&a, 200);
            lv_anim_start(&a);
        } else {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, color_cont);
            lv_anim_set_exec_cb(&a, color_changer_anim_cb);
            lv_anim_set_values(&a, 256, 0);
            lv_anim_set_time(&a, 200);
            lv_anim_start(&a);
        }
    }
}
static void color_event_cb(lv_obj_t * obj, lv_event_t e)
{
    LV_UNUSED(obj);

    if(e == LV_EVENT_CLICKED) {
        lv_color_palette_t * palette = lv_event_get_user_data();
        lv_theme_default_init(NULL, *palette, *palette, font_small, font_normal, font_subtitle);

        lv_color_t color = lv_color_get_palette_main(*palette);
        lv_style_set_text_color(&style_icon, color);
        lv_chart_set_series_color(chart1, ser1, color);
        lv_chart_set_series_color(chart2, ser3, color);
    }
}

static lv_obj_t * create_meter_box(lv_obj_t * parent, const char * title, const char * text1, const char * text2, const char * text3)
{
    lv_obj_t * cont = lv_obj_create(parent, NULL);
    lv_obj_set_height(cont, LV_SIZE_CONTENT);
    lv_obj_set_flex_grow(cont, 1);

    lv_obj_t * title_label = lv_label_create(cont, NULL);
    lv_label_set_text(title_label, title);
    lv_obj_add_style(title_label, LV_PART_MAIN, LV_STATE_DEFAULT, &style_subtitle);

    lv_obj_t * meter = lv_meter_create(cont, NULL);
    lv_obj_set_width(meter, LV_SIZE_PCT(100));
    lv_obj_remove_style(meter, LV_PART_MAIN, LV_STATE_ANY, NULL);
    lv_obj_remove_style(meter, LV_PART_INDICATOR, LV_STATE_ANY, NULL);

    lv_obj_t * bullet1 = lv_obj_create(cont, NULL);
    lv_obj_set_size(bullet1, 13, 13);
    lv_obj_remove_style(bullet1, LV_PART_SCROLLBAR, LV_STATE_ANY, NULL);
    lv_obj_add_style(bullet1, LV_PART_MAIN, LV_STATE_DEFAULT, &style_bullet);
    lv_obj_set_style_bg_color(bullet1, LV_PART_MAIN, LV_STATE_DEFAULT, lv_color_red());
    lv_obj_t * label1 = lv_label_create(cont, NULL);
    lv_label_set_text(label1, text1);

    lv_obj_t * bullet2 = lv_obj_create(cont, NULL);
    lv_obj_set_size(bullet2, 13, 13);
    lv_obj_remove_style(bullet2, LV_PART_SCROLLBAR, LV_STATE_ANY, NULL);
    lv_obj_add_style(bullet2, LV_PART_MAIN, LV_STATE_DEFAULT, &style_bullet);
    lv_obj_set_style_bg_color(bullet2, LV_PART_MAIN, LV_STATE_DEFAULT, lv_color_blue());
    lv_obj_t * label2 = lv_label_create(cont, NULL);
    lv_label_set_text(label2, text2);

    lv_obj_t * bullet3 = lv_obj_create(cont, NULL);
    lv_obj_set_size(bullet3, 13, 13);
    lv_obj_remove_style(bullet3, LV_PART_SCROLLBAR, LV_STATE_ANY, NULL);
    lv_obj_add_style(bullet3, LV_PART_MAIN, LV_STATE_DEFAULT, &style_bullet);
    lv_obj_set_style_bg_color(bullet3, LV_PART_MAIN, LV_STATE_DEFAULT, lv_color_green());
    lv_obj_t * label3 = lv_label_create(cont, NULL);
    lv_label_set_text(label3, text3);

    if(disp_size == DISP_MEDIUM) {
        static bool inited = false;
        static lv_grid_t grid;
        if(!inited) {
            static lv_coord_t grid_col_dsc[4] = {LV_GRID_CONTENT, LV_GRID_FR(1), LV_GRID_CONTENT,LV_GRID_FR(8)};
            static lv_coord_t grid_row_dsc[6] = {LV_GRID_CONTENT, LV_GRID_FR(1), LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_FR(1)};
            lv_grid_init(&grid);
            lv_grid_set_template(&grid, grid_col_dsc, 4, grid_row_dsc, 6);
            inited = true;
        }

        lv_obj_set_layout(cont, &grid);
        lv_obj_set_grid_cell(title_label, LV_GRID_START, 0, 4, LV_GRID_START, 0, 1);
        lv_obj_set_grid_cell(meter, LV_GRID_START, 0, 1, LV_GRID_START, 1, 3);
        lv_obj_set_grid_cell(bullet1, LV_GRID_START, 2, 1, LV_GRID_START, 2, 1);
        lv_obj_set_grid_cell(bullet2, LV_GRID_START, 2, 1, LV_GRID_START, 3, 1);
        lv_obj_set_grid_cell(bullet3, LV_GRID_START, 2, 1, LV_GRID_START, 4, 1);
        lv_obj_set_grid_cell(label1, LV_GRID_START, 3, 1, LV_GRID_START, 2, 1);
        lv_obj_set_grid_cell(label2, LV_GRID_START, 3, 1, LV_GRID_START, 3, 1);
        lv_obj_set_grid_cell(label3, LV_GRID_START, 3, 1, LV_GRID_START, 4, 1);
    }
    else {
        static bool inited = false;
        static lv_grid_t grid;
        if(!inited) {
            static lv_coord_t grid_col_dsc[2] = {LV_GRID_CONTENT, LV_GRID_FR(1)};
            static lv_coord_t grid_row_dsc[5] = {LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_CONTENT};
            lv_grid_init(&grid);
            lv_grid_set_template(&grid, grid_col_dsc, 2, grid_row_dsc, 5);
            inited = true;
        }

        lv_obj_set_layout(cont, &grid);
        lv_obj_set_grid_cell(title_label, LV_GRID_START, 0, 2, LV_GRID_START, 0, 1);
        lv_obj_set_grid_cell(meter, LV_GRID_START, 0, 2, LV_GRID_START, 1, 1);
        lv_obj_set_grid_cell(bullet1, LV_GRID_START, 0, 1, LV_GRID_START, 2, 1);
        lv_obj_set_grid_cell(bullet2, LV_GRID_START, 0, 1, LV_GRID_START, 3, 1);
        lv_obj_set_grid_cell(bullet3, LV_GRID_START, 0, 1, LV_GRID_START, 4, 1);
        lv_obj_set_grid_cell(label1, LV_GRID_START, 1, 1, LV_GRID_START, 2, 1);
        lv_obj_set_grid_cell(label2, LV_GRID_START, 1, 1, LV_GRID_START, 3, 1);
        lv_obj_set_grid_cell(label3, LV_GRID_START, 1, 1, LV_GRID_START, 4, 1);
    }


    return meter;

}

static lv_obj_t * create_shop_item(lv_obj_t * parent, const void * img_src, const char * name, const char * category, const char * price)
{
    static bool inited = false;
    static lv_grid_t grid;
    if(!inited) {
        static lv_coord_t grid_col_dsc[4] = {LV_GRID_CONTENT, 5, LV_GRID_FR(1), LV_GRID_FR(1)};
        static lv_coord_t grid_row_dsc[2] = {LV_GRID_FR(1), LV_GRID_FR(1)};
        lv_grid_init(&grid);
        lv_grid_set_template(&grid, grid_col_dsc, 4, grid_row_dsc, 2);
        inited = true;
    }

    lv_obj_t * cont = lv_obj_create(parent, NULL);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, LV_SIZE_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_layout(cont, &grid);

    lv_obj_t * img = lv_img_create(cont, NULL);
    lv_img_set_src(img, img_src);
    lv_obj_set_grid_cell(img, LV_GRID_START, 0, 1, LV_GRID_START, 0, 2);

    lv_obj_t * label;
    label = lv_label_create(cont, NULL);
    lv_label_set_text(label, name);
    lv_obj_set_grid_cell(label, LV_GRID_START, 2, 1, LV_GRID_END, 0, 1);

    label = lv_label_create(cont, NULL);
    lv_label_set_text(label, category);
    lv_obj_add_style(label, LV_PART_MAIN, LV_STATE_DEFAULT, &style_text_muted);
    lv_obj_set_grid_cell(label, LV_GRID_START, 2, 1, LV_GRID_START, 1, 1);

    label = lv_label_create(cont, NULL);
    lv_label_set_text(label, price);
    lv_obj_set_grid_cell(label, LV_GRID_END, 3, 1, LV_GRID_END, 0, 1);

    return cont;
}

static void ta_event_cb(lv_obj_t * ta, lv_event_t e)
{
    lv_obj_t * kb = lv_event_get_user_data();
    if(e == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_set_height(tv, LV_VER_RES / 2);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_scroll_to_view_recursive(ta, LV_ANIM_OFF);
    }
    else if(e == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_set_height(tv, LV_VER_RES);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    else if(e == LV_EVENT_READY || e == LV_EVENT_CANCEL) {
        lv_obj_set_height(tv, LV_VER_RES);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(ta, LV_STATE_FOCUSED);
        lv_indev_reset(NULL, ta);   /*To forget the last clicked object to make it focusable again*/
    }
}

static void birthday_event_cb(lv_obj_t * ta, lv_event_t e)
{
    if(e == LV_EVENT_FOCUSED) {
        if(calendar == NULL) {
            lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
            calendar = lv_calendar_create(lv_layer_top());
            lv_obj_set_style_bg_opa(lv_layer_top(), LV_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_50);
            lv_obj_set_style_bg_color(lv_layer_top(), LV_PART_MAIN, LV_STATE_DEFAULT, lv_color_grey());
            if(disp_size == DISP_SMALL) lv_obj_set_size(calendar, 180, 180);
            else if(disp_size == DISP_MEDIUM) lv_obj_set_size(calendar, 200, 200);
            else  lv_obj_set_size(calendar, 300, 300);
            lv_calendar_set_showed_date(calendar, 1990, 01);
            lv_obj_align(calendar, NULL, LV_ALIGN_CENTER, 0, 30);
            lv_obj_add_event_cb(calendar, calendar_event_cb, ta);

            calendar_header = lv_calendar_header_dropdown_create(lv_layer_top(), calendar);
        }
    }
}

static void calendar_event_cb(lv_obj_t * obj, lv_event_t e)
{
    lv_obj_t * ta = lv_event_get_user_data();
    if(e == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t d;
        lv_calendar_get_pressed_date(obj, &d);
        char buf[32];
        lv_snprintf(buf, sizeof(buf), "%02d.%02d.%d", d.day, d.month, d.year);
        lv_textarea_set_text(ta, buf);

        lv_obj_del(calendar);
        lv_obj_del(calendar_header);
        calendar = NULL;
        calendar_header = NULL;
        lv_obj_clear_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_bg_opa(lv_layer_top(), LV_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    }
}

static void slider_event_cb(lv_obj_t * obj, lv_event_t e)
{
    if(e == LV_EVENT_REFR_EXT_DRAW_SIZE) {
        lv_coord_t *s = lv_event_get_param();
        *s = LV_MAX(*s, 60);
    } else if(e == LV_EVENT_DRAW_PART_END) {
        lv_obj_draw_dsc_t * dsc = lv_event_get_param();
        if(dsc->part == LV_PART_KNOB && lv_obj_has_state(obj, LV_STATE_PRESSED)) {
            char buf[8];
            lv_snprintf(buf, sizeof(buf), "%d", lv_slider_get_value(obj));

            lv_point_t text_size;
            lv_txt_get_size(&text_size, buf, font_normal, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

            lv_area_t txt_area;
            txt_area.x1 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2 - text_size.x / 2;
            txt_area.x2 = txt_area.x1 + text_size.x;
            txt_area.y2 = dsc->draw_area->y1 - 10;
            txt_area.y1 = txt_area.y2 - text_size.y;

            lv_area_t bg_area;
            bg_area.x1 = txt_area.x1 - LV_DPX(8);
            bg_area.x2 = txt_area.x2 + LV_DPX(8);
            bg_area.y1 = txt_area.y1 - LV_DPX(8);
            bg_area.y2 = txt_area.y2 + LV_DPX(8);

            lv_draw_rect_dsc_t rect_dsc;
            lv_draw_rect_dsc_init(&rect_dsc);
            rect_dsc.bg_color = lv_color_grey_darken_3();
            rect_dsc.radius = LV_DPX(5);
            lv_draw_rect(&bg_area, dsc->clip_area, &rect_dsc);
            
            lv_draw_label_dsc_t label_dsc;
            lv_draw_label_dsc_init(&label_dsc);
            label_dsc.color = lv_color_white();
            label_dsc.font = font_normal;
            lv_draw_label(&txt_area, dsc->clip_area, &label_dsc, buf, NULL);
        }
    }
}

static void chart_event_cb(lv_obj_t * obj, lv_event_t e)
{
    if(e == LV_EVENT_DRAW_PART_BEGIN) {
        lv_obj_draw_dsc_t * dsc = lv_event_get_param();
        /*Set the markers' text*/
        if(dsc->part == LV_PART_TICKS && dsc->id == LV_CHART_AXIS_X) {
            if(lv_chart_get_type(obj) == LV_CHART_TYPE_BAR) {
                const char * month[] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII"};
                lv_snprintf(dsc->text, sizeof(dsc->text), "%s", month[dsc->value]);
            } else {
                const char * month[] = {"Jan", "Febr", "March", "Apr", "May", "Jun", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
                lv_snprintf(dsc->text, sizeof(dsc->text), "%s", month[dsc->value]);
            }
        }

        /*Add the faded area before the lines are drawn */
        else if(dsc->part == LV_PART_ITEMS) {
            /*Add  a line mask that keeps the area below the line*/
            if(dsc->p1 && dsc->p2) {
                lv_draw_mask_line_param_t line_mask_param;
                lv_draw_mask_line_points_init(&line_mask_param, dsc->p1->x, dsc->p1->y, dsc->p2->x, dsc->p2->y, LV_DRAW_MASK_LINE_SIDE_BOTTOM);
                int16_t line_mask_id = lv_draw_mask_add(&line_mask_param, NULL);

                /*Add a fade effect: transparent bottom covering top*/
                lv_coord_t h = lv_obj_get_height(obj);
                lv_draw_mask_fade_param_t fade_mask_param;
                lv_draw_mask_fade_init(&fade_mask_param, &obj->coords, LV_OPA_COVER, obj->coords.y1 + h / 8, LV_OPA_TRANSP,obj->coords.y2);
                int16_t fade_mask_id = lv_draw_mask_add(&fade_mask_param, NULL);

                /*Draw a rectangle that will be affected by the mask*/
                lv_draw_rect_dsc_t draw_rect_dsc;
                lv_draw_rect_dsc_init(&draw_rect_dsc);
                draw_rect_dsc.bg_opa = LV_OPA_50;
                draw_rect_dsc.bg_color = dsc->line_dsc->color;

                lv_area_t obj_clip_area;
                _lv_area_intersect(&obj_clip_area, dsc->clip_area, &obj->coords);

                lv_area_t a;
                a.x1 = dsc->p1->x;
                a.x2 = dsc->p2->x - 1;
                a.y1 = LV_MIN(dsc->p1->y, dsc->p2->y);
                a.y2 = obj->coords.y2;
                lv_draw_rect(&a, &obj_clip_area, &draw_rect_dsc);

                /*Remove the masks*/
                lv_draw_mask_remove_id(line_mask_id);
                lv_draw_mask_remove_id(fade_mask_id);
            }

            const lv_chart_series_t * ser = dsc->sub_part_ptr;

            if(lv_chart_get_pressed_point(obj) == dsc->id) {
                if(lv_chart_get_type(obj) == LV_CHART_TYPE_LINE) {
                    dsc->rect_dsc->outline_color = lv_color_white();
                    dsc->rect_dsc->outline_width = 2;
                } else {
                    dsc->rect_dsc->shadow_color = ser->color;
                    dsc->rect_dsc->shadow_width = 15;
                    dsc->rect_dsc->shadow_spread = 0;
                }

                char buf[8];
                lv_snprintf(buf, sizeof(buf), "%d", dsc->value);

                lv_point_t text_size;
                lv_txt_get_size(&text_size, buf, font_normal, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

                lv_area_t txt_area;
                if(lv_chart_get_type(obj) == LV_CHART_TYPE_BAR) {
                    txt_area.y2 = dsc->draw_area->y1 - LV_DPX(15);
                    txt_area.y1 = txt_area.y2 - text_size.y;
                    if(ser == lv_chart_get_series_next(obj, NULL)) {
                        txt_area.x1 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2;
                        txt_area.x2 = txt_area.x1 + text_size.x;
                    } else {
                        txt_area.x2 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2;
                        txt_area.x1 = txt_area.x2 - text_size.x;
                    }
                } else {
                    txt_area.x1 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2 - text_size.x / 2;
                    txt_area.x2 = txt_area.x1 + text_size.x;
                    txt_area.y2 = dsc->draw_area->y1 - LV_DPX(15);
                    txt_area.y1 = txt_area.y2 - text_size.y;
                }

                lv_area_t bg_area;
                bg_area.x1 = txt_area.x1 - LV_DPX(8);
                bg_area.x2 = txt_area.x2 + LV_DPX(8);
                bg_area.y1 = txt_area.y1 - LV_DPX(8);
                bg_area.y2 = txt_area.y2 + LV_DPX(8);

                lv_draw_rect_dsc_t rect_dsc;
                lv_draw_rect_dsc_init(&rect_dsc);
                rect_dsc.bg_color = ser->color;
                rect_dsc.radius = LV_DPX(5);
                lv_draw_rect(&bg_area, dsc->clip_area, &rect_dsc);

                lv_draw_label_dsc_t label_dsc;
                lv_draw_label_dsc_init(&label_dsc);
                label_dsc.color = lv_color_white();
                label_dsc.font = font_normal;
                lv_draw_label(&txt_area, dsc->clip_area, &label_dsc, buf, NULL);
            } else {
                dsc->rect_dsc->outline_width = 0;
                dsc->rect_dsc->shadow_width = 0;
            }
        }
    }
}


static void shop_chart_event_cb(lv_obj_t * obj, lv_event_t e)
{
    LV_UNUSED(obj);

    if(e == LV_EVENT_DRAW_PART_BEGIN) {
        lv_obj_draw_dsc_t * dsc = lv_event_get_param();
        /*Set the markers' text*/
        if(dsc->part == LV_PART_TICKS && dsc->id == LV_CHART_AXIS_X) {
            const char * month[] = {"Jan", "Febr", "March", "Apr", "May", "Jun", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
            lv_snprintf(dsc->text, sizeof(dsc->text), "%s", month[dsc->value]);
        }
        if(dsc->part == LV_PART_ITEMS) {
            dsc->rect_dsc->bg_opa = LV_OPA_TRANSP; /*We will draw it later*/
        }
    }
    if(e == LV_EVENT_DRAW_PART_END) {
        lv_obj_draw_dsc_t * dsc = lv_event_get_param();
        /*Add the faded area before the lines are drawn */
        if(dsc->part == LV_PART_ITEMS) {
            static const uint32_t devices[10] = {32, 43, 21, 56, 29, 36, 19, 25, 62, 35};
            static const uint32_t clothes[10] = {12, 19, 23, 31, 27, 32, 32, 11, 21, 32};
            static const uint32_t services[10] = {56, 38, 56, 13, 44, 32, 49, 64, 17, 33};

            lv_draw_rect_dsc_t draw_rect_dsc;
            lv_draw_rect_dsc_init(&draw_rect_dsc);

            lv_coord_t h = lv_area_get_height(dsc->draw_area);

            lv_area_t a;
            a.x1 = dsc->draw_area->x1;
            a.x2 = dsc->draw_area->x2;

            a.y1 = dsc->draw_area->y1;
            a.y2 = a.y1 + 4 + (devices[dsc->id] * h) / 100; /*+4 to overlap the radius*/
            draw_rect_dsc.bg_color = lv_color_red();
            draw_rect_dsc.radius = 4;
            lv_draw_rect(&a, dsc->clip_area, &draw_rect_dsc);

            a.y1 = a.y2 - 4;                                    /*-4 to overlap the radius*/
            a.y2 = a.y1 +  (clothes[dsc->id] * h) / 100;
            draw_rect_dsc.bg_color = lv_color_blue();
            draw_rect_dsc.radius = 0;
            lv_draw_rect(&a, dsc->clip_area, &draw_rect_dsc);

            a.y1 = a.y2;
            a.y2 = a.y1 + (services[dsc->id] * h) / 100;
            draw_rect_dsc.bg_color = lv_color_green();
            lv_draw_rect(&a, dsc->clip_area, &draw_rect_dsc);
        }
    }
}


static void meter1_indic1_anim_cb(void * var, int32_t v)
{
    lv_meter_set_indicator_end_value(meter1, var, v);

    lv_obj_t * card = lv_obj_get_parent(meter1);
    lv_obj_t * label = lv_obj_get_child(card, -5);
    lv_label_set_text_fmt(label, "Revenue: %d %%", v);
}

static void meter1_indic2_anim_cb(void * var, int32_t v)
{
    lv_meter_set_indicator_end_value(meter1, var, v);

    lv_obj_t * card = lv_obj_get_parent(meter1);
    lv_obj_t * label = lv_obj_get_child(card, -3);
    lv_label_set_text_fmt(label, "Sales: %d %%", v);

}

static void meter1_indic3_anim_cb(void * var, int32_t v)
{
    lv_meter_set_indicator_end_value(meter1, var, v);

    lv_obj_t * card = lv_obj_get_parent(meter1);
    lv_obj_t * label = lv_obj_get_child(card, -1);
    lv_label_set_text_fmt(label, "Costs: %d %%", v);
}

static void meter2_timer_cb(lv_timer_t * timer)
{
    lv_meter_indicator_t ** indics = timer->user_data;

    static bool down1 = false;
    static bool down2 = false;
    static bool down3 = false;


    if(down1) {
        session_desktop -= 137;
        if(session_desktop < 1400) down1 = false;
    } else {
        session_desktop += 116;
        if(session_desktop > 4500) down1 = true;
    }

    if(down2) {
        session_tablet -= 3;
        if(session_tablet < 1400) down2 = false;
    } else {
        session_tablet += 9;
        if(session_tablet > 4500) down2 = true;
    }

    if(down3) {
        session_mobile -= 57;
        if(session_mobile < 1400) down3 = false;
    } else {
        session_mobile += 76;
        if(session_mobile > 4500) down3 = true;
    }

    uint32_t all = session_desktop + session_tablet + session_mobile;
    uint32_t pct1 = (session_desktop * 97) / all;
    uint32_t pct2 = (session_tablet * 97) / all;

    lv_meter_set_indicator_start_value(meter2, indics[0], 0);
    lv_meter_set_indicator_end_value(meter2, indics[0], pct1);

    lv_meter_set_indicator_start_value(meter2, indics[1], pct1 + 1);
    lv_meter_set_indicator_end_value(meter2, indics[1], pct1 + 1 + pct2);

    lv_meter_set_indicator_start_value(meter2, indics[2], pct1 + 1 + pct2 + 1);
    lv_meter_set_indicator_end_value(meter2, indics[2], 99);

    lv_obj_t * card = lv_obj_get_parent(meter2);
    lv_obj_t * label;

    label = lv_obj_get_child(card, -5);
    lv_label_set_text_fmt(label, "Desktop: %d", session_desktop);

    label = lv_obj_get_child(card, -3);
    lv_label_set_text_fmt(label, "Tablet: %d", session_tablet);

    label = lv_obj_get_child(card, -1);
    lv_label_set_text_fmt(label, "Mobile: %d", session_mobile);
}

static void meter3_anim_cb(void * var, int32_t v)
{
    lv_meter_set_indicator_value(meter3, var, v);

    lv_obj_t * label = lv_obj_get_child(meter3, 0);
    lv_label_set_text_fmt(label, "%d", v);
    lv_obj_t * unit = lv_obj_get_child(meter3, 1);
    lv_obj_align(unit, label, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, 0);
}
