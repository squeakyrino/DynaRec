// DynaRec.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"

int maine()
{
	char test = 0xef;

	__asm {
		mov test, al
		add al, 0x1
		mov test, 0x29
		mov al, test
	}

	return 0;
}

