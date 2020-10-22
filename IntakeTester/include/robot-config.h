using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor lInkake;
extern motor rInkake;
extern bumper bump;
extern controller Controller1;
extern motor fLeftDrive;
extern motor fRightDrive;
extern motor bLeftDrive;
extern motor bRightDrive;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );