#include <Arduboy2.h>

#define DITHER 3

class Arduboy2Ex : public Arduboy2Base {
public:
	Arduboy2Ex() : Arduboy2Base() {};
	
	bool buttonDown(const uint8_t button) {
		// Should've had this in it by default
		return (currentButtonState & button);
	};
	bool allButtonsDown(const uint8_t button) {
		return (currentButtonState & button) == button;
	};
	
	// uh
	void ditherScreen() {
		uint8_t c = 0b01010101;
		for (uint16_t i = 0; i < WIDTH * HEIGHT / 8; i++) {
			sBuffer[i] &= c;
			c = ~c;
		}
	};
	
	// Using display segments
	void fastRect(const uint8_t x, const uint8_t y, const uint8_t w, const uint8_t h, uint8_t color) {
		if (x >= WIDTH || y >= HEIGHT/8) return;
		if (x + w - 1 >= WIDTH) return;
		if (y + h - 1 >= HEIGHT/8) return;
		
		if (color == DITHER) color = 0b01010101;
		
		for (uint8_t j = 0; j < h; j++) {
			for (uint8_t i = 0; i < w; i++) {
				if (color == BLACK) {
					sBuffer[x + i + (y + j)*WIDTH] = 0;
				} else if (color == WHITE) {
					sBuffer[x + i + (y + j)*WIDTH] = 0xff;
				} else if (color == INVERT) {
					sBuffer[x + i + (y + j)*WIDTH] ^= 0xff;
				} else {
					sBuffer[x + i + (y + j)*WIDTH] &= color;
					color = ~color;
				}
			}
		}
	};
};
