using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor bLeftDrive;
extern motor bRightDrive;
extern motor fLeftDrive;
extern motor fRightDrive;
extern motor lIntake;
extern motor rIntake;
extern motor conveyor;
extern motor trashHandler;
extern optical eyes;
extern distance dist;
extern limit clickL;
extern inertial accella;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );