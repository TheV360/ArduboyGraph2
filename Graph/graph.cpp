#include "graph.h"

// void Graph::recalculate(const Function function) {
// 	for (uint8_t i = 0; i < width; i++) {
// 		data[i] = function.calculate(screenToGraphX(i));
// 	}
// }

void Graph::draw(const Function function) {
	ab.drawFastVLine(graphToScreenX(0), 0, height);
	ab.drawFastHLine(0, graphToScreenY(0), width);
	
	// float lastNotch = ;
	// for (uint8_t i = 0; i < width; i++) {
	// 	ab.drawFastVLine(i, graphToScreenY(0) - 1, 3);
	// }
	// for (uint8_t i = 0; i < height; i++) {
	// 	ab.drawFastHLine(graphToScreenX(0) - 1, i, 3);
	// }
	
	for (float i = round(window.xMin); i < round(window.xMax); i += 1.0f) {
		ab.drawFastVLine(graphToScreenX(i), graphToScreenY(0) - 1, 2);
	}
	for (float i = round(window.yMin); i < round(window.yMax); i += 1.0f) {
		ab.drawFastHLine(graphToScreenX(0), graphToScreenY(i), 2);
	}
	
	int8_t prevY;
	int8_t currentY = graphToScreenY(function.calculate(screenToGraphX(0)));
	for (uint8_t i = 1; i < width; i++) {
		prevY = currentY;
		currentY = graphToScreenY(function.calculate(screenToGraphX(i)));
		ab.drawLine(i - 1, prevY, i, currentY);
	}
}

// int8_t Graph::graphToScreenX(const float x) {
// 	return keepReasonable((x - window.xMin) / (window.xMax - window.xMin) * width);
// }
// int8_t Graph::graphToScreenY(const float y) {
// 	return keepReasonable((1.0f - ((y - window.yMin) / (window.yMax - window.yMin))) * height);
// }
int8_t Graph::graphToScreenX(const float x) {
	return keepReasonable(invLerp(window.xMin, window.xMax, x) * (float)width);
}
int8_t Graph::graphToScreenY(const float y) {
	return keepReasonable(invLerp(window.yMax, window.yMin, y) * (float)height);
}

float Graph::screenToGraphX(const int8_t x) {
	return lerp(window.xMin, window.xMax, x / (float)(width - 1));
}
float Graph::screenToGraphY(const int8_t y) {
	return lerp(window.yMax, window.yMin, y / (float)(height - 1));
}

// STATIC

int8_t Graph::keepReasonable(const float n) {
	if (n > 127.0f)
		return 127;
	else if (n < -128.0f)
		return -128;
	else
		return (int8_t)round(n);
}

float Graph::lerp(const float a, const float b, const float p) {
	return (1 - p) * a + p * b;
}
float Graph::invLerp(const float a, const float b, const float p) {
	return (p - a) / (b - a);
}
