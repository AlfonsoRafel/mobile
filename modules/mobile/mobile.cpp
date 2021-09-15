//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "mobile.h"

#include "pc_serial_com.h"
#include "lm_393.h"
#include "hc_sr04.h"
#include "dc_motor.h"
#include "speed_control.h"

//=====[Declaration of private defines]======================================

//=====[Declaration of private data types]=====================================
int dist;
float spd_right;
float spd_left;
float duty ;
int freq =0;

ultrasonic hc_sr04(A3, A4, .1, 1);
tachometer tachometerRightFront(A1, 0, 1); 
tachometer tachometerLeftFront(A2, 0, 1);
dc_motor motorRightFront(PF_2, PE_3);
dc_motor motorLeftFront(PE_5, PE_6);

drivingMode_t drivingMode;
//=====[Implementations of public functions]===================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void mobileSystemInit()
{   
    pcSerialComInit();
    hc_sr04.startUpdates();
    tachometerRightFront.startUpdates();
    tachometerLeftFront.startUpdates();
    motorRightFront.motorControlInit();
    motorLeftFront.motorControlInit();
    speedControlInit();  
}

void mobileSystemUpdate()
{   
    pcSerialComUpdate();
    // Measurements
    dist = hc_sr04.getCurrentDistance();
    spd_right = tachometerRightFront.getCurrentSpeed();
    spd_left = tachometerLeftFront.getCurrentSpeed();
    duty = setPointUpdate();

    setDrivingMode();
    //printStatus();
    // Update Time by Software Interruptions

}
//=====[Implementations of private functions]==================================

void printStatus(){
    freq = freq + 1;
    if (freq==40){
        printf( "DutyCycle %f\n", duty);
        printf( "Speed Right %f rpm\n", spd_right);
        printf( "Speed Left %f rpm\n", spd_left);
        printf( "Distance %d mm\n", dist);
        freq=0;
    }
}

void setDrivingMode()
{
    drivingMode = getDrivingMode();
    
    switch (drivingMode) {
        case a: drivingMode_A(); break;
        case b: drivingMode_B(); break;
        case c: drivingMode_C(); break;
        default:  break;
    } 

}
void drivingMode_A()
{
    if(dist>=250) {
        motorRightFront.motorDirectionWrite(DIRECTION_2);
        motorLeftFront.motorDirectionWrite(DIRECTION_2);  
        motorRightFront.motorControlUpdate();
        motorLeftFront.motorControlUpdate();  
    }
    else {
        motorRightFront.motorDirectionWrite(STOPPED);
        motorLeftFront.motorDirectionWrite(STOPPED);
        motorRightFront.motorControlUpdate();
        motorLeftFront.motorControlUpdate();
        delay(1000);
        motorRightFront.motorDirectionWrite(DIRECTION_1);
        motorRightFront.motorControlUpdate();
        delay(2000);  
        motorRightFront.motorDirectionWrite(STOPPED);
        motorRightFront.motorControlUpdate();
    }
}

void drivingMode_B()
{
    if(dist>=250) {
        motorRightFront.motorDirectionWrite(DIRECTION_2);
        motorLeftFront.motorDirectionWrite(DIRECTION_2);  
        motorRightFront.motorControlUpdate();
        motorLeftFront.motorControlUpdate();  
    }
    else {
        motorRightFront.motorDirectionWrite(STOPPED);
        motorLeftFront.motorDirectionWrite(STOPPED);
        motorRightFront.motorControlUpdate();
        motorLeftFront.motorControlUpdate();
        delay(1000);
        motorRightFront.motorDirectionWrite(DIRECTION_1);
        motorLeftFront.motorDirectionWrite(DIRECTION_1);
        motorRightFront.motorControlUpdate();
        motorLeftFront.motorControlUpdate();
        delay(1000);  
        motorRightFront.motorDirectionWrite(STOPPED);
        motorLeftFront.motorDirectionWrite(STOPPED);
        motorRightFront.motorControlUpdate();
        motorLeftFront.motorControlUpdate();
    }  
}
void drivingMode_C()
{
    
}