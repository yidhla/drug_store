#include "simulation.h"
#include <cstdio>
#include <cstring>
#include "preDef.h"
#include "test.h"
#include <iostream>

int main (int argc, char* argv[])
{
    char medicineFileName[100];
    char strategyFileName[100];
    char deleteFileName[100];
    char logFileName[100] = "NULL";
    char TmedicineFileName[100];
    char TstrategyFileName[100];
    char TdeleteFileName[100];
    char type[100];
    int ci = 1;
    while (ci < argc)
    {
    	if (strcmp(argv[ci], "-t") == 0)
        {
            strcpy(type, argv[++ci]);
            ++ci;
        }
        else if (strcmp(argv[ci], "-m") == 0)
        {
            strcpy(medicineFileName, argv[++ci]);
            ++ci;
        }
        else if (strcmp(argv[ci], "-s") == 0)
        {
            strcpy(strategyFileName, argv[++ci]);
            ++ci;
        }
        else if (strcmp(argv[ci], "-d") == 0)
        {
            strcpy(deleteFileName, argv[++ci]);
            ++ci;
        }
        else if (strcmp(argv[ci], "-wm") == 0)
        {
            strcpy(TmedicineFileName, argv[++ci]);
            ++ci;
        }
        else if (strcmp(argv[ci], "-ws") == 0)
        {
            strcpy(TstrategyFileName, argv[++ci]);
            ++ci;
        }
        else if (strcmp(argv[ci], "-wd") == 0)
        {
            strcpy(TdeleteFileName, argv[++ci]);
            ++ci;
        }
        else if (strcmp(argv[ci], "-l") == 0)
        {
            strcpy(logFileName, argv[++ci]);
            ++ci;
        }
        else
        {
        	printf("cookie error!\n");
        	exit(0);
		}
    }
    if (strcmp(logFileName, "NULL") == 0)
    {
    	strcpy(logFileName, "log.txt");
	}
    //printf("%s\n%s\n%s\n%s\n\n", medicineFileName, strategyFileName, deleteFileName, logFileName);
	/*
    strcpy(medicineFileName, "E:\\c++\\gg\\simulation\\data10\\medicine.txt");
    strcpy(strategyFileName, "E:\\c++\\gg\\simulation\\data10\\strategy.txt");
    strcpy(deleteFileName, "E:\\c++\\gg\\simulation\\data10\\delete.txt");
    strcpy(logFileName, "log.txt");
	*/
	////simulation
	if (strcmp(type, "simulation") == 0)
	{
		//printf("HERE\n");
		SIMULATION simulation(medicineFileName, strategyFileName, deleteFileName, logFileName);
	    double res = simulation.run(type);
	    printf("simulation benefit: %lf\n", res);
	}
	////test
	else if (strcmp(type, "test") == 0)
	{
		//printf("HERE\n");
		FILE* myBestSimulation = fopen("myBestSimulation.txt", "a+");
		if (myBestSimulation == NULL)
		{
			printf("Cannot create myBestSimulation.txt!\n");
			exit(0);
		}
		TEST test(TmedicineFileName);
		double bestRes = -1e10;
		int ba, bb, bc;
		ba = bb = bc = -1;
		for (int a = 0; a < 7; ++a)
		{
			for (int b = 0; b < 7; ++b)
			{
				for (int c = 0; c < 7; ++c)
				{
					test.setBestStrategy(TstrategyFileName, a, b, c);
					SIMULATION Tsimulation(TmedicineFileName, TstrategyFileName, TdeleteFileName, logFileName);
				    double res = Tsimulation.run(type);
				    if (res > bestRes)
				    {
				    	bestRes = res;
				    	ba = a;
				    	bb = b;
				    	bc = c;
					}
				    //printf("my best simulation benefit: %lf %d %d %d\n", res, a, b, c);
				}
			}
		}
		fprintf(myBestSimulation, "%lf\n", bestRes);
		printf("my real real best simulation benefit: %lf %d %d %d\n", bestRes, ba, bb, bc);
	}
	else
	{
		printf("type cookie error!\n");
		exit(0);
	}
    return 0;
}
