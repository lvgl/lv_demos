/**
 * @file lv_theme_alien.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include "lv_theme.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_theme_t theme;

static lv_style_t def;
static lv_style_t bg;

static lv_style_t panel;        /*General fancy background (for e.g. chart or ta)*/
static lv_style_t sb;

static lv_style_t label_sm;
static lv_style_t label_md;
static lv_style_t label_lg;

static lv_style_t btn_sm_rel;
static lv_style_t btn_sm_pr;
static lv_style_t btn_sm_trel;
static lv_style_t btn_sm_tpr;
static lv_style_t btn_sm_ina;

static lv_style_t btn_md_rel;
static lv_style_t btn_md_pr;
static lv_style_t btn_md_trel;
static lv_style_t btn_md_tpr;
static lv_style_t btn_md_ina;

static lv_style_t btn_lg_rel;
static lv_style_t btn_lg_pr;
static lv_style_t btn_lg_trel;
static lv_style_t btn_lg_tpr;
static lv_style_t btn_lg_ina;

static lv_style_t bar_bg;
static lv_style_t bar_indic;
static lv_style_t slider_knob;
static lv_style_t sw_bg;
static lv_style_t sw_indic;
static lv_style_t sw_knob;

static lv_style_t list_bg;
static lv_style_t list_rel;
static lv_style_t list_pr;
static lv_style_t list_trel;
static lv_style_t list_tpr;
static lv_style_t list_ina;

static lv_style_t ddlist_bg;
static lv_style_t ddlist_sel;

static lv_style_t roller_bg;
static lv_style_t roller_sel;

static lv_style_t cb_bg;
static lv_style_t cb_rel;
static lv_style_t cb_pr;
static lv_style_t cb_trel;
static lv_style_t cb_tpr;
static lv_style_t cb_ina;

