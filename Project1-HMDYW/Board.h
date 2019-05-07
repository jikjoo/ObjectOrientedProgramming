#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "setting.h"
#include "Player.h"

struct Stat {
	int sum_offer;
	int sum_offered;
	int num_accept;
};

class Board 
{
public:
	Board(Player **P,int NP);
	~Board();
	
	int findRecord(const string&,const string&,History*,History*);
	void recordMatch(const string&,const string&,int,int,bool,bool);
	void showHistory(string);
	void showScores();
	
private:
	map< string, vector<History> > mBoard;
	map< string, int > mScore;
	map< string, Stat > mStat;
};

#endif
