def event_handler(obj, event):
    if event == lv.EVENT.VALUE_CHANGED:
        idx = obj.get_selected()
        option = obj.get_options().split("\n")[idx]
        print("Option: %s" % option)

# Create a drop down list
ddlist = lv.ddlist(lv.scr_act())
ddlist.set_options("\n".join([
                    "Apple",
                    "Banana",
                    "Orange",
                    "Melon",
                    "Grape",
                    "Raspberry"]))

ddlist.set_fix_width(150)
ddlist.set_draw_arrow(True)
ddlist.align(None, lv.ALIGN.IN_TOP_MID, 0, 20)
ddlist.set_event_cb(event_handler)