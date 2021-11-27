/*
    I got my instructions on how to make the GPU from this video: https://youtu.be/l7rce6IQDWs
    Signal timings are from http://tinyvga.com/vga-timing
*/

#include <Arduino.h>
#include "TimerHelpers.h"

using namespace std;

struct VGA {
    const int PIN_RED = 8;
    const int PIN_GREEN = 9;
    const int PIN_BLUE = 10;

    const int PIN_HORIZONTAL_SYNC = 11;
    const int PIN_VERTICAL_SYNC = 12;

    // x, y, hz
    const int OUTPUT_RESOLUTION[3] = {160, 120, 60};

    // min, max
    const int OUTPUT_MIN_MAX_ANALOG_SIGNAL = 255;

    // microseconds
    const double OUTPUT_PERIOD_HORIZONTAL = (1 / 60) * 1e6;
    const double OUTPUT_PERIOD_VERTICAL = (1 / 60) * 1e6;
};

VGA VGAController;

void setup() {

    Serial.begin(9600);

    pinMode(VGAController.PIN_RED, OUTPUT);
    pinMode(VGAController.PIN_GREEN, OUTPUT);
    pinMode(VGAController.PIN_BLUE, OUTPUT);
    pinMode(VGAController.PIN_HORIZONTAL_SYNC, OUTPUT);
    pinMode(VGAController.PIN_VERTICAL_SYNC, OUTPUT);
}

void loop() {

    analogWrite(VGAController.PIN_RED, VGAController.OUTPUT_MIN_MAX_ANALOG_SIGNAL);
    analogWrite(VGAController.PIN_GREEN, VGAController.OUTPUT_MIN_MAX_ANALOG_SIGNAL);
    analogWrite(VGAController.PIN_BLUE, VGAController.OUTPUT_MIN_MAX_ANALOG_SIGNAL);
}