#pragma once
#ifndef __CENERATOR_H__
#define __CENERATOR_H__

class Generator
{
public:
	Generator();
	Generator(int * newSudoku);
	int * getNewSudoku();
	
private:
	int * getRandomRorC();
	int * getRandomNumber();
	void swapRows(int r1, int r2);
	void swapColumns(int c1, int c2);
	void swapNumbers(int n1, int n2);
	int initSudoku[9][9] = { { 7, 8, 9, 1, 2, 3, 4, 5, 6 },
	                         { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
	                         { 4, 5, 6, 7, 8, 9, 1, 2, 3 },
	                         { 8, 9, 1, 2, 3, 4, 5, 6, 7 },
	                         { 2, 3, 4, 5, 6, 7, 8, 9, 1 },
	                         { 5, 6, 7, 8, 9, 1, 2, 3, 4 },
	                         { 9, 1, 2, 3, 4, 5, 6, 7, 8 },
	                         { 3, 4, 5, 6, 7, 8, 9, 1, 2 },
	                         { 6, 7, 8, 9, 1, 2, 3, 4, 5 }
	                         };

};

#endif // !__CENERATOR_H__