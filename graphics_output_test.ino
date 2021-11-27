/*
    I got my instructions on how to make the GPU from this video: https://youtu.be/l7rce6IQDWs
    Signal timings are from http://tinyvga.com/vga-timing
    https://tomverbeure.github.io/video_timings_calculator (400x300)
    https://forum.arduino.cc/t/turn-your-uno-into-a-vga-output-device/99969/63?page=4
*/

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

using namespace std;

struct VGA_400x300 {
    const byte PIN_RED = A0;
    const byte PIN_GREEN = A1;
    const byte PIN_BLUE = A2;

    const byte PIN_HORIZONTAL_SYNC = 3;
    const byte PIN_VERTICAL_SYNC = 9;

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
volatile byte *vga_buffer = new byte[VGAController.OUTPUT_RESOLUTION[0] * VGAController.OUTPUT_RESOLUTION[1]];

void setup() {

    Serial.begin(9600);

    TIMSK0 = 0;
    TCCR0A = 0;
    TCCR0B = (1 << CS00);
    OCR0A = 0;
    OCR0B = 0;
    TCNT0 = 0;

    pinMode(VGAController.PIN_RED, OUTPUT);
    pinMode(VGAController.PIN_GREEN, OUTPUT);
    pinMode(VGAController.PIN_BLUE, OUTPUT);
    pinMode(VGAController.PIN_HORIZONTAL_SYNC, OUTPUT);
    pinMode(VGAController.PIN_VERTICAL_SYNC, OUTPUT);

    TCCR2A = bit(WGM20) | bit(WGM21) | bit(COM2B1); //pin3=COM2B1
    TCCR2B = bit(WGM22) | bit(CS21); //8 prescaler
    OCR2A = 63; // 32 / 0.5 uS=64 (minus one)
    OCR2B = 7; // 4 / 0.5 uS=8 (minus one)
    TIFR2 = bit(OCF2B); // clear Compare Match B flag
    TIMSK2 = bit(OCIE2B); // enable Compare Match B interrupt

    VGAController.is_initialized = true;

    sei();
}

ISR(TIMER2_COMPB_vect) {

    register byte r, g, b = 0;

    VGAController.y++;
    if (VGAController.y > VGAController.OUTPUT_RESOLUTION_TOTAL[1]) VGAController.y = 0;

    // output 8 pixels 50 times (8*50=400=width)
    // honestly I have no idea what this does, I'll have to research more into assembly
    asm volatile(
        ".rept 50\n"
        "   ld r16, Z+\n"
        "   out %[port], r16\n"
        "   lsl r16\n"
        "   out %[port], r16\n"
        "   lsl r16\n"
        "   out %[port], r16\n"
        "   lsl r16\n"
        "   out %[port], r16\n"
        "   lsl r16\n"
        "   out %[port], r16\n"
        "   lsl r16\n"
        "   out %[port], r16\n"
        "   lsl r16\n"
        "   out %[port], r16\n"
        "   lsl r16\n"
        "   out %[port], r16\n"
        ".endr"
        :
        : [port] "I" (_SFR_IO_ADDR(PORTD)),
        "z" "I" ((byte*)vga_buffer + VGAController.y * 50)
        : "r16", "memory"
    );
}

void loop() {}