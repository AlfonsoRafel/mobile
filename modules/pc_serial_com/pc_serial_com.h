//=====[#include guards - begin]===============================================

#ifndef _PC_SERIAL_COM_H_
#define _PC_SERIAL_COM_H_
#define CODE_NUMBER_OF_KEYS   4

//=====[Libraries]=============================================================

//=====[Declaration of public defines]=======================================
typedef enum{
    a,
    b,
    c,
} drivingMode_t;
//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void pcSerialComInit();
char pcSerialComCharRead();
void pcSerialComStringWrite( const char* str );
void pcSerialComUpdate();
static void drivingModeInfo();
drivingMode_t getDrivingMode();

//=====[#include guards - end]=================================================

#endif // _PC_SERIAL_COM_H_