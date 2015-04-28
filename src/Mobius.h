//
//  Mobius.h
//

#ifndef Mobius_Mobius_h
#define Mobius_Mobius_h


#include "Strip.h"
#include "Emitter.h"
#include "Pin.h"
#include "LED.h"
#include "Button.h"


namespace Mobius {

    void stip() {
        Strip::getInstance()->tick();
    }
    
    
    int size() {
        return Strip::getInstance()->items.size();
    }
    
    
    class Power: public PinNode {
    public:
        static const int PROGRESS = 30;
        
        Power(int duration) : PinNode(0, 0) {
            this->effect = new Effects::Fade(duration);
        }
        
        virtual void on() {
            this->effect->set(1);
        }

        virtual void off() {
            this->effect->set(0);
        }

        virtual void tick(long now) {
            if (this->effect->active) {
                this->effect->tick(now);
                this->value = this->effect->value;
                
                this->dispatchValue(this->value);
                this->trigger(PROGRESS);
            }
        }
    };
    
}


/*
class Mobius {

    class Sensor: public Pin {
    protected:
        long lastRead = 0;
        
        
    public:
        int DELAY = 50;
        static const int VALUE = 30;
        
        Sensor(int pin) : Pin(pin, INPUT) {
            Mobius::getInstance()->add(this);
        }
        
        virtual void tick() {
            long now = millis();
            
            // Если времени с последенего момента имезения больше `DELAY`, проверяем реальность изменения
            if ((now - this->lastRead) > Sensor::DELAY) {
                this->lastRead = now;
                this->__value = this->read(true);
                
                if (this->value != this->__value) {
                    this->value = this->__value;
                    this->trigger(VALUE);
                }
            }
        }
    };

};
*/


#endif
