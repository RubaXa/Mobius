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
#include "Motor.h"
#include "Sensor.h"


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


#endif
