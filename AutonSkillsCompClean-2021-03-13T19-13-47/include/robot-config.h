using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor bLeftDrive;
extern motor bRightDrive;
extern motor fLeftDrive;
extern motor fRightDrive;
extern motor lIntake;
extern motor rIntake;
extern motor conveyL;
extern motor conveyR;
extern distance dist;
extern inertial accella;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );