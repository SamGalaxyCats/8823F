using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor fLeftDrive;
extern motor fRightDrive;
extern motor bLeftDrive;
extern motor bRightDrive;
extern controller Controller1;
extern motor lift;
extern motor rampIntake;
extern motor bLinkake;
extern motor bRinkake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );