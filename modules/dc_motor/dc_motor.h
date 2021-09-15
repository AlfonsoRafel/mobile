#ifndef MBED_DC_MOTOR_H
#define MBED_DC_MOTOR_H

#include "mbed.h"

typedef enum {
            DIRECTION_1,
            DIRECTION_2,
            STOPPED
        } MotorDirection_t;

class dc_motor
{
    public:
        /**iniates the class with the specified trigger pin, echo pin, update speed, timeout **/
        dc_motor(PinName directionPosPin, PinName directionNegPin);
        /** returns the last measured distance**/
        void motorControlInit(void);
        void motorDirectionWrite(MotorDirection_t Direction);
        MotorDirection_t motorDirectionRead();
        void motorControlUpdate();
        
    private:
        DigitalInOut _directionPos;
        DigitalInOut _directionNeg;
        MotorDirection_t motorDirection;
        MotorDirection_t motorState;
        
};
#endif