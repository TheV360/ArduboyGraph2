#ifndef RPNFUNCOBJ_H
#define RPNFUNCOBJ_H

#define FUNCTION_MAX_TOKENS 16
#define FUNCTION_MAX_CONST 16

#define TOKEN_MINIMUM 0x80

#define TOKEN_ADD 0x80 // +
#define TOKEN_SUB 0x81 // -
#define TOKEN_MUL 0x82 // *
#define TOKEN_DIV 0x83 // /
#define TOKEN_POW 0x84 // ^
#define TOKEN_OPR 0xe0 // (
#define TOKEN_CPR 0xe1 // )
#define TOKEN_VAR 0xfe // x
#define TOKEN_NOP 0xff // stop reading

const char TOKEN_LABELS[] PROGMEM = {
	'+', '-', '*', '/', '^', 'x'
};

class Function {
	public:
		uint8_t function[FUNCTION_MAX_TOKENS];
		float constants[FUNCTION_MAX_CONST];
		
		float calculate(float x);
};

#endif
