//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "pc_serial_com.h"
#include "mobile.h"

//=====[Declaration of private defines]======================================

//=====[Declaration of private data types]=====================================

typedef enum{
    PC_SERIAL_COMMANDS,
    PC_SERIAL_GET_CODE,
    PC_SERIAL_SAVE_NEW_CODE,
} pcSerialComMode_t;

//=====[Declaration and initialization of public global objects]===============

Serial uartUsb(USBTX, USBRX);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

char codeSequenceFromPcSerialCom[CODE_NUMBER_OF_KEYS];

//=====[Declaration and initialization of private global variables]============

static pcSerialComMode_t pcSerialComMode = PC_SERIAL_COMMANDS;
drivingMode_t drivingMode_s = a;
static bool codeComplete = false;
static int numberOfCodeChars = 0;

//=====[Declarations (prototypes) of private functions]========================

static void pcSerialComCommandUpdate( char receivedChar );

static void availableCommands();
//static void commandShowCurrentMotorState();

//=====[Implementations of public functions]===================================

void pcSerialComInit()
{
    availableCommands();
}

char pcSerialComCharRead()
{
    char receivedChar = '\0';
    if( uartUsb.readable() ) {
        receivedChar = uartUsb.getc();
    }
    return receivedChar;
}

void pcSerialComStringWrite( const char* str )
{
    uartUsb.printf( "%s", str );
}

void pcSerialComUpdate()
{
    char receivedChar = pcSerialComCharRead();
    if( receivedChar != '\0' ) {
        switch ( pcSerialComMode ) {
            case PC_SERIAL_COMMANDS:
                pcSerialComCommandUpdate( receivedChar );
            break;
           
            default:
                pcSerialComMode = PC_SERIAL_COMMANDS;
            break;
        }
    }    
}


//=====[Implementations of private functions]==================================



static void pcSerialComCommandUpdate( char receivedChar )
{
    switch (receivedChar) {
        case 'a': case 'A': drivingMode_s = a;
        uartUsb.printf( "Mode A selected\r\n" ); break;
        case 'b': case 'B': drivingMode_s = b;
        uartUsb.printf( "Mode B selected\r\n" ); break;
        case 'c': case 'C': drivingMode_s = c;
        uartUsb.printf( "Mode C selected\r\n" ); break;
        case 'i': case 'I': drivingModeInfo(); break;
        default: availableCommands(); break;
    } 
}

static void availableCommands()
{
    uartUsb.printf( "Select Driving Mode:\r\n" );
    uartUsb.printf( "Press 'a' or 'A' to select A mode\r\n" );
    uartUsb.printf( "Press 'b' or 'B' to select B mode\r\n" );
    uartUsb.printf( "Press 'c' or 'C' to select C mode\r\n" );
    uartUsb.printf( "Press 'i' or 'I' to get Driving Mode Details\r\n" );
    uartUsb.printf( "\r\n" );
}

static void drivingModeInfo()
{
    uartUsb.printf( "Mode A: stop at 25cm far from object, drive back while turning and driving forward again.\r\n" );
    uartUsb.printf( "Mode B: stop at 25cm far from object, drive back without turning and driving forward again.\r\n" );
    uartUsb.printf( "Mode C: under development.\r\n" );
 
}

drivingMode_t getDrivingMode()
{
    return drivingMode_s;
 
}