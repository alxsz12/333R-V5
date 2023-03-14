#include "display/lv_misc/lv_color.h"
#include "main.h"

lv_obj_t *DisplayControl::mtabview = lv_tabview_create(lv_scr_act(), NULL); // creates the tabview

//Inertial Tab
lv_obj_t *DisplayControl::mtabview_inertial = lv_tabview_add_tab(
    DisplayControl::mtabview,
    "Inertial"); // creates the tab on the screen that shows the calculated robot position
lv_obj_t *DisplayControl::mtabview_inertial_container =
    lv_obj_create(DisplayControl::mtabview_inertial, NULL);
lv_obj_t *DisplayControl::mtabview_inertial_btn = 
    lv_btn_create(mtabview_inertial_container, NULL);//creates the inertial reset button
//lv_obj_t *DisplayControl::mtabview_inertial_btn = 
  //  lv_btn_set_fit(mtabview_inertial_btn, 100, 40);
//lv_obj_t *DisplayControl::mtabview_inertial_btn = 
//    lv_btn_set_action(mtabview_inertial_btn, LV_BTN_ACTION_PR, resetAction);
lv_obj_t *DisplayControl::mtabview_inertial_label =
    lv_label_create(mtabview_inertial_container, NULL); 
lv_obj_t *DisplayControl::mtabview_inertial_label_2 =
    lv_label_create(mtabview_inertial_container, NULL); 
lv_obj_t *DisplayControl::mtabview_inertial_label_3 =
    lv_label_create(mtabview_inertial_container, NULL); 
lv_obj_t *DisplayControl::mtabview_inertial_label_4 =
    lv_label_create(mtabview_inertial_container, NULL);
lv_obj_t *DisplayControl::mtabview_inertial_label_5 =
    lv_label_create(mtabview_inertial_container, NULL);
lv_obj_t *DisplayControl::mtabview_inertial_label_6 =
    lv_label_create(mtabview_inertial_container, NULL); 
lv_obj_t *DisplayControl::mtabview_inertial_label_7 =
    lv_label_create(mtabview_inertial_container, NULL); 
lv_obj_t *DisplayControl::mtabview_inertial_label_8 =
    lv_label_create(mtabview_inertial_container, NULL); 
lv_obj_t *DisplayControl::mtabview_inertial_label_9 =
    lv_label_create(mtabview_inertial_container, NULL);
lv_obj_t *DisplayControl::mtabview_inertial_label_10 =
    lv_label_create(mtabview_inertial_container, NULL);
lv_obj_t *DisplayControl::mtabview_inertial_label_11 =
    lv_label_create(mtabview_inertial_container, NULL); 
lv_obj_t *DisplayControl::mtabview_inertial_label_12 =
    lv_label_create(mtabview_inertial_container, NULL); 
lv_obj_t *DisplayControl::mtabview_inertial_label_13 =
    lv_label_create(mtabview_inertial_container, NULL);
lv_obj_t *DisplayControl::mtabview_inertial_label_14 =
    lv_label_create(mtabview_inertial_container, NULL);
lv_obj_t *DisplayControl::mtabview_inertial_label_15 =
    lv_label_create(mtabview_inertial_container, NULL);


lv_obj_t *DisplayControl::mtabview_auton = lv_tabview_add_tab(
    DisplayControl::mtabview, "Auton"); // creates the tab with the auton selection dropdown
lv_obj_t *DisplayControl::mtabview_auton_dropdown =
    lv_ddlist_create(mtabview_auton, NULL); // creates the auton selection dropdown
lv_obj_t *DisplayControl::mtabview_auton_dropdown_side =
    lv_ddlist_create(mtabview_auton, NULL); // creates the side selection dropdown
lv_obj_t *DisplayControl::mtabview_auton_dropdown_color =
    lv_ddlist_create(mtabview_auton, NULL); // creates the color selection dropdown
lv_res_t DisplayControl::tabview_auton_dropdowns_action(
    lv_obj_t *idropdown) // specifies the code to be executed when the auton dropdown is changed
{
    FILE *file;                    // creates an object that will be used to reference the file containing the
                                   // selected auton
    if (pros::usd::is_installed()) // makes sure the sd card is installed before trying to access
                                   // its contents
    {
        file = fopen("/usd/auton_settings.txt", "w"); // opens the auton settings file
        if (file)                                     // makes sure the file was accessed correctly
        {
            fprintf(file, "%i",
                    (lv_ddlist_get_selected(mtabview_auton_dropdown) 
                    * 100
                     + lv_ddlist_get_selected(mtabview_auton_dropdown_side) 
                     * 10 + lv_ddlist_get_selected(mtabview_auton_dropdown_color))); // update sd card based on new value
            std::cout << "set /usd/auton_settings.txt to "
                      << std::to_string(lv_ddlist_get_selected(mtabview_auton_dropdown) 
                      * 100 + lv_ddlist_get_selected(mtabview_auton_dropdown_side) 
                      * 10 + lv_ddlist_get_selected(mtabview_auton_dropdown_color))
                      << std::endl;
        }
        else
        {
            std::cout
                << "/usd/auton_settings.txt is null"
                << std::endl; // output to the terminal if the sd card was not accessed correctly
        }
        fclose(file);
        // Auton::readSettings(); // update auton based on new sd card values
    }

    return LV_RES_OK; // required for dropdown callback
}

//---------------------------------------------Graph Setup
lv_obj_t *DisplayControl::mtabview_graph = lv_tabview_add_tab(
    DisplayControl::mtabview, "Graph"); // creates the tab with the graph for debugging
lv_obj_t *DisplayControl::mtabview_graph_chart =
    lv_chart_create(DisplayControl::mtabview_graph, NULL); // create the graph

// create 8 series of different color, so it is easy to make a graph with any color
lv_chart_series_t *DisplayControl::mtabview_graph_chart_series_0 =
    lv_chart_add_series(DisplayControl::mtabview_graph_chart, LV_COLOR_RED);
lv_chart_series_t *DisplayControl::mtabview_graph_chart_series_1 =
    lv_chart_add_series(DisplayControl::mtabview_graph_chart, LV_COLOR_ORANGE);
lv_chart_series_t *DisplayControl::mtabview_graph_chart_series_2 =
    lv_chart_add_series(DisplayControl::mtabview_graph_chart, LV_COLOR_YELLOW);
lv_chart_series_t *DisplayControl::mtabview_graph_chart_series_3 =
    lv_chart_add_series(DisplayControl::mtabview_graph_chart, LV_COLOR_GREEN);
lv_chart_series_t *DisplayControl::mtabview_graph_chart_series_4 =
    lv_chart_add_series(DisplayControl::mtabview_graph_chart, LV_COLOR_BLUE);
lv_chart_series_t *DisplayControl::mtabview_graph_chart_series_5 =
    lv_chart_add_series(DisplayControl::mtabview_graph_chart, LV_COLOR_PURPLE);
lv_chart_series_t *DisplayControl::mtabview_graph_chart_series_6 =
    lv_chart_add_series(DisplayControl::mtabview_graph_chart, LV_COLOR_MAGENTA);
lv_chart_series_t *DisplayControl::mtabview_graph_chart_series_7 =
    lv_chart_add_series(DisplayControl::mtabview_graph_chart, LV_COLOR_CYAN);
//Styles

lv_style_t DisplayControl::mstyle_tabview_indic;
lv_style_t DisplayControl::mstyle_tabview_btn;
lv_style_t DisplayControl::mstyle_tabview_btn_tgl;
lv_style_t DisplayControl::mstyle_tabview_btn_pr;
lv_style_t DisplayControl::mstyle_tabview_container;
lv_style_t DisplayControl::mstyle_text;

lv_obj_t *DisplayControl::mtabview_misc =
    lv_tabview_add_tab(DisplayControl::mtabview, "Misc"); // creates the miscelaneus debugging tab
lv_obj_t *DisplayControl::mtabview_misc_container =
    lv_obj_create(DisplayControl::mtabview_misc, NULL);
lv_obj_t *DisplayControl::mtabview_misc_label =
    lv_label_create(mtabview_misc_container, NULL); // creates the left text box
lv_obj_t *DisplayControl::mtabview_misc_label_2 =
    lv_label_create(mtabview_misc_container, NULL); // creates the right text bo
lv_obj_t *DisplayControl::mtabview_misc_label_3 =
    lv_label_create(mtabview_misc_container, NULL); // creates the right text bo
lv_obj_t *DisplayControl::mtabview_misc_label_4 =
    lv_label_create(mtabview_misc_container, NULL); // creates the right text bo
lv_obj_t *DisplayControl::mtabview_misc_label_5 =
    lv_label_create(mtabview_misc_container, NULL);
lv_obj_t *DisplayControl::mtabview_misc_label_6 =
    lv_label_create(mtabview_misc_container, NULL);

DisplayControl::DisplayControl()
{
    /* ----------------------- Style Setup ----------------------- /
     * Specifies what each style should look like when they are used.
     */
    lv_style_copy(&mstyle_tabview_indic, &lv_style_plain);
    mstyle_tabview_indic.body.padding.inner = 5;

    lv_style_copy(&mstyle_tabview_btn, &lv_style_plain);
    mstyle_tabview_btn.body.main_color = LV_COLOR_PURPLE;
    mstyle_tabview_btn.body.grad_color = LV_COLOR_PURPLE;
    mstyle_tabview_btn.text.color = LV_COLOR_WHITE;
    mstyle_tabview_btn.body.border.part = LV_BORDER_BOTTOM;
    mstyle_tabview_btn.body.border.color = LV_COLOR_WHITE;
    mstyle_tabview_btn.body.border.width = 1;
    mstyle_tabview_btn.body.padding.ver = 4;

    lv_style_copy(&mstyle_tabview_btn_tgl, &mstyle_tabview_btn);
    mstyle_tabview_btn_tgl.body.border.part = LV_BORDER_FULL;
    mstyle_tabview_btn_tgl.body.border.width = 2;

    lv_style_copy(&mstyle_tabview_btn_pr, &lv_style_plain);
    mstyle_tabview_btn_pr.body.main_color = LV_COLOR_WHITE;
    mstyle_tabview_btn_pr.body.grad_color = LV_COLOR_WHITE;
    mstyle_tabview_btn_pr.text.color = LV_COLOR_WHITE;

    lv_style_copy(&mstyle_tabview_container, &lv_style_plain_color);
    if(def::mtr_it.getTemperature() >= 50 )
    {
        mstyle_tabview_container.body.main_color = LV_COLOR_RED;
        mstyle_tabview_container.body.grad_color = LV_COLOR_RED;
    }
    else
    {
        mstyle_tabview_container.body.main_color = LV_COLOR_PURPLE;
        mstyle_tabview_container.body.grad_color = LV_COLOR_PURPLE;
    }
    mstyle_tabview_container.body.border.width = 0;
    mstyle_tabview_container.body.radius = 0;
    mstyle_tabview_container.body.padding.inner = 0;
    mstyle_tabview_container.body.padding.hor = 0;
    mstyle_tabview_container.body.padding.ver = 0;

    lv_style_copy(&mstyle_text, &lv_style_plain);
    mstyle_text.text.color = LV_COLOR_WHITE;
    mstyle_text.text.opa = LV_OPA_100;

    lv_tabview_set_style(mtabview, LV_TABVIEW_STYLE_INDIC,
                         &mstyle_tabview_indic); // set tabview styles
    lv_tabview_set_style(mtabview, LV_TABVIEW_STYLE_BTN_REL, &mstyle_tabview_btn);
    lv_tabview_set_style(mtabview, LV_TABVIEW_STYLE_BTN_PR, &mstyle_tabview_btn_pr);
    lv_tabview_set_style(mtabview, LV_TABVIEW_STYLE_BTN_TGL_REL, &mstyle_tabview_btn_tgl);
    lv_tabview_set_style(mtabview, LV_TABVIEW_STYLE_BTN_TGL_PR, &mstyle_tabview_btn_pr);

//Inertial tab
    lv_page_set_sb_mode(mtabview_inertial, LV_SB_MODE_OFF); // hide scrollbar

    lv_obj_set_style(mtabview_inertial, &mstyle_tabview_container); // set styles
    lv_obj_set_style(mtabview_inertial_container, &mstyle_tabview_container);
    lv_obj_set_size(mtabview_inertial_container, lv_obj_get_width(mtabview_inertial),
                    lv_obj_get_height(mtabview_inertial)); // set up the background
    lv_obj_align(mtabview_inertial_container, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style(mtabview_inertial_label, &mstyle_text); // set up text boxes (labels)
    lv_obj_set_style(mtabview_inertial_label_2, &mstyle_text);
    
    //lv_btn_set_style
    lv_obj_align(mtabview_inertial_btn, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 75);
    lv_btn_set_style(mtabview_inertial_btn, LV_TABVIEW_STYLE_INDIC, &mstyle_tabview_indic); // set tabview styles
    lv_btn_set_style(mtabview_inertial_btn, LV_TABVIEW_STYLE_BTN_REL, &mstyle_tabview_btn);
    lv_btn_set_style(mtabview_inertial_btn, LV_TABVIEW_STYLE_BTN_PR, &mstyle_tabview_btn_pr);
    lv_btn_set_style(mtabview_inertial_btn, LV_TABVIEW_STYLE_BTN_TGL_REL, &mstyle_tabview_btn_tgl);
    lv_btn_set_style(mtabview_inertial_btn, LV_TABVIEW_STYLE_BTN_TGL_PR, &mstyle_tabview_btn_pr);
    
    lv_obj_align(mtabview_inertial_label, mtabview_inertial_container, LV_ALIGN_IN_TOP_LEFT, 0, 0); // align labels //1
    lv_obj_align(mtabview_inertial_label_2, mtabview_inertial_container, LV_ALIGN_IN_TOP_LEFT, 0, 25);//1
    lv_obj_align(mtabview_inertial_label_3, mtabview_inertial_container, LV_ALIGN_IN_TOP_LEFT, 0, 50);//1
    lv_obj_align(mtabview_inertial_label_4, mtabview_inertial_container, LV_ALIGN_IN_TOP_LEFT, 0, 75); //2
    lv_obj_align(mtabview_inertial_label_5, mtabview_inertial_container, LV_ALIGN_IN_TOP_LEFT, 0, 100);//2
    lv_obj_align(mtabview_inertial_label_6, mtabview_inertial_container, LV_ALIGN_IN_TOP_LEFT, 0, 125);//2
    lv_obj_align(mtabview_inertial_label_7, mtabview_inertial_container, LV_ALIGN_IN_TOP_LEFT, 0, 150);//3
    lv_obj_align(mtabview_inertial_label_8, mtabview_inertial_container, LV_ALIGN_IN_TOP_LEFT, 0, 175);//3
    lv_obj_align(mtabview_inertial_label_9, mtabview_inertial_container, LV_ALIGN_IN_TOP_LEFT, 0, 200);//3
    lv_obj_align(mtabview_inertial_label_10, mtabview_inertial_container, LV_ALIGN_IN_TOP_MID, 0, 0);//4
    lv_obj_align(mtabview_inertial_label_11, mtabview_inertial_container, LV_ALIGN_IN_TOP_MID, 0, 25);//4
    lv_obj_align(mtabview_inertial_label_12, mtabview_inertial_container, LV_ALIGN_IN_TOP_MID, 0, 50);//4
    lv_obj_align(mtabview_inertial_label_13, mtabview_inertial_container, LV_ALIGN_IN_TOP_MID, 0, 75);//5
    lv_obj_align(mtabview_inertial_label_14, mtabview_inertial_container, LV_ALIGN_IN_TOP_MID, 0, 100);//5
    lv_obj_align(mtabview_inertial_label_15, mtabview_inertial_container, LV_ALIGN_IN_TOP_MID, 0, 125);//5

    lv_label_set_text(mtabview_inertial_label, "1No data provided."); // set default text for labels
    lv_label_set_text(mtabview_inertial_label_2, "2No data provided."); // To be no data provided
    lv_label_set_text(mtabview_inertial_label_3, "3No data provided."); // set default text for labels
    lv_label_set_text(mtabview_inertial_label_4, "4No data provided."); 
    lv_label_set_text(mtabview_inertial_label_5, "5No data provided.");
    /* ------------------------ Auton Tab ------------------------  /
     * When making autons, you must add the text this dropdown, a new
     * enum value in Auton.hpp, and a new case in the switch in Auton.cpp.
     */
    lv_ddlist_set_options(mtabview_auton_dropdown, "None\n"
                                                    "Test\n"
                                                    "SAWP\n"
                                                    "HSWP\n"
                                                    "PROG\n"
                                                    "PROGS\n"
                                                   ); // auton types in selection dropdown
    lv_ddlist_set_options(mtabview_auton_dropdown_side, "Right\n"
                                                        "Left\n"); // color selector
    lv_ddlist_set_options(mtabview_auton_dropdown_color, "Red\n"
                                                         "Blue\n"); // color selector

    lv_ddlist_set_action(mtabview_auton_dropdown,
                         tabview_auton_dropdowns_action); // set the dropdown callback to
                                                          // tabview_auton_dropdown_action()
    lv_ddlist_set_action(mtabview_auton_dropdown_side, tabview_auton_dropdowns_action);
    lv_ddlist_set_action(mtabview_auton_dropdown_color, tabview_auton_dropdowns_action);

    lv_obj_align(mtabview_auton_dropdown_color, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
    lv_obj_align(mtabview_auton_dropdown_side, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_align(mtabview_auton_dropdown, NULL, LV_ALIGN_IN_TOP_LEFT, 0,
                 0); // align the dropdown in the top left
    lv_ddlist_set_fix_height(mtabview_auton_dropdown, 200);

    lv_obj_set_style(mtabview_auton, &mstyle_tabview_container); // set styles

    /* ------------------------ Graph Tab ------------------------ */
    lv_obj_set_style(mtabview_graph, &mstyle_tabview_container); // set styles
    lv_obj_set_style(mtabview_graph_chart, &mstyle_tabview_btn_pr);

    lv_page_set_sb_mode(mtabview_graph, LV_SB_MODE_OFF); // hide scrollbar

    lv_chart_set_type(mtabview_graph_chart, LV_CHART_TYPE_LINE); // make chart graph lines
    lv_chart_set_point_count(mtabview_graph_chart,
                             lv_obj_get_width(mtabview_graph_chart) * 2); // set number of points
    lv_chart_set_div_line_count(mtabview_graph_chart, 9, 5);              // set the number of chart lines
    lv_obj_set_size(mtabview_graph_chart, lv_obj_get_width(mtabview_graph),
                    lv_obj_get_height(mtabview_graph));                // set the graph to fill the screen
    lv_obj_align(mtabview_graph_chart, NULL, LV_ALIGN_CENTER, 0, -10); // center chart


    /* ------------------------- Misc Tab ------------------------ */
    lv_page_set_sb_mode(mtabview_misc, LV_SB_MODE_OFF); // hide scrollbar

    lv_obj_set_style(mtabview_misc, &mstyle_tabview_container); // set styles
    lv_obj_set_style(mtabview_misc_container, &mstyle_tabview_container);
    lv_obj_set_size(mtabview_misc_container, lv_obj_get_width(mtabview_misc),
                    lv_obj_get_height(mtabview_misc)); // set up the background
    lv_obj_align(mtabview_misc_container, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style(mtabview_misc_label, &mstyle_text); // set up text boxes (labels)
    lv_obj_set_style(mtabview_misc_label_2, &mstyle_text);

    lv_label_set_text(mtabview_misc_label, "No data provided."); // set default text for labels
    lv_label_set_text(mtabview_misc_label_2, "No data provided."); // To be no data provided
    lv_label_set_text(mtabview_misc_label_3, "No data provided."); // set default text for labels
    lv_label_set_text(mtabview_misc_label_4, "No data provided."); // To be no data provided
    lv_label_set_text(mtabview_misc_label_5, "No data provided."); // set default text for labels
    lv_label_set_text(mtabview_misc_label_6, "No data provided."); // To be no data provided


    lv_obj_align(mtabview_misc_label, mtabview_misc_container, LV_ALIGN_IN_TOP_LEFT, 0, 0); // align labels
    lv_obj_align(mtabview_misc_label_2, mtabview_misc_container, LV_ALIGN_IN_TOP_RIGHT, -70, 0);
    lv_obj_align(mtabview_misc_label_3, mtabview_misc_container, LV_ALIGN_IN_LEFT_MID, 0, 0);
    lv_obj_align(mtabview_misc_label_4, mtabview_misc_container, LV_ALIGN_IN_RIGHT_MID, -70, 0);
    lv_obj_align(mtabview_misc_label_5, mtabview_misc_container, LV_ALIGN_IN_TOP_LEFT, 0, 50);
    lv_obj_align(mtabview_misc_label_6, mtabview_misc_container, LV_ALIGN_IN_TOP_RIGHT, -70, 50);

}


void DisplayControl::setInertialData(int ilabel,
                                 std::string itext) // sets the information on the OdomDebug window to the new
                                   // calculated odom data
{
    if (ilabel == 1)
    {
        lv_label_set_text(mtabview_inertial_label, itext.c_str());
    }
    else if (ilabel == 2)
    {
        lv_label_set_text(mtabview_inertial_label_2, itext.c_str());
    }
    else if (ilabel == 3)
    {
        lv_label_set_text(mtabview_inertial_label_3, itext.c_str());
    }
    else if (ilabel == 4)
    {
        lv_label_set_text(mtabview_inertial_label_4, itext.c_str());
    }
    else if (ilabel == 5)
    {
        lv_label_set_text(mtabview_inertial_label_5, itext.c_str());
    }
    else if (ilabel == 6)
    {
        lv_label_set_text(mtabview_inertial_label_6, itext.c_str());
    }
    else if (ilabel == 7)
    {
        lv_label_set_text(mtabview_inertial_label_7, itext.c_str());
    }
    else if (ilabel == 8)
    {
        lv_label_set_text(mtabview_inertial_label_8, itext.c_str());
    }
    else if (ilabel == 9)
    {
        lv_label_set_text(mtabview_inertial_label_9, itext.c_str());
    }
    else if (ilabel == 10)
    {
        lv_label_set_text(mtabview_inertial_label_10, itext.c_str());
    }
    else if (ilabel == 11)
    {
        lv_label_set_text(mtabview_inertial_label_11, itext.c_str());
    }
    else if (ilabel == 12)
    {
        lv_label_set_text(mtabview_inertial_label_12, itext.c_str());
    }
    else if (ilabel == 13)
    {
        lv_label_set_text(mtabview_inertial_label_13, itext.c_str());
    }
    else if (ilabel == 14)
    {
        lv_label_set_text(mtabview_inertial_label_14, itext.c_str());
    }
    else if (ilabel == 15)
    {
        lv_label_set_text(mtabview_inertial_label_14, itext.c_str());
    }
}

void DisplayControl::setAutonDropMen() // update the auton dropdown to match the sd card
{
    lv_ddlist_set_selected(mtabview_auton_dropdown, (int)Auton::auton);
    lv_ddlist_set_selected(mtabview_auton_dropdown_side, (int)Auton::side);
    lv_ddlist_set_selected(mtabview_auton_dropdown_color, (int)Auton::color);
}


void DisplayControl::setChartData(int iseries,
                                  double ivalue) // inputs new values to a specific chart series
{
    switch (iseries) // updates the correct series with the new value
    {
    case 0:
        lv_chart_set_next(mtabview_graph_chart, mtabview_graph_chart_series_0, ivalue);
        break;
    case 1:
        lv_chart_set_next(mtabview_graph_chart, mtabview_graph_chart_series_1, ivalue);
        break;
    case 2:
        lv_chart_set_next(mtabview_graph_chart, mtabview_graph_chart_series_2, ivalue);
        break;
    case 3:
        lv_chart_set_next(mtabview_graph_chart, mtabview_graph_chart_series_3, ivalue);
        break;
    case 4:
        lv_chart_set_next(mtabview_graph_chart, mtabview_graph_chart_series_4, ivalue);
        break;
    case 5:
        lv_chart_set_next(mtabview_graph_chart, mtabview_graph_chart_series_5, ivalue);
        break;
    case 6:
        lv_chart_set_next(mtabview_graph_chart, mtabview_graph_chart_series_6, ivalue);
        break;
    case 7:
        lv_chart_set_next(mtabview_graph_chart, mtabview_graph_chart_series_7, ivalue);
        break;
    }
}

void DisplayControl::setMiscData(int ilabel,
                                 std::string itext) // set the text on text box (label) 1 or 2
{
    if (ilabel == 1)
    {
        lv_label_set_text(mtabview_misc_label, itext.c_str());
    }
    else if (ilabel == 2)
    {
        lv_label_set_text(mtabview_misc_label_2, itext.c_str());
    }
    else if (ilabel == 3)
    {
        lv_label_set_text(mtabview_misc_label_3, itext.c_str());
    }
    else if (ilabel == 4)
    {
        lv_label_set_text(mtabview_misc_label_4, itext.c_str());
    }
    else if (ilabel == 5)
    {
        lv_label_set_text(mtabview_misc_label_5, itext.c_str());
    }
    else if (ilabel == 6)
    {
        lv_label_set_text(mtabview_misc_label_6, itext.c_str());
    }
}