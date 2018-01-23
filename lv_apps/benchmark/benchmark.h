/**
 * @file benchmark.h
 *
 */

#ifndef BENCHMARK_H
#define BENCHMARK_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../../lv_ex_conf.h"
#if USE_LV_DEMO
    
#include "../../../lvgl/lvgl.h"
    
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Open a graphics benchmark
 */
void bechmark_create(void);
/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_BENCHMARK*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BENCHMARK_H */
