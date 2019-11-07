#include "graph.h"

void Graph::begin() {
	window.xMin = -10.0f;
	window.xMax = +10.0f;
	window.yMin = -10.0f;
	window.yMax = -10.0f;
}

void Graph::recalculate(const Function function) {
	for (uint8_t i = 0; i < GRAPH_WIDTH; i++) {
		data[i] = function.calculate(
			lerp(
				window.xMin,
				window.xMax,
				i / (float)(GRAPH_WIDTH - 1)
			)
		);
	}
	Serial.println(
		lerp(
			window.xMin,
			window.xMax,
			(GRAPH_WIDTH/4) / (float)(GRAPH_WIDTH - 1)
		)
	);
	Serial.println(data[GRAPH_WIDTH/4]);
}

void Graph::draw() {
	// uint8_t tmp = graphToScreenY(data[0]);
	// for (uint8_t i = 1; i < GRAPH_WIDTH; i++) {
	// 	ab.drawLine(i - 1, tmp, i, tmp = graphToScreenY(data[i]));
	// }
	for (uint8_t i = 1; i < GRAPH_WIDTH; i++) {
		ab.drawLine(i - 1, data[i - 1], i, data[i]);
	}
	Serial.println(data[32]);
}

uint8_t Graph::graphToScreenX(float x) {
	return round((+x - window.xMin) / (window.xMax - window.xMin) * GRAPH_WIDTH);
}

uint8_t Graph::graphToScreenY(float y) {
	return round((-y - window.yMin) / (window.yMax - window.yMin) * GRAPH_HEIGHT);
}
