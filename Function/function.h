#ifndef RPNFUNCOBJ_H
#define RPNFUNCOBJ_H

#define FUNCTION_MAX_TOKENS 32
#define FUNCTION_MAX_CONST 8

#define TOKEN_CONSTANT_START 0x00
#define TOKEN_OPERATOR_START 0x40
#define TOKEN_FUNCTION_START 0x80
#define TOKEN_SPECIALS_START 0xf0

#define TOKEN_UNKNOWN 0

#define TOKEN_NEG 0x40 // unary minus
#define TOKEN_ADD 0x41 // +
#define TOKEN_SUB 0x42 // -
#define TOKEN_MUL 0x43 // *
#define TOKEN_DIV 0x44 // /
#define TOKEN_POW 0x45 // ^
#define TOKEN_MOD 0x46 // %

#define TOKEN_SIN 0x80 // sin
#define TOKEN_COS 0x81 // sin

#define TOKEN_LBR 0xf0 // (
#define TOKEN_RBR 0xf1 // )
#define TOKEN_CE  0xfc // e
#define TOKEN_CPI 0xfd // pi
#define TOKEN_VAR 0xfe // x
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
		bool isOperator(const uint8_t input);
		bool isFunction(const uint8_t input);
		
		bool getAssociativity(const uint8_t input);
		uint8_t getPrecedence(const uint8_t input);
};

#endif
