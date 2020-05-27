```eval_rst
:github_url: https://github.com/littlevgl/docs/blob/master/en/lv_examples/README.md
```
```eval_rst
:github_url: https://github.com/littlevgl/docs/blob/master/lv_examples/README.md
```
# Examples for Littlev Graphics Library

LittlevGL is a free and open-source graphics library providing everything you need to create a Graphical User Interface (GUI) on embedded systems with easy-to-use graphical elements, beautiful visual effects and low memory footprint.

GitHub: https://github.com/littlevgl/lvgl
Website: https://littlevgl.com

## Add the examples to your projects
1. Clone this repository: `git clone https://github.com/littlevgl/lv_examples.git` or download from the [Download page](https://littlevgl.com/download). To always use the newest version the cloning is recommended.
2. The `lv_examples` directory should be next to the `lvgl` directory in your project.

Similary to `lv_conf.h` there is a configuration file for the examples too. It is called `lv_ex_conf.h`.
1. Copy `lv_examples/lv_ex-conf_templ.h` next to `lv_examples` directory
2. Rename is to `lv_ex_conf.h`
3. Delete the first `#if` and  last `#endif` to enable the file's content
4. Enable or Disable modules

To find out more about each example, look at its specific README file.

## Contributing
For contribution and coding style guidelines, please refer to the file docs/CONTRIBUTNG.md in the main LittlevGL repo:
  https://github.com/littlevgl/lvgl
You are encouraged to use the 'astyle' util to format your code prior to pushing it. The files docs/astyle_(c/h) contain astyle rules to format source and header files according to the project coding guidelines.

