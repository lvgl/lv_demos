/**
 * @file lv_demo_music.h
 *
 */

#ifndef LV_DEMO_MUSIC_H
#define LV_DEMO_MUSIC_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_examples.h"

/*********************
 *      DEFINES
 *********************/
#define LV_DEMO_MUSIC_LANDSCAPE       1

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

const char * _lv_demo_music_get_title(uint32_t track_id);
const char * _lv_demo_music_get_artist(uint32_t track_id);
const char * _lv_demo_music_get_genre(uint32_t track_id);
uint32_t _lv_demo_music_get_track_length(uint32_t track_id);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DEMO_MUSICL_H*/
