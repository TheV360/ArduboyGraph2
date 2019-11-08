#include "graph.h"

void Graph::begin() {
	window.xMin = -10.0f;
	window.xMax = +10.0f;
	window.yMin = -10.0f;
	window.yMax = +10.0f;
}

void Graph::recalculate(const Function function) {
	for (uint8_t i = 0; i < GRAPH_WIDTH; i++) {
		data[i] = function.calculate(screenToGraphX(i));
	}
}

void Graph::draw() {
	ab.drawFastVLine(graphToScreenX(0), 0, GRAPH_HEIGHT);
	ab.drawFastHLine(0, graphToScreenY(0), GRAPH_WIDTH);
	
	for (float i = round(window.xMin); i <= round(window.xMax); i += 1.0f) {
		ab.drawFastVLine(graphToScreenX(i), graphToScreenY(0) - 1, 3);
	}
	
	for (float i = round(window.yMin); i <= round(window.yMax); i += 1.0f) {
		ab.drawFastHLine(graphToScreenX(0) - 1, graphToScreenY(i), 3);
	}
	
	int8_t tmp = graphToScreenY(data[0]);
	for (uint8_t i = 1; i < GRAPH_WIDTH - 1; i++) {
		ab.drawLine(i - 1, tmp, i, graphToScreenY(data[i]));
		tmp = graphToScreenY(data[i]);
	}
}

int8_t Graph::graphToScreenX(const float x) {
	return keepReasonable((x - window.xMin) / (window.xMax - window.xMin) * GRAPH_WIDTH);
}

int8_t Graph::graphToScreenY(const float y) {
	return keepReasonable((1.0f - ((y - window.yMin) / (window.yMax - window.yMin))) * GRAPH_HEIGHT);
}

float Graph::screenToGraphX(const int8_t x) {
	return lerp(window.xMin, window.xMax, x / (float)(GRAPH_WIDTH - 1));
}

float Graph::screenToGraphY(const int8_t y) {
	return lerp(window.yMax, window.yMin, y / (float)(GRAPH_HEIGHT - 1));
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
	return a + (b - a) * p;
}
