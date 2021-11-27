#include "VGAX.h"

VGAX vga;

void setup() {

    //Serial.begin(9600);

    vga.begin();
    vga.clear(11);
}

void loop() {

	// dont clear the framebuffer, we will only do this when needed
	//vga.clear(10);
	
	for (register byte y = 0; y != VGAX_HEIGHT; y++) {

		for (register byte x = 0; x != VGAX_WIDTH; x++) {

			register byte color = 10;

			if ((y % (byte)(VGAX_HEIGHT / 4)) == 0 || (x % (byte)(VGAX_WIDTH / 4)) == 0) color = 01;

			vga.putpixel(x, y, color);
		}
	}

	vga.delay(17);
}