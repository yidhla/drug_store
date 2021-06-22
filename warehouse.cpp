#include "warehouse.h"
#include "preDef.h"
#include "drug.h"
#include <algorithm>

bool comp(DRUG& d1, DRUG& d2)
{
	if (d1.getExpirationDate() == d2.getExpirationDate())
	{
		return d1.getPurchasePrice() > d2.getPurchasePrice();
	}
	return d1.getExpirationDate() < d2.getExpirationDate();
}

void WAREHOUSE::sortByEAP()
{
	std::sort(totalDrugs, totalDrugs+50, comp);
}

bool WAREHOUSE::inputFromFile(char* medicineFileName)
{
	FILE * fin = fopen(medicineFileName, "r+");
    if (fin == NULL)
    {
        printf("Failed to open file %s!\n", medicineFileName);
        return false;
    }
    int i = 0;
    double purchasePrice;
    int expirationDate;
    while (i < TOTALDRUGS)
    {
        int state = fscanf(fin, "%lf %d", &purchasePrice, &expirationDate);
        if (state == EOF)
        {
            printf("Failed to read %d group(s) of data!\n", TOTALDRUGS);
            return false;
        }
        totalDrugs[i].setId(i);
        totalDrugs[i].setPurchasePrice(purchasePrice);
        totalDrugs[i].setExpirationDate(expirationDate);
        totalDrugs[i].setState(1);
        ++i;
    }
    if (fclose(fin) == EOF)
    {
        printf("Failed to close file %s!\n", medicineFileName);
        return false;
    }
    return true;
}
