//
//  Motor.h
//

#ifndef Mobius_Motor_h
#define Mobius_Motor_h


namespace Mobius {
    
    class Motor: public Pin {
    private:
        int __direction;
        
    public:
        static const int CW = 1;
        static const int CCW = -1;
        
        byte pinA;
        byte pinB;
        int direction = CW;
        
        Motor(byte pinA, byte pinB) : Pin(0, 0) {
            this->pinA = pinA;
            this->pinB = pinB;
            
            pinMode(pinA, OUTPUT);
            pinMode(pinB, OUTPUT);
        }
        
        void setSpeed(float speed) {
            this->value = speed;
        }
        
        void tick(long now) {
            if (this->__value != this->value || this->__direction != this->direction) {
                this->__value = this->value;
                this->__direction = direction;
                
                if (this->direction == CW) {
                    analogWrite(this->pinA, this->value * 255);
                    digitalWrite(this->pinB, 0);
                } else {
                    digitalWrite(this->pinA, 0);
                    analogWrite(this->pinB, this->value * 255);
                }
            }
        }
    };
    
}


#endif
