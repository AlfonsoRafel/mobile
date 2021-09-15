//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "mobile.h"


//=====[Declaration of private defines]======================================
AnalogIn Pote(A0);

typedef enum {
    encoderRightFront,
    encoderLeftFront
} encoder;

PwmOut pwmSpeed[] = {(PB_4), (PA_0)};

static float dutyCycle = 0.5f;
static float period = 0.01f;
//=====[Declaration of private data types]=====================================

//=====[Implementations of public functions]===================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

float setPointRead()
{   
    return Pote.read();
}

void setPeriod(encoder enc, float period)
{   
    pwmSpeed[enc].period(period);
}

void setDutyCycle(encoder enc, float dutyCycle)
{   
    pwmSpeed[enc].write(dutyCycle);
}

float setPointUpdate()
{   
    dutyCycle=setPointRead();
    setDutyCycle(encoderRightFront, dutyCycle);
    setDutyCycle(encoderLeftFront, dutyCycle);
    return dutyCycle;
}


void speedControlInit()
{   
    setPeriod(encoderRightFront, period);
    setDutyCycle(encoderRightFront, dutyCycle);
    setPeriod(encoderLeftFront, period);
    setDutyCycle(encoderLeftFront, dutyCycle);
}


//=====[Implementations of private functions]==================================
