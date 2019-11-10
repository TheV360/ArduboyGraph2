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
	
	graph.begin();
	
	function.getFunction(funcText);
}

void loop() {
	if (!ab.nextFrame()) return;
	ab.pollButtons();
	
	ab.clear();
	
	if (state == 0) {
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
		if (ab.justPressed(UP_BUTTON) && cursor > 0) cursor--;
		if (ab.justPressed(DOWN_BUTTON) && cursor < 2) cursor++;
		
		if (ab.justPressed(A_BUTTON)) {
			switch (cursor) {
				case 0:
					do {keypad.lazyFunctionEntry(funcText);} while (!function.getFunction(funcText));
					break;
				case 1:
					graph.draw(function);
					ab.display();
					for (;;) {
						if (!ab.nextFrame()) continue;
						ab.pollButtons();
						if (ab.justPressed(B_BUTTON)) break;
						ab.display();
					}
					break;
				case 2:
					state = 0;
					cursor = 0;
					toTheTokens = false;
					break;
			}
		}
		
		gf.setCursor(8, 0);
		gf.println(F("Set function"));
		gf.println(F("See graph"));
		gf.println(F("See RPN debug"));
		gf.setCursor(0, cursor * 7);
		gf.print('>');
	}
	
	ab.display();
}
