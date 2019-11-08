#ifndef RPNFUNCOBJ_H
#define RPNFUNCOBJ_H

#define FUNCTION_MAX_TOKENS 32
#define FUNCTION_MAX_CONST 8

#define TOKEN_UNKNOWN 0x00
#define TOKEN_MINIMUM 0x80
#define TOKEN_FUNCTION 0xa0

#define TOKEN_NEG 0x80 // - again
#define TOKEN_ADD 0x81 // +
#define TOKEN_SUB 0x82 // -
#define TOKEN_MUL 0x83 // *
#define TOKEN_DIV 0x84 // /
#define TOKEN_POW 0x85 // ^
#define TOKEN_MOD 0x86 // %
#define TOKEN_VAR 0xfe // x
#define TOKEN_NOP 0xff // stop reading

struct OperatorInfo {
	bool assoc : 1;
	uint8_t precedence : 7;
};

const OperatorInfo OPERATOR_INFO[] PROGMEM = {
	{false, 2}, // +
	{false, 2}, // -
	{false, 3}, // *
	{false, 3}, // /
	{true,  4}, // ^
	{false, 3}, // %
};

class Function {
	public:
		uint8_t function[FUNCTION_MAX_TOKENS];
		float constants[FUNCTION_MAX_CONST];
		
		float calculate(const float x);
		
		bool getFunction(const char* input);
		
		uint8_t getToken(const char input);
};

#endif
