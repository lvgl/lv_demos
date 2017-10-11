/**
 * @file lv_test_label.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_test_label.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a default object and test the basic functions
 */
void lv_test_label_1(void)
{
    /* Default object
     * GOAL: A label with "Text" text*/
    lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);

    /* Set label text
     * GOAL: A label with "I'm testing\nthe labels" */
    lv_obj_t * label2 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label2, "I'm testing\nthe labels");
    lv_obj_align_us(label2, label1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);

    /* Set a static array as text and modify letter is it later
     * GOAL: label with "STATic text" text*/
    static char label_static_text[] =  {"static text"};
    lv_obj_t * label3 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_static(label3, label_static_text);
    lv_obj_align_us(label3, label2, LV_ALIGN_OUT_RIGHT_TOP, 20, 0);
    label_static_text[0] = 'S';         /*Randomly modify letters*/
    label_static_text[1] = 'T';
    label_static_text[2] = 'A';
    label_static_text[3] = 'T';
    lv_label_set_text(label3, NULL);    /*Refresh after modification*/

    /* Set text from array
     * GOAL:*/
    char array_text[3]; /*Not static to see the text will remain after this variable is destroyed*/
    array_text[0] = 'a';
    array_text[1] = 'b';
    array_text[2] = 'c';    /*Not need to be '\0' terminated*/
    lv_obj_t * label4 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_array(label4, array_text, sizeof(array_text));
    lv_obj_align_us(label4, label3, LV_ALIGN_OUT_RIGHT_TOP, 20, 0);

    /* Test copying and styling dynamic label
     * GOAL: Same as 'label2' but with background */
    lv_obj_t * label5 = lv_label_create(lv_scr_act(), label2);
    lv_obj_set_style(label5, lv_style_get(LV_STYLE_PRETTY_COLOR, NULL));
    lv_obj_align_us(label5, label2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);

    /* Test copying and styling static label
     * GOAL: Same as 'label3' but with background */
    lv_obj_t * label6 = lv_label_create(lv_scr_act(), label3);
    lv_obj_set_style(label6, lv_style_get(LV_STYLE_PRETTY_COLOR, NULL));
    lv_obj_align_us(label6, label3, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);

    /* Test copying and styling array label
     * GOAL: Same as 'label4' but with background */
    lv_obj_t * label7 = lv_label_create(lv_scr_act(), label4);
    lv_obj_set_style(label7, lv_style_get(LV_STYLE_PRETTY_COLOR, NULL));
    lv_obj_align_us(label7, label4, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);
}

/**
 * Test long modes
 */
void lv_test_label_2(void)
{
    /* LV_LABEL_LONG_EXPAND (default)
     * GOAL: A label with a long line*/
    lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_style(label1, lv_style_get(LV_STYLE_PLAIN_COLOR, NULL));    /*Set a background to clearly see the label size*/
    lv_label_set_text(label1, "This is a very long line which is not broken.");
    lv_label_set_long_mode(label1, LV_LABEL_LONG_EXPAND);

    /* LV_LABEL_LONG_BERAK (set width and test line break)
     * GOAL: the words are wrapped into multiple lines */
    lv_obj_t * label2 = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_style(label2, lv_style_get(LV_STYLE_PLAIN_COLOR, NULL));
    lv_label_set_text(label2, "This is a long line and a VeryVeryLongWordToWrap.\n"
                              "A new line and a lot of spaces:                        . Can you see them?");
    lv_label_set_long_mode(label2, LV_LABEL_LONG_BREAK);
    lv_obj_align_us(label2, label1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);
    lv_obj_set_width_us(label2, 100);

    /* LV_LABEL_LONG_ROLL (set size and test rolling)
     * GOAL: the text is rolled in both directions*/
    lv_obj_t * label3 = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_style(label3, lv_style_get(LV_STYLE_PLAIN_COLOR, NULL));
    lv_label_set_text(label3, "This is a text to roll\nin both\ndirections:\nhorizontally and vertically");
    lv_label_set_long_mode(label3, LV_LABEL_LONG_ROLL);
    lv_obj_align_us(label3, label2, LV_ALIGN_OUT_RIGHT_TOP, 20, 0);
    lv_obj_set_size_us(label3, 100, 50);

    /* LV_LABEL_LONG_SCROLL (create a parent and label on it)
     * GOAL: the text is scrolled in both directions */
    lv_obj_t * bg1 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_style(bg1, lv_style_get(LV_STYLE_PRETTY, NULL));
    lv_obj_align_us(bg1, label3, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);

    lv_obj_t * label4 = lv_label_create(bg1, NULL);
    lv_obj_set_style(label4, lv_style_get(LV_STYLE_PLAIN_COLOR, NULL));
    lv_label_set_text(label4, "This is a text to roll\nin both\ndirections:\nhorizontally and vertically");
    lv_label_set_long_mode(label4, LV_LABEL_LONG_SCROLL);

}

/**
 * Test mixed features
 */
void lv_test_label_3(void)
{
    /* Create a label with '\r', '\n', '\r\n' and '\n\r' line breaks
     * GOAL: The text in 5 lines without empty lines*/
    lv_obj_t * label1 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label1, "Line1\n"
                              "Line2\r"
                              "Line3\r\n"
                              "Line4\n\r"
                              "Line5");


    /* Activate the no break feature
     * GOAL: same as 'label1' but in one line*/
    lv_obj_t * label2 = lv_label_create(lv_scr_act(), label1);
    lv_label_set_no_break(label2, true);
    lv_obj_align_us(label2, label1, LV_ALIGN_OUT_RIGHT_TOP, 20, 0);

    /* Test recoloring
     * GOAL: the word "red" is red*/
    lv_obj_t * label3 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label3, "This is a #ff0000 red# word");
    lv_label_set_recolor(label3, true);
    lv_obj_align_us(label3, label1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);

#if TXT_UTF8 != 0

    /* Test UTF-8 support with LV_LABEL_LONG_BREAK, new lines and recolor
     * GOAL: the word "red" is red*/
    lv_obj_t * label4 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label4, "Normal ASCII\n"
                              "UTF-8 letters:áÁééőŐöÖúÚűŰ\n"
                              "Recolor UTF-8: #ff0000 öŐ##00ff00 üŰ##0000ff éÉ#");
    lv_label_set_recolor(label4, true);
    lv_label_set_long_mode(label4, LV_LABEL_LONG_BREAK);
    lv_obj_set_width_us(label4, 100);
    lv_obj_align_us(label4, label3, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);

#endif

}


/**********************
 *   STATIC FUNCTIONS
 **********************/
