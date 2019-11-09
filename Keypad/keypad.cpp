#include "keypad.h"

void Keypad::begin(const char* function = NULL) {
	// Set function mode.
	setLayout(1);
	
	// Reset submission status.
	submitted = false;
	
	// Clear existing text, if any.
	clear();
	
	// Copy string
	if (function) strcpy(text, function);
}

void Keypad::begin(const float number = 0.0f, const uint8_t digits = 2) {
	// Set number mode.
	setLayout(0);
	
	// Reset submission status.
	submitted = false;
	
	// Clear existing text, if any.
	clear();
	
	// Get string from number.
	dtostrf(number, 0, digits, text);
	// Get length.
	while (text[++textLen] != '\0');
}

// The lazy way to do things.
// Entirely takes over the loop. Don't use?
float Keypad::lazyNumberEntry(const float number = 0.0f, const uint8_t digits = 2) {
	begin(number, digits);
	
	while (!submitted) {
		if (!ab.nextFrame()) continue;
		ab.pollButtons();
		
		ab.clear();
		
		update();
		draw();
		
		ab.display();
	}
	
	return getValue();
}

// The lazy way to do things.
// Entirely takes over the loop. Don't use?
void Keypad::lazyFunctionEntry(char* function) {
	begin(function);
	
	while (!submitted) {
		if (!ab.nextFrame()) continue;
		ab.pollButtons();
		
		ab.clear();
		
		update();
		draw();
		
		ab.display();
	}
	
	getValue(function);
}

// The right way to do things.
void Keypad::update() {
	if (ab.justPressed(LEFT_BUTTON ) && cursor > 0) cursor--;
	if (ab.justPressed(RIGHT_BUTTON) && cursor < (width * height) - 1) cursor++;
	
	if (ab.justPressed(UP_BUTTON   ) && cursor >= width) cursor -= width;
	if (ab.justPressed(DOWN_BUTTON ) && cursor < width * (height - 1)) cursor += width;
	
	if (ab.justPressed(A_BUTTON)) press();
	if (ab.justPressed(B_BUTTON)) backspace();
}

// The right way to do things.
void Keypad::draw() {
	// Keypad portion
	for (uint8_t i = 0; i <= width; i++)  {
		ab.drawFastVLine(x + i*10, y, 51);
	}
	for (uint8_t i = 0; i <= height; i++)  {
		ab.drawFastHLine(x, y + i*10, 31);
	}
	
	// Labels (tmp)
	for (uint8_t j = 0; j < height; j++) {
		for (uint8_t i = 0; i < width; i++) {
			gf.setCursor(x + i*10 + 4, y + j*10 + 2);
			// gf.print(getKeyString(getLayoutKey(i, j)));
		}
	}
	
	// Cursor
	ab.drawRect(
		x + (cursor % 3) * 10,
		y + (cursor / 3) * 10,
		11, 11, BLACK
	);
	ab.drawRect(
		x + (cursor % 3) * 10 - 1,
		y + (cursor / 3) * 10 - 1,
		13, 13, WHITE
	);
	
	gf.setCursor(x + 2, y - 8);
	gf.print(text);
}

// Because `submitted` is private.
bool Keypad::isSubmitted() {
	return submitted;
}

// Get text
void Keypad::getValue(char* function) {
	strcpy(function, text);
}

// Get value after everything is said and done.
float Keypad::getValue() {
	return atof(text);
}

// Get layout
void Keypad::setLayout(const uint8_t index) {
	cursor = 0;
	layout = index;
	
	// KeypadLayout* kp = pgm_read_ptr(&KEYPAD_LAYOUTS[index]);
	
	// width = pgm_read_byte(kp.width);
	// height = pgm_read_byte(kp.height);
}

// Get layout key
// uint8_t Keypad::getLayoutKey(const uint8_t x, const uint8_t y) {
// 	return ;
// }

// This is what happens when you press a button.
void Keypad::press() {
	switch (cursor) {
		case 0: // OK
			submitted = true;
			text[textLen] = '\0';
			return;
		case 1: // Backspace
			backspace();
			break;
		case 2: // Bomb
			clear();
			break;
		default:
			// text[textLen++] = (char)pgm_read_byte(KEYPAD_LABELS + cursor);
			break;
	}
}

// When you backspace
void Keypad::backspace() {
	if (textLen) text[--textLen] = '\0';
}
// When you backspace

// Delete all
void Keypad::clear() {
	while (textLen) text[--textLen] = '\0';
}
