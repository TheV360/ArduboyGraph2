#include "function.h"

float Function::calculate(const float x = 0.0f) {
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
			} else if (function[i] == TOKEN_POW) {
				stack.push(pow(stack.pop(), stack.pop()));
			} else if (function[i] == TOKEN_MOD) {
				// stack.push(stack.pop() % stack.pop());
			} else if (function[i] == TOKEN_VAR) {
				stack.push(x);
			} else if (function[i] == TOKEN_NEG) {
				stack.push(-stack.pop());
			} else {
				break;
			}
		}
	}
	
	return stack.pop();
}

void Function::getFunction(const char* input) {
	return;
	/*
	uint8_t inputLen = 0;
	while (input[++inputLen] != '\0');
	
	uint8_t prevToken = TOKEN_NOP;
	uint8_t token;
	char* endOfNumber;
	
	StackArray<uint8_t> operators;
	
	uint8_t outputFIndex = 0;
	uint8_t outputCIndex = 0;
	
	for (uint8_t i = 0; i < inputLen; i++) {
		prevToken = token;
		token = getToken(input[i]);
		
		// Encountering a number:
		function[outputFIndex] = outputCIndex;
		constants[outputCIndex++] = strtod(input + i, endOfNumber);
		if (input + i == endOfNumber) continue;
		i = endOfNumber - input - 1;
	}
	*/
}

uint8_t Function::getToken(const char input) {
	switch (input) {
		case '+': return TOKEN_ADD;
		case '-': return TOKEN_SUB;
		case '*': return TOKEN_MUL;
		case '/': return TOKEN_DIV;
		case '^': return TOKEN_POW;
		case 'x': return TOKEN_VAR;
		case '\0':return TOKEN_NOP;
	}
}
