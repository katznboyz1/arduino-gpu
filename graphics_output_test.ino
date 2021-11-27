/*
    I got my instructions on how to make the GPU from this video: https://youtu.be/l7rce6IQDWs
    Signal timings are from http://tinyvga.com/vga-timing
    https://tomverbeure.github.io/video_timings_calculator (400x300)
*/

#include <Arduino.h>
#include "TimerHelpers.h"

using namespace std;

struct VGA_400x300 {
    const int PIN_RED = 8;
    const int PIN_GREEN = 9;
    const int PIN_BLUE = 10;

    const int PIN_HORIZONTAL_SYNC = 11;
    const int PIN_VERTICAL_SYNC = 12;

    // x, y, hz
    const int OUTPUT_RESOLUTION[3] = {400, 300, 60};
    const int OUTPUT_RESOLUTION_TOTAL[2] = {496, 324};

    // min, max
    const int OUTPUT_MIN_MAX_ANALOG_SIGNAL = 255;

    const double VERTICAL_SYNC_kHz = 19.153;
    const double VERTICAL_SYNC_Hz = 59.115;

    volatile int x, y = 0;
    volatile int r, g, b = 1;
};

VGA_400x300 VGAController;

void setup() {

    Serial.begin(9600);

    pinMode(VGAController.PIN_RED, OUTPUT);
    pinMode(VGAController.PIN_GREEN, OUTPUT);
    pinMode(VGAController.PIN_BLUE, OUTPUT);
    pinMode(VGAController.PIN_HORIZONTAL_SYNC, OUTPUT);
    pinMode(VGAController.PIN_VERTICAL_SYNC, OUTPUT);
}

void loop() {

    analogWrite(VGAController.PIN_RED, VGAController.OUTPUT_MIN_MAX_ANALOG_SIGNAL * VGAController.r);
    analogWrite(VGAController.PIN_GREEN, VGAController.OUTPUT_MIN_MAX_ANALOG_SIGNAL * VGAController.g);
    analogWrite(VGAController.PIN_BLUE, VGAController.OUTPUT_MIN_MAX_ANALOG_SIGNAL * VGAController.b);
}