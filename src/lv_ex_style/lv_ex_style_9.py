import lvgl as lv
import init_gui
from lv_colors import *
from imagetools import get_png_info, open_png

# Register PNG image decoder
decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

# Create a screen with a draggable image
with open('cogwheel.png','rb') as f:
  png_data = f.read()

png_img_dsc = lv.img_dsc_t({
    'data_size': len(png_data),
    'data': png_data 
})

style = lv.style_t()
style.init()
# Set a background color and a radius
style.set_radius(lv.STATE.DEFAULT, 5)
style.set_bg_opa(lv.STATE.DEFAULT, lv.OPA.COVER)
style.set_bg_color(lv.STATE.DEFAULT, LV_COLOR_SILVER)
style.set_border_width(lv.STATE.DEFAULT, 2)
style.set_border_color(lv.STATE.DEFAULT, LV_COLOR_BLUE)
style.set_pad_top(lv.STATE.DEFAULT, 10)
style.set_pad_bottom(lv.STATE.DEFAULT, 10)
style.set_pad_left(lv.STATE.DEFAULT, 10)
style.set_pad_right(lv.STATE.DEFAULT, 10)

style.set_image_recolor(lv.STATE.DEFAULT, LV_COLOR_BLUE)
style.set_image_recolor_opa(lv.STATE.DEFAULT, lv.OPA._50)

# Create an object with the new style
obj = lv.img(lv.scr_act(), None)
lv.img.cache_set_size(2)

obj.add_style(lv.img.PART.MAIN, style)
obj.set_src(png_img_dsc)
obj.align(None, lv.ALIGN.CENTER, 0, 0)
