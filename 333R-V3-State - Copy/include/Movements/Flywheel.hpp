#pragma once
#include "main.h"

class Flywheel
{
public:

// enum class Volts
// {
//     Twelve,
//     HTwelve,
//     Eleven,
//     HEleven,
//     Ten,
// } static vt; //vt;

static void flyTest();

static void AShoot(int s, bool wait);
};

namespace def
{
extern Flywheel flywheel;  
}