#ifndef __TEST__H__
#define __TEST__H__

#include "warehouse.h"
#include "strategy.h"

class TEST{
	private:
		WAREHOUSE warehouse;
		STRATEGY strategy;
	    double profitWhenSell[50][10]; //profitWhenSell[i][j] means day j sell drug[i] can get how much(base profit:purchsePrice-management fee)
		double lossWhenDelete[50][10]; //lossWhenSell[i][j] means day j delete drug[i] will lose how much(base loss:purchsePrice+management fee)
	public:
		TEST(char* medicineFileName);
		void setBestStrategy(char* streagyFileName, int a, int b, int c);
};

#endif
