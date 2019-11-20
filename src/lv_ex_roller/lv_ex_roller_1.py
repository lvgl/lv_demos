def event_handler(obj, event):
    if event == lv.EVENT.VALUE_CHANGED:
        idx = obj.get_selected()
        option = obj.get_options().split("\n")[idx]
        print("Selected month: %s" % option);

roller1 = lv.roller(lv.scr_act())
roller1.set_options("\n".join([
                    "January",
                    "February",
                    "March",
                    "April",
                    "May",
                    "June",
                    "July",
                    "August",
                    "September",
                    "October",
                    "November",
                    "December"]), lv.roller.MODE.INIFINITE)

roller1.set_visible_row_count(4)
roller1.align(None, lv.ALIGN.CENTER, 0, 0)
roller1.set_event_cb(event_handler)