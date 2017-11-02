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

    struct {
        lv_style_t *sm;
        lv_style_t *md;
        lv_style_t *lg;
    }label;

    struct {
        lv_style_t *bg;
        lv_style_t *indic;
    }bar;

    struct {
        lv_style_t *bg;
        lv_style_t *indic;
        lv_style_t *knob;
    }slider;

    struct {
        lv_style_t *bg;
        lv_style_t *indic;
        lv_style_t *knob;
    }sw;

    struct {
        lv_style_t *area;
        lv_style_t *oneline;
        lv_style_t *sb;
    }ta;

    struct {
        lv_style_t *bg;
    }chart;

    struct {
        lv_style_t *bg;
        lv_style_t *rel;
        lv_style_t *pr;
        lv_style_t *trel;
        lv_style_t *tpr;
    }btnm;

    struct {
        lv_style_t *indic;
        lv_style_t *rel;
        lv_style_t *pr;
        lv_style_t *trel;
        lv_style_t *tpr;
    }tab;

    struct {
        lv_style_t *bg;
        lv_style_t *rel;
        lv_style_t *pr;
    }mbox;

    struct {
        lv_style_t *rel;
        lv_style_t *pr;
        lv_style_t *trel;
        lv_style_t *tpr;
        lv_style_t *ina;
        lv_style_t *sb;
    }list;

    struct {
        lv_style_t *bg;
        lv_style_t *sel;
    }ddlist;

    struct {
        lv_style_t *bg;
        lv_style_t *sel;
    }roller;

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
}lv_theme_t;

/**********************
 *  GLOBAL PROTOTYPES
 **********************/
void lv_theme_alien_init(font_t *font_sm, font_t *font_md, font_t *font_lg);
lv_theme_t * lv_theme_get_alien(void) ;

/**********************
 *    MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_THEMES_H*/
