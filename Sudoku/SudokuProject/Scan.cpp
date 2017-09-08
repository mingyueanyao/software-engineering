#include "Scan.h"

#include <iostream>
using namespace std;

int Scan::checkInput(int argc, char * argv[])
{
	int N, flag;
	flag = sscanf_s(argv[2], "%d", &N);

	if (argc == 3 && flag)
	{
		return N;
	}
	else
	{
		return flag;
	}
}
