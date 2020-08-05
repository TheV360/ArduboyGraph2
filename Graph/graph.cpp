#include "graph.h"

void Graph::draw(const Function function) {
	// Draw axis lines.
	ab.drawFastVLine(graphToScreenX(0), 0, height);
	ab.drawFastHLine(0, graphToScreenY(0), width);
	
	// Draw notches on those lines.
	// TODO: it seems this might not be a good solution for graphing large graphs, as it works in graph space rather than screen space.
	// 		I think this was fixed in the previous solution. Why didn't I keep that?
	
	// float lastNotch = ;
	// for (uint8_t i = 0; i < width; i++) {
	// 	ab.drawFastVLine(i, graphToScreenY(0) - 1, 3);
	// }
	// for (uint8_t i = 0; i < height; i++) {
	// 	ab.drawFastHLine(graphToScreenX(0) - 1, i, 3);
	// }
	
	if (window.yMin < 0.0f && window.yMax > 0.0f) {
		for (float i = round(window.xMin); i <= round(window.xMax); i += 1.0f) {
			ab.drawFastVLine(graphToScreenX(i), graphToScreenY(0) - 1, 2);
		}
	}
	if (window.xMin < 0.0f && window.xMax > 0.0f) {
		for (float i = round(window.yMin); i <= round(window.yMax); i += 1.0f) {
			ab.drawFastHLine(graphToScreenX(0), graphToScreenY(i), 2);
		}
	}
	
	float tmp;
	
	// TODO: this is a hack solution. Check formula before you even call draw?
	
	ErrorType currentError = function.calculate(screenToGraphX(0), tmp);
	if (!ignorableError(currentError)) {
		lazierShowError(currentError);
		return;
	}
	
	ErrorType prevError;
	int8_t prevY;
	int8_t currentY = graphToScreenY(tmp);
	
	for (uint8_t i = 1; i < width; i++) {
		prevError = currentError;
		prevY = currentY;
		
		currentError = function.calculate(screenToGraphX(i), tmp);
		currentY = graphToScreenY(tmp);
		
		// Only draw if current point is okay to draw.
		if (currentError == ErrorType::OK) {
			if (prevError == ErrorType::OK) {
				// If the previous result didn't have any problem
				// then plot a line from the previous point to this one.
				ab.drawLine(i - 1, prevY, i, currentY);
			} else {
				// Otherwise, just draw this point.
				ab.drawPixel(i, currentY);
				// Note: this may draw the same pixel twice, once with drawPixel, then again with drawLine.
			}
		}
	}
}

// Maps graph coordinates to screen coordinates.
int8_t Graph::graphToScreenX(const float x) {
	return keepReasonable(invLerp(window.xMin, window.xMax, x) * (float)(width - 1));
}
int8_t Graph::graphToScreenY(const float y) {
	return keepReasonable(invLerp(window.yMax, window.yMin, y) * (float)(height - 1));
}

// Maps screen coordinates to graph coordinates.
float Graph::screenToGraphX(const int8_t x) {
	return lerp(window.xMin, window.xMax, x / (float)(width - 1));
}
float Graph::screenToGraphY(const int8_t y) {
	return lerp(window.yMax, window.yMin, y / (float)(height - 1));
}

// STATIC

// Clamps the float to the range [-128, 127] to use with displaying its data.
int8_t Graph::keepReasonable(const float n) {
	if (n >= 127.0f)
		return 127;
	else if (n <= -128.0f)
		return -128;
	else
		return (int8_t)round(n);
}

// Utility functions.
float Graph::lerp(const float a, const float b, const float p) {
	return (1 - p) * a + p * b;
}
float Graph::invLerp(const float a, const float b, const float p) {
	return (p - a) / (b - a);
}
