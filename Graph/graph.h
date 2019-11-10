#pragma once

struct Window {
	float xMin;
	float xMax;
	float yMin;
	float yMax;
};

class Graph {
	public:
		void draw(const Function function);
		
		int8_t graphToScreenX(const float x);
		int8_t graphToScreenY(const float y);
		
		float screenToGraphX(const int8_t x);
		float screenToGraphY(const int8_t y);
		
		Window window = {-10.0f, 10.0f, -10.0f, 10.0f};
	private:
		// float data[GRAPH_WIDTH];
		
		uint8_t width = 63;
		uint8_t height = 63;
		
		static int8_t keepReasonable(const float n);
		static float lerp(const float a, const float b, const float p);
		static float invLerp(const float a, const float b, const float p);
};
