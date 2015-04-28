//
//  LED.h
//

#ifndef Mobius_LED_h
#define Mobius_LED_h

#include "Pin.h"


namespace Mobius {

	class LED: public Pin {
	public:
		static const byte ON = 10;
		static const byte OFF = 11;

		LED(int pin) : Pin (pin, OUTPUT) {
		}


		virtual void tick(long now) {
			Pin::tick(now);

			this->state = this->value > 0;

			if (this->__state != this->state) {
				this->__state = this->state;

				if (this->state) {
					this->trigger(ON);
				} else {
					this->trigger(OFF);
				}
			}
		}


		//
		// Array: Массив идиодов
		//
		class Array: public Pin {
		private:
			int *pins;
			float delta;


		public:
			int length;
            
            static Array * range(byte startPin, byte endPin) {
                int length = (endPin - startPin) + 1;
				int *pins = new int[length];
                
				for (int i = 0; i < length; i++) {
					pins[i] = startPin + i;
				}
                
                return new Array(pins, length);
            }
            
            
			Array(int *pins, int length) : Pin(0, 0) {
				this->pins = pins;
				this->mode = OUTPUT;
				this->length = length;
				this->delta = 1.0 / this->length;

				for (int i = 0; i < this->length; i++) {
					pinMode(this->pins[i], this->mode);
				}
			}
            

			virtual void tick(long now) {
				float value;

				if (this->__value != this->value) {
					this->__value = this->value;

					for (int i = 0; i < this->length; i++) {
						value = (this->value - this->delta * i) / this->delta;
						analogWrite(this->pins[i], value <= 0 ? 0 : (value >= 1 ? 255 : value * 255));
					}
				}
			}
		};
	};

}


#endif
