from lv_colors import lv_colors

with open('../../../assets/img_hand.bin','rb') as f:
    hand_img_data = f.read()
    
# create the hands image data

img_hand_dsc = lv.img_dsc_t(
    {
        "header": {"always_zero": 0, "w": 100, "h": 9, "cf": lv.img.CF.TRUE_COLOR_ALPHA},
        "data": hand_img_data,
        "data_size": len(hand_img_data),
    }
)

# needle colors
needle_colors=[lv_colors.BLUE,lv_colors.ORANGE,lv_colors.PURPLE]

# create the gauge
gauge1=lv.gauge(lv.scr_act(),None)
gauge1.set_needle_count(3, needle_colors)
gauge1.set_size(200,200)
gauge1.align(None,lv.ALIGN.CENTER,0,0)
gauge1.set_needle_img(img_hand_dsc, 4, 4)
gauge1.set_style_local_image_recolor_opa(lv.gauge.PART.NEEDLE, lv.STATE.DEFAULT, lv.OPA.COVER)

# Set the values
gauge1.set_value(0, 10)
gauge1.set_value(1, 20)
gauge1.set_value(2, 30)
