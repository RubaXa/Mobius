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
        byte pinEn;
        
        int direction = CW;
        
        Motor(byte pinA, byte pinB, byte pinEn = 0) : Pin(0, 0) {
            this->pinA = pinA;
            this->pinB = pinB;
            this->pinEn = pinEn;
            
            pinMode(pinA, OUTPUT);
            pinMode(pinB, OUTPUT);
            
            if (pinEn) {
                pinMode(pinEn, OUTPUT);
            }
        }
        
        void setSpeed(float speed) {
            this->value = speed;
        }
        
        void setDirection(short int dir) {
            this->direction = dir;
        }
        
        void tick(long now) {
            if (this->__value != this->value || this->__direction != this->direction) {
                this->__value = this->value;
                this->__direction = direction;
                
                if (this->direction == CW) {
                    analogWrite(this->pinA, this->value * 255);
                    digitalWrite(this->pinB, LOW);
                } else {
                    digitalWrite(this->pinA, LOW);
                    analogWrite(this->pinB, this->value * 255);
                }
                
                if (this->pinEn) {
                    analogWrite(this->pinEn, this->value * 255);
                }
            }
        }
    };
    
}


#endif
