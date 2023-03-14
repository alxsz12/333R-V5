#pragma once
#include "main.h"

class FlywheelStateMachine 
{

public:
    enum class MStates        // enumeration to organize possible states
    {
      off,
      shoot,
      Twelve,
      Eleven,
      ElevenH,
      Ten,
    };
    static MStates getState();
    static void setState(MStates istate);

    static void enableControl();
    static void disableControl();

    static void controlState(); // update the state based on controller input

    static void speedu();

    static void update();       // move the flywheel based on the state
    static void run();    

private:    
    static Motor &mmtr;

    static MStates mstate;
    static bool mcontrolEnabled;
    
    static ControllerButton &mbtnShoot;   
    static ControllerButton &mbtnUp;    
    static ControllerButton &mbtnDown;    
};
