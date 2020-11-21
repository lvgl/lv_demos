LV_USE_LINE=1

style = lv.style_t()
style.init()

style.set_line_color(lv.STATE.DEFAULT, LV_COLOR_GRAY)
style.set_line_width(lv.STATE.DEFAULT, 6)
style.set_line_rounded(lv.STATE.DEFAULT, True)
    
if LV_USE_LINE:
    # Create an object with the new style
    obj = lv.line(lv.scr_act(), None)
    obj.add_style(lv.line.PART.MAIN, style)
    
    #static lv_point_t p[] = {{10, 30}, {30, 50}, {100, 0}};
    p =  [ {"x":10, "y":30}, 
           {"x":30, "y":50}, 
           {"x":100, "y":0}]
    
    obj.set_points(p, 3)

    obj.align(None, lv.ALIGN.CENTER, 0, 0)
