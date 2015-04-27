//
//  Pin.h
//

#ifndef Mobius_Pin_h
#define Mobius_Pin_h


#include "Strip.h"
#include "Emitter.h"
#include "Effects.h"


namespace Mobius {

	class Pin: public Strip::Item, public Emitter {
	protected:
		bool __state;
		float __value = 0;
        Effects::Effect *effect;


		// Установить mode пина
		void setMode(int mode) {
			this->mode = mode;
			pinMode(this->pin, mode);
		}


		// Записать зачение
		void write(float value, bool analog = false) {
			if (analog) {
				analogWrite(this->pin, 255 * value);
			} else {
				digitalWrite(this->pin, value);
			}

			this->__value = value;
		}


		// Прочесть значение
		float read(bool analog = false) {
			if (analog) {
				return analogRead(this->pin) / 1023.0;
			}
			else {
				return digitalRead(this->pin);
			}
		}



	public:
		byte pin;
		byte mode;
		bool state = false;
		float value = 0; // от 0 до 1


		// Конструктор
		Pin(byte pin, byte mode) : Item() {
			this->pin = pin;
            this->effect = Effects::NONE;

			if (pin > 0) {
				this->setMode(mode);
			}
		}

        
        // Установить effect на сигнал
        void setEffect(Effects::Effect *effect) {
            this->effect = effect;
            effect->value = this->value;
        }
        

		// Установить значение
		virtual void setValue(float value) {
			if (this->effect->enabled) {
				this->effect->set(value);
			}

			this->value = value;
		}

        
        // Получить реальное значение
		virtual float getValue() {
			return this->effect->enabled ? this->effect->value : this->value;
		}
        

		// Включить сигнал
		virtual void on() {
			this->setValue(1);
		}


		// Выключить сигнал
		virtual void off() {
			this->setValue(0);
		}


		virtual void tick(long now) {
			if (this->mode == OUTPUT) {
				if (this->effect->active) {
					this->effect->tick(now);
					this->write(this->effect->value, true);
				}
				else if (this->value != this->__value) {
					this->write(this->value);
				}
			}
		}
	}; // Pin
    
    
    
    
    //
    // PinNode
    //
    class PinNode: public Pin {
    private:
        List <Pin> devices;
        
        
    protected:
        virtual void dispatchState(bool state) {
            for (int i = 0; i < this->devices.size(); i++) {
                Pin *device = this->devices.get(i);
                
                if (state) {
                    device->on();
                } else {
                    device->off();
                }
            }
        }

        virtual void dispatchValue(float value) {
            for (int i = 0; i < this->devices.size(); i++) {
                Pin *device = this->devices.get(i);
                
                device->setValue(value);
            }
        }
        
        
    public:
        PinNode(byte pin, byte mode): Pin(pin, mode) {
        }
        
        // Присоединить устройство
        virtual void attach(Pin *device) {
            this->devices.push(device);
        }
    };

}

#endif
