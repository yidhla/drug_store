#ifndef __STORE__H__
#define __STORE__H__

#include "drug.h"
#include "preDef.h"
#include "warehouse.h"
#include "strategy.h"
#include <cstdio>

class STORE{
	private:
		DRUG* productsOnTheShelves[10];
	public:
		STORE()
		{
			for (int i = 0; i < 10; ++i)
			{
				productsOnTheShelves[i] = NULL;
			}
		}
		void print()
		{
			for (int i = 0; i < 10; ++i)
			{
				printf("drugs on the shelves No.%d %d\n", i, productsOnTheShelves[i]->getId());
			}
		}
		bool comp(DRUG* d1, DRUG* d2);
		int putDrugsOnTheShelves(WAREHOUSE& warehouse, STRATEGY& strategy, int day);
		void clearStore();
		int sort3(int realDrugs); //sort drugs on the selve by selling price and bzq
		DRUG* getDrugOnTheShelves(int index);
};

#endif
