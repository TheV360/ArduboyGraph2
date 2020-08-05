#pragma once

class Cursor {
	public:
		int8_t x;
		int8_t y;
		
		void toggleVisibility();
		void move(const uint8_t newX, const uint8_t newY);
};
