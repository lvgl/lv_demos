CSRCS += lv_test_tileview.c

DEPPATH += --dep-path lv_examples/lv_tests/lv_test_objx/lv_test_tileview
VPATH += :lv_examples/lv_tests/lv_test_objx/lv_test_tileview

CFLAGS += "-I$(LVGL_DIR)/lv_examples/lv_tests/lv_test_objx/lv_test_tileview"
