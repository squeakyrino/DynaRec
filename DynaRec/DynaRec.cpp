#include "stdafx.h"
#include "CodeEmitter.h"
#include <iostream>

using namespace std;

int main()
{
	CodeEmitter codeEmitter;

	/*

	char test = 0xef;

	__asm {
	mov test, al
	add al, 0x1
	mov test, 0x29
	mov al, test
	}

	*/

#if 1
	cout << "Moving Value 50 To Register AL..." << endl;
	//Move Immediate value to a register (ItoR)
	codeEmitter.mov8ItoR(EAX, 50);

	cout << "Adding Value 14 To Register AL..." << endl;
	codeEmitter.add8ItoR(EAX, 14);

	//Move value from al to address 200
	//Register to Memory (RtoM)
	codeEmitter.mov8RtoM((unsigned int)codeEmitter.address() + (unsigned int)200, EAX);
#endif

	codeEmitter.add32ItoR(EBX, 15);
	codeEmitter.ret();

	codeEmitter.executeBlock();


	
	unsigned int value = 0x0;
	cout << "Result Found :: " << value << endl;

    return 0;
}

