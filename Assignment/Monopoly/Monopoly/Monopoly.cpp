// Monopoly.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Razan Alsaddi

#include <iostream>
#include"Block.h"
#include"Player.h"
#include "Dice.h"
using namespace std;
int main()
{
	Dice d;

	Player* p1 = new Player("Sam");
	Player* p2 = new Player("Razan");

	Block* b1 = new Block("Toronto",50,20);
	Block* b2 = new Block("Edmonton", 40,10);
	Block* b3 = new Block("Montreal", 60,30);
	Block* b4 = new Block("Waterloo ", 75,15);
	Block* b5 = new Block("Calgary", 90, 20);
	Block* b6 = new Block("Ottawa", 50, 10);

	vector<Block*> allCities;
	allCities.push_back(b1);
	allCities.push_back(b2);
	allCities.push_back(b3);
	allCities.push_back(b4);
	allCities.push_back(b5);
	allCities.push_back(b6);

	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0) {
			cout << "Player 1 : " << p1->getName() << endl;
			cout << "Rolling the Dise ..... " << endl;
			int c = d.roll();
			string stateCity;
			cout << "******************************" << endl;
			cout << "Dice number is " << c << endl;
			cout << "City info :" << endl;
			cout << "City name :" << allCities[c - 1]->getCityName() << endl;
			cout << "Purchase Value :" << allCities[c - 1]->getPurchaseValue() << endl;
			cout << "Rental Value:" << allCities[c - 1]->getRentalValue() << endl;
			if (allCities[c - 1]->getisPurchesed() == YES)
				stateCity = "YES";
			else
				stateCity = "NO";

			cout << "isPurchesed  :" << stateCity << endl;
			cout << "Owner Name :" << allCities[c - 1]->getOwnerName() << endl;
			cout << "******************************" << endl;
			cout << endl;


			if (allCities[c - 1]->getisPurchesed() == NO)
			{
				cout << "Please enter 'Y' if you want to purchase and 'S' if you want to skip";
				char chose;
				cin >> chose;
				if (chose == 'Y' || chose == 'y')
				{
					allCities[c - 1]->setOwnerName("Sam");
					allCities[c - 1]->setisPurchesed(YES);
					p1->subMoney(allCities[c - 1]->getPurchaseValue());
					p1->addCily(allCities[c - 1]);
					p1->printPlayerInfo();
				}

			}
			else
			{
				if (allCities[c - 1]->getOwnerName() == "Razan")
				{
					cout << "It is owned by Razan " << endl;
					p1->subMoney(allCities[c - 1]->getRentalValue());
					p1->printPlayerInfo();
				}
			}

		}

		else
		{
			cout << "Player 2 : " << p2->getName() << endl;
			cout << "Rolling the Dise ..... " << endl;
			int c = d.roll();
			string stateCity;
			cout << "******************************" << endl;
			cout << "Dice number is " << c << endl;
			cout << "City info :" << endl;
			cout << "City name :" << allCities[c - 1]->getCityName() << endl;
			cout << "Purchase Value :" << allCities[c - 1]->getPurchaseValue() << endl;
			cout << "Rental Value:" << allCities[c - 1]->getRentalValue() << endl;
			if (allCities[c - 1]->getisPurchesed() == YES)
				stateCity = "YES";
			else
				stateCity = "NO";

			cout << "isPurchesed  :" << stateCity << endl;
			cout << "Owner Name :" << allCities[c - 1]->getOwnerName() << endl;
			cout << "******************************" << endl;
			cout << endl;


			if (allCities[c - 1]->getisPurchesed() == NO)
			{
				cout << "Please enter 'Y' if you want to purchase and 'S' if you want to skip";
				char chose;
				cin >> chose;
				if (chose == 'Y' || chose == 'y')
				{
					allCities[c - 1]->setOwnerName("Razan");
					allCities[c - 1]->setisPurchesed(YES);
					p2->subMoney(allCities[c - 1]->getPurchaseValue());
					p2->addCily(allCities[c - 1]);
					p2->printPlayerInfo();
				}

			}
			else
			{
				if (allCities[c - 1]->getOwnerName() == "Sam")
				{
					cout << "It is owned by Sam " << endl;
					p2->subMoney(allCities[c - 1]->getRentalValue());
					p2->printPlayerInfo();
				}
			}
		
		
		
		
		
		
		
		
		}

	}



	allCities.clear();
	delete p1;
	p1 = nullptr;
	delete p2;
	p2 = nullptr;
	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
