#include <iostream>
#include <string>
#include <map>
#include "setting.h"
#include "Player.h"
#include "Board.h"

using namespace std;

Board::Board(Player **P,int NP)
{
	for( int i=0 ; i<NP ; i++ ) {
		for( int j=0 ; j<NP ; j++ ) {
			if( i==j ) continue;
			string match_id = P[i]->name() + P[j]->name();
			vector<History> history;
			mBoard.insert(make_pair(match_id,history));
		}
	}
	
	for( int i=0 ; i<NP ; i++ ) {
		int score = 0;
		mScore.insert(make_pair(P[i]->name(),score));
		Stat stat = {0,0,0};
		mStat.insert(make_pair(P[i]->name(),stat));
	}
}

Board::~Board()
{
	
}

int Board::findRecord(const string& p1,const string& p2,History *hist1,History *hist2)
{
	string match_id;
	map< string,vector<History> >::iterator f;
	int nmatch;
		
	match_id = p1 + p2;
	f = mBoard.find(match_id);
	nmatch = f->second.size();
	for( int i=0 ; i<nmatch ; i++ ) hist1[i] = f->second.at(i);
	
	match_id = p2 + p1;
	f = mBoard.find(match_id);
	nmatch = f->second.size();
	for( int i=0 ; i<nmatch ; i++ ) hist2[i] = f->second.at(i);

	return nmatch;	
}

void Board::recordMatch(const string& p1,const string& p2,int offer1,int offer2,bool accept1,bool accept2)
{
	string match_id;
	map< string,vector<History> >::iterator f;
	
	// record
	match_id = p1 + p2;
	f = mBoard.find(match_id);
	f->second.push_back(History(offer1,accept2));
	match_id = p2 + p1;
	f = mBoard.find(match_id);
	f->second.push_back(History(offer2,accept1));

	// determine scores
	if( accept2 ) { mScore[p1] += MONEY_GIVEN-offer1; mScore[p2] += offer1; }
	if( accept1 ) { mScore[p1] += offer2; mScore[p2] += MONEY_GIVEN-offer2; }
	
	// stat
	mStat[p1].sum_offer += offer1;
	mStat[p1].sum_offered += offer2;
	mStat[p1].num_accept += (accept1)?1:0;
	mStat[p2].sum_offer += offer2;
	mStat[p2].sum_offered += offer1;
	mStat[p2].num_accept += (accept2)?1:0;
}

void Board::showHistory(string name)
{
	map<string,vector<History> >::iterator it;
	for( it = mBoard.begin() ; it != mBoard.end() ; it++ ) {
		if(it->first.find(name) == string::npos) continue;
		cout << it->first << " : ";
		for( int j=0 ; j<it->second.size() ; j++ ) {
			printf("(%3d,%c) ",it->second[j].offer,(it->second[j].accept==true)?'A':'R');
		}
		cout << endl;
	}	
}

void Board::showScores()
{
	map<string,int>::iterator it;
	printf("%20s %10s %10s %10s %10s %10s\n","Name","Score","AvgEarned","AvgOffer","AvgOffered","AcceptRate");
	for( it = mScore.begin() ; it != mScore.end() ; it++ ) {
		printf("%20s ",it->first.c_str());
		printf("%10d ",it->second);
		printf("%10.2f ",((double)it->second)/NUMMATCH/(mScore.size()-1));
		printf("%10.2f ",((double)mStat[it->first].sum_offer)/NUMMATCH/(mScore.size()-1));
		printf("%10.2f ",((double)mStat[it->first].sum_offered)/NUMMATCH/(mScore.size()-1));
		printf("%10.2f ",((double)mStat[it->first].num_accept)/NUMMATCH/(mScore.size()-1));		
		cout << endl;
	}
}


