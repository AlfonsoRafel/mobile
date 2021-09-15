 #include "lm_393.h"

    tachometer::tachometer(PinName echoPin, float updateSpeed, float timeout)
    :_echo(echoPin)
    {
        _updateSpeed = updateSpeed;
        _timeout = timeout;
        _t.start ();
        count = 0;
    }
    
    tachometer::tachometer(PinName echoPin, float updateSpeed, float timeout, void onUpdate(int))
    :_echo(echoPin)
    {
        _onUpdateMethod=onUpdate;
        _updateSpeed = updateSpeed;
        _timeout = timeout;
        _t.start ();
        count = 0;
    }
       void tachometer::_countInt()
    { 
        count = count + 1;
    }
        
    void tachometer::_updateRPM()
    {
        _speed = count/20.0*60.0; 
        count = 0;      
        _tout.detach();
        //_tout.attach(this, &tachometer::_startTrig, _updateSpeed);   
        _tout.attach(callback(this, &tachometer::_startTrig), _updateSpeed);
    }
 
    void tachometer::_startTrig(void)
    {
        //_tout.detach();          
        //_echo.rise(this, &tachometer::_startT);  
        _echo.mode(PullUp);
        _echo.rise(callback(this, &tachometer::_countInt)); 
        _echo.enable_irq ();
        //_tout.attach(this, &tachometer::_startTrig,_timeout);
        _tout.attach(callback(this, &tachometer::_updateRPM),_timeout);
                         
    }
    
    int tachometer::getCurrentSpeed(void)
    {
        return _speed;
    }
    void tachometer::pauseUpdates(void)
    {
        _tout.detach();
        _echo.rise(NULL);
        _echo.fall(NULL);
    }
    void tachometer::startUpdates(void)
    {
        _startTrig();
    }
    void tachometer::attachOnUpdate(void method(int))
    {
        _onUpdateMethod = method;
    }
    void tachometer::changeUpdateSpeed(float updateSpeed)
    {
        _updateSpeed = updateSpeed;
    }
    float tachometer::getUpdateSpeed()
    {
        return _updateSpeed;
    }
    int tachometer::isUpdated(void)
    {
        //printf("%d", done);
        d=done;
        done = 0;
        return d;
    }
    void tachometer::checkDistance(void)
    {
        if(isUpdated())
        {
            (*_onUpdateMethod)(_speed);
        }
    }
