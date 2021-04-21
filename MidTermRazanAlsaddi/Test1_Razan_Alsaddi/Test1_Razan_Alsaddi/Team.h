#pragma once
#include <memory>
#include <vector>
#include"PlayerPoolGenerator.h"

class Team
{
private:
	string teamName;
	double cashAvailable;
	double cashSpent;
	int cumulativeSkillRating;
	vector<Player> playersPurchased;
public:
	Team(string name)
	{
		teamName = name;
		cashAvailable = 100000;
		cashSpent = 0;
		cumulativeSkillRating = 0;
	}

	void subCashAvailable(double sub)
	{
		cashAvailable -= sub;
		cashSpent += sub;
	}

	void addSkill(int skill)
	{
		cumulativeSkillRating += skill;
	}

	void addPlayer(Player p)
	{
		playersPurchased.push_back(p);
	}

	void printTeam()
	{
		for (Player p : playersPurchased)
			p.PrintPlayer();
	}

	void printInfo()
	{
		cout << "Cash on hand: " << cashAvailable << "\n";
		cout << "Cash Spent:  " << cashSpent << "\n";
		
	}

	double getCashAvailble()
	{
		return cashAvailable;
	}
	int getcumulativeSkillRating()
	{
		
		return cumulativeSkillRating;
	}
	
	double getAve() 
	{
		if (playersPurchased.size() == 0)
			return 0;
		else 
			return cumulativeSkillRating / playersPurchased.size();
		
	}

};
