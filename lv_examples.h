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
#include "../lv_ex_conf.h"
#include "src/lv_ex_widgets/lv_ex_widgets.h"
#include "src/lv_ex_demos/lv_demo_widgets/lv_demo_widgets.h"

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
