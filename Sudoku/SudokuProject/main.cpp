#include "Scan.h"
#include "Print.h"

int main(int argc, char* argv[])
{
	Scan in;
	Print out;
	
	int N = in.checkInput(argc, argv);
	if (!N)
	{
	    out.printError();
	}
	else
	{
	    out.printSudokuToFile(N, ".\\sudoku.txt");
	}

	return 0;
}