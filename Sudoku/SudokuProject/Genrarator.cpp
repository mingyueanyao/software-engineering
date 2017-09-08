#include "Genrarator.h"

#include <time.h>
#include <stdlib.h>

#define FIXED_ROW 0
#define FIXED_COLUMN 0
#define FIXED_NUMBER 7

Generator::Generator()
{
	srand(time(0));
}

Generator::Generator(int * newSudoku)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			initSudoku[i][j] = newSudoku[i * 9 + j];
		}	
	}
}

int * Generator::getNewSudoku()
{
	
	int * random;
	int random1, random2;

	random = getRandomRorC();
	random1 = random[0];
	random2 = random[1];
	swapRows(random1, random2);

	random = getRandomRorC();
	random1 = random[0];
	random2 = random[1];
	swapColumns(random1, random2);

	
	int cnt = rand() % 81 + 1;
	for (int i = 0; i < cnt; i++)
	{
		random = getRandomNumber();
		random1 = random[0];
		random2 = random[1];
		swapNumbers(random1, random2);
	}
	

	return &initSudoku[0][0];
}

int * Generator::getRandomRorC()
{
	int random[2];

	do
	{
		random[0] = rand() % 9;
	} 
	while (random[0] == FIXED_ROW);

	int flag;
	do
	{
		flag = rand() % 2;
		switch (random[0] % 3)
		{
		case 0:
			switch (flag)
			{
			case 0:
				random[1] = random[0] + 1;
				break;
			default:
				random[1] = random[0] + 2;
			}
			break;
		case 1:
			switch (flag)
			{
			case 0:
				random[1] = random[0] + 1;
				break;
			default:
				random[1] = random[0] - 1;
			}
			break;
		default:
			switch (flag)
			{
			case 0:
				random[1] = random[0] - 1;
				break;
			default:
				random[1] = random[0] - 2;
			}
		}
	} 
	while (random[1] == FIXED_ROW);

	return random;
}

int * Generator::getRandomNumber()
{
	int random[2];

	do
	{
		random[0] = rand() % 9 + 1;
	} 
	while (random[0] == FIXED_NUMBER);

	do
	{
		random[1] = rand() % 9 + 1;
	} 
	while (random[1] == FIXED_NUMBER || random[1] == random[0]);

	return random;
}

void Generator::swapRows(int r1, int r2)
{
	int i, temp;
	for (i = 0; i < 9; i++)
	{
		temp = initSudoku[r1][i];
		initSudoku[r1][i] = initSudoku[r2][i];
		initSudoku[r2][i] = temp;
	}
}

void Generator::swapColumns(int c1, int c2)
{
	int i, temp;
	for (i = 0; i < 9; i++)
	{
		temp = initSudoku[i][c1];
		initSudoku[i][c1] = initSudoku[i][c2];
		initSudoku[i][c2] = temp;
	}
}

void Generator::swapNumbers(int n1, int n2)
{
	int i, j, temp;
	int m, n, p, q;	//��¼�Ź�����Ҫ�������������ֵ�����

	for (i = 0, j = 0;;)
	{
		if (initSudoku[i][j] == n1)
		{
			m = i;
			n = j;
		}

		if (initSudoku[i][j] == n2)
		{
			p = i;
			q = j;
		}

		//�����Ź���
		if ((j + 1) % 3 != 0)
		{
			j++;
			continue;
		}
		//���˾Ź����ұ߽� 
		else
		{
			//�Ź�����һ��
			if ((i + 1) % 3 != 0)
			{
				i++;
				j -= 2;
				continue;
			}
			//��һ���Ź��� 
			else
			{
				//����ɨ����ľŹ�����Ҫ����������
				temp = initSudoku[m][n];
				initSudoku[m][n] = initSudoku[p][q];
				initSudoku[p][q] = temp;

				//�¸��Ź�������� 
				if (j != 8)
				{
					j++;
					i -= 2;
					continue;
				}
				//�¸��Ź�������һ�� 
				else
				{
					//������һ�� 
					if (i != 8)
					{
						i++;
						j = 0;
						continue;
					}
					//�Ÿ��Ź���ȫ���������
					else
					{
						break;
					}
				}
			}
		}
	}
}
