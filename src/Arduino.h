//
//  Arduino.h — Mock functions
//

#ifndef Mobius_Arduino_h
#define Mobius_Arduino_h

typedef unsigned short int byte;


int constrain(float val, float min, float max) {
    return 0;
}

int map(int value, int fromLow, int fromHigh, int toLow, int toHigh) {
    return 0;
}


int round(float val) {
    return 0;
}


double cos(float val) {
    return .0;
}


double sin(float val) {
    return .0;
}


int inputSignal = 0;
int digitalRead(int pin) {
    return inputSignal;
}

int analogRead(int pin) {
    return inputSignal;
}


void digitalWrite(int pin, int value) {
    
}


void analogWrite(int pin, int value) {
    
}



void pinMode(int pin, int mod) {
    
}

int millis() {
    static int time = 0;
    time = time + 100;
    return time;
}

const int LOW = 0;
const int HIGH = 1;
const int INPUT = 0;
const int OUTPUT = 1;


#endif
