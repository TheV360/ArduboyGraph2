#include "function.h"

float Function::calculate(const float x = 0.0f) {
	StackArray<float> stack;
	
	for (uint8_t i = 0; i < FUNCTION_MAX_TOKENS; i++) {
		if (function[i] < TOKEN_OPERATOR_START) {
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
				stack.push(fmod(stack.pop(), stack.pop()));
			} else if (function[i] == TOKEN_VAR) {
				stack.push(x);
			} else if (function[i] == TOKEN_NEG) {
				stack.push(-stack.pop());
			} else {
				break;
			}
		}
	}
	
	if (stack.isEmpty()) return 0.0f;
	return stack.pop();
}

bool Function::getFunction(const char* input) {
	uint8_t inputLen = 0;
	while (input[++inputLen] != '\0');
	
	uint8_t prevToken;
	uint8_t token = TOKEN_NOP;
	char* endOfNumber;
	
	StackArray<uint8_t> operators;
	
	uint8_t outputFIndex = 0;
	uint8_t outputCIndex = 0;
	
	for (uint8_t i = 0; i < inputLen; i++) {
		prevToken = token;
		token = getToken(input[i]);
		
		if (token == TOKEN_UNKNOWN) {
			// Encountering a number:
			function[outputFIndex++] = token = outputCIndex;
			if (prevToken == TOKEN_SUB) {
				constants[outputCIndex++] = strtod(input + i - 1, &endOfNumber);
			} else {
				constants[outputCIndex++] = strtod(input + i, &endOfNumber);
			}
			if (i == endOfNumber - input) continue;
			i = endOfNumber - input - 1;
		} else if (isFunction(token)) {
			operators.push(token);
		} else if (isOperator(token)) {
			if (token == TOKEN_SUB && isOperator(prevToken) || prevToken == TOKEN_RBR) {
				token = TOKEN_NEG;
			}
			
			// Hopefully this is more readable.
			while (
				operators.count() && (
					isFunction(operators.peek()) || (
						isOperator(operators.peek()) && (
							getPrecedence(operators.peek()) > getPrecedence(token) ||
							getPrecedence(operators.peek()) == getPrecedence(token) && !getAssociativity(operators.peek())
						) && operators.peek() != TOKEN_LBR
					)
				)
			) {
				function[outputFIndex++] = operators.pop();
			}
			operators.push(token);
		} else if (token == TOKEN_LBR) {
			operators.push(token);
			// if (prevToken == TOKEN_RBR || prevToken < TOKEN_OPERATOR_START)
			// todo
		} else if (token == TOKEN_RBR) {
			while (operators.count() && operators.peek() != TOKEN_LBR) {
				function[outputFIndex++] = operators.pop();
			}
			if (operators.isEmpty()) {
				return false;
			} else {
				operators.pop();
			}
		} else {
			// Probably a special constant.
			function[outputFIndex++] = token;
		}
	}
	
	while (operators.count()) function[outputFIndex++] = operators.pop();
	function[outputFIndex++] = TOKEN_NOP;
	
	return true;
}

uint8_t Function::getToken(const char input) {
	switch (input) {
		case  '+': return TOKEN_ADD;
		case  '-': return TOKEN_SUB;
		case  '*': return TOKEN_MUL;
		case  '/': return TOKEN_DIV;
		case  '^': return TOKEN_POW;
		case  '%': return TOKEN_MOD;
		case  '(': return TOKEN_LBR;
		case  ')': return TOKEN_RBR;
		case  'x': return TOKEN_VAR;
		case '\0': return TOKEN_NOP;
		default  : return TOKEN_UNKNOWN;
	}
}

bool Function::isConstant(const uint8_t input) {
	return input >= TOKEN_CONSTANT_START && input < TOKEN_OPERATOR_START;
}

bool Function::isOperator(const uint8_t input) {
	return input >= TOKEN_OPERATOR_START && input < TOKEN_FUNCTION_START;
}

bool Function::isFunction(const uint8_t input) {
	return input >= TOKEN_FUNCTION_START && input < TOKEN_SPECIALS_START;
}

bool Function::getAssociativity(const uint8_t input) {
	switch (input) {
		case TOKEN_NEG:
		case TOKEN_ADD:
		case TOKEN_SUB:
		case TOKEN_MUL:
		case TOKEN_DIV:
		case TOKEN_MOD:
			return false;
		case TOKEN_POW:
			return true;
	}
}

uint8_t Function::getPrecedence(const uint8_t input) {
	switch (input) {
		case TOKEN_ADD:
		case TOKEN_SUB:
			return 2;
		case TOKEN_MUL:
		case TOKEN_DIV:
		case TOKEN_MOD:
			return 3;
		case TOKEN_POW:
			return 4;
		case TOKEN_NEG:
			return 5;
	}
}
