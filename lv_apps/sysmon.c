///**
// * @file lv_sysmon.c
// *
// */
//
///*********************
// *      INCLUDES
// *********************/
//#include "sysmon.h"
//
//#include <stdio.h>
//#include "lvgl/lvgl.h"
//#include "misc/os/ptask.h"
//#include "misc/os/idle.h"
//#include "misc/gfx/text.h"
//
//#include "lvgl/lv_objx/lv_chart.h"
//
//
///*********************
// *      DEFINES
// *********************/
//#define CPU_LABEL_COLOR     "FF0000"
//#define MEM_LABEL_COLOR     "0000FF"
//#define CHART_POINT_NUM     100
//#define REFR_TIME    500
//
///**********************
// *      TYPEDEFS
// **********************/
//
///**********************
// *  STATIC PROTOTYPES
// **********************/
//
//static void sysmon_task(void * param);
//static void sysmon_refr(void);
//static lv_action_res_t win_close_action(lv_obj_t * btn);
//
///**********************
// *  STATIC VARIABLES
// **********************/
//
//static lv_obj_t * win;
//static lv_obj_t * chart;
//static lv_chart_dl_t * cpu_dl;
//static lv_chart_dl_t * mem_dl;
//static lv_obj_t * label;
//static lv_style_t style_cbtn;
//
//static uint8_t mem_pct[CHART_POINT_NUM];
//static uint8_t cpu_pct[CHART_POINT_NUM];
//#if USE_DYN_MEM != 0  && DM_CUSTOM == 0
//static  dm_mon_t mem_mon;
//#endif
//
///**********************
// *      MACROS
// **********************/
//
///**********************
// *   GLOBAL FUNCTIONS
// **********************/
//
///**
// * Initialize the sytem monitor
// */
//void sysmon_init(void)
//{
//    ptask_create(sysmon_task, REFR_TIME, PTASK_PRIO_LOW, NULL);
//
//    memset(mem_pct, 0, sizeof(mem_pct));
//    memset(cpu_pct, 0, sizeof(cpu_pct));
//
//    lv_style_copy(&style_cbtn, lv_style_get(LV_STYLE_BUTTON_ON_RELEASED));
//    style_cbtn.text.font = font_get(FONT_SYMBOL_30);
//
//    win = lv_win_create(lv_scr_act(), NULL);
//    lv_win_set_styles_cbtn(win, &style_cbtn, &style_cbtn);
//    lv_win_add_cbtn(win, SYMBOL_CLOSE, win_close_action);
//
//    /*Make the window content responsive*/
//    lv_cont_set_layout(lv_page_get_scrl(lv_win_get_page(win)), LV_CONT_LAYOUT_PRETTY);
//
//    /*Create a chart with two data lines*/
//    chart = lv_chart_create(win, NULL);
//    lv_obj_set_size(chart, LV_HOR_RES / 2, LV_VER_RES / 2);
//    lv_obj_set_pos(chart, LV_DPI / 10, LV_DPI / 10);
//    lv_chart_set_pnum(chart, CHART_POINT_NUM);
//    lv_chart_set_range(chart, 0, 100);
//    lv_chart_set_type(chart, LV_CHART_LINE);
//    lv_chart_set_dl_width(chart, 2 << LV_ANTIALIAS);
//    cpu_dl =  lv_chart_add_data_line(chart, COLOR_RED);
//    mem_dl =  lv_chart_add_data_line(chart, COLOR_BLUE);
//
//    memcpy(cpu_dl->points, cpu_pct, sizeof(cpu_pct));
//    memcpy(mem_dl->points, mem_pct, sizeof(mem_pct));
//
//    /*Create a label for the details of Memory and CPU usage*/
//    label = lv_label_create(win, NULL);
//    lv_label_set_recolor(label, true);
//    lv_obj_align(label, chart, LV_ALIGN_OUT_RIGHT_TOP, LV_DPI / 4, 0);
//
//    sysmon_refr();
//}
//
///**
// * Delete the System monitor Window.
// */
//void sysmon_close(void)
//{
//    lv_obj_del(win);
//    win = NULL;
//    label = NULL;
//    chart = NULL;
//    cpu_dl = NULL;
//    mem_dl = NULL;
//}
//
///**********************
// *   STATIC FUNCTIONS
// **********************/
//
///**
// * Called periodically to monitor the CPU and memory usage.
// * It refreshes the shortcuts and windows and also add notifications if there is any problem.
// * @param param unused
// */
//static void sysmon_task(void * param)
//{
//    /*Shift out the oldest data*/
//    uint16_t i;
//    for(i = 1; i < CHART_POINT_NUM; i++) {
//        mem_pct[i - 1] = mem_pct[i];
//        cpu_pct[i - 1] = cpu_pct[i];
//    }
//
//    /*Get CPU and memory information */
//    uint8_t cpu_busy = 0;
//#if USE_IDLE != 0   /*Use the more precise idle module if enabled*/
//    cpu_busy = 100 - idle_get();
//#else
//    cpu_busy = 100 - ptask_get_idle();
//#endif
//
//    uint8_t mem_used_pct = 0;
//#if  USE_DYN_MEM != 0  && DM_CUSTOM == 0
//    dm_monitor(&mem_mon);
//    mem_used_pct = mem_mon.pct_used;
//#endif
//
//    /*Add the CPU and memory data*/
//    cpu_pct[CHART_POINT_NUM - 1] = cpu_busy;
//    mem_pct[CHART_POINT_NUM - 1] = mem_used_pct;
//
//    /*Refresh the and windows*/
//    sysmon_refr();
//}
//
///**
// * Refresh the shortcuts and windows.
// */
//static void sysmon_refr(void)
//{
//    if(win == NULL) return;
//    char buf_long[256];
//    sprintf(buf_long, "%c%s CPU: %d %%%c\n\n",TXT_RECOLOR_CMD, CPU_LABEL_COLOR, cpu_pct[CHART_POINT_NUM - 1], TXT_RECOLOR_CMD);
//
//#if USE_DYN_MEM != 0  && DM_CUSTOM == 0
//    sprintf(buf_long, "%s%c%s MEMORY: %d %%%c\nTotal: %d bytes\nUsed: %d bytes\nFree: %d bytes\nFrag: %d %%",
//                  buf_long,
//                  TXT_RECOLOR_CMD,
//                  MEM_LABEL_COLOR,
//                  mem_pct[CHART_POINT_NUM - 1],
//                  TXT_RECOLOR_CMD,
//                  (int)mem_mon.size_total,
//                  (int)mem_mon.size_total - mem_mon.size_free, mem_mon.size_free, mem_mon.pct_frag);
//
//#else
//    sprintf(buf_long, "%s%c%s MEMORY: N/A%c", buf_long, TXT_RECOLOR_CMD, MEM_LABEL_COLOR, TXT_RECOLOR_CMD);
//#endif
//    lv_label_set_text(label, buf_long);
//
//    lv_chart_set_next(chart, mem_dl, mem_pct[CHART_POINT_NUM - 1]);
//    lv_chart_set_next(chart, cpu_dl, cpu_pct[CHART_POINT_NUM - 1]);
//}
//
//static lv_action_res_t win_close_action(lv_obj_t * btn)
//{
//    sysmon_close();
//    return LV_ACTION_RES_INV;
//}
