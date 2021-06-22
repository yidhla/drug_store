#include "store.h"
#include "preDef.h"
#define tiny 1e-6
#include <algorithm>
#include <cmath>
const double PAS[7] = {-1.5, -1, -0.5, 0, 2, 4, 6};

int STORE::putDrugsOnTheShelves(WAREHOUSE& warehouse, STRATEGY& strategy, int day)
{
	 for (int i = 0; i < DRUGSPERDAY; ++i)
	{
		 if (strategy.getIndex(day, i) == -1)
		 {
		 	//printf("QUEKOU\n");
		 	return i+1;
		 }
		productsOnTheShelves[i] = warehouse.getDrugById(strategy.getIndex(day, i));
		double tmp = productsOnTheShelves[i]->getPurchasePrice()+PAS[strategy.getPIndex(day, i)];
		productsOnTheShelves[i]->setSellingPrice(tmp);
		productsOnTheShelves[i]->setState(0);
	}
	 //print();
	 return DRUGSPERDAY;
}

void STORE::clearStore()
{
	for (int i = 0; i < DRUGSPERDAY; ++i)
	{
		if (productsOnTheShelves[i] != NULL)
		   productsOnTheShelves[i]->setState(1); //lay back drugs into warefare
		productsOnTheShelves[i] = NULL;
	}
}

DRUG* STORE::getDrugOnTheShelves(int index)
{
	return productsOnTheShelves[index];
}

int STORE::sort3(int realDrugs) //select sort store.productsOnTheShelves[]
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = i+1; j < realDrugs; ++j)
		{
			if (productsOnTheShelves[j] == NULL) continue;
			if (productsOnTheShelves[j]->getSellingPrice() < productsOnTheShelves[i]->getSellingPrice())
			{
				DRUG* tmp = productsOnTheShelves[j];
				productsOnTheShelves[j] = productsOnTheShelves[i];
				productsOnTheShelves[i] = tmp;
			}
		}
	}
}
