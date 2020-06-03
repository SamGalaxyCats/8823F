using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor leftDrive;
extern motor rightDrive;
extern inertial accella;
extern encoder rightEncoder;
extern encoder leftEncoder;
extern signature sight__RED_BOX;
extern signature sight__BUTTER;
extern signature sight__SIG_3;
extern signature sight__SIG_4;
extern signature sight__SIG_5;
extern signature sight__SIG_6;
extern signature sight__SIG_7;
extern vision sight;
extern sonar ultrasonic;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );