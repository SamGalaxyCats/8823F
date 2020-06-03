#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftDrive = motor(PORT20, ratio18_1, false);
motor rightDrive = motor(PORT11, ratio18_1, true);
inertial accella = inertial(PORT6);
encoder rightEncoder = encoder(Brain.ThreeWirePort.C);
encoder leftEncoder = encoder(Brain.ThreeWirePort.G);
/*vex-vision-config:begin*/
signature sight__RED_BOX = signature (1, 5349, 6501, 5925, 2521, 3325, 2923, 1.3, 0);
signature sight__BUTTER = signature (2, 0, 0, 0, 0, 0, 0, 3, 0);
signature sight__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature sight__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature sight__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature sight__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature sight__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision sight = vision (PORT15, 23, sight__RED_BOX, sight__BUTTER, sight__SIG_3, sight__SIG_4, sight__SIG_5, sight__SIG_6, sight__SIG_7);
/*vex-vision-config:end*/
sonar ultrasonic = sonar(Brain.ThreeWirePort.E);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}