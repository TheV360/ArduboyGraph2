#include "table.h"

void Table::reset() {
	position = 0.0f;
	deltaX = 1.0f;
}

void Table::initSeq(const Function function) {
	for (uint8_t i = 0; i < TABLE_HEIGHT; i++) {
		table[0][i] = position + deltaX * i;
		function.calculate(table[0][i], table[1][i]);
	}
	sequential = true;
}

void Table::initDisc() {
	for (uint8_t i = 0; i < TABLE_HEIGHT; i++) {
		table[0][i] = NAN;
		table[1][i] = NAN;
	}
	sequential = false;
}

void Table::scrollUp(const Function function) {
	position -= deltaX;
	
	for (uint8_t i = TABLE_HEIGHT - 1; i > 0; i--) {
		table[0][i] = table[0][i - 1];
		table[1][i] = table[1][i - 1];
	}
	table[0][0] = position;
	function.calculate(table[0][0], table[1][0]);
}

void Table::scrollDown(const Function function) {
	position += deltaX;
	
	for (uint8_t i = 0; i < TABLE_HEIGHT - 1; i++) {
		table[0][i] = table[0][i + 1];
		table[1][i] = table[1][i + 1];
	}
	
	table[0][TABLE_HEIGHT - 1] = position + deltaX * (TABLE_HEIGHT - 1);
	function.calculate(table[0][TABLE_HEIGHT - 1], table[1][TABLE_HEIGHT - 1]);
}

void Table::draw() {
	ab.fastRect(64, 0, 32, 1, WHITE);
	ab.fastRect(97, 0, 31, 1, WHITE);
	ab.fastRect(64, 1, 1, 7, WHITE);
	
	gf.setTextColor(BLACK);
	
	gf.setCursor(65, 0);
	gf.print(F("x"));
	
	gf.setCursor(98, 0);
	gf.print(F("f(x)"));
	
	gf.setTextColor(WHITE);
	
	for (uint8_t i = 0; i < TABLE_HEIGHT; i++) {
		gf.setCursor(66, 9 + i * 9);
		gf.print(table[0][i]);
		
		if (isnan(table[1][i])) {
			ab.fillRect(97, 8 + i * 9, 31, 8);
			
			gf.setTextColor(BLACK);
			
			gf.setCursor(98, 9 + i * 9);
			gf.print(F("ERROR"));
			
			gf.setTextColor(WHITE);
		} else {
			gf.setCursor(98, 9 + i * 9);
			gf.print(table[1][i]);
		}
		
		ab.drawFastVLine(96, 8 + i * 9, 8);
		ab.drawFastHLine(64, 16 + i * 9, 64);
	}
	
	ab.drawFastHLine(64, 8 + TABLE_HEIGHT * 9, 64);
	
	gf.setCursor(66, 10 + TABLE_HEIGHT * 9);
	gf.print(F("dx="));
	gf.print(deltaX);
	
	ab.drawFastVLine(117, 54, 10);
	Icons::drawIcon(6, 119, 55);
}
