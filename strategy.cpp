#include "strategy.h"
#include <cstdio>

bool STRATEGY::inputFromStrategyFile(char* strategyFileName)
{
	FILE* sF = fopen(strategyFileName, "r");
	if (sF == NULL)
    {
        printf("Failed to open file %s!\n", strategyFileName);
		return false;
    }
    int i = 0;
    while (i < TOTALDAYS)
    {
        int j = 0;
        while (j < DRUGSPERDAY)
        {
            fscanf(sF, "%d,%d", &index[i][j], &pricingIndex[i][j]);
            ++j;
        }
        ++i;
    }
    if (fclose(sF) == EOF)
    {
        printf("Failed to close file %s!\n", strategyFileName);
        return false;
    }
    return true;
}
