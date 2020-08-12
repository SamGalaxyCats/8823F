#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor fLeftDrive = motor(PORT1, ratio18_1, false);
motor fRightDrive = motor(PORT10, ratio18_1, true);
motor bLeftDrive = motor(PORT11, ratio18_1, false);
motor bRightDrive = motor(PORT20, ratio18_1, false);
controller Controller1 = controller(primary);
motor lift = motor(PORT5, ratio18_1, false);
motor rampIntake = motor(PORT4, ratio18_1, false);
motor bLinkake = motor(PORT15, ratio18_1, false);
motor bRinkake = motor(PORT16, ratio18_1, true);

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