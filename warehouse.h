#ifndef __WAREHOUSE__H__
#define __WAREHOUSE__H__

#include "preDef.h"
#include "drug.h"
#include <cstdio>

class WAREHOUSE{
	private:
		DRUG totalDrugs[50];
	public:
		bool inputFromFile(char* medicineFileName);
		void print()
		{
			for (int i = 0; i < 50; ++i)
			{
				printf("warehouse_print: %d %lf %d\n", totalDrugs[i].getId(), totalDrugs[i].getPurchasePrice(), totalDrugs[i].getExpirationDate());
			}
		}
		DRUG* getDrugById(int id)
		{
			return &totalDrugs[id];
		}
		void sortByEAP();
};

#endif
