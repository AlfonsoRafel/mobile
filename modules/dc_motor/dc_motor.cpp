#include "dc_motor.h"
#include "arm_book_lib.h"

dc_motor::dc_motor(PinName directionPosPin, PinName directionNegPin)
:_directionPos(directionPosPin), _directionNeg(directionNegPin)
{
 
}


void dc_motor::motorControlInit()
{
    _directionPos.mode(PullUp);
    _directionNeg.mode(PullUp);
    _directionPos.output();
    _directionNeg.output();

    motorDirection = STOPPED;
    motorState = STOPPED;
}

MotorDirection_t dc_motor::motorDirectionRead()
{
    return motorDirection;
}

void dc_motor::motorDirectionWrite( MotorDirection_t Direction )
{
    motorDirection = Direction;
}

void dc_motor::motorControlUpdate()
{
  switch ( motorState ) {
            case DIRECTION_1:
                if ( motorDirection == DIRECTION_2) {
                    _directionPos = LOW;
                    _directionNeg = HIGH;
                    motorState = DIRECTION_2;
                }
                if ( motorDirection == STOPPED ) {
                    _directionPos = LOW;
                    _directionNeg = LOW;
                    motorState = STOPPED;
                }
            break;
    
            case DIRECTION_2:
                if ( motorDirection == DIRECTION_1) {
                    _directionPos = HIGH;
                    _directionNeg = LOW;
                    motorState = DIRECTION_1;
                }
                if ( motorDirection == STOPPED ) {
                    _directionPos = LOW;
                    _directionNeg = LOW;
                    motorState = STOPPED;
                }
            break;
            case STOPPED:
            default:
                if ( motorDirection == DIRECTION_1 ) {
                    _directionPos = HIGH;
                    motorState = DIRECTION_1;
                }
                
                if ( motorDirection == DIRECTION_2 ) {
                    _directionNeg = HIGH;
                    motorState = DIRECTION_2;
                }
            break;
        }
    }        
