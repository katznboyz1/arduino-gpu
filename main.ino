#include "VGAX.h"

VGAX vga;

static char x= -VGAX_WIDTH;

void setup() {

    //Serial.begin(9600);

    vga.begin();
    vga.clear(11);
}

void loop() {

	if (x < 100) {vga.tone(440 + x);} else {vga.noTone();}

	vga.clear(11);
	
	x++;

	for (register uint8_t y = 0; y != VGAX_HEIGHT; y++) {

		for (register uint8_t x = 0; x != VGAX_BWIDTH; x++) {

			vga.putpixel(x, y, 1);
		}
	}

	if (x == VGAX_WIDTH) x = -VGAX_WIDTH;

	vga.delay(17);
}