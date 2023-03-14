#pragma once
#include "main.h"

class DisplayControl
{
  static lv_obj_t *mtabview; // contains the whole tabview

  static lv_obj_t *mtabview_inertial; // tabview page with odom debugger
  static lv_obj_t *mtabview_inertial_container; // container on the misc page to hold elements
  static lv_obj_t *mtabview_inertial_btn;
  static lv_obj_t *mtabview_inertial_label;     // text box on misc page
  static lv_obj_t *mtabview_inertial_label_2;   // second text box on misc page
  static lv_obj_t *mtabview_inertial_label_3;     // text box on misc page
  static lv_obj_t *mtabview_inertial_label_4;   // second text box on misc page
  static lv_obj_t *mtabview_inertial_label_5;   // second text box on misc page
  static lv_obj_t *mtabview_inertial_label_6;     // text box on misc page
  static lv_obj_t *mtabview_inertial_label_7;   // second text box on misc page
  static lv_obj_t *mtabview_inertial_label_8;     // text box on misc page
  static lv_obj_t *mtabview_inertial_label_9;   // second text box on misc page
  static lv_obj_t *mtabview_inertial_label_10;   // second text box on misc pagestatic lv_obj_t *mtabview_inertial_label;     // text box on misc page
  static lv_obj_t *mtabview_inertial_label_11;   // second text box on misc page
  static lv_obj_t *mtabview_inertial_label_12;     // text box on misc page
  static lv_obj_t *mtabview_inertial_label_13;   // second text box on misc page
  static lv_obj_t *mtabview_inertial_label_14;   // second text box on misc page
  static lv_obj_t *mtabview_inertial_label_15;   // second text box on misc page
  static lv_style_t resetRel;
  static lv_style_t resetPr;
  static lv_res_t resetAction(lv_obj_t *itbn); // action when reset button is pressed

  static lv_obj_t *mtabview_auton;                                     // tab for setting auton
  static lv_obj_t *mtabview_auton_dropdown;                            // autons to choose from
  static lv_obj_t *mtabview_auton_dropdown_side;                       // right or left selector
  static lv_obj_t *mtabview_auton_dropdown_color;                      // blue or red selector
  static lv_res_t tabview_auton_dropdowns_action(lv_obj_t *idropdown); // event handler

  static lv_obj_t *mtabview_graph;                         // tabview page with graph
  static lv_obj_t *mtabview_graph_chart;                   // graph
  static lv_chart_series_t *mtabview_graph_chart_series_0; // chart series...
  static lv_chart_series_t *mtabview_graph_chart_series_1;
  static lv_chart_series_t *mtabview_graph_chart_series_2;
  static lv_chart_series_t *mtabview_graph_chart_series_3;
  static lv_chart_series_t *mtabview_graph_chart_series_4;
  static lv_chart_series_t *mtabview_graph_chart_series_5;
  static lv_chart_series_t *mtabview_graph_chart_series_6;
  static lv_chart_series_t *mtabview_graph_chart_series_7;

  static lv_obj_t *mtabview_misc;           // extra tabview page for anything
  static lv_obj_t *mtabview_misc_container; // container on the misc page to hold elements
  static lv_obj_t *mtabview_misc_label;     // text box on misc page
  static lv_obj_t *mtabview_misc_label_2;   // second text box on misc page
  static lv_obj_t *mtabview_misc_label_3;     // text box on misc page
  static lv_obj_t *mtabview_misc_label_4;   // second text box on misc page
  static lv_obj_t *mtabview_misc_label_5;     // text box on misc page
  static lv_obj_t *mtabview_misc_label_6;   // second text box on misc page

  static lv_style_t mstyle_tabview_indic;     // for page indicator line
  static lv_style_t mstyle_tabview_btn;       // for page header
  static lv_style_t mstyle_tabview_btn_tgl;   // for selected page header
  static lv_style_t mstyle_tabview_btn_pr;    // for pressed page header
  static lv_style_t mstyle_tabview_container; // for page background
  static lv_style_t mstyle_text;              // for text

  public:
    DisplayControl();

    void setInertialData(int ilabel,
                                 std::string itext);

    void setAutonDropMen(); // Sets the auton dropdown selector

    void setChartData(int iseries,
                    double ivalue); // sets the value of one of the series in the chart

    void setMiscData(int ilabel,
                   std::string itext); // sets the information displayed in the misc tab
};

namespace def
{
  extern DisplayControl
      display; // declares the display object as extern, to make sure it only gets constructed once
}