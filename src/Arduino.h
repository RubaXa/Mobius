//
//  Arduino.h — Mock functions
//

#ifndef Mobius_Arduino_h
#define Mobius_Arduino_h


typedef unsigned short int byte;


void delayMicroseconds(int ms) {
    
}

void attachInterrupt(int pin, void fn(), int mode) {
    
}

void detachInterrupt(int pin) {
    
}


float pulseIn(int pin, byte value, int timeout = 0) {
    return 0;
}

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

long millis() {
    static int time = 0;
    time = time + 100;
    return time;
}

long micros() {
    static long time = 0;
    time = time + 1000;
    return time;
}


const int LOW = 0;
const int HIGH = 1;
const int INPUT = 0;
const int OUTPUT = 1;

const int RISING = 3;
const int FALLING = 4;


#endif
