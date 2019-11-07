#ifndef KEYPADOBJ_H
#define KEYPADOBJ_H

const char KEYPAD_LABELS[] PROGMEM = {
	'k', 'e', 'd',
	'7', '8', '9',
	'4', '5', '6',
	'1', '2', '3',
	'0', '.', '-',
};

class Keypad {
	public:
		void begin(float number, uint8_t digits);
		
		float lazyNumberEntry(float number, uint8_t digits);
		
		void update();
		void draw();
		
		float getValue();
		
		uint8_t x = 12;
		uint8_t y = 12;
		
		bool isSubmitted();
		
	private:
		void press();
		void backspace();
		
		uint8_t cursor;
		
		char text[32];
		uint8_t textLen;
		
		uint8_t width = 3;
		uint8_t height = 6;
		
		bool submitted = false;
};

#endif
