#include <Arduboy2.h>

class Arduboy2Ex : public Arduboy2Base {
public:
	Arduboy2Ex() : Arduboy2Base() {};
	
	bool buttonDown(uint8_t button) {
		// Should've had this in it by default
		return (currentButtonState & button);
	};
	bool allButtonsDown(uint8_t button) {
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
};
