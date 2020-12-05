#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor fLeftDrive = motor(PORT1, ratio18_1, false);
motor fRightDrive = motor(PORT9, ratio18_1, true);
motor bLeftDrive = motor(PORT11, ratio18_1, false);
motor bRightDrive = motor(PORT20, ratio18_1, true);
controller Controller1 = controller(primary);
motor trashHandler = motor(PORT5, ratio6_1, true);
motor conveyor = motor(PORT4, ratio6_1, false);
motor lIntake = motor(PORT15, ratio18_1, false);
motor rIntake = motor(PORT16, ratio18_1, true);
/*vex-vision-config:begin*/
vision sight = vision (PORT17, 50);
/*vex-vision-config:end*/
inertial Accella = inertial(PORT18);
optical eyes = optical(PORT12);

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