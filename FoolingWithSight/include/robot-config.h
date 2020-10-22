using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern signature Sight__RED_THING;
extern signature Sight__BLUE_THING;
extern signature Sight__SIG_3;
extern signature Sight__SIG_4;
extern signature Sight__SIG_5;
extern signature Sight__SIG_6;
extern signature Sight__SIG_7;
extern vision Sight;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );