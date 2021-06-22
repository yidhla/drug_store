#ifndef __SIMULATION__H__
#define __SIMULATION__H__

#include "preDef.h"
#include "store.h"
#include "warehouse.h" 
#include "strategy.h"

class SIMULATION{
	private:
		STORE store;
		WAREHOUSE warehouse;
		STRATEGY strategy;
		int discards[10][50]; //discards[i][j] == 1 means day i and drug j are to be discarded
		double res;
		char logFileName[100];
		char deleteFileName[100];
	public:
		SIMULATION(char* medicineFileName, char* strategyFileName, char* deleteFileName, char* lFN);
		bool inputFromDeleteFile(char* deleteFileName);
		double run(char *type);
};

#endif
