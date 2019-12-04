#pragma once

#define TABLE_HEIGHT 5

class Table {
	public:
		float table[2][TABLE_HEIGHT];
		
		float position;
		float deltaX;
		
		void reset();
		void calculate(const Function function);
		
		void scrollUp(const Function function);
		void scrollDown(const Function function);
		
		void draw();
};
