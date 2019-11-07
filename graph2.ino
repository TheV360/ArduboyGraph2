#include "extend.h"
#include "GraphFont/GraphFont.cpp"
#include <Tinyfont.h>

Arduboy2Ex ab;
GraphFont gf = GraphFont(ab.sBuffer, Arduboy2::width(), Arduboy2::height());
Tinyfont tf = Tinyfont(ab.sBuffer, Arduboy2::width(), Arduboy2::height());

#include "StackArray/StackArray.h"

// I'm a heathen and I use the arduboy class in my classes.

float lerp(float a, float b, float p) {
	return a + (b - a) * p;
}

#include "Keypad/keypad.cpp"
#include "Function/function.cpp"

Keypad keypad;
Function function;

#include "Graph/graph.cpp"
Graph graph;

uint8_t h = 0;
float res;

uint8_t cursor = 0;
bool toTheTokens = false;

void setup() {
	ab.begin();
	
	Serial.begin(800);
	
	graph.begin();
	
	function.constants[0] = 2.0f;
	function.function[0] = 0xFE;
	function.function[1] = 0xFE;
	function.function[2] = 0x82;
	function.function[3] = 0xFF;
}

void loop() {
	if (!ab.nextFrame()) return;
	ab.pollButtons();
	
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
		// res = function.calculate(keypad.lazyNumberEntry(0.0f, 2));
		graph.recalculate(function);
		
		while (!ab.justPressed(A_BUTTON)) {
			if (!ab.nextFrame()) continue;
			ab.pollButtons();
			ab.clear();
			graph.draw();
			ab.display();
		}
	}
	
	for (uint8_t i = 0; i < 6; i++) {
		gf.setCursor(0, i * 7);
		gf.print(function.constants[i]);
		
		gf.setCursor(64, i * 7);
		gf.print(function.function[i], HEX);
	}
	
	gf.setCursor(32, 0);
	gf.print(res);
	
	gf.setCursor(32, cursor*7);
	gf.print(toTheTokens ? '>' : '<');
	
	ab.display();
}
