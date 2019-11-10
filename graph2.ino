#include "extend.h"
#include "GraphFont/GraphFont.cpp"

Arduboy2Ex ab;
GraphFont gf = GraphFont(ab.sBuffer, Arduboy2::width(), Arduboy2::height());

#include "StackArray/StackArray.h"

// I'm a heathen and I use the arduboy class in my classes.
#include "Keypad/keypad.cpp"
#include "Function/function.cpp"
#include "Graph/graph.cpp"

Keypad keypad;
Function function;
Graph graph;

uint8_t state = 1;

uint8_t cursor = 0;
bool toTheTokens = false;

char funcText[32] = "2*x^2+5*x";

void setup() {
	ab.begin();
	
	Serial.begin(9600);
	
	ab.ditherScreen();
	ab.display();
	ab.clear();
	
	function.getFunction(funcText);
	graph.draw(function);
}

void loop() {
	if (!ab.nextFrame()) return;
	ab.pollButtons();
	
	if (state == 0) {
		ab.clear();
		
		if (ab.justPressed(UP_BUTTON   ) && cursor > 0) cursor--;
		if (ab.justPressed(DOWN_BUTTON )) cursor++;
		if (ab.justPressed(LEFT_BUTTON )) toTheTokens = false;
		if (ab.justPressed(RIGHT_BUTTON)) toTheTokens = true;
		
		if (ab.justPressed(A_BUTTON)) {
			if (toTheTokens) {
				function.function[cursor] = (uint8_t)keypad.lazyNumberEntry((float)function.function[cursor], 0);
			} else {
				function.constants[cursor] = keypad.lazyNumberEntry(function.constants[cursor], 3);
			}
		}
		if (ab.justPressed(B_BUTTON)) {
			state = 1;
		}
		
		for (uint8_t i = 0; i < 8; i++) {
			gf.setCursor(0, i * 7);
			gf.print(function.constants[i]);
			
			gf.setCursor(64, i * 7);
			gf.print(function.function[i], HEX);
		}
		
		gf.setCursor(32, cursor*7);
		gf.print(toTheTokens ? '>' : '<');
	} else if (state == 1) {
		ab.fillRect(64, 0, 64, 64, BLACK);
		
		if (ab.justPressed(UP_BUTTON) && cursor >= 2) cursor -= 2;
		if (ab.justPressed(DOWN_BUTTON) && cursor <= 3) cursor += 2;
		if (ab.justPressed(LEFT_BUTTON) && cursor > 0) cursor--;
		if (ab.justPressed(RIGHT_BUTTON) && cursor < 6) cursor++;
		
		if (ab.justPressed(A_BUTTON)) {
			switch (cursor) {
				case 0:
					do {keypad.lazyFunctionEntry(funcText);} while (!function.getFunction(funcText));
					ab.ditherScreen();
					ab.display();
					ab.clear();
					graph.draw(function);
					break;
				case 1:
					state = 2;
					break;
				case 6:
					state = 0;
					break;
			}
			cursor = 0;
		}
		
		ab.drawFastHLine(65, 0, 63);
		ab.drawFastHLine(64, 1, 64);
		ab.drawFastHLine(65, 63, 63);
		
		for (uint8_t i = 0; i < 2; i++) {
			ab.drawFastVLine(64 + i * 32, 2, 61);
		}
		for (uint8_t j = 0; j <= 3; j++) {
			ab.drawFastHLine(64, 2 + j * 20, 64);
		}
		
		gf.setCursor(66, 4);
		gf.print(F("Function"));
		gf.setCursor(98, 4);
		gf.print(F("Window"));
		gf.setCursor(66, 24);
		gf.print(F("Table"));
		gf.setCursor(98, 24);
		gf.print(F("Trace"));
		gf.setCursor(66, 44);
		gf.print(F("Direct"));
		gf.setCursor(98, 44);
		gf.print(F("Tools"));
		
		ab.drawFastHLine(65 + (cursor % 2) * 32, 2 + (cursor / 2) * 20, 31, BLACK);
		ab.drawFastHLine(65 + (cursor % 2) * 32, 22 + (cursor / 2) * 20, 31, BLACK);
		ab.drawFastHLine(65 + (cursor % 2) * 32, 1 + (cursor / 2) * 20, 32);
		ab.drawFastHLine(65 + (cursor % 2) * 32, 23 + (cursor / 2) * 20, 32);
	} else if (state == 2) {
		ab.fillRect(64, 0, 64, 64, BLACK);
		
		if (ab.justPressed(UP_BUTTON) && cursor > 0) cursor--;
		if (ab.justPressed(DOWN_BUTTON) && cursor < 3) cursor++;
		
		if (ab.justPressed(A_BUTTON)) {
			switch (cursor) {
				case 0:
					graph.window.xMin = keypad.lazyNumberEntry(graph.window.xMin, 3);
					break;
				case 1:
					graph.window.xMax = keypad.lazyNumberEntry(graph.window.xMax, 3);
					break;
				case 2:
					graph.window.yMin = keypad.lazyNumberEntry(graph.window.yMin, 3);
					break;
				case 3:
					graph.window.yMax = keypad.lazyNumberEntry(graph.window.yMax, 3);
					break;
			}
		}
		if (ab.justPressed(B_BUTTON)) {
			ab.ditherScreen();
			ab.display();
			ab.clear();
			graph.draw(function);
			state = 1;
			cursor = 0;
		}
		
		gf.setCursor(72, 4);
		gf.println(F("x min"));
		gf.println(graph.window.xMin, 3);
		gf.println(F("x max"));
		gf.println(graph.window.xMax, 3);
		gf.println(F("y min"));
		gf.println(graph.window.yMin, 3);
		gf.println(F("y max"));
		gf.println(graph.window.yMax, 3);
		
		gf.setCursor(66, 4 + cursor * 14);
		gf.print('>');
	}
	
	ab.display();
}
