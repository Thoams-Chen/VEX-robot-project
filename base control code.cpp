#include "robot-config.h"
          
int main() {
    
double carSpeedPCTfb,carSpeedPCTlr;
    carSpeedPCTfb= Controller1.Axis3.position(percentUnits::pct);
    carSpeedPCTlr= Controller1.Axis4.position(percentUnits::pct)/2;
    
    while(Brain.Screen.pressing()) {         
    Brain.Screen.clearScreen();    
    Brain.Screen.print(Brain.Battery.temperature());
    Brain.Screen.print(Brain.Battery.capacity());
    }
    
    while(Brain.Battery.capacity()<20)
    {
        Brain.Screen.print("low low-battery");
     }
    
    if (Controller1.Axis3.value()>0)
    { 
    RMotor.spin(directionType::fwd,carSpeedPCTfb,percentUnits::pct);
    LMotor.spin(directionType::fwd,carSpeedPCTfb,percentUnits::pct);
    }
    
   if (Controller1.Axis3.value()<0)
   {
    RMotor.spin(directionType::rev,carSpeedPCTfb,percentUnits::pct);
    LMotor.spin(directionType::rev,carSpeedPCTfb,percentUnits::pct);
   }
    if( Controller1.Axis4.value()<0)
    {
    RMotor.spin(directionType::fwd,carSpeedPCTlr,percentUnits::pct);
    LMotor.spin(directionType::rev,carSpeedPCTlr,percentUnits::pct);
    } 
    if( Controller1.Axis4.value()>0)
    
   { RMotor.spin(directionType::rev,carSpeedPCTlr,percentUnits::pct);
     LMotor.spin(directionType::fwd,carSpeedPCTlr,percentUnits::pct);
   }
   
   else
   { LMotor.stop();
     RMotor.stop();
     }
 vex::task::sleep(20);
    
}
