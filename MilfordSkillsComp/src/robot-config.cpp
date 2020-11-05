#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor bRightDrive = motor(PORT1, ratio18_1, true);
motor bLeftDrive = motor(PORT2, ratio18_1, false);
motor fRightDrive = motor(PORT10, ratio18_1, true);
motor fLeftDrive = motor(PORT11, ratio18_1, false);
motor rIntake = motor(PORT3, ratio18_1, true);
motor lIntake = motor(PORT9, ratio18_1, false);
motor trashHandler = motor(PORT4, ratio18_1, false);
motor conveyor = motor(PORT8, ratio18_1, false);
/*vex-vision-config:begin*/
vision sight = vision (PORT17, 50);
/*vex-vision-config:end*/
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