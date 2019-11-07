#include "function.h"

float Function::calculate(float x = 0.0f) {
	StackArray<float> stack;
	
	for (uint8_t i = 0; i < FUNCTION_MAX_TOKENS; i++) {
		if (function[i] < TOKEN_MINIMUM) {
			stack.push(constants[function[i]]);
		} else {
			if (function[i] == TOKEN_ADD) {
				stack.push(stack.pop() + stack.pop());
			} else if (function[i] == TOKEN_SUB) {
				stack.push(stack.pop() - stack.pop());
			} else if (function[i] == TOKEN_MUL) {
				stack.push(stack.pop() * stack.pop());
			} else if (function[i] == TOKEN_DIV) {
				stack.push(stack.pop() / stack.pop());
			} else if (function[i] == TOKEN_VAR) {
				stack.push(x);
			} else {
				break;
			}
		}
	}
	
	return stack.pop();
}
