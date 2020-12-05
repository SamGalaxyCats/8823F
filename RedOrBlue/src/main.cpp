/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\abowsher                                         */
/*    Created:      Sat Nov 14 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// eyes                 optical       9               
// TrashHandler         motor         1               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

bool lightIsOn;
bool isRunningLight;

void lightThing()
{
  isRunningLight = true;
  eyes.setLightPower(1, percent);
  eyes.setLight(ledState::on);
  lightIsOn = true;
  vex::task::sleep(1000);
  eyes.setLight(ledState::off);
  lightIsOn = false;
  vex::task::sleep(1500);
  isRunningLight = false;
}

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  printf("\n");
  int redLimit = 50;
  int blueLimit = 200;
  //double colorFound = 0;
  while(1)
  {
    /*if(!isRunningLight)
    {
      eyes.objectDetected(lightThing);
      colorFound = eyes.color();
    }*/
    Brain.Screen.setCursor(2,1);
    Brain.Screen.print(eyes.hue());
    if(eyes.hue() < redLimit)
    {
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("This object is ");
      Brain.Screen.setPenColor(eyes.color());
      Brain.Screen.print("red ");
      Brain.Screen.setPenColor(white);
    }
    else if(eyes.hue() < blueLimit)
    {
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("This object is ");
      Brain.Screen.setPenColor(eyes.color());
      Brain.Screen.print("blue");
      Brain.Screen.setPenColor(white);
    }
    else
    {
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("There is no object.");
    }
    vex::task::sleep(25);
  }  
}
