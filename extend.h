#include <Arduboy2.h>

#define DITHER 0b01010101
#define STRIPES 0b011001100

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
		
		if (color == BLACK) {
			for (uint8_t i = 0; i < w; i++) {
				for (uint8_t j = 0; j < h; j++) {
					sBuffer[x + i + (y + j)*WIDTH] = 0;
				}
			}
		} else if (color == WHITE) {
			for (uint8_t i = 0; i < w; i++) {
				for (uint8_t j = 0; j < h; j++) {
					sBuffer[x + i + (y + j)*WIDTH] = 0xff;
				}
			}
		} else if (color == INVERT) {
			for (uint8_t i = 0; i < w; i++) {
				for (uint8_t j = 0; j < h; j++) {
					sBuffer[x + i + (y + j)*WIDTH] ^= 0xff;
				}
			}
		} else if (color == DITHER) {
			for (uint8_t i = 0; i < w; i++) {
				for (uint8_t j = 0; j < h; j++) {
					sBuffer[x + i + (y + j)*WIDTH] = color;
				}
				color = ~color;
			}
		} else {
			for (uint8_t i = 0; i < w; i++) {
				for (uint8_t j = 0; j < h; j++) {
					sBuffer[x + i + (y + j)*WIDTH] &= color;
				}
				color = (color << 1) | (color >> 7);
			}
		}
	};
	
	// Modified slightly from https://mlxxxp.github.io/documents/Arduino/libraries/Arduboy2/Doxygen/html/Arduboy2_8cpp_source.html#l00554
	void drawFastHLine2(int16_t x, int16_t y, uint8_t w, uint8_t color) {
		int16_t xEnd; // last x point + 1
		
		// Do y bounds checks
		if (y < 0 || y >= HEIGHT)
			return;
		
		xEnd = x + w;
		
		// Check if the entire line is not on the display
		if (xEnd <= 0 || x >= WIDTH)
			return;
		
		// Don't start before the left edge
		if (x < 0)
			x = 0;
		
		// Don't end past the right edge
		if (xEnd > WIDTH)
			xEnd = WIDTH;
		
		// calculate actual width (even if unchanged)
		w = xEnd - x;
		
		// buffer pointer plus row offset + x offset
		register uint8_t *pBuf = sBuffer + ((y / 8) * WIDTH) + x;
		
		// pixel mask
		register uint8_t mask = 1 << (y & 7);
		
		switch (color)
		{
			case WHITE:
				while (w--)
				{
					*pBuf++ |= mask;
				}
				break;
			
			case BLACK:
				mask = ~mask;
				while (w--)
				{
					*pBuf++ &= mask;
				}
				break;
			
			case INVERT:
				while (w--)
				{
					*pBuf++ ^= mask;
				}
				break;
		}
	};
};
