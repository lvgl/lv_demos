CSRCS += lv_demo_widgets.c

DEPPATH += --dep-path $(LVGL_DIR)/lv_examples/src/lv_demo_widgets
VPATH += :$(LVGL_DIR)/lv_examples/src/lv_demo_widgets
CFLAGS += "-I$(LVGL_DIR)/lv_examples/src/lv_demo_widgets"

