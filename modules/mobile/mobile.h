//=====[#include guards - begin]===============================================

#ifndef _MOBILE_SYSTEM_H_
#define _MOBILE_SYSTEM_H_

//=====[Libraries]=============================================================

//=====[Declaration of public defines]=======================================

#define SYSTEM_TIME_INCREMENT_MS   100

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void mobileSystemInit();
void mobileSystemUpdate();
void avoidObstacles();
void printStatus();


void setDrivingMode();
void drivingMode_A();
void drivingMode_B();
void drivingMode_C();

//=====[#include guards - end]=================================================

#endif // _SMART_HOME_SYSTEM_H_