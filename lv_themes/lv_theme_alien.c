/**
 * @file lv_theme_alien.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"
#include "lv_themes.h"
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

static lv_style_t ta_sb;

static lv_style_t tab_rel;
static lv_style_t tab_pr;
static lv_style_t tab_trel;
static lv_style_t tab_tpr;
static lv_style_t tab_indic;

static lv_style_t list_rel;
static lv_style_t list_pr;
static lv_style_t list_trel;
static lv_style_t list_tpr;
static lv_style_t list_ina;
static lv_style_t list_sb;


/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void lv_theme_alien_init(font_t *font_sm, font_t *font_md, font_t *font_lg)
{
    /*Background*/
    lv_style_copy(&def, &lv_style_plain);
    def.body.opa = OPA_COVER;
    def.glass = 0;

    def.body.empty = 0;
    def.body.color_main = COLOR_HEX(0x202020);
    def.body.color_gradient = COLOR_HEX(0x202020);
    def.body.radius = 0;
    def.body.padding.hor = LV_DPI / 8;
    def.body.padding.ver = LV_DPI / 8;
    def.body.padding.inner = LV_DPI / 6;
    def.body.border.color = COLOR_SILVER;
    def.body.border.width = 1 << LV_ANTIALIAS;
    def.body.border.opa = OPA_COVER;
    def.body.shadow.color = COLOR_SILVER;
    def.body.shadow.width = 0;
    def.body.shadow.type = LV_SHADOW_FULL;

    def.text.color = COLOR_HEX(0xD0D0D0);
    def.text.font = font_sm;
    def.text.space_letter = 1 << LV_ANTIALIAS;
    def.text.space_line = 2 << LV_ANTIALIAS;
    def.text.align = LV_TEXT_ALIGN_LEFT;

    def.image.color = COLOR_HEX(0xD0D0D0);
    def.image.intense = OPA_TRANSP;

    def.line.color = COLOR_HEX(0x43744b);
    def.line.width = 1 << LV_ANTIALIAS;

    /*Background*/
    lv_style_copy(&bg, &def);
    bg.body.color_main = COLOR_HEX(0x303030);
    bg.body.color_gradient = COLOR_HEX(0x012307);
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
    panel.text.color = COLOR_HEX(0xe1f4e4);

    /*Buttons*/
    lv_style_copy(&btn_sm_rel, &def);
    btn_sm_rel.glass = 0;
    btn_sm_rel.body.empty = 1;
    btn_sm_rel.body.radius = LV_RADIUS_CIRCLE;
    btn_sm_rel.body.border.width = 3 << LV_ANTIALIAS;
    btn_sm_rel.body.border.color = COLOR_HEX(0x43744b);
    btn_sm_rel.body.border.color = COLOR_HEX(0x2ce84b);
    btn_sm_rel.body.border.opa = OPA_80;
    btn_sm_rel.text.color = COLOR_HEX(0xD0D0D0);
    btn_sm_rel.text.font = font_sm;
    btn_sm_rel.text.align = LV_TEXT_ALIGN_MID;

    lv_style_copy(&btn_sm_pr, &btn_sm_rel);
    btn_sm_pr.body.opa = OPA_70;
    btn_sm_pr.body.empty = 0;
    btn_sm_pr.body.color_main = COLOR_HEX(0x404040);
    btn_sm_pr.body.color_gradient = COLOR_HEX(0x40804b);
    btn_sm_pr.body.border.opa = OPA_60;
    btn_sm_pr.text.font = font_sm;
    btn_sm_pr.text.align = LV_TEXT_ALIGN_MID;
    btn_sm_pr.text.color = COLOR_HEX(0xe1f4e2);

    lv_style_copy(&btn_md_rel, &btn_sm_rel);
    btn_md_rel.text.font = font_md;

    lv_style_copy(&btn_md_pr, &btn_sm_pr);
    btn_md_pr.text.font = font_md;

    lv_style_copy(&btn_lg_rel, &btn_sm_rel);
    btn_lg_rel.text.font = font_lg;

    lv_style_copy(&btn_lg_pr, &btn_sm_pr);
    btn_lg_pr.text.font = font_lg;

    /*Labels*/
    lv_style_copy(&label_sm, &def);
    label_sm.text.font = font_sm;
    label_sm.text.color = COLOR_HEX(0xd7efdb);

    lv_style_copy(&label_md, &def);
    label_md.text.font = font_md;
    label_md.text.color = COLOR_HEX(0xd7efdb);

    lv_style_copy(&label_lg, &def);
    label_lg.text.font = font_lg;
    label_lg.text.color = COLOR_HEX(0xd7efdb);

    /*Bar*/
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
    bar_indic.body.color_main = COLOR_HEX(0x7ed38c);
    bar_indic.body.color_gradient = COLOR_HEX(0x7ed38c);

    /*Slider knob*/
    lv_style_copy(&slider_knob, &def);
    slider_knob.body.opa = OPA_60;
    slider_knob.body.radius = LV_RADIUS_CIRCLE;
    slider_knob.body.color_main = COLOR_WHITE;
    slider_knob.body.color_gradient = COLOR_SILVER;
    slider_knob.body.border.width = 1 << LV_ANTIALIAS;
    slider_knob.body.border.color = COLOR_GRAY;
    slider_knob.body.border.opa = OPA_50;

    /*Switch*/
    lv_style_copy(&sw_bg, &bar_bg);
    sw_bg.body.opa = OPA_COVER;
    sw_bg.body.padding.ver = -2  << LV_ANTIALIAS;
    sw_bg.body.padding.hor = -2  << LV_ANTIALIAS;
    sw_bg.body.color_main = COLOR_HEX(0x606060);
    sw_bg.body.color_gradient = COLOR_HEX(0x909090);
    sw_bg.body.border.width = 2 << LV_ANTIALIAS;
    sw_bg.body.border.opa = OPA_50;

    lv_style_copy(&sw_indic, &bar_indic);
    sw_indic.body.shadow .width = LV_DPI / 12;
    sw_indic.body.padding.ver = 0;
    sw_indic.body.padding.hor = 0;

    lv_style_copy(&sw_knob, &slider_knob);
    sw_knob.body.opa = OPA_80;

    /*Text area*/

    lv_style_copy(&ta_sb, &def);
    ta_sb.body.opa = OPA_50;
    ta_sb.body.radius = LV_DPI / 10;
    ta_sb.body.color_main = COLOR_HEX3(0xeee);
    ta_sb.body.color_gradient = COLOR_HEX3(0xeee);
    ta_sb.body.border.color = COLOR_HEX3(0xfff);
    ta_sb.body.border.width = 1 << LV_ANTIALIAS;
    ta_sb.body.border.opa = OPA_80;

    /*Tabs*/
    lv_style_copy(&tab_rel, &def);
    tab_rel.body.color_main = COLOR_HEX(0x606060);
    tab_rel.body.color_gradient = COLOR_HEX(0x606060);
    tab_rel.body.padding.hor = 0;
    tab_rel.body.padding.ver = 0;
    tab_rel.body.padding.inner = 0;
    tab_rel.body.border.width = 1 << LV_ANTIALIAS;
    tab_rel.body.border.color = COLOR_SILVER;
    tab_rel.body.border.opa = OPA_40;
    tab_rel.text.color = COLOR_HEX(0xD0D0D0);
    tab_rel.text.font = font_sm;

    lv_style_copy(&tab_pr, &tab_rel);
    tab_pr.body.color_main = COLOR_HEX(0x404040);
    tab_pr.body.color_gradient = COLOR_HEX(0x404040);

    lv_style_copy(&tab_trel, &def);
    tab_trel.body.empty = 1;
    tab_trel.body.padding.hor = 0;
    tab_trel.body.padding.ver = 0;
    tab_trel.body.padding.inner = 0;
    tab_trel.body.border.width = 1 << LV_ANTIALIAS;
    tab_trel.body.border.color = COLOR_SILVER;
    tab_trel.body.border.opa = OPA_40;
    tab_trel.text.color = COLOR_HEX(0xd7efdb);
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
    tab_tpr.text.color = COLOR_HEX(0xd7efdb);
    tab_tpr.text.font = font_md;

    lv_style_copy(&tab_indic, &def);
    tab_indic.body.border.width = 0;
    tab_indic.body.color_main = COLOR_HEX(0x16de37);
    tab_indic.body.color_gradient = COLOR_HEX(0x16de37);

    /*List*/
    lv_style_copy(&list_rel, &def);
    list_rel.body.empty = 1;
    list_rel.body.border.width = 1 << LV_ANTIALIAS;
    list_rel.body.border.color = COLOR_HEX(0x43744b);
    list_rel.body.border.opa = OPA_40;
    list_rel.text.color = COLOR_HEX(0xd7efdb);
    list_rel.text.font = font_sm;

    lv_style_copy(&list_pr, &list_rel);
    list_pr.body.empty = 0;
    list_pr.body.opa = OPA_COVER;
    list_pr.body.color_main = COLOR_HEX(0x45684b);
    list_pr.body.color_gradient = COLOR_HEX(0x45684b);
    list_pr.text.color = COLOR_HEX(0xe5f5e8);

    lv_style_copy(&list_trel, &list_rel);
    lv_style_copy(&list_tpr, &list_pr);
    lv_style_copy(&list_ina, &def);

    lv_style_copy(&list_sb, &def);
    list_sb.body.opa = OPA_50;
    list_sb.body.radius = LV_RADIUS_CIRCLE;
    list_sb.body.border.color = COLOR_BLACK;
    list_sb.body.border.opa = OPA_COVER;
    list_sb.body.border.width = 1 << LV_ANTIALIAS;
    list_sb.body.color_main = COLOR_HEX(0x9eebab);
    list_sb.body.color_gradient = COLOR_HEX(0x9eebab);

    /*For backward compatibility initialize all theme elements with a default style */
    uint16_t i;
    lv_style_t **style_p = (lv_style_t**) &theme;
    for(i = 0; i < sizeof(lv_theme_t) / sizeof(lv_style_t*); i++) {
        *style_p = &def;
        style_p++;
    }

    /*Fill the theme with style pointers*/
    theme.bg = &bg;
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
    theme.ta.area = &panel;
    theme.ta.oneline = &panel;
    theme.ta.sb = &ta_sb;
    theme.chart.bg = &panel;
    theme.tab.rel = &tab_rel;
    theme.tab.pr = &tab_pr;
    theme.tab.trel = &tab_trel;
    theme.tab.tpr = &tab_tpr;
    theme.tab.indic = &tab_indic;
    theme.mbox.bg = &panel;
    theme.list.rel = &list_rel;
    theme.list.pr = &list_pr;
    theme.list.trel = &list_trel;
    theme.list.tpr = &list_tpr;
    theme.list.ina = &list_ina;
    theme.list.sb = &list_sb;
    theme.ddlist.bg = &panel;
    theme.roller.bg = &panel;
}


lv_theme_t * lv_theme_get_alien(void)
{
    return &theme;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