static lv_style_t tab_rel;
static lv_style_t tab_pr;
static lv_style_t tab_trel;
static lv_style_t tab_tpr;
static lv_style_t tab_indic;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void lv_theme_alien_init(uint16_t hue, font_t *font_sm, font_t *font_md, font_t *font_lg)
{
    /*Background*/
    lv_style_copy(&def, &lv_style_plain);
    def.body.opa = OPA_COVER;
    def.glass = 0;

    def.body.empty = 0;
    def.body.color_main = COLOR_HEX3(0x222);
    def.body.color_gradient = COLOR_HEX3(0x222);
    def.body.radius = 0;
    def.body.padding.hor = LV_DPI / 8;
    def.body.padding.ver = LV_DPI / 8;
    def.body.padding.inner = LV_DPI / 4;
    def.body.border.color = COLOR_SILVER;
    def.body.border.width = 1 << LV_ANTIALIAS;
    def.body.border.opa = OPA_COVER;
    def.body.shadow.color = COLOR_SILVER;
    def.body.shadow.width = 0;
    def.body.shadow.type = LV_SHADOW_FULL;

    def.text.color = COLOR_HEX3(0xDDD);
    def.text.font = font_sm;
    def.text.letter_space = 1 << LV_ANTIALIAS;
    def.text.line_space = 2 << LV_ANTIALIAS;

    def.image.color = COLOR_HEX3(0xDDD);
    def.image.intense = OPA_TRANSP;

    def.line.color = COLOR_HEX(0xDDD);
    def.line.width = 1 << LV_ANTIALIAS;

    /*Background*/
    lv_style_copy(&bg, &def);
    bg.body.color_main = COLOR_HEX3(0x333);
    bg.body.color_gradient =  COLOR_HEX3(0x333);
    bg.body.border.width = 0;
    bg.body.border.opa = OPA_70;
    bg.body.shadow.color = COLOR_SILVER;

    /*Panel*/
    lv_style_copy(&panel, &def);
    panel.body.radius = LV_DPI / 10;
    panel.body.color_main = COLOR_HEX3(0x666);
    panel.body.color_gradient = COLOR_HEX3(0x666);
    panel.body.border.color = COLOR_HEX3(0xccc);
    panel.body.border.width = 2 << LV_ANTIALIAS;
    panel.body.border.opa = OPA_60;
    panel.text.color = color_hsv_to_rgb(hue, 8, 96);

    /*Scrollbar*/
    lv_style_copy(&sb, &def);
    sb.body.opa = OPA_50;
    sb.body.radius = LV_RADIUS_CIRCLE;
    sb.body.border.color = COLOR_SILVER;
    sb.body.border.opa = OPA_40;
    sb.body.border.width = 1 << LV_ANTIALIAS;
    sb.body.color_main = color_hsv_to_rgb(hue, 33, 92);
    sb.body.color_gradient = color_hsv_to_rgb(hue, 33, 92);
    sb.body.padding.hor = 1 << LV_ANTIALIAS;
    sb.body.padding.ver = 1 << LV_ANTIALIAS;
    sb.body.padding.inner = LV_DPI / 15;      /*Scrollbar width*/

    /*Buttons*/
#if USE_LV_BTN != 0
    lv_style_copy(&btn_sm_rel, &def);
    btn_sm_rel.glass = 0;
    btn_sm_rel.body.empty = 1;
    btn_sm_rel.body.radius = LV_RADIUS_CIRCLE;
    btn_sm_rel.body.border.width = 3 << LV_ANTIALIAS;
    btn_sm_rel.body.border.color = color_hsv_to_rgb(hue, 70, 90);
    btn_sm_rel.body.border.opa = OPA_80;
    btn_sm_rel.body.padding.hor = LV_DPI / 4;
    btn_sm_rel.body.padding.ver = LV_DPI / 6;
    btn_sm_rel.body.padding.inner = LV_DPI / 10;
    btn_sm_rel.text.color = color_hsv_to_rgb(hue, 8, 96);
    btn_sm_rel.text.font = font_sm;

    lv_style_copy(&btn_sm_pr, &btn_sm_rel);
    btn_sm_pr.body.opa = OPA_COVER;
    btn_sm_pr.body.empty = 0;
    btn_sm_pr.body.color_main = color_hsv_to_rgb(hue, 50, 50);
    btn_sm_pr.body.color_gradient = color_hsv_to_rgb(hue, 50, 50);
    btn_sm_pr.body.border.opa = OPA_60;
    btn_sm_pr.text.font = font_sm;
    btn_sm_pr.text.color = color_hsv_to_rgb(hue, 10, 100);

    lv_style_copy(&btn_sm_trel, &btn_sm_pr);
    btn_sm_trel.body.opa = OPA_COVER;
    btn_sm_trel.body.empty = 0;
    btn_sm_trel.body.color_main = color_hsv_to_rgb(hue, 50, 60);
    btn_sm_trel.body.color_gradient = color_hsv_to_rgb(hue, 50, 60);
    btn_sm_trel.body.border.opa = OPA_60;
    btn_sm_trel.body.border.color = color_hsv_to_rgb(hue, 80, 90);
    btn_sm_trel.text.font = font_sm;
    btn_sm_trel.text.color = color_hsv_to_rgb(hue, 0, 100);

    lv_style_copy(&btn_sm_tpr, &btn_sm_trel);
    btn_sm_tpr.body.opa = OPA_COVER;
    btn_sm_tpr.body.empty = 0;
    btn_sm_tpr.body.color_main = color_hsv_to_rgb(hue, 50, 50);
    btn_sm_tpr.body.color_gradient = color_hsv_to_rgb(hue, 50, 50);
    btn_sm_tpr.body.border.opa = OPA_60;
    btn_sm_tpr.body.border.color = color_hsv_to_rgb(hue, 80, 70);
    btn_sm_tpr.text.font = font_sm;
    btn_sm_tpr.text.color = color_hsv_to_rgb(hue, 10, 90);

    lv_style_copy(&btn_sm_ina, &btn_sm_rel);
    btn_sm_ina.body.border.opa = OPA_60;
    btn_sm_ina.body.border.color = color_hsv_to_rgb(hue, 10, 50);
    btn_sm_ina.text.font = font_sm;
    btn_sm_ina.text.color = color_hsv_to_rgb(hue, 10, 90);

    lv_style_copy(&btn_md_rel, &btn_sm_rel);
    btn_md_rel.body.padding.hor = LV_DPI / 3;
    btn_md_rel.body.padding.ver = LV_DPI / 5;
    btn_md_rel.body.padding.inner = LV_DPI / 8;
    btn_md_rel.text.font = font_md;

    lv_style_copy(&btn_md_pr, &btn_sm_pr);
    btn_md_pr.body.padding.hor = LV_DPI / 3;
    btn_md_pr.body.padding.ver = LV_DPI / 5;
    btn_md_pr.body.padding.inner = LV_DPI / 8;
    btn_md_pr.text.font = font_md;

    lv_style_copy(&btn_md_trel, &btn_sm_trel);
    btn_md_trel.body.padding.hor = LV_DPI / 3;
    btn_md_trel.body.padding.ver = LV_DPI / 5;
    btn_md_trel.body.padding.inner = LV_DPI / 8;
    btn_md_trel.text.font = font_md;

    lv_style_copy(&btn_md_tpr, &btn_sm_tpr);
    btn_md_tpr.body.padding.hor = LV_DPI / 3;
    btn_md_tpr.body.padding.ver = LV_DPI / 5;
    btn_md_tpr.body.padding.inner = LV_DPI / 8;
    btn_md_tpr.text.font = font_md;

    lv_style_copy(&btn_md_ina, &btn_sm_ina);
    btn_md_ina.body.padding.hor = LV_DPI / 3;
    btn_md_ina.body.padding.ver = LV_DPI / 5;
    btn_md_ina.body.padding.inner = LV_DPI / 8;
    btn_md_ina.text.font = font_md;

    lv_style_copy(&btn_lg_rel, &btn_sm_rel);
    btn_lg_rel.body.padding.hor = LV_DPI / 2;
    btn_lg_rel.body.padding.ver = LV_DPI / 4;
    btn_lg_rel.body.padding.inner = LV_DPI / 6;
    btn_lg_rel.text.font = font_lg;

    lv_style_copy(&btn_lg_pr, &btn_sm_pr);
    btn_lg_pr.body.padding.hor = LV_DPI / 2;
    btn_lg_pr.body.padding.ver = LV_DPI / 4;
    btn_lg_pr.body.padding.inner = LV_DPI / 6;
    btn_lg_pr.text.font = font_lg;

    lv_style_copy(&btn_lg_trel, &btn_sm_trel);
    btn_lg_trel.body.padding.hor = LV_DPI / 2;
    btn_lg_trel.body.padding.ver = LV_DPI / 4;
    btn_lg_trel.body.padding.inner = LV_DPI / 6;
    btn_lg_trel.text.font = font_lg;

    lv_style_copy(&btn_lg_tpr, &btn_sm_tpr);
    btn_lg_tpr.body.padding.hor = LV_DPI / 2;
    btn_lg_tpr.body.padding.ver = LV_DPI / 4;
    btn_lg_tpr.body.padding.inner = LV_DPI / 6;
    btn_lg_tpr.text.font = font_lg;

    lv_style_copy(&btn_lg_ina, &btn_sm_ina);
    btn_lg_ina.body.padding.hor = LV_DPI / 2;
    btn_lg_ina.body.padding.ver = LV_DPI / 4;
    btn_lg_ina.body.padding.inner = LV_DPI / 6;
    btn_lg_ina.text.font = font_lg;
#endif

    /*Labels*/
#if USE_LV_LABEL != 0
    lv_style_copy(&label_sm, &def);
    label_sm.text.font = font_sm;
    label_sm.text.color = color_hsv_to_rgb(hue, 8, 96);

    lv_style_copy(&label_md, &label_sm);
    label_md.text.font = font_md;

    lv_style_copy(&label_lg, &label_sm);
    label_lg.text.font = font_lg;
#endif

    /*Bar*/
#if USE_LV_BAR
    lv_style_copy(&bar_bg, &def);
    bar_bg.body.opa = OPA_30;
    bar_bg.body.radius = LV_RADIUS_CIRCLE;
    bar_bg.body.color_main = COLOR_WHITE;
    bar_bg.body.color_gradient = COLOR_SILVER;
    bar_bg.body.border.width = 2 << LV_ANTIALIAS;
    bar_bg.body.border.color = COLOR_SILVER;
    bar_bg.body.border.opa = OPA_20;
    bar_bg.body.padding.hor = 0;
    bar_bg.body.padding.ver = LV_DPI / 6;
    bar_bg.body.padding.inner = 0;

    lv_style_copy(&bar_indic, &def);
    bar_indic.body.radius = LV_RADIUS_CIRCLE;
    bar_indic.body.border.width = 2 << LV_ANTIALIAS;
    bar_indic.body.border.color = COLOR_SILVER;
    bar_indic.body.border.opa = OPA_70;
    bar_indic.body.padding.hor = 0;
    bar_indic.body.padding.ver = 0;
    bar_indic.body.shadow.width = LV_DPI / 8;
    bar_indic.body.color_main = color_hsv_to_rgb(hue, 40, 80);
    bar_indic.body.color_gradient = color_hsv_to_rgb(hue, 40, 80);
#endif

    /*Slider knob*/
#if USE_LV_SLIDER != 0
    lv_style_copy(&slider_knob, &def);
    slider_knob.body.opa = OPA_60;
    slider_knob.body.radius = LV_RADIUS_CIRCLE;
    slider_knob.body.color_main = COLOR_WHITE;
    slider_knob.body.color_gradient = COLOR_SILVER;
    slider_knob.body.border.width = 1 << LV_ANTIALIAS;
    slider_knob.body.border.color = COLOR_GRAY;
    slider_knob.body.border.opa = OPA_50;
#endif

    /*Switch*/
#if USE_LV_SW != 0
    lv_style_copy(&sw_bg, &bar_bg);
    sw_bg.body.opa = OPA_COVER;
    sw_bg.body.padding.ver = -2  << LV_ANTIALIAS;
    sw_bg.body.padding.hor = -2  << LV_ANTIALIAS;
    sw_bg.body.color_main = COLOR_HEX3(0x666);
    sw_bg.body.color_gradient = COLOR_HEX3(0x999);
    sw_bg.body.border.width = 2 << LV_ANTIALIAS;
    sw_bg.body.border.opa = OPA_50;

    lv_style_copy(&sw_indic, &bar_indic);
    sw_indic.body.shadow .width = LV_DPI / 12;
    sw_indic.body.padding.ver = 0;
    sw_indic.body.padding.hor = 0;

    lv_style_copy(&sw_knob, &slider_knob);
    sw_knob.body.opa = OPA_80;
#endif

    /*Check box*/
#if USE_LV_CB != 0
    lv_style_copy(&cb_rel, &bg);
    cb_rel.body.radius = LV_DPI / 20;
    cb_rel.body.border.width = 1 << LV_ANTIALIAS;
    cb_rel.body.border.color = COLOR_GRAY;
    cb_rel.body.color_main = COLOR_WHITE;
    cb_rel.body.color_gradient = COLOR_SILVER;

    lv_style_copy(&cb_bg, &bg);
    cb_bg.body.empty = 1;
    cb_bg.body.border.width = 0;
    cb_bg.body.padding.inner =  LV_DPI / 8;
    cb_bg.body.padding.hor =  0;
    cb_bg.body.padding.ver =  0;
    cb_bg.text.font = font_sm;

    lv_style_copy(&cb_pr, &cb_rel);
    cb_pr.body.color_main = color_hsv_to_rgb(hue, 10, 90);
    cb_pr.body.color_main = color_hsv_to_rgb(hue, 10, 82);

    lv_style_copy(&cb_trel, &cb_rel);
    cb_trel.body.border.width = 4 << LV_ANTIALIAS;
    cb_trel.body.border.color = COLOR_WHITE;
    cb_trel.body.border.opa = OPA_60;
    cb_trel.body.color_main = color_hsv_to_rgb(hue, 50, 82);
    cb_trel.body.color_gradient = color_hsv_to_rgb(hue, 50, 62);

    lv_style_copy(&cb_tpr, &cb_trel);
    cb_tpr.body.border.color = COLOR_SILVER;
    cb_tpr.body.border.opa = OPA_70;
    cb_tpr.body.color_main = color_hsv_to_rgb(hue, 50, 72);
    cb_tpr.body.color_gradient = color_hsv_to_rgb(hue, 50, 52);

    lv_style_copy(&cb_ina, &cb_trel);
    cb_ina.body.border.width = 1 << LV_ANTIALIAS;
    cb_ina.body.border.color = COLOR_GRAY;
    cb_ina.body.color_main = COLOR_SILVER;
    cb_ina.body.color_gradient = COLOR_SILVER;
#endif

    /*List*/
#if USE_LV_LIST != 0
    lv_style_copy(&list_rel, &def);
    list_rel.body.empty = 1;
    list_rel.body.border.width = 1 << LV_ANTIALIAS;
    list_rel.body.border.color = color_hsv_to_rgb(hue, 50, 85);
    list_rel.body.border.opa = OPA_COVER;
    list_rel.text.color = color_hsv_to_rgb(hue, 10, 94);
    list_rel.text.font = font_sm;

    lv_style_copy(&list_pr, &list_rel);
    list_pr.body.empty = 0;
    list_pr.body.opa = OPA_COVER;
    list_pr.body.color_main = color_hsv_to_rgb(hue, 34, 41);
    list_pr.body.color_gradient = color_hsv_to_rgb(hue, 34, 41);
    list_pr.text.color = color_hsv_to_rgb(hue, 7, 96);

    lv_style_copy(&list_trel, &list_rel);
    lv_style_copy(&list_tpr, &list_pr);
    lv_style_copy(&list_ina, &def);

    lv_style_copy(&list_bg, &list_rel);
    list_bg.body.padding.hor = 0;
    list_bg.body.padding.ver = 0;
#endif

    /*Drop down list*/
#if USE_LV_DDLIST != 0
    lv_style_copy(&ddlist_bg, &panel);
    ddlist_bg.text.line_space = LV_DPI / 10;

    lv_style_copy(&ddlist_sel, &panel);
    ddlist_sel.body.color_main = color_hsv_to_rgb(hue, 45, 40);
    ddlist_sel.body.color_gradient = color_hsv_to_rgb(hue, 45, 40);
    ddlist_sel.body.opa = OPA_COVER;
    ddlist_sel.body.radius = 0;
#endif

    /*Roller*/
#if USE_LV_ROLLER != 0
    lv_style_copy(&roller_bg, &ddlist_bg);
    roller_bg.text.line_space = LV_DPI / 6;
    roller_bg.body.radius = LV_DPI / 20;
    roller_bg.body.color_main = COLOR_HEX3(0x222);
    roller_bg.body.color_gradient = COLOR_HEX3(0x999);
    roller_bg.body.border.opa = OPA_30;
    roller_bg.text.opa = OPA_70;
    roller_bg.text.color = color_hsv_to_rgb(hue, 15, 100);
    roller_bg.body.shadow.width = LV_DPI / 20;
    roller_bg.body.shadow.color = COLOR_HEX3(0x111);

    lv_style_copy(&roller_sel, &panel);
    roller_sel.body.empty = 1;
    roller_sel.body.radius = 0;
#endif

    /*Tabview*/
#if USE_LV_TABVIEW != 0
    lv_style_copy(&tab_rel, &def);
    tab_rel.body.color_main = COLOR_HEX3(0x666);
    tab_rel.body.color_gradient = COLOR_HEX3(0x666);
    tab_rel.body.padding.hor = 0;
    tab_rel.body.padding.ver = 0;
    tab_rel.body.padding.inner = 0;
    tab_rel.body.border.width = 1 << LV_ANTIALIAS;
    tab_rel.body.border.color = COLOR_SILVER;
    tab_rel.body.border.opa = OPA_40;
    tab_rel.text.color = COLOR_HEX3(0xDDD);
    tab_rel.text.font = font_sm;

    lv_style_copy(&tab_pr, &tab_rel);
    tab_pr.body.color_main = COLOR_HEX3(0x444);
    tab_pr.body.color_gradient = COLOR_HEX3(0x444);

    lv_style_copy(&tab_trel, &def);
    tab_trel.body.empty = 1;
    tab_trel.body.padding.hor = 0;
    tab_trel.body.padding.ver = 0;
    tab_trel.body.padding.inner = 0;
    tab_trel.body.border.width = 1 << LV_ANTIALIAS;
    tab_trel.body.border.color = COLOR_SILVER;
    tab_trel.body.border.opa = OPA_40;
    tab_trel.text.color = color_hsv_to_rgb(hue, 10, 94);
    tab_trel.text.font = font_md;

    lv_style_copy(&tab_tpr, &def);
    tab_tpr.body.color_main = COLOR_GRAY;
    tab_tpr.body.color_gradient = COLOR_GRAY;
    tab_tpr.body.padding.hor = 0;
    tab_tpr.body.padding.ver = 0;
    tab_tpr.body.padding.inner = 0;
    tab_tpr.body.border.width = 1 << LV_ANTIALIAS;
    tab_tpr.body.border.color = COLOR_SILVER;
    tab_tpr.body.border.opa = OPA_40;
    tab_tpr.text.color = color_hsv_to_rgb(hue, 10, 94);
    tab_tpr.text.font = font_md;

    lv_style_copy(&tab_indic, &def);
    tab_indic.body.border.width = 0;
    tab_indic.body.color_main = color_hsv_to_rgb(hue, 80, 87);
    tab_indic.body.color_gradient = color_hsv_to_rgb(hue, 80, 87);
#endif

    /*For backward compatibility initialize all theme elements with a default style */
    uint16_t i;
    lv_style_t **style_p = (lv_style_t**) &theme;
    for(i = 0; i < sizeof(lv_theme_t) / sizeof(lv_style_t*); i++) {
        *style_p = &def;
        style_p++;
    }

    /*Fill the theme with style pointers*/
    theme.bg = &bg;
    theme.panel = &panel;
    theme.btn.sm.rel = &btn_sm_rel;
    theme.btn.sm.pr = &btn_sm_pr;
    theme.btn.sm.trel = &btn_sm_trel;
    theme.btn.sm.tpr =  &btn_sm_tpr;
    theme.btn.sm.ina =  &btn_sm_ina;
    theme.btn.md.rel =  &btn_md_rel;
    theme.btn.md.pr =   &btn_md_pr;
    theme.btn.md.trel = &btn_md_trel;
    theme.btn.md.tpr =  &btn_md_tpr;
    theme.btn.md.ina =  &btn_md_ina;
    theme.btn.lg.rel =  &btn_lg_rel;
    theme.btn.lg.pr =   &btn_lg_pr;
    theme.btn.lg.trel = &btn_lg_trel;
    theme.btn.lg.tpr =  &btn_lg_tpr;
    theme.btn.lg.ina =  &btn_lg_ina;
    theme.label.sm = &label_sm;
    theme.label.md = &label_md;
    theme.label.lg = &label_lg;
    theme.bar.bg = &bar_bg;
    theme.bar.indic = &bar_indic;
    theme.slider.bg = &bar_bg;
    theme.slider.indic = &bar_indic;
    theme.slider.knob = &slider_knob;
    theme.sw.bg = &sw_bg;
    theme.sw.indic = &sw_indic;
    theme.sw.knob = &sw_knob;
    theme.cb.bg = &cb_bg;
    theme.cb.bullet.rel = &cb_rel;
    theme.cb.bullet.pr = &cb_pr;
    theme.cb.bullet.trel = &cb_trel;
    theme.cb.bullet.tpr = &cb_tpr;
    theme.cb.bullet.ina = &cb_ina;
    theme.page.bg = &panel;
    theme.page.scrl = &lv_style_transp_fit;
    theme.page.sb = &sb;
    theme.ta.area = &panel;
    theme.ta.oneline = &panel;
    theme.ta.sb = &sb;
    theme.ddlist.bg = &ddlist_bg;
    theme.ddlist.sel = &ddlist_sel;
    theme.ddlist.sb = &sb;
    theme.roller.bg = &roller_bg;
    theme.roller.sel = &roller_sel;
    theme.chart.bg = &panel;
    theme.tabview.tab.rel = &tab_rel;
    theme.tabview.tab.pr = &tab_pr;
    theme.tabview.tab.trel = &tab_trel;
    theme.tabview.tab.tpr = &tab_tpr;
    theme.tabview.indic = &tab_indic;
    theme.mbox.bg = &panel;
    theme.list.sb = &sb;
    theme.list.bg = &list_bg;
    theme.list.btn.rel = &list_rel;
    theme.list.btn.pr = &list_pr;
    theme.list.btn.trel = &list_trel;
    theme.list.btn.tpr = &list_tpr;
    theme.list.btn.ina = &list_ina;
}


lv_theme_t * lv_theme_get_alien(void)
{
    return &theme;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
