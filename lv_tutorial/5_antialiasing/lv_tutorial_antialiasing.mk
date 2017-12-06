CSRCS += lv_tutorial_antialiasing.c

DEPPATH += --dep-path lv_examples/lv_tutorial/5_antialiasing
VPATH += :lv_examples/lv_tutorial/5_antialiasing

CFLAGS += "-I$(LVGL_DIR)/lv_examples/lv_tutorial/5_antialiasing"
