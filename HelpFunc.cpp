#include "HelpFunc.h"

int generateRandom()
{
	srand(time(NULL));
	int num = rand() % 100;
	if (num % 2 == 0) return 1;
	else return 0;
}

int max(const int a, const int b)
{
	if (a >= b) return a;
	return b;
}

int min(const int a, const int b)
{
	if (a <= b) return a;
	return b;
}
