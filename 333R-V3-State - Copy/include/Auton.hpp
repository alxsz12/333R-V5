#pragma once
#include "main.h"

class Auton
{
public:
 enum class Autons
 {
    none, 
    Test,
    SAWP,
    HSWP, 
    PROG,
    PROGS,
 } static auton;

 enum class Sides
 {
    Right,
    Left
 } static side;

 enum class Colors
  {
    Red,
    Blue
  } static color,
      opponent; // selected color and opposite color
      
  static void readSettings(); // read the sd card to set the settings
  static void suspendAsyncTask();

  static void runAuton(); // runs the selected auton

  static bool cEn;
  static void cEnable();

private:
  static void startAsyncTaskWithSettings(std::function<bool()> iasyncCondition, std::function<void()> iasyncAction);
  static void async_task_func(void *); // async task function
  static std::function<bool()> masyncCondition;
  static std::function<void()> masyncAction;
  static pros::Task masync_task;

  static void startTaskAfterDelay(QTime idelay, std::function<void()> iaction);
  static void delay_task_func(void *); // task to execute an action after some time
  static std::function<void()> mdelayAction;
  static Timer mtimer;
  static QTime mstartTime;
  static QTime mdelayTime;
  static pros::Task mdelay_task;
};