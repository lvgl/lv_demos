def event_handler(obj, event):
    if event == lv.EVENT.CLICKED:
        date = obj.get_pressed_date()
        if date is not None:
            obj.set_today_date(date)

calendar = lv.calendar(lv.scr_act())
calendar.set_size(230, 230)
calendar.align(None, lv.ALIGN.CENTER, 0, 0)
calendar.set_event_cb(event_handler)

# Set the today
today = lv.calendar_date_t()
today.year = 2018
today.month = 10
today.day = 23

calendar.set_today_date(today)
calendar.set_showed_date(today)

# Highlight some days
highlihted_days = [lv.calendar_date_t() for i in range(3)]
highlihted_days[0].year = 2018
highlihted_days[0].month = 10
highlihted_days[0].day = 6

highlihted_days[1].year = 2018
highlihted_days[1].month = 10
highlihted_days[1].day = 11

highlihted_days[2].year = 2018
highlihted_days[2].month = 11
highlihted_days[2].day = 22

calendar.set_highlighted_dates(highlihted_days, len(highlihted_days))