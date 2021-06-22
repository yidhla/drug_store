#include "simulation.h"
#include <cstdio>
#include "preDef.h"
#include <iostream>
#include <cstring>
#include "drug.h"
#define TOTALDRUGS 50

SIMULATION::SIMULATION(char* medicineFileName, char* strategyFileName, char* dFN, char* lFN)
{
	if (!warehouse.inputFromFile(medicineFileName))
	{
		exit(0);
	}
	//printf("%s\n", strategyFileName);
	if (!strategy.inputFromStrategyFile(strategyFileName))
	{
		exit(0);
	}
	res = 0;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			discards[i][j] = 0;
		}
	}
	strcpy(deleteFileName, dFN);
	//printf("0HERE: %s\n", deleteFileName);
	if (!inputFromDeleteFile(deleteFileName))
	{
		exit(0);
	}
	if (strcmp("log.txt", lFN) != 0)
	{
		strcpy(logFileName, lFN);
	}
	else
	{
		strcpy(logFileName, "log.txt");
	}
}

bool SIMULATION::inputFromDeleteFile(char* deleteFileName)
{
	FILE* dF = fopen(deleteFileName, "r");
	//printf("0HERE: %s\n", deleteFileName);
	if (dF == NULL)
	{
		printf("deleteFile %s cannot read!\n", deleteFileName);
		return false;
	}
	int state = 1;
	int day, index;
	while (state != EOF)
	{
		state = fscanf(dF, "%d %d", &day, &index);
		if (state == EOF)
		{
			break;
		}
		discards[day][index] = 1;
	}
	fclose(dF);
	return true;
}

double SIMULATION::run(char * type)
{
	FILE* lF = fopen(logFileName, "w+");
	if (lF == NULL)
	{
		printf("create file %s failed!\n", logFileName);
		exit(0);
	}
	fprintf(lF, "log:\n");
	fclose(lF);
	lF = fopen(logFileName, "a");
	for (int i = 0; i < 10; ++i)
	{
		fprintf(lF, "DAY %d:\n", i);
		////1.clear drugs yesterday
		store.clearStore();
		////2.put drugs on the shelves
		int realDrugs = store.putDrugsOnTheShelves(warehouse, strategy, i);
		////3.beginning to sell drugs and calculate initial money
		store.sort3(realDrugs);
		////output to log
		for (int ii = 0; ii < realDrugs; ++ii)
		{
			if (store.getDrugOnTheShelves(ii) == NULL) continue;
			fprintf(lF, "put on the shelves:%d %lf\n", store.getDrugOnTheShelves(ii)->getId(),store.getDrugOnTheShelves(ii)->getSellingPrice());
			//printf("put on the shelves:%d %lf\n", store.getDrugOnTheShelves(ii)->getId(),store.getDrugOnTheShelves(ii)->getSellingPrice());
		}
		////4.caculate money of selling
		for (int j = 0; j < 3; ++j)
		{
			if (store.getDrugOnTheShelves(j) == NULL) continue;
			res += (store.getDrugOnTheShelves(j)->getSellingPrice() - store.getDrugOnTheShelves(j)->getPurchasePrice());
			fprintf(lF, "selled drug:%d %lf %lf %lf\n", store.getDrugOnTheShelves(j)->getId(), store.getDrugOnTheShelves(j)->getSellingPrice(),store.getDrugOnTheShelves(j)->getPurchasePrice(), res);
			//printf("selled drug:%d %lf %lf %lf\n", store.getDrugOnTheShelves(j)->getId(), store.getDrugOnTheShelves(j)->getSellingPrice(),store.getDrugOnTheShelves(j)->getPurchasePrice(), res);
			store.getDrugOnTheShelves(j)->setId(-1);
		}
		int deleted[50];
		memset(deleted, 0, sizeof(deleted));
		//printf("0HERE: %s\n", deleteFileName);
		FILE* dF;
		if (strcmp(type, "simulation") == 0)
		dF = fopen(deleteFileName, "r+");
		else
		dF = fopen(deleteFileName, "w+");
		if (dF == NULL)
		{
			printf("write to deleteFile failed\n");
			exit(0);
		}
		////5.calculate real money and renew expirationDate
		for (int k = 0; k < 50; ++k)
		{
			if (warehouse.getDrugById(k)->getId() == -1) continue;
			if (warehouse.getDrugById(k)->getState() == 0) continue;
			if (warehouse.getDrugById(k)->getExpirationDate() - i <= 0 && deleted[k] == 0 && strcmp(type, "test") == 0)
			{
				warehouse.getDrugById(k)->setId(-1);
				deleted[k] = 1;
				fprintf(dF, "%d %d\n", i, k);
				continue;
				//printf("%d %d\n", i, k);
			}
			if (warehouse.getDrugById(k)->getExpirationDate() - i <= 5)
			   res -= 1;
			else
				res -= 0.5;
			int date = warehouse.getDrugById(k)->getExpirationDate();
			//warehouse.getDrugById(k)->setExpirationDate(date-1);
			fprintf(lF, "management fee:%d %d %lf\n", warehouse.getDrugById(k)->getId(), date, res);
			//printf("management fee:%d %d %lf\n", warehouse.getDrugById(k)->getId(), date, res);
		}
		fclose(dF);
		////6.discard
		for (int k = 0; k < 50; ++k)
		{
			if (discards[i][k] == 1)
			{
				warehouse.getDrugById(k)->setId(-1);
				res -= warehouse.getDrugById(k)->getPurchasePrice();
				fprintf(lF, "discard drug id: %d purchasePrice: %lf\n", k, warehouse.getDrugById(k)->getPurchasePrice());
				//printf("discard drug id: %d purchasePrice: %lf\n", k, warehouse.getDrugById(k)->getPurchasePrice());
			}
		}
	}
	fclose(lF);
	return res;
	
}
