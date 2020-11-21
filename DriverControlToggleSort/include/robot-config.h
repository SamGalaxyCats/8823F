using namespace vex;

extern brain Brain;

using signature = vision::signature;

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
extern signature sight__BLUE_BALL;
extern signature sight__RED_BALL;
extern signature sight__SIG_3;
extern signature sight__SIG_4;
extern signature sight__SIG_5;
extern signature sight__SIG_6;
extern signature sight__SIG_7;
extern vision sight;
extern inertial Accella;
extern optical eyes;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );