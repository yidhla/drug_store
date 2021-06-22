#ifndef __STRATEGY__H__
#define __STRATEGY__H__

#define TOTALDAYS 10
#define DRUGSPERDAY 10

class STRATEGY{
	private:
		int index[TOTALDAYS][DRUGSPERDAY];
  		int pricingIndex[TOTALDAYS][DRUGSPERDAY];
	public:
		bool inputFromStrategyFile(char* strategyFileName);
		int getIndex(int day, int number)
		{
			return index[day][number];
		}
		int getPIndex(int day, int number)
		{
			return pricingIndex[day][number];
		}
};

#endif
