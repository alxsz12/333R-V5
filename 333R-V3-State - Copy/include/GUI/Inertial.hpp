/**
 * odomDebug.hpp
 *
 * The contents of this file were not written by any members of 333R*.
 *
 *    * slight modifications were made to make it work with the display
 */
#pragma once
#include "main.h"

class InertialDebug
{
  private:
    // parent container
    lv_obj_t * container = nullptr;
    lv_style_t cStyle;

    // status label
    lv_obj_t * statusLabel = nullptr;
    lv_style_t textStyle;

    // reset button styles
    lv_style_t resetRel;
    lv_style_t resetPr;

    static lv_res_t resetAction(lv_obj_t *); // action when reset button is pressed
};