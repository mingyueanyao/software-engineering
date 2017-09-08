#pragma once
#ifndef __PRINT_H__
#define __PRINT_H__

#include <string>
using namespace std;

class Print
{
public:
	void printError();
	void printSudokuToFile(int N, char * filepath);
};

#endif // !__PRINT_H__

