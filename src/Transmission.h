//
//  Transmission.h
//

#ifndef Mobius_Transmission_h
#define Mobius_Transmission_h

namespace Mobius {
    
    class Transmission: public Strip::Item {
    protected:
        Motor *leftMotor;
        Motor *rightMotor;
        HardwareSerial *serial;
        
    public:
        Effects::Fade *power;
        Effects::Fade *rotate;
        
        static const byte MOTOR_LEFT = 0;
        static const byte MOTOR_RIGHT = 1;

        static const int FORWARD = 1;
        static const int BACKWARD = -1;
        static const int LEFTWARD = -1;
        static const int RIGHTWARD = 1;

        Transmission() : Item() {
            this->power = new Effects::Fade(100, 50);
            this->rotate = new Effects::Fade(100);
        }
        
        void addMotors(Motor *left, Motor *right) {
            this->leftMotor = left;
            this->rightMotor = right;
        }
        
        void moveTo(int vector) {
            this->power->set(vector);
        }
        
        void rotateTo(int vector) {
            this->rotate->set(vector);
        }
        
        void useSerial(HardwareSerial &serial) {
            this->serial = &serial;
        }
        
        virtual void tickSerial() {
            static String cmd = "";
            static String input = "";
            static char chr;
            static int keyCode;
            static bool pressed;
            
            if (this->serial) {
                while (this->serial->available()) {
                    chr = (char)this->serial->read();
                    
                    if (chr == '!') {
                        cmd = input;
                        input = "";
                    } else {
                        input += chr;
                    }
                }
                
                pressed = cmd.startsWith("D");
                keyCode = cmd.substring(1).toInt();
                
                // UP & DOWN
                if (keyCode == 38 || keyCode == 40) {
                    if (pressed) {
                        this->moveTo(keyCode == 38 ? Transmission::FORWARD : Transmission::BACKWARD);
                    } else {
                        this->moveTo(0);
                    }
                }
                
                // LEFT & RIGHT
                if (keyCode == 37 || keyCode == 39) {
                    if (pressed) {
                        this->rotateTo(keyCode == 37 ? Transmission::LEFTWARD : Transmission::RIGHTWARD);
                    }
                    else {
                        this->rotateTo(0);
                    }
                }
            }
        }
        
        virtual void tick(long now) {
            this->tickSerial();
            
            this->power->tick(now);
            this->rotate->tick(now);
            
            float speed = this->power->value;
            int dir = speed >= 0 ? Motor::CW : Motor::CCW;
            
            float rotateSpeed = this->rotate->value;
            float speedLeft = speed || (int)(this->rotate->valueTo > 0);
            float speedRight = speed || (int)(this->rotate->valueTo < 0);
            
            this->leftMotor->setDirection(dir);
            this->rightMotor->setDirection(dir);
            
            this->leftMotor->setSpeed(abs(speedLeft * (rotateSpeed < 0 ? 1 - abs(rotateSpeed*0.8) : 1)));
            this->rightMotor->setSpeed(abs(speedRight * (rotateSpeed > 0 ? 1 - abs(rotateSpeed*0.8) : 1)));
        }
    };
    
}


#endif
