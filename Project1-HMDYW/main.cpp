#include <iostream>
#include <ctime>
#include <cstdlib>
#include "setting.h"
#include "Player.h"
#include "Board.h"

// dummy players
#include "Player_Teresa.h"
#include "Player_Scrooge.h"
#include "Player_JunheeSeok.h"
#include "Player_ColinSeok.h"
#include "Player_test.h"

// student players
// change "2017000000" to your student id
#include "Player_2014170935.h"

using namespace std;

int main(int argc, char** argv) 
{
	srand(time(NULL));
	
	// generate instants
	Player *Players[MAXPLAYERS];
	int NumPlayers = 0;
	
	// dummy players
	Players[NumPlayers++] = new Player_Teresa;
	Players[NumPlayers++] = new Player_Scrooge;
	Players[NumPlayers++] = new Player_JunheeSeok;
	Players[NumPlayers++] = new Player_ColinSeok;
	// student players
	// change "2017000000" to your student id
	Players[NumPlayers++] = new Player_2014170935;
	
	for(int i=40; i<=60;i+=10){ //offer range
		for (int j=40;j<=60; j+= 10){ // accept range
			Players[NumPlayers++] = new Player_test(i,j);
		}
	}
	// creat a score board
	Board B(Players,NumPlayers);

	// matches
	for( int nmatch = 0 ; nmatch < NUMMATCH ; nmatch++ ) {
		for( int i=0 ; i<NumPlayers ; i++ ) {
			for( int j=i+1 ; j<NumPlayers ; j++ ) {
				// find match records
				History hist1[NUMMATCH], hist2[NUMMATCH];
				int n = B.findRecord(Players[i]->name(),Players[j]->name(),hist1,hist2);
				// turns for offer
				int offer1 = Players[i]->offer(Players[j]->name(),MONEY_GIVEN,hist1,hist2,n);
				int offer2 = Players[j]->offer(Players[i]->name(),MONEY_GIVEN,hist2,hist1,n);
				// check offers
				if( offer1>MONEY_GIVEN ) offer1 = MONEY_GIVEN;
				if( offer1<0 ) offer1 = 0;
				if( offer2>MONEY_GIVEN ) offer2 = MONEY_GIVEN;
				if( offer2<0 ) offer2 = 0;
				// turns for response
				bool accept1 = Players[i]->accept(Players[j]->name(),offer2,hist1,hist2,n);
				bool accept2 = Players[j]->accept(Players[i]->name(),offer1,hist2,hist1,n);
				// recording matches
				B.recordMatch(Players[i]->name(),Players[j]->name(),offer1,offer2,accept1,accept2);
			}
		}
	}
	//B.showHistory("Jikjoo");
	B.showScores();

	return 0;
}
