#ifndef GRAPHOBJ_H
#define GRAPHOBJ_H

#define GRAPH_WIDTH 63
#define GRAPH_HEIGHT 63

#define GRAPH_SHOULD_STORE
// todo: make this do something other than make errors if removed

#define GRAPH_MAX_DASH 32

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
		
		int8_t graphToScreenX(const float x);
		int8_t graphToScreenY(const float y);
		
		float screenToGraphX(const int8_t x);
		float screenToGraphY(const int8_t y);
		
		Window window;
	private:
#ifdef GRAPH_SHOULD_STORE
		float data[GRAPH_WIDTH];
#endif
		
		static int8_t keepReasonable(const float n);
		static float lerp(const float a, const float b, const float p);
};

#endif
