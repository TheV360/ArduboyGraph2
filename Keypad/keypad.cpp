#include "keypad.h"

void Keypad::begin(const float number = 0.0f, const uint8_t digits = 2) {
	// Reset submission status.
	submitted = false;
	
	// Clear existing text, if any.
	while (textLen > 0) text[textLen--] = '\0';
	
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
			gf.setCursor(x + i*10 + 2, y + j*10 + 2);
			gf.print((char)pgm_read_byte(KEYPAD_LABELS + i + j*width));
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

// Get value after everything is said and done.
float Keypad::getValue() {
	return atof(text);
}

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
			while (textLen) text[--textLen] = '\0';
			break;
		default:
			text[textLen++] = (char)pgm_read_byte(KEYPAD_LABELS + cursor);
			break;
	}
}

// And when you backspace
void Keypad::backspace() {
	if (textLen) text[--textLen] = '\0';
}
