#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor bLeftDrive = motor(PORT11, ratio18_1, true);
motor bRightDrive = motor(PORT19, ratio18_1, false);
motor fLeftDrive = motor(PORT1, ratio18_1, true);
motor fRightDrive = motor(PORT9, ratio18_1, false);
motor lIntake = motor(PORT15, ratio6_1, false);
motor rIntake = motor(PORT14, ratio6_1, true);
motor conveyL = motor(PORT3, ratio6_1, false);
motor conveyR = motor(PORT5, ratio6_1, true);
distance dist = distance(PORT13);
inertial accella = inertial(PORT18);
controller Controller1 = controller(primary);

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