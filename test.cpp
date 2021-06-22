#include "test.h"
#include "warehouse.h"
#include "drug.h"
#include <iostream>
#include <cstdio>
#include <cstring>

TEST::TEST(char* medicineFileName)
{
	if (!warehouse.inputFromFile(medicineFileName))
	{
		exit(0);
	}
}

void TEST::setBestStrategy(char* streagyFileName, int a, int b, int c)
{
	////calculate strategy
	warehouse.sortByEAP();
	////write strategy
	FILE* sF = fopen(streagyFileName, "w");
	if (sF == NULL)
	{
		printf("file %s cannot open!\n", streagyFileName);
		exit(0);
	}
	fprintf(sF, "");
	fclose(sF);
	sF = fopen(streagyFileName, "a");
	//int a, b, c; a=b=c=6;
	int ans = 0;
	for (int i = 0; i < 50 && ans < 30;)
	{
		if (warehouse.getDrugById(i)->getId() == -1) ++i;
	   fprintf(sF, "%d,%d", warehouse.getDrugById(i)->getId(), a); ++i; ++ans;
	   if (warehouse.getDrugById(i)->getId() == -1) ++i;
	   fprintf(sF, " %d,%d", warehouse.getDrugById(i)->getId(), b); ++i; ++ans;
	   if (warehouse.getDrugById(i)->getId() == -1) ++i;
	   fprintf(sF, " %d,%d", warehouse.getDrugById(i)->getId(), c); ++i; ++ans;
	   int cnt = 3;
	   for (int j = i+3; j < 50; ++j)
	   {
		   if ((warehouse.getDrugById(j)->getPurchasePrice() > warehouse.getDrugById(i)->getPurchasePrice()) && (warehouse.getDrugById(j)->getPurchasePrice() > warehouse.getDrugById(i+1)->getPurchasePrice()) && (warehouse.getDrugById(j)->getPurchasePrice() > warehouse.getDrugById(i+2)->getPurchasePrice()))
		   {
		   	  //printf("HERE\n");
			  fprintf(sF, " %d,%d", warehouse.getDrugById(j)->getId(), 6);
			  ++cnt;
			  if (cnt >= 10)
				 break;
		   }
	   }
	   while (cnt < 10)
	   {
			 fprintf(sF, " %d,%d", -1, 6);
			 ++cnt;
	   }
 	   fprintf(sF, "\n");
	}
	fclose(sF);
}
