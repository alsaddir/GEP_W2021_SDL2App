#pragma once
#include<string>
#include <iostream>
using namespace std;
//Razan Alsaddi
enum state
{
	YES, NO

};
class Block 
{
private:
	string cityName;
	int purchaseValue;
	int rentalValue;
	string ownerName;
	state isPurchased;
public:
	
	void setCityName(string cityname) { cityName = cityname; }
	void setPurchaseValue(int pvalue) { purchaseValue = pvalue; }
	void setRentalValue(int rvalue) { rentalValue = rvalue; }
	void setOwnerName(string oname) { ownerName = oname; }
	void setisPurchesed(state b) { isPurchased = b; }

	string getCityName() { return cityName; }
	int getPurchaseValue() { return purchaseValue; }
	int getRentalValue() { return rentalValue; }
	string getOwnerName() { return ownerName; }
	state getisPurchesed() { return isPurchased; }

	Block(string cityname, int pvalue, int rvalue)
	{
		cityName = cityname;
		purchaseValue = pvalue;
		rentalValue = rvalue;
		ownerName = "No one yet";
		isPurchased = NO;
	}











};
