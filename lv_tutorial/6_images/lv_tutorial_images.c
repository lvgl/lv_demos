/**
 * @file lv_tutorial_images.h
 *
 */

/*
 * -------------------------------------------------------------------------------------------
 * Learn how to use images stored internally (in flash) or externally (like on an SD card)
 *-------------------------------------------------------------------------------------------
 *
 * The basic object to display images is 'lv_img'. It can accept 3 type of image sources:
 *
 * 1. IMAGE CONVETED TO C ARRAY
 *  With the online image converter tool you can convert your images into C arrays:
 *  https://littlevgl.com/image-to-c-array
 *
 *  If you have the converted file:
 *    - Copy the result C file into your project
 *    - Declare the image variable with 'LV_IMG_DECLARE(image_name);'
 *    - Set it for an image obeject: 'lv_img_set_src(img1, &image_name);'
 *
 *  In this case you don't need to think about color format because
 *  all color formats are included in the C file and the currently active
 *  (according to 'LV_COLOR_DEPTH' in 'lv_conf.h') will be enabled.
 *
 * 2. IMAGE FROM FILE
 *  With the above mentioned online image converter tool you can convert images to binary files too.
 *  However now you should choose the right color format.
 *  The result of the conversion should be a *.bin file which can be copied to any external sources (e.g. SD card)
 *
 *  To read this file you need to provide some functions for LittlevGL. You will see it in the example below.
 *
 *  To set a file for an image object use: 'lv_img_set_src(img, "S:path/to/image.bin")'
 *
 * 3. IMAGE FROM SYMBOL FONT
 *  The symbol fonts are letters however they look like small images.
 *  To set symbols in an image use: 'lv_img_set_src(img, SYMBOL_CLOSE)'
 *
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_tutorial_images.h"
#if USE_LV_TUTORIALS

#include "lvgl/lvgl.h"
#include <stdio.h>
#include <errno.h>

/*********************
 *      DEFINES
 *********************/
#define PC_FILES    1       /*If you are on PC you can add PC file function to 'lv_fs'*/

/**********************
 *      TYPEDEFS
 **********************/
typedef  FILE*  pc_file_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
#if PC_FILES
/*Interface functions to standard C file functions (only the required ones to image handling)*/
static lv_fs_res_t pcfs_open (void * file_p, const char * fn, lv_fs_mode_t mode);
static lv_fs_res_t pcfs_close (void * file_p);
static lv_fs_res_t pcfs_read (void * file_p, void * buf, uint32_t btr, uint32_t * br);
static lv_fs_res_t pcfs_seek (void * file_p, uint32_t pos);
static lv_fs_res_t pcfs_tell (void * file_p, uint32_t * pos_p);
#endif

/**********************
 *  STATIC VARIABLES
 **********************/
/*Declare the "source code image" which is stored in the flash*/
LV_IMG_DECLARE(red_flower);

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create images from variable and file
 */
