#pragma once

#include <Windows.h>
#include <vector>
#include "Warcraft.h"

enum OPCODES : UINT {
	OPTYPE_ENDPROGRAM = 1,
	OPTYPE_OLDJUMP,
	OPTYPE_FUNCTION,
	OPTYPE_ENDFUNCTION,
	OPTYPE_LOCAL,
	OPTYPE_GLOBAL,
	OPTYPE_CONSTANT,
	OPTYPE_FUNCARG,
	OPTYPE_EXTENDS,
	OPTYPE_TYPE,
	OPTYPE_POPN,
	OPTYPE_MOVRLITERAL,
	OPTYPE_MOVRR,
	OPTYPE_MOVRV,
	OPTYPE_MOVRCODE,
	OPTYPE_MOVRA,
	OPTYPE_MOVVR,
	OPTYPE_MOVAR,
	OPTYPE_PUSH,
	OPTYPE_POP,
	OPTYPE_CALLNATIVE,
	OPTYPE_CALLJASS,
	OPTYPE_I2R,
	OPTYPE_AND,
	OPTYPE_OR,
	OPTYPE_EQUAL,
	OPTYPE_NOTEQUAL,
	OPTYPE_LESSEREQUAL,
	OPTYPE_GREATEREQUAL,
	OPTYPE_LESSER,
	OPTYPE_GREATER,
	OPTYPE_ADD,
	OPTYPE_SUB,
	OPTYPE_MUL,
	OPTYPE_DIV,
	OPTYPE_MOD,
	OPTYPE_NEGATE,
	OPTYPE_NOT,
	OPTYPE_RETURN,
	OPTYPE_LABE,
	OPTYPE_JUMPIFTRUE,
	OPTYPE_JUMPIFFALSE,
	OPTYPE_JUMP,
	OPTYPE_STARTLUATHREAD
};

enum OPCODE_VARIABLE_TYPE : UINT {
	OPCODE_VARIABLE_NOTHING = 0,
	OPCODE_VARIABLE_UNKNOWN,
	OPCODE_VARIABLE_NULL,
	OPCODE_VARIABLE_CODE,
	OPCODE_VARIABLE_INTEGER,
	OPCODE_VARIABLE_REAL,
	OPCODE_VARIABLE_STRING,
	OPCODE_VARIABLE_HANDLE,
	OPCODE_VARIABLE_BOOLEAN,
	OPCODE_VARIABLE_INTEGER_ARRAY,
	OPCODE_VARIABLE_REAL_ARRAY,
	OPCODE_VARIABLE_STRING_ARRAY,
	OPCODE_VARIABLE_HANDLE_ARRAY,
	OPCODE_VARIABLE_BOOLEAN_ARRAY
};

#ifndef _JassMachine_h
#define _JassMachine_h
typedef struct {
	DWORD unk;
	DWORD zero1;
	DWORD zero2;
	DWORD zero3;
	DWORD zero4;
	DWORD zero5;
	DWORD type1;
	DWORD type2;
	DWORD value;
	DWORD zero6;

	void set(DWORD value, OPCODE_VARIABLE_TYPE type) {
		this->value = value;
		type1 = type;
		type2 = type;
	}

} JASS_DATA_SLOT, * PJASS_DATA_SLOT;

typedef struct {
private:
	DWORD unk1;
	DWORD unk2;
	size_t stack_top; // Idk why it's here
	PJASS_DATA_SLOT stack[32];
	size_t size;
public:
	PJASS_DATA_SLOT pop() {
		return stack[--size];
	}

	PJASS_DATA_SLOT& operator[](size_t index) {
		return stack[index];
	}

	void clear(size_t number) {
		size = number < size ? size - number : 0;
	}

	size_t Size() {
		return size;
	}
} JASS_STACK, * PJASS_STACK;

typedef struct {
private:
	std::vector<JASS_OPCODE> oplist;
public:
	void addop(BYTE opcode, BYTE reg = 0, DWORD value = NULL, BYTE type = OPCODE_VARIABLE_NOTHING, BYTE rettype = OPCODE_VARIABLE_NOTHING) {
		JASS_OPCODE* _opcode = new JASS_OPCODE;
		_opcode->rettype = rettype;
		_opcode->type = type;
		_opcode->reg = reg;
		_opcode->opcode = opcode;
		_opcode->value = value;

		oplist.push_back(*_opcode);
	}

	DWORD getcode() {
		return ((DWORD)&oplist - (DWORD)getJassMachine()->code_table->codes) / 4;
	}

} JASS_OPLIST, * PJASS_OPLIST;
#endif

//---------------------------------------------------------

void jassOpcodeInitialize();