using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor fLeftDrive;
extern motor fRightDrive;
extern motor bLeftDrive;
extern motor bRightDrive;
extern controller Controller1;
extern motor trashHandler;
extern motor conveyor;
extern motor lIntake;
extern motor rIntake;
extern inertial Accella;
extern optical eyes;
extern distance dist;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );