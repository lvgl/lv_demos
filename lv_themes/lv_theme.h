/**
 *@file lv_themes.h
 *
 */

#ifndef LV_THEMES_H
#define LV_THEMES_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *    INCLUDES
 *********************/

/*********************
 *    DEFINES
 *********************/

/**********************
 *    TYPEDEFS
 **********************/
typedef struct {
    lv_style_t *bg;
    lv_style_t *panel;
#if USE_LV_BTN != 0
    struct {
        struct {
            lv_style_t *rel;
            lv_style_t *pr;
            lv_style_t *trel;
            lv_style_t *tpr;
            lv_style_t *ina;
        }sm;

        struct {
            lv_style_t *rel;
            lv_style_t *pr;
            lv_style_t *trel;
            lv_style_t *tpr;
            lv_style_t *ina;
        }md;

        struct {
            lv_style_t *rel;
            lv_style_t *pr;
            lv_style_t *trel;
            lv_style_t *tpr;
            lv_style_t *ina;
        }lg;
    }btn;
#endif

#if USE_LV_LABEL != 0
    struct {
        lv_style_t *sm;
        lv_style_t *md;
        lv_style_t *lg;
    }label;
#endif

#if USE_LV_BAR != 0
    struct {
        lv_style_t *bg;
        lv_style_t *indic;
    }bar;
#endif

#if USE_LV_SLIDER != 0
    struct {
        lv_style_t *bg;
        lv_style_t *indic;
        lv_style_t *knob;
    }slider;
#endif

#if USE_LV_SW != 0
    struct {
        lv_style_t *bg;
        lv_style_t *indic;
        lv_style_t *knob;
    }sw;
#endif

#if USE_LV_PAGE != 0
    struct {
        lv_style_t *bg;
        lv_style_t *scrl;
        lv_style_t *sb;
    }page;
#endif

#if USE_LV_TA != 0
    struct {
        lv_style_t *area;
        lv_style_t *oneline;
        lv_style_t *sb;
    }ta;
#endif

#if USE_LV_LIST
    struct {
        lv_style_t *bg;
        lv_style_t *sb;
        struct {
            lv_style_t *rel;
            lv_style_t *pr;
            lv_style_t *trel;
            lv_style_t *tpr;
            lv_style_t *ina;
        }btn;
    }list;
#endif

#if USE_LV_DDLIST != 0
    struct {
        lv_style_t *bg;
        lv_style_t *sel;
        lv_style_t *sb;
    }ddlist;
#endif

#if USE_LV_CHART != 0
    struct {
        lv_style_t *bg;
    }chart;
#endif

#if USE_LV_CB != 0
    struct {
        lv_style_t *bg;
        struct {
            lv_style_t *rel;
            lv_style_t *pr;
            lv_style_t *trel;
            lv_style_t *tpr;
            lv_style_t *ina;
        }bullet;
    }cb;
#endif

#if USE_LV_BTNM != 0
    struct {
        lv_style_t *bg;
        lv_style_t *rel;
        lv_style_t *pr;
        lv_style_t *trel;
        lv_style_t *tpr;
    }btnm;
#endif

#if USE_LV_TABVIEW != 0
    struct {
        lv_style_t *bg;
        lv_style_t *sb;
        lv_style_t *indic;
        struct {
            lv_style_t *rel;
            lv_style_t *pr;
            lv_style_t *trel;
            lv_style_t *tpr;
        }tab;
    }tabview;
#endif

#if USE_LV_MBOX != 0
    struct {
        lv_style_t *bg;
        lv_style_t *rel;
        lv_style_t *pr;
    }mbox;
#endif

#if USE_LV_ROLLER != 0
    struct {
        lv_style_t *bg;
        lv_style_t *sel;
    }roller;
#endif

#if USE_LV_WIN != 0
    struct {
        lv_style_t *bg;
        lv_style_t *header;
        struct {
            lv_style_t *rel;
            lv_style_t *pr;
        }cbtn;
        struct {
            lv_style_t *bg;
            lv_style_t *scrl;
        }cont;
    }win;
#endif
}lv_theme_t;

/**********************
 *  GLOBAL PROTOTYPES
 **********************/
void lv_theme_alien_init(uint16_t hue, font_t *font_sm, font_t *font_md, font_t *font_lg);
lv_theme_t * lv_theme_get_alien(void) ;

/**********************
 *    MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_THEMES_H*/
