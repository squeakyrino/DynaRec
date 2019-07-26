#include "stdafx.h"
#include "CodeEmitter.h"

void CodeEmitter::emitByte(unsigned char byte)
{
	buffer[bufferPointer++] = byte;
}

void CodeEmitter::emitWord(unsigned short word)
{
	*((unsigned short*)(buffer + bufferPointer)) = word;
	bufferPointer += 2;
}

void CodeEmitter::emitDword(unsigned long dword)
{
	*((unsigned long*)(buffer + bufferPointer)) = dword;
	bufferPointer += 4;
}

/*
	mod -
	rem -
	r/m - 
	*/
void CodeEmitter::modRM(unsigned char mod, X86RegisterType rem, X86RegisterType rm)
{
	//TODO better understand how this works
	emitByte(((mod << 6) | ((unsigned char)rem << 3) | (unsigned char)rm));
}

void CodeEmitter::sibSB(unsigned char sib, unsigned char rm, unsigned char index)
{
	//?
}

CodeEmitter::CodeEmitter(unsigned long bufferSize)
	: buffer (NULL),
	bufferPointer(0),
	bufferSize(bufferSize)
{
	//buffer = new unsigned char[bufferSize];
	buffer = (unsigned char *)VirtualAlloc(0, bufferSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
}

CodeEmitter::~CodeEmitter()
{
	if (buffer != NULL) {
		VirtualFree(buffer, bufferSize, MEM_RELEASE);
		buffer = NULL;
	}
}

void CodeEmitter::executeBlock()
{
	if (bufferPointer > 0) {
		void(*blockFunction)() = (void(*)()) buffer;
		blockFunction();
	}
}

void CodeEmitter::mov16RtoM(unsigned int to, X86RegisterType from)
{
	emitByte(0x66);
	emitByte(0x89);
	modRM(0, from, (X86RegisterType)DISP32);
	emitDword(from);
}

void CodeEmitter::mov16MtoR(X86RegisterType to, unsigned int from)
{
	emitByte(0x66);
	emitByte(0x8B);
	modRM(0, to, (X86RegisterType)DISP32);
	emitDword(from);
}

void CodeEmitter::add32ItoR(X86RegisterType to, unsigned int from)
{
	if (to == EAX)
	{
		emitByte(0x05);
	}
	else {
		emitByte(0x81);
		modRM(3, (X86RegisterType)0, to);
	}

	emitDword(from);
}

void CodeEmitter::mov8ItoR(X86RegisterType to, unsigned char imediateValue)
{
	emitByte(0xB0);
	emitByte(imediateValue);
}

void CodeEmitter::add8ItoR(X86RegisterType to, unsigned char imediateValue)
{
	emitByte(0x04);
	emitByte(imediateValue);
}

void CodeEmitter::mov8RtoM(unsigned int to, X86RegisterType from)
{
	emitByte(0x88);
	modRM(0, from, (X86RegisterType)DISP32);
	emitDword(to);
}

void CodeEmitter::ret()
{
	emitByte(0xC3);
}

unsigned char* CodeEmitter::address() {
	return buffer;
}