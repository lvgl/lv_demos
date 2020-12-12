import lvgl as lv
import sys
import os

def init_gui():
    lv.init()

    try:    
        osVersion=os.uname()
        print("Running: ",osVersion)
        try:
            # check if we are running on a t-watch
            import ttgo
            from axp_constants import AXP202_VBUS_VOL_ADC1,AXP202_VBUS_CUR_ADC1,AXP202_BATT_CUR_ADC1,AXP202_BATT_VOL_ADC1
        
            watch = ttgo.Watch()
            tft = watch.tft
            power = watch.pmu
            power.adc1Enable(AXP202_VBUS_VOL_ADC1
                             | AXP202_VBUS_CUR_ADC1 
                             | AXP202_BATT_CUR_ADC1
                             | AXP202_BATT_VOL_ADC1, True)
            watch.lvgl_begin()
            watch.tft.backlight_fade(100)
            print("Running on the LilyGo t-watch 2020")
        except:    
            try:
                # check if we are running onf an ili9431
                import lvesp32
                from ili9XXX import ili9341,COLOR_MODE_BGR,LANDSCAPE
                from xpt2046 import xpt2046
                import espidf as esp
                
                # Initialize ILI9341 display
                disp = ili9341(miso=19,mosi=23,clk=18, cs=26, dc=5, rst=-1, power=-1, backlight=-1, backlight_on=0, power_on=0,
                   spihost=esp.VSPI_HOST, mhz=40, factor=4, hybrid=True, width=320, height=240,
                   colormode=COLOR_MODE_BGR, rot=LANDSCAPE, invert=False, double_buffer=True, half_duplex=True)
                
                # Register xpt2046 touch driver
                touch = xpt2046(spihost=esp.VSPI_HOST,cal_x0=3799, cal_x1 = 353, cal_y0=220, cal_y1 = 3719, transpose=False)
                print("Running on the ili9341 module")
            except:
                print("Not running a supported lvgl enabled version of Micropython. Giving up...")
                sys.exit()

    except:        
        try:
            import SDL
            SDL.init(w=240,h=240)
            
            # Register SDL display driver.
            
            disp_buf1 = lv.disp_buf_t()
            buf1_1 = bytes(240 * 10)
            disp_buf1.init(buf1_1, None, len(buf1_1)//4)
            disp_drv = lv.disp_drv_t()
            disp_drv.init()
            disp_drv.buffer = disp_buf1
            disp_drv.flush_cb = SDL.monitor_flush
            disp_drv.hor_res = 240
            disp_drv.ver_res = 240
            disp_drv.register()
            
            # Register SDL mouse driver
            
            indev_drv = lv.indev_drv_t()
            indev_drv.init() 
            indev_drv.type = lv.INDEV_TYPE.POINTER
            indev_drv.read_cb = SDL.mouse_read
            indev_drv.register()
            print("Running the Unix version")
        except:
            print("Not running a supported lvgl enabled version of Micropython. Giving up...")
            sys.exit()
        
    # Create a screen and load it
    scr = lv.obj()
    lv.scr_load(scr)

init_gui()
