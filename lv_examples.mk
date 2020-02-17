include $(LVGL_DIR)/lv_examples/src/lv_ex_widgets/lv_ex_widgets.mk

# FIXME: move the below lines to demos directory

CSRCS += lv_demo_widgets/lv_demo_widgets.c
DEPPATH += --dep-path $(LVGL_DIR)/lv_examples/src/lv_ex_demos
VPATH += :$(LVGL_DIR)/lv_examples/src/lv_ex_demos
CFLAGS += "-I$(LVGL_DIR)/lv_examples/src/lv_ex_demos"