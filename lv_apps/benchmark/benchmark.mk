CSRCS += benchmark.c
CSRCS += img_benchmark_bg.c

DEPPATH += --dep-path lv_examples/lv_apps/benchmark
VPATH += :lv_examples/lv_apps/benchmark

CFLAGS += "-I$(LVGL_DIR)/lv_examples/lv_apps/benchmark"
