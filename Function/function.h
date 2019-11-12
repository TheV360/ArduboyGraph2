#pragma once

#define FUNCTION_MAX_TOKENS 64
#define FUNCTION_MAX_CONST 16

#define TOKEN_CONSTANT_START 0x00
#define TOKEN_VARIABLE_START 0x40
#define TOKEN_OPERATOR_START 0x60
#define TOKEN_FUNCTION_START 0x80
#define TOKEN_SPECIAL_START 0xf0

// Constants
#define TOKEN_UNKNOWN 0
// Variables
#define TOKEN_VAR 0x40 // x
#define TOKEN_E   0x41 // e
#define TOKEN_PI  0x42 // pi
// Operators
#define TOKEN_NEG 0x60 // unary minus
#define TOKEN_ADD 0x61 // +
#define TOKEN_SUB 0x62 // -
#define TOKEN_MUL 0x63 // *
#define TOKEN_DIV 0x64 // /
#define TOKEN_POW 0x65 // ^
#define TOKEN_MOD 0x66 // %
// Functions
#define TOKEN_SIN 0x80 // sin
#define TOKEN_COS 0x81 // cos
// Special
#define TOKEN_LBR 0xf0 // (
#define TOKEN_RBR 0xf1 // )
#define TOKEN_NOP 0xff // stop reading

class Function {
	public:
		uint8_t function[FUNCTION_MAX_TOKENS];
		float constants[FUNCTION_MAX_CONST];
		
		float calculate(const float x);
		
		bool getFunction(const char* input);
	private:
		uint8_t getToken(const char input);
		
		bool isConstant(const uint8_t input);
		bool isValue(const uint8_t input);
		bool isOperator(const uint8_t input);
		bool isFunction(const uint8_t input);
		bool isSpecial(const uint8_t input);
		
		bool getAssociativity(const uint8_t input);
		uint8_t getPrecedence(const uint8_t input);
};
