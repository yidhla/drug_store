#ifndef __DRUG__H__
#define __DRUG__H__

class DRUG{
	private:
		double purchasePrice;
		double sellingPrice;
		int expirationDate;
		int id; //id==-1 means the drug of No.id goes none(deleted, or selled)
		int state; //state==0 not in warehouse, state==1 in warefare
	public:
		DRUG()
		{
			;
		}
		DRUG(int i, double pP, int eD, int s):id(i), purchasePrice(pP) , expirationDate(eD), state(s) {}
		int getState();
		int setState(int s);
		int getId();
		int setId(int index);
		int setExpirationDate(int eD);
		int getExpirationDate();
		double setPurchasePrice(double pP);
		double setSellingPrice(double sP);
		double getPurchasePrice();
		double getSellingPrice();
};

#endif