void lv_tutorial_image(void)
{
    /*************************
     * IMAGE FROM SOURCE CODE
     *************************/

    lv_obj_t *img_src = lv_img_create(lv_scr_act(), NULL);  /*Crate an image object*/
    lv_img_set_src(img_src, &red_flower);  /*Set the created file as image (a red fl  ower)*/
    lv_obj_set_pos(img_src, 10, 10);      /*Set the positions*/
    lv_obj_set_drag(img_src, true);

#if PC_FILES
    /**************************
     * IMAGE FROM BINARY FILE
     **************************/

    /* Add a simple drive to open images from PC*/
    lv_fs_drv_t pcfs_drv;                         /*A driver descriptor*/
    memset(&pcfs_drv, 0, sizeof(lv_fs_drv_t));    /*Initialization*/

    pcfs_drv.file_size = sizeof(pc_file_t);       /*Set up fields...*/
    pcfs_drv.letter = 'P';
    pcfs_drv.open = pcfs_open;
    pcfs_drv.close = pcfs_close;
    pcfs_drv.read = pcfs_read;
    pcfs_drv.seek = pcfs_seek;
    pcfs_drv.tell = pcfs_tell;
    lv_fs_add_drv(&pcfs_drv);


    lv_obj_t *img_bin = lv_img_create(lv_scr_act(), NULL);  /*Create an image object*/
    /* Set the image's file according to the current color depth
     * a blue flower picture*/
#if LV_COLOR_DEPTH == 8
    lv_img_set_src(img_bin, "P:/lv_examples/lv_tutorial/6_images/blue_flower_8.bin");
#elif LV_COLOR_DEPTH == 16
    lv_img_set_src(img_bin, "P:/lv_examples/lv_tutorial/6_images/blue_flower_16.bin");
#elif LV_COLOR_DEPTH == 24
    lv_img_set_src(img_bin, "P:/lv_examples/lv_tutorial/6_images/blue_flower_24.bin");
#endif

    lv_obj_align(img_bin, img_src, LV_ALIGN_OUT_RIGHT_TOP, 20, 0);     /*Align next to the source image*/
    lv_obj_set_drag(img_bin, true);
#endif

    lv_obj_t * img_symbol = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img_symbol, SYMBOL_OK);
    lv_obj_set_drag(img_symbol, true);
    lv_obj_align(img_symbol, img_src, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);     /*Align next to the source image*/
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Open a file from the PC
 * @param file_p pointer to a FILE* variable
 * @param fn name of the file.
 * @param mode element of 'fs_mode_t' enum or its 'OR' connection (e.g. FS_MODE_WR | FS_MODE_RD)
 * @return LV_FS_RES_OK: no error, the file is opened
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t pcfs_open (void * file_p, const char * fn, lv_fs_mode_t mode)
{
    errno = 0;

    const char * flags = "";

    if(mode == LV_FS_MODE_WR) flags = "wb";
    else if(mode == LV_FS_MODE_RD) flags = "rb";
    else if(mode == (LV_FS_MODE_WR | LV_FS_MODE_RD)) flags = "a+";

    /*Make the path relative to the current directory (the projects root folder)*/
    char buf[256];
    sprintf(buf, "./%s", fn);

    pc_file_t f = fopen(buf, flags);
    if((long int)f <= 0) return LV_FS_RES_UNKNOWN;
    else {
        fseek(f, 0, SEEK_SET);

        /* 'file_p' is pointer to a file descriptor and
         * we need to store our file descriptor here*/
        pc_file_t *fp = file_p;         /*Just avoid the confusing casings*/
        *fp = f;
    }

    return LV_FS_RES_OK;
}


/**
 * Close an opened file
 * @param file_p pointer to a FILE* variable. (opened with lv_ufs_open)
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv__fs_res_t enum
 */
static lv_fs_res_t pcfs_close (void * file_p)
{
    pc_file_t *fp = file_p;         /*Just avoid the confusing casings*/
    fclose(*fp);
    return LV_FS_RES_OK;
}

/**
 * Read data from an opened file
 * @param file_p pointer to a FILE variable.
 * @param buf pointer to a memory block where to store the read data
 * @param btr number of Bytes To Read
 * @param br the real number of read bytes (Byte Read)
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv__fs_res_t enum
 */
static lv_fs_res_t pcfs_read (void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    pc_file_t *fp = file_p;         /*Just avoid the confusing casings*/
    *br = fread(buf, 1, btr, *fp);
    return LV_FS_RES_OK;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param file_p pointer to a FILE* variable. (opened with lv_ufs_open )
 * @param pos the new position of read write pointer
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv__fs_res_t enum
 */
static lv_fs_res_t pcfs_seek (void * file_p, uint32_t pos)
{
    pc_file_t *fp = file_p;         /*Just avoid the confusing casings*/
    fseek(*fp, pos, SEEK_SET);
    return LV_FS_RES_OK;
}

/**
 * Give the position of the read write pointer
 * @param file_p pointer to a FILE* variable.
 * @param pos_p pointer to to store the result
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv__fs_res_t enum
 */
static lv_fs_res_t pcfs_tell (void * file_p, uint32_t * pos_p)
{
    pc_file_t *fp = file_p;         /*Just avoid the confusing casings*/
    *pos_p = ftell(*fp);
    return LV_FS_RES_OK;
}

#endif /*USE_LV_TUTORIALS*/
