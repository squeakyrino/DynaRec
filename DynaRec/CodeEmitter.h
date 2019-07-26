#pragma once

#include <Windows.h>

enum ASSEMBLER_HELP_VALUES {
	SIB = 4, ///< SIB Value Passed To SibSB
	DISP32 = 5 ///< DISP32 Value Passed To ModRM
};

typedef enum
{
	EAX = 0,
	EBX = 3,
	ECX = 1,
	EDX = 2,
	ESI = 6,
	EDI = 7,
	EBP = 5,
	ESP = 4
} X86RegisterType;




class CodeEmitter
{
private:
	unsigned char* buffer;
	unsigned long bufferSize;
	unsigned long bufferPointer;

	//Emitter functions

	//Emits 8 bits of data to our code generation buffer.
	void emitByte(unsigned char byte);
	
	//Emits 16 bits of data to our code generation buffer.
	void emitWord(unsigned short word);

	//Emits 32 bits of data to our code generation buffer.
	void emitDword(unsigned long dword);

	// Emitter Modifier Functions

	//standard opcode emitter helper.
	void modRM(unsigned char mod, X86RegisterType rem, X86RegisterType rm);
	
	//standard opcode emitter helper.
	void sibSB(unsigned char sib, unsigned char rm, unsigned char index);


public:
	CodeEmitter(unsigned long bufferSize = 256);
	~CodeEmitter();

	unsigned char* address();


	void executeBlock();

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Move Opcode Emitters

	/** Move 16 bits of data from memory into an x86 CPU register.
	*/
	void mov16RtoM(unsigned int to, X86RegisterType from);
		 
	/** Move 16 bits of data from an x86 CPU register to memory.
	*/	 
	void mov16MtoR(X86RegisterType to, unsigned int from);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Add Opcode Emitters

	/** Adds an immediate value to an x86 CPU register.
	*/
	void add32ItoR(X86RegisterType to, unsigned int from);


	void mov8ItoR(X86RegisterType to, unsigned char imediateValue);

	void add8ItoR(X86RegisterType to, unsigned char imediateValue);
	
	void mov8RtoM(unsigned int to, X86RegisterType from);
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Return Opcode Emitter

	/** This opcode must end every recompiled block.
	*/
	void ret();
};

