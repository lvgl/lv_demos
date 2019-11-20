welcome_info = "Welcome to the modal message box demo!\nPress the button to display a message box."
in_msg_info = "Notice that you cannot touch the button again while the message box is open."

# resolution of the screen
HOR_RES = lv.disp_get_hor_res(lv.disp_get_default())
VER_RES = lv.disp_get_ver_res(lv.disp_get_default())

# global mbox
mbox = None

def mbox_event_cb(obj, evt):
    if evt == lv.EVENT.DELETE and obj == mbox:
        # Delete the parent modal background
        mbox.get_parent().del_async()
        info.set_text(welcome_info)
    elif evt == lv.EVENT.VALUE_CHANGED:
        # A button was clicked
        mbox.start_auto_close(0)

def btn_event_cb(btn, evt):
    if evt == lv.EVENT.CLICKED:
        # Create a full-screen background
        modal_style = lv.style_t()
        lv.style_copy(modal_style, lv.style_plain_color)
        # Set the background's style
        modal_style.body.main_color = modal_style.body.grad_color = lv.color_make(0,0,0)
        modal_style.body.opa = lv.OPA._50
        
        # Create a base object for the modal background
        obj = lv.obj(lv.scr_act())
        obj.set_style(modal_style)
        obj.set_pos(0, 0)
        obj.set_size(HOR_RES, VER_RES)
        obj.set_opa_scale_enable(True)  # Enable opacity scaling for the animation

        btns2 = ["Ok", "Cancel", ""]

        # Create the message box as a child of the modal background
        global mbox
        mbox = lv.mbox(obj)
        mbox.add_btns(btns2)
        mbox.set_text("Hello world!")
        mbox.align(None, lv.ALIGN.CENTER, 0, 0)
        mbox.set_event_cb(mbox_event_cb)

        # Fade the message box in with an animation
        a = lv.anim_t()
        lv.anim_init(a)
        lv.anim_set_time(a, 500, 0)
        lv.anim_set_values(a, lv.OPA.TRANSP, lv.OPA.COVER)
        lv.anim_set_exec_cb(a, obj, lv.obj.set_opa_scale)
        lv.anim_create(a)

        info.set_text(in_msg_info)
        info.align(None, lv.ALIGN.IN_BOTTOM_LEFT, 5, -5)

# Create a button, then set its position and event callback
btn = lv.btn(lv.scr_act())
btn.set_size(200, 60)
btn.set_event_cb(btn_event_cb)
btn.align(None, lv.ALIGN.IN_TOP_LEFT, 20, 20)

# Create a label on the button
label = lv.label(btn)
label.set_text("Display a message box!")

# Create an informative label on the screen
info = lv.label(lv.scr_act())
info.set_text(welcome_info)
info.set_long_mode(lv.label.LONG.BREAK) # Make sure text will wrap
info.set_width(HOR_RES - 10)
info.align(None, lv.ALIGN.IN_BOTTOM_LEFT, 5, -5)
