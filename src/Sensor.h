//
//  Sensor.h
//

#ifndef Mobius_Sensor_h
#define Mobius_Sensor_h

#include "Pin.h"

namespace Mobius {

    namespace Sensor {

        class Sensor: public Pin {
        protected:
            long lastRead = 0;


        public:
            int DELAY = 50;
            static const int VALUE = 40;

            Sensor(int pin) : Pin(pin, INPUT) {
            }

            virtual void tick(long now) {
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


        //
        // Ultrasonic
        //
        class Ultrasonic: public Sensor {
        protected:
            int timeout;

            
        public:
            int DELAY = 150;
            static const int DISTANCE = 100;

            int max;

            byte trigPin;
            byte echoPin;

            Ultrasonic(byte trigPin, byte echoPin, int max = 400, int timeout = 0) : Sensor(0) {
                this->trigPin = trigPin;
                this->echoPin = echoPin;

                this->max = max;
                this->value = max;
                this->timeout = timeout || max * 58;

                pinMode(trigPin, OUTPUT);
                pinMode(echoPin, INPUT);
            }


            virtual void tick(long now) {
                if ((now - this->lastRead) > Ultrasonic::DELAY) { // debounce
                    this->lastRead = now;

                    digitalWrite(this->trigPin, LOW);

                    delayMicroseconds(2);
                    digitalWrite(this->trigPin, HIGH);

                    delayMicroseconds(10);
                    digitalWrite(this->trigPin, LOW);
                    
                    this->value = pulseIn(this->echoPin, HIGH, this->timeout) / 58; // cm
                    
                    if (this->value == 0) {
                        this->value = this->max;
                    }

                    if (this->__value != this->value) {
                        this->__value = this->value;
                        this->trigger(DISTANCE);
                    }
                }
            }
        };
    }

}

#endif

