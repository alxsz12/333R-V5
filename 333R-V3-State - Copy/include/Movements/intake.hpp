#pragma once
#include "main.h"

class Intake
{
public:
  enum class COLO        // enumeration to organize possible states
  {
    Red,
    Blue
  };
    static void RollerColor();
    static void SkillsColor();
    static void Blue();
    static void Red();
};

namespace def
{
    extern Intake intake;
}