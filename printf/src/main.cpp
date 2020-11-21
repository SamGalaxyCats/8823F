/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\abowsher                                         */
/*    Created:      Sat Nov 14 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  double dub = 1.15151515;
  int num = 5;
  bool yes = true;
  printf("Sample double: %0.2f\nSample int: %d\nSample boolean: %d", dub, num, yes);  
}
