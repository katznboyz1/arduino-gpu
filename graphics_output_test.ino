#include <Arduino.h>

using namespace std;

const int PIN_RED = 8;
const int PIN_GREEN = 9;
const int PIN_BLUE = 10;
const int PIN_HORIZONTAL_SYNC = 11;
const int PIN_VERTICAL_SYNC = 12;

void setup() {

    Serial.begin(9600);

    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_HORIZONTAL_SYNC, OUTPUT);
    pinMode(PIN_VERTICAL_SYNC, OUTPUT);
}

void loop() {

}