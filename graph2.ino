#include "extend.h"
#include "GraphFont/GraphFont.cpp"
#include <Tinyfont.h>

Arduboy2Ex ab;
GraphFont gf = GraphFont(ab.sBuffer, Arduboy2::width(), Arduboy2::height());
Tinyfont tf = Tinyfont(ab.sBuffer, Arduboy2::width(), Arduboy2::height());

#include "StackArray/StackArray.h"

// I'm a heathen and I use the arduboy class in my classes.

#include "Keypad/keypad.cpp"
Keypad keypad;

#include "Function/function.cpp"
Function function;

#include "Graph/graph.cpp"
Graph graph;

uint8_t state = 0;

uint8_t cursor = 0;
bool toTheTokens = false;

void setup() {
	ab.begin();
	
	Serial.begin(800);
	
	graph.begin();
	
	if (!function.getFunction(F("2x^2+5x+2"))) {
		function.constants[0] = 2.0f;
		function.constants[1] = 5.0f;
		
		function.function[0] = TOKEN_VAR;
		function.function[1] = 0;
		function.function[2] = TOKEN_POW;
		function.function[3] = 0;
		function.function[4] = TOKEN_MUL;
		function.function[5] = 1;
		function.function[6] = TOKEN_VAR;
		function.function[7] = TOKEN_MUL;
		function.function[8] = TOKEN_ADD;
		function.function[9] = TOKEN_NOP;
	}
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
			graph.recalculate(function);
			
			graph.draw();
			ab.display();
			for (;;) {
				if (!ab.nextFrame()) continue;
				ab.pollButtons();
				if (ab.justPressed(B_BUTTON)) break;
				ab.display(); // emu gets angry when this not present!!!
			}
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
		
	}
	
	ab.display();
}
