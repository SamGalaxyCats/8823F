#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor fLeftDrive = motor(PORT1, ratio18_1, false);
motor fRightDrive = motor(PORT9, ratio18_1, true);
motor bLeftDrive = motor(PORT11, ratio18_1, false);
motor bRightDrive = motor(PORT19, ratio18_1, true);
motor lIntake = motor(PORT15, ratio18_1, false);
motor rIntake = motor(PORT16, ratio18_1, true);
motor conveyor = motor(PORT3, ratio6_1, false);
motor trashHandler = motor(PORT5, ratio6_1, true);
optical eyes = optical(PORT12);
distance dist = distance(PORT6);
inertial accella = inertial(PORT18);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}