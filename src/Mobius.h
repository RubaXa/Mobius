//
//  Mobius.h
//

#ifndef Mobius_Mobius_h
#define Mobius_Mobius_h


#include "Strip.h"
#include "Emitter.h"
#include "Pin.h"
#include "Led.h"
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
  public:
    class Motor: public Pin {
    private:
        int __direction;
        
    public:
        static const int CW = 1;
        static const int CCW = -1;
        
        int directionPin;
        int direction = CW;
        
        Motor(int pin, int directionPin) : Pin(pin, OUTPUT) {
            this->directionPin = directionPin;
            pinMode(directionPin, OUTPUT);
        }
                
        void setSpeed(int speed) {
            this->value = speed;
        }
        
        
        void tick() {
            if (this->__value != this->value || this->__direction != this->direction) {
                this->__value = this->value;
                this->__direction = direction;
                
                if (this->direction == CW) {
                    analogWrite(this->pin, this->value);
                    digitalWrite(this->directionPin, 0);
                } else {
                    digitalWrite(this->pin, 0);
                    analogWrite(this->directionPin, this->value);
                }
            }
        }
    };
    
    
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
    
    
    static Mobius * getInstance() {
        static Mobius *instance = new Mobius();
        return instance;
    }
    
    
    void add(Pin *pin) {
        this->items.push(pin);
    }
    
    
    // Монтировать диод
    Led *mountLed(int pin) {
        Led *led = new Led(pin);
        this->items.push(led);
        return led;
    }
    
    
    // Монтировать кнопку
    Button *mountButton(int pin) {
        Button *btn = new Button(pin);
        this->items.push(btn);
        return btn;
    }
    
    
    // Монтировать диодную панель
    Led::Array * mountLedBar(int startPin, int endPin) {
        int length = (endPin - startPin) + 1;
        int *pins = new int[length];
        
        for (int i = 0; i < length; i++) {
            pins[i] = startPin + i;
        }
        
        return this->mountLedArray(pins, length);
    }
    
    
    // Монтировать массив диодов
    Led::Array * mountLedArray(int *pins, int length) {
        Led::Array *leds = new Led::Array(pins, length);
        this->items.push(leds);
        return leds;
    }

    
    Sensor * mountSensor(int pin) {
        Sensor *sensor = new Sensor(pin);
        this->items.push(sensor);
        return sensor;
    }

    
    Motor * mountMotor(int pin, int directionPin) {
        Motor *motor = new Motor(pin, directionPin);
        this->items.push(motor);
        return motor;
    }

    
    void tick() {
        for (int i = 0; i < this->items.size(); i++) {
            this->items.get(i)->tick();
        }
    }
    
    
    class Power: public Button {
    private:
        Effects::Effect *effect;
        
        
    public:
        static const int MAX = 255;
        static const int PROGRESS = 20;
        
        Power(int duration) : Button(0) {
            this->effect = new Effects::Fade(duration);
            Mobius::getInstance()->add(this);
        }
        
        virtual void on() {
            this->effect->set(this->MAX);
        }
        
        virtual void off() {
            this->effect->set(0, false);
        }
        
        
        virtual void tick() {
            if (this->effect->active) {
                this->effect->tick();
                this->value = this->effect->value;
                
                this->trigger(PROGRESS);
                
                for (int i = 0; i < this->devices.size(); i++) {
                    Pin *device = this->devices.get(i);

                    device->setValue(this->value / 255.0);
                    device->tick();
                }
            }
        }
    };
    
  
  private:
    List <Unit> items;
    
    
};
*/


#endif
