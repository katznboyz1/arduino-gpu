/*
    I got my instructions on how to make the GPU from this video: https://youtu.be/l7rce6IQDWs
    Signal timings are from http://tinyvga.com/vga-timing (specifically http://tinyvga.com/vga-timing/640x480@60Hz)
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
    const int OUTPUT_RESOLUTION[3] = {200, 200, 60};

    const long double OUTPUT_PERIOD = (1 / 60);

    const int MAX_MIN_ANALOG_SIGNAL[2] = {0, 255};

    // must be one bit, so I'm using a boolean for readability
    const bool VGA_HORIZONTAL_SYNC;
    const bool VGA_VERTICAL_SYNC;
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

    analogWrite(VGAController.PIN_RED, VGAController.MAX_MIN_ANALOG_SIGNAL[1]);
    analogWrite(VGAController.PIN_GREEN, VGAController.MAX_MIN_ANALOG_SIGNAL[1]);
    analogWrite(VGAController.PIN_BLUE, VGAController.MAX_MIN_ANALOG_SIGNAL[1]);

    analogWrite(VGAController.PIN_HORIZONTAL_SYNC, VGAController.VGA_HORIZONTAL_SYNC);
    analogWrite(VGAController.PIN_VERTICAL_SYNC, VGAController.VGA_VERTICAL_SYNC);
}