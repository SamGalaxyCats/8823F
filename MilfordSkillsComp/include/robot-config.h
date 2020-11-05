using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor bRightDrive;
extern motor bLeftDrive;
extern motor fRightDrive;
extern motor fLeftDrive;
extern motor rIntake;
extern motor lIntake;
extern motor trashHandler;
extern motor conveyor;
extern signature sight__RED_BALL;
extern signature sight__BLUE_BALL;
extern signature sight__SIG_3;
extern signature sight__SIG_4;
extern signature sight__SIG_5;
extern signature sight__SIG_6;
extern signature sight__SIG_7;
extern vision sight;
extern inertial accella;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );