#include "Print.h"
#include "Genrarator.h"

#include <stdio.h>
#include <fstream>
using namespace std;

void Print::printError()
{
	printf("ERROR:Please input as;\"-c N(0<N<=100w)\"\n");
}

void Print::printSudokuToFile(int N, char * filepath)
{
	Generator gen;
	int * newSudoku;
	ofstream ofile(filepath, ios :: out);

	if (!ofile.is_open())
	{
		printf("File Open Error!\n");
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			newSudoku = gen.getNewSudoku();
			for (int j = 0; j < 81; j++)
			{
				ofile << newSudoku[j] << " ";
				if ((j + 1) % 9 == 0)
				{
					ofile << "\n";
				}
			}
			ofile << "\n";
		}
	}
	
	ofile.close();
}

