/**
 * @file lv_examples.h
 *
 */

#ifndef LV_EXAMPLES_H
#define LV_EXAMPLES_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lvgl/lvgl.h"

#if defined(LV_EX_CONF_PATH)
#define __LV_TO_STR_AUX(x) #x
#define __LV_TO_STR(x) __LV_TO_STR_AUX(x)
#include __LV_TO_STR(LV_EX_CONF_PATH)
#undef __LV_TO_STR_AUX
#undef __LV_TO_STR
#elif defined(LV_EX_CONF_INCLUDE_SIMPLE)
#include "lv_ex_conf.h"
#else
#include "../lv_ex_conf.h"
#endif

#include "src/lv_ex_widgets/lv_ex_widgets.h"
#include "src/lv_ex_style/lv_ex_style.h"
#include "src/lv_demo_widgets/lv_demo_widgets.h"

/*********************
 *      DEFINES
 *********************/
/*Test  lvgl version*/
#if LV_VERSION_CHECK(7, 0, 0) == 0
#error "lv_examples: Wrong lvgl version"
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/


/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_EXAMPLES_H*/
