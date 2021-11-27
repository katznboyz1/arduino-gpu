/*
    I got my instructions on how to make the GPU from this video: https://youtu.be/l7rce6IQDWs
    Signal timings are from http://tinyvga.com/vga-timing
    https://tomverbeure.github.io/video_timings_calculator (400x300)
    https://forum.arduino.cc/t/turn-your-uno-into-a-vga-output-device/99969/63?page=4
*/

#include <Arduino.h>

using namespace std;

struct VGA_400x300 {
    const byte PIN_RED = 8;
    const byte PIN_GREEN = 9;
    const byte PIN_BLUE = 10;

    const byte PIN_HORIZONTAL_SYNC = 11;
    const byte PIN_VERTICAL_SYNC = 12;

    // x, y, hz
    const int16_t OUTPUT_RESOLUTION[3] = {400, 300, 60};
    const int16_t OUTPUT_RESOLUTION_TOTAL[2] = {496, 324};

    // min, max
    const int OUTPUT_MIN_MAX_ANALOG_SIGNAL = 255;

    const double VERTICAL_SYNC_kHz = 19.153;
    const double VERTICAL_SYNC_Hz = 59.115;

    volatile int16_t x, y = 0;

    bool is_initialized = false;
};

VGA_400x300 VGAController;

ISR(TIMER2_OVF_vect) {

    sei();
    __asm__("sleep \n");
}

void setup() {

    Serial.begin(9600);

    pinMode(VGAController.PIN_RED, OUTPUT);
    pinMode(VGAController.PIN_GREEN, OUTPUT);
    pinMode(VGAController.PIN_BLUE, OUTPUT);
    pinMode(VGAController.PIN_HORIZONTAL_SYNC, OUTPUT);
    pinMode(VGAController.PIN_VERTICAL_SYNC, OUTPUT);

    digitalWrite(VGAController.PIN_RED, LOW);
    digitalWrite(VGAController.PIN_GREEN, LOW);
    digitalWrite(VGAController.PIN_BLUE, LOW);
    digitalWrite(VGAController.PIN_HORIZONTAL_SYNC, LOW);
    digitalWrite(VGAController.PIN_VERTICAL_SYNC, LOW);

    VGAController.is_initialized = true;
}

void loop() {

    digitalWrite(VGAController.PIN_HORIZONTAL_SYNC, HIGH);

    for (register int i = 0; i < VGAController.OUTPUT_RESOLUTION[0]; i++) {

        // these numbers mean nothing, I just chose them randomly to test
        digitalWrite(VGAController.PIN_RED, HIGH);
        digitalWrite(VGAController.PIN_GREEN, HIGH);
        digitalWrite(VGAController.PIN_BLUE, HIGH);
        delayMicroseconds(10);
        digitalWrite(VGAController.PIN_RED, LOW);
        digitalWrite(VGAController.PIN_GREEN, LOW);
        digitalWrite(VGAController.PIN_BLUE, LOW);
        delayMicroseconds(10);
        digitalWrite(VGAController.PIN_HORIZONTAL_SYNC, HIGH);
        delayMicroseconds(4);
        digitalWrite(VGAController.PIN_HORIZONTAL_SYNC, LOW);
    }

    digitalWrite(VGAController.PIN_HORIZONTAL_SYNC, HIGH);
}