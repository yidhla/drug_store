#include "drug.h"

int DRUG::getState()
{
	return state;
}
int DRUG::setState(int s)
{
	state = s;
}
int DRUG::getId()
{
	return id;
}
int DRUG::setId(int index)
{
	id = index;
	return id;
}
int DRUG::setExpirationDate(int eD)
{
	expirationDate = eD;
	return eD;
}
int DRUG::getExpirationDate()
{
	return expirationDate;
}
double DRUG::setPurchasePrice(double pP)
{
	purchasePrice = pP;
	return pP;
}
double DRUG::setSellingPrice(double sP)
{
	sellingPrice = sP;
	return sP;
}
double DRUG::getPurchasePrice()
{
	return purchasePrice;
}
double DRUG::getSellingPrice()
{
	return sellingPrice;
}

