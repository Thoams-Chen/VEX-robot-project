#include "robot-config.h"
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
vex::competition    Competition;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void stopMotors(){
    LeftMotor.stop();
    RightMotor.stop();
}
void autonomous( void ) {
    ArmMotor.resetRotation();
    LeftMotor.resetRotation();
    RightMotor.resetRotation();
    double squareDim = 22.1;
    double firstDisk = 58.6;
    double wheelCircum = M_PI * 8;
    double platformWidth = 20.5;
    int autonomousLine = 69;
    double measuredLength = 5; //This value is the vertical distance from the robot to the point the angle meets the back wall
    double diskCupRadius = 3.8;
    double coneVerticalDistance = 23.6;
    LeftMotor.setVelocity(75,velocityUnits::pct);
    RightMotor.setVelocity(75,velocityUnits::pct);
    while((LMotor.rotation(rotationUnits::rev))*wheelCircum< autonomousLine and SonarBack.distance(distanceUnits::in)<autonomousLine){
        LeftMotor.spin(directionType::fwd);
        RightMotor.spin(directionType::fwd);
    }
    stopMotors();
    while(SonarA.distance(distanceUnits::in)>firstDisk-platformWidth){
        LeftMotor.spin(directionType::rev);
            RightMotor.spin(directionType::rev);
    }
    stopMotors()
    while(SonarA<turnDistance()){
        LeftMotor.spin(directionType::rev);
        RightMotor.spin(directionType::fwd);
    }
    stopMotors();  
        *//RightMotor.rotateFor(2.5,timeUnits::sec);
           LeftMotor.rotateFor(2.5,timeUnits::sec);
    ArmMotor.rotateTo(270,rotationUnits::deg,100,velocityUnits::pct);
    LeftMotor.rotateTo(90,rotationUnits::deg,100,velocityUnits::pct);
    RightMotor.rotateTo(90,rotationUnits::deg,100,velocityUnits::pct);

}
void usercontrol( void ) {
     
    while (1){
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    ClawMotor.setVelocity(Controller1.Axis1.position(percent),percent);//velocityUnits::rpm not sure pect it will work//
    ArmMotor.setVelocity(Controller1.Axis2.position(percent),percent);
    LeftMotor.setVelocity(((Controller1.Axis3.position(percent)*0.7)-(Controller1.Axis4.position(percent)*0.3)),percent);
    RightMotor.setVelocity(((Controller1.Axis3.position(percent)*0.7)+(Controller1.Axis4.position(percent)*0.7)),percent);
   vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.   
  }
    LeftMotor.spin(forward);
    RightMotor.spin(forward);
    ArmMotor.spin(forward);
    ClawMotor.spin(forward);
    if(while((Controller1.ButtonDown.pressing() or (Controller1.ButtonLeft.pressing() or (Controller1.ButtonRight.pressing() or Controller1.ButtonUp.pressing()))))){
      LeftMotor.setVelocity(100,velocityUnits::rpm);
      RightMotor.setVelocity(100,velocityUnits::rpm);
      if(Controller1.ButtonUp.pressing()){
        LeftMotor.spin(forward);
        RightMotor.spin(forward);
      }
      if(Controller1.ButtonDown.pressing()){
        LeftMotor.spin(reverse);
        RightMotor.spin(reverse);
      }
      if(Controller1.ButtonLeft.pressing()){
        LeftMotor.spin(reverse);
        RightMotor.spin(forward);
      }
      if(Controller1.ButtonRight.pressing()){
        LeftMotor.spin(forward);
        RightMotor.spin(reverse);
      }
    }
    if((Controller1.ButtonR1.pressing() or Controller1.ButtonR2.pressing()))
    {
      ArmMotor.setVelocity(100,percent);
      ArmMotor.setStopping(hold);
      if(Controller1.ButtonR1.pressing()){
        ArmMotor.rotateFor(720,rotationUnits::deg);
      }else{
        if(Controller1.ButtonR2.pressing()){
          ArmMotor.rotateFor(-720,rotationUnits::deg);
        }else{
          ArmMotor.stop();
        }
      }
    }
    if((Controller1.ButtonL1.pressing() or Controller1.ButtonL2.pressing())){
      ClawMotor.setVelocity(80,percent);
      ClawMotor.setStopping(hold);
      if(Controller1.ButtonL1.pressing()){
        ClawMotor.spin(forward);
      }else{
        if(Controller1.ButtonL2.pressing()){
          ClawMotor.spin(reverse);
        }else{
          ClawMotor.stop();
        }
      }
    }if(Brain.Battery.capacity()<50%){
        Controller.rumble(“you need to charge -.-!");
    
}
 


//
// Main will set up the competition functions and callbacks.
//
int main() {
    
    //Run the pre-autonomous function. 
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}