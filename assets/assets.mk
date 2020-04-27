CSRCS += img_cogwheel_alpha16.c
CSRCS += img_cogwheel_argb.c
CSRCS += img_cogwheel_chroma_keyed.c
CSRCS += img_cogwheel_indexed16.c
CSRCS += lv_font_montserrat_12_compr_az.c
CSRCS += lv_font_montserrat_16_compr_az.c
CSRCS += lv_font_montserrat_28_compr_az.c

DEPPATH += --dep-path $(LVGL_DIR)/lv_examples/assets
VPATH += :$(LVGL_DIR)/lv_examples/assets
CFLAGS += "-I$(LVGL_DIR)/lv_examples/assets"

