//
//  Button.h
//

#ifndef Mobius_Button_h
#define Mobius_Button_h

#include "Pin.h"

namespace Mobius {

	class Button: public PinNode {
	protected:
		long lastRead = 0;
		float lastValue = 0;
		List <Pin> devices;


	public:
		int DELAY = 50;
		static const int UP = 20;
		static const int DOWN = 21;

		bool pressed = false;


		Button(int pin) : PinNode(pin, INPUT) {
			if (pin > 0) {
				this->write(1);
                this->value = 0;
			}
		}


		void on() {
			// Ничего не делают
		}


		void off() {
			// Ничего не делают
		}

		
        virtual void tick(long now) {
			// Читаем текущее состояние
			float currentValue = this->read();


			// Првоеряем, не изменилось ли оно с момента последнего чтения
			if (currentValue != this->lastValue) {
				this->lastRead = now;
				this->lastValue = currentValue;
			}


			// Если времени с последенего момента имезения больше `DELAY`, проверяем реальность изменения
			if ((now - this->lastRead) > Button::DELAY) {
				// Проверяем само значение
				if (currentValue != this->value) {
					this->value = currentValue;
					this->pressed = !this->value;

					this->dispatchState(this->pressed);

					// Испускаем событие
					if (this->pressed) {
						this->trigger(Button::DOWN);
					} else {
						this->trigger(Button::UP);
					}
				}
			}
		}
	};

}

#endif
