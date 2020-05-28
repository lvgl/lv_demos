# Examples for LVGL

LVGL is a free and open-source graphics library providing everything you need to create a Graphical User Interface (GUI) on embedded systems with easy-to-use graphical elements, beautiful visual effects and low memory footprint.

GitHub: https://github.com/lvgl/lvgl
Website: https://lvgl.io

## Add the examples to your projects
1. Clone this repository: `git clone https://github.com/lvgl/lv_examples.git`.
2. The `lv_examples` directory should be next to the `lvgl` directory in your project.

Similary to `lv_conf.h` there is a configuration file for the examples too. It is called `lv_ex_conf.h`.
1. Copy `lv_examples/lv_ex_conf_templ.h` next to `lv_examples` directory
2. Rename is to `lv_ex_conf.h`
3. Change the first `#if 0` to `#if 1` to enable the file's content
4. Enable or Disable modules


## Contributing
For contribution and coding style guidelines, please refer to the file docs/CONTRIBUTNG.md in the main LVGL repo:
  https://github.com/lvgl/lvgl

