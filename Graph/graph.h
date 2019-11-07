#ifndef GRAPHOBJ_H
#define GRAPHOBJ_H

#define GRAPH_WIDTH 63
#define GRAPH_HEIGHT 63

struct Window {
	float xMin;
	float xMax;
	float yMin;
	float yMax;
};

class Graph {
	public:
		void begin();
		
		void recalculate(const Function function);
		void draw();
		
		uint8_t graphToScreenX(float x);
		uint8_t graphToScreenY(float y);
		
		Window window;
	private:
		float data[GRAPH_WIDTH];
};

#endif
