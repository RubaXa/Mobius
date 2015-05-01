//
//  Effects.h
//   - Fade
//   - Blink
//

#ifndef Mobius_Effects_h
#define Mobius_Effects_h


#define PI 3.1415926535897932384626433832795


namespace Mobius {

	namespace Effects {
		//
		// Effect: Базовый класс
		//
		class Effect {
		protected:
			long startTime = 0;

			int duration = 0;
			int durationOn = 0;
			int durationOff = 0;

		public:
			float value = 0;
			float valueFrom = 0;
			float valueTo = 0;
            
			bool active = false;
			bool enabled = false;


			Effect(int durationOn, int durationOff) {
				this->enabled = (durationOn > 0 || durationOff > 0);
				this->durationOn = durationOn;
				this->durationOff = durationOff;
			}


			virtual void set(float value) {
			}


			virtual void tick(long now) {
			}

		};


		//
		// Шоркат для «нет эффекта»
		//
		static Effect *NONE = new Effect(0, 0);


		//
		// Fade(X, Y = X)
		//
		class Fade: public Effect {
		public:
			Fade(int durationOn, int durationOff = 0) : Effect(durationOn, durationOff ? durationOff : durationOn) {
			}


			void set(float value) {
                if (this->valueTo != value) {
                    this->active = true;
                    this->startTime = millis();
                    this->duration = (this->value > value) ? this->durationOff : this->durationOn;

                    this->valueFrom = this->value;
                    this->valueTo = value;
                }
			}


			void tick(long now) {
				float progress = ((now - this->startTime) / (float)this->duration);

				if (progress >= 1.0) {
					this->value = this->valueTo;
					this->active = false;
				} else {
					this->value = this->valueFrom + (this->valueTo - this->valueFrom) * progress;
				}
                    
			}
		};


		//
		// Blink(X)
		//
		class Blink: public Effect {
		public:
			Blink(int duration) : Effect(duration, 0) {
			}

			void set(float value) {
				this->active = value > 0;
				this->startTime = millis();
				this->duration = this->durationOn;
			}

			void tick(long now) {
				this->value = !(((now - this->startTime) / this->duration) % 2);
			}
		};
	}

}

#endif
