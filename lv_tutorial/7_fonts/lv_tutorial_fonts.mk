CSRCS += lv_tutorial_fonts.c
CSRCS += ubuntu_40_ascii.c
CSRCS += ubuntu_40_cyrillic.c

DEPPATH += --dep-path lv_examples/lv_tutorial/7_fonts
VPATH += :lv_examples/lv_tutorial/7_fonts

CFLAGS += "-I$(LVGL_DIR)/lv_examples/lv_tutorial/7_fonts"
