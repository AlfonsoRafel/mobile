#ifndef MBED_TACHOMETER_H
#define MBED_TACHOMETER_H

#include "mbed.h"

class tachometer
{
    public:
        /**iniates the class with the specified trigger pin, echo pin, update speed, timeout **/
        tachometer(PinName echoPin, float updateSpeed, float timeout);
        /**iniates the class with the specified trigger pin, echo pin, update speed, timeout and method to call when the distance changes**/
        tachometer(PinName echoPin, float updateSpeed, float timeout, void onUpdate(int));
        /** returns the last measured distance**/
        int getCurrentSpeed(void);
        /**pauses measuring the distance**/
        void pauseUpdates(void);
        /**starts mesuring the distance**/
        void startUpdates(void);
        /**attachs the method to be called when the distances changes**/
        void attachOnUpdate(void method(int));
        /**changes the speed at which updates are made**/
        void changeUpdateSpeed(float updateSpeed);
        /**gets whether the distance has been changed since the last call of isUpdated() or checkDistance()**/
        int isUpdated(void);
        /**gets the speed at which updates are made**/
        float getUpdateSpeed(void);
        /**call this as often as possible in your code, eg. at the end of a while(1) loop,
        and it will check whether the method you have attached needs to be called**/
        void checkDistance(void);
    private:
        InterruptIn _echo;
        Timer _t;
        Timeout _tout;
        int _distance;
        float _speed;
        int count;
        float _updateSpeed;
        int start;
        int end;
        volatile int done;
        void (*_onUpdateMethod)(int);
        void _countInt(void);
        void _updateRPM(void);
        void _startTrig(void);
        float _timeout;
        int d;
};
#endif