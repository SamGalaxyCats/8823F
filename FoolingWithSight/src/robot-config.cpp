#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature Sight__RED_THING = signature (1, 9321, 10221, 9771, -1639, -973, -1306, 2.5, 0);
signature Sight__BLUE_THING = signature (2, -4657, -2923, -3790, 7281, 12801, 10041, 2.1, 0);
vision Sight = vision (PORT3, 50, Sight__RED_THING, Sight__BLUE_THING);
/*vex-vision-config:end*/
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