#ifndef KEYPADOBJ_H
#define KEYPADOBJ_H

#define KEYPAD_K_0 0x00
#define KEYPAD_K_1 0x01
#define KEYPAD_K_2 0x02
#define KEYPAD_K_3 0x03
#define KEYPAD_K_4 0x04
#define KEYPAD_K_5 0x05
#define KEYPAD_K_6 0x06
#define KEYPAD_K_7 0x07
#define KEYPAD_K_8 0x08
#define KEYPAD_K_9 0x09
#define KEYPAD_K_DECIMAL 0x10
#define KEYPAD_K_SIGN 0x11
#define KEYPAD_K_LPAREN 0x12
#define KEYPAD_K_RPAREN 0x13
#define KEYPAD_K_ADDITION 0x14
#define KEYPAD_K_SUBTRACT 0x15
#define KEYPAD_K_MULTIPLY 0x16
#define KEYPAD_K_DIVISION 0x17
#define KEYPAD_K_DELETE 0xFD
#define KEYPAD_K_CLEAR 0xFE
#define KEYPAD_K_OK 0xFF

struct KeypadLayout {
	uint8_t width;
	uint8_t height;
	uint8_t labels[];
};

const KeypadLayout KEYPAD_LAYOUT_NUMBER[] PROGMEM = {
	3, 5,
	{
		KEYPAD_K_OK, KEYPAD_K_DELETE , KEYPAD_K_CLEAR,
		KEYPAD_K_7 , KEYPAD_K_8      , KEYPAD_K_9    ,
		KEYPAD_K_4 , KEYPAD_K_5      , KEYPAD_K_6    ,
		KEYPAD_K_1 , KEYPAD_K_2      , KEYPAD_K_3    ,
		KEYPAD_K_0 , KEYPAD_K_DECIMAL, KEYPAD_K_SIGN ,
	}
};

const KeypadLayout KEYPAD_LAYOUT_FUNCTION[] PROGMEM = {
	5, 5,
	{
		KEYPAD_K_LPAREN, KEYPAD_K_RPAREN  , KEYPAD_K_OK, KEYPAD_K_DELETE , KEYPAD_K_CLEAR,
		KEYPAD_K_LPAREN, KEYPAD_K_DIVISION, KEYPAD_K_7 , KEYPAD_K_8      , KEYPAD_K_9    ,
		KEYPAD_K_LPAREN, KEYPAD_K_MULTIPLY, KEYPAD_K_4 , KEYPAD_K_5      , KEYPAD_K_6    ,
		KEYPAD_K_LPAREN, KEYPAD_K_SUBTRACT, KEYPAD_K_1 , KEYPAD_K_2      , KEYPAD_K_3    ,
		KEYPAD_K_LPAREN, KEYPAD_K_ADDITION, KEYPAD_K_0 , KEYPAD_K_DECIMAL, KEYPAD_K_SIGN ,
	}
};

const KeypadLayout* const KEYPAD_LAYOUTS[] PROGMEM = {
	KEYPAD_LAYOUT_NUMBER, KEYPAD_LAYOUT_FUNCTION
};

class Keypad {
	public:
		void begin(const char* function);
		void begin(const float number, const uint8_t digits);
		
		void lazyFunctionEntry(char* function);
		float lazyNumberEntry(const float number, const uint8_t digits);
		
		void update();
		void draw();
		
		void getValue(char* function);
		float getValue();
		
		bool isSubmitted();
		
		uint8_t x = 12;
		uint8_t y = 12;
		
	private:
		void setLayout(const uint8_t index);
		uint8_t getLayoutKey(const uint8_t x, const uint8_t y);
		
		
		uint8_t layout;
		
		void press();
		
		void backspace();
		void clear();
		
		uint8_t cursor;
		
		char text[32];
		uint8_t textLen;
		
		uint8_t width = 3;
		uint8_t height = 5;
		
		bool submitted = false;
};

#endif
