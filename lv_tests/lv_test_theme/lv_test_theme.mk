CSRCS += lv_test_theme_1.c
CSRCS += lv_test_theme_2.c

DEPPATH += --dep-path lv_examples/lv_tests/lv_test_theme
VPATH += :lv_examples/lv_tests/lv_test_theme

CFLAGS += "-I$(LVGL_DIR)/lv_examples/lv_tests/lv_test_theme"
