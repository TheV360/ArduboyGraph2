#include "cursor.h"

void Cursor::toggleVisibility() {
	ab.fastRect(x, 0, 1, 8, INVERT);
	ab.drawFastHLine2(0, y, 62, INVERT);
}

void Cursor::move(const uint8_t newX, const uint8_t newY) {
	toggleVisibility();
	x = newX; y = newY;
	toggleVisibility();
}
