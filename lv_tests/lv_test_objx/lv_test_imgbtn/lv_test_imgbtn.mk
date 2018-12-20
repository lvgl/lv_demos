CSRCS += lv_test_imgbtn.c \
         imgbtn_img_1.c \
         imgbtn_img_2.c \
         imgbtn_img_3.c \
         imgbtn_img_4.c

DEPPATH += --dep-path lv_examples/lv_tests/lv_test_objx/lv_test_imgbtn
VPATH += :lv_examples/lv_tests/lv_test_objx/lv_test_imgbtn

CFLAGS += "-I$(LVGL_DIR)/lv_examples/lv_tests/lv_test_objx/lv_test_imgbtn"
