#include "Bingo.h"
#include "setting.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>

// default players
#include "Bingo_ColinSeok.h"
#include "Bingo_JunheeSeok.h"

// student players
// change "20160000" to your student id
#include "Bingo_2014170935.h"
#include "Bingo_2014170935_0.h"
#include "Bingo_2014170935_1.h"
#include "Bingo_2014170935_2.h"

map<string, int> SCORE;

using namespace std;

int main(int argc, char *argv[]) {
	srand(time(NULL));

	// generate instant
	Bingo *Players[MAXPLAYERS];
	int NumPlayers = 0;

	// dummy players
	Players[NumPlayers++] = new Bingo_JunheeSeok;
	Players[NumPlayers++] = new Bingo_ColinSeok;

	// add your player here by changing "20160000" to your student id
	//	Players[NumPlayers++] = new Bingo_2014170935;
	Players[NumPlayers++] = new Bingo_2014170935_0;
	Players[NumPlayers++] = new Bingo_2014170935_1;
	Players[NumPlayers++] = new Bingo_2014170935_2;

	// initialize score
	for (int i = 0; i < NumPlayers; i++)
		SCORE[Players[i]->name()] = 0;

	// matches
	for (int nmatch = 0; nmatch < NUMMATCH; nmatch++) {
		for (int i = 0; i < NumPlayers; i++) {
			for (int j = i + 1; j < NumPlayers; j++) {
				Bingo *P1 = Players[i], *P2 = Players[j];
				int callHistory1[BINGO_SIZE * BINGO_SIZE], callHistory2[BINGO_SIZE * BINGO_SIZE];
				int turn = 0;
				// ready
				P1->genMat(BINGO_SIZE);
				P2->genMat(BINGO_SIZE);
				// play
				while (turn < BINGO_SIZE * BINGO_SIZE) {
					// call a number
					int call1 = P1->myCall(callHistory2, callHistory1, turn);
					int call2 = P2->myCall(callHistory1, callHistory2, turn);
					// save to history
					callHistory1[turn] = call1;
					callHistory2[turn] = call2;
					turn++;
					// mark
					P1->markMine(call1);
					P2->markMine(call1);
					P1->markMine(call2);
					P2->markMine(call2);
#ifdef DEBUG
					// show
					//cout << P1->name() << endl;
					P1->show();
					//cout << P2->name() << endl;
					P2->show();
					cout << endl;
#endif
					// check bingo
					bool bingo1 = P1->isBingo(), bingo2 = P2->isBingo();
#ifdef DEBUG_LAST
					if (bingo1 || bingo2) {
						P1->show();
						P2->show();
						cout << endl;
					}
#endif
					if (bingo1 == true && bingo2 == false) {
						SCORE[P1->name()] += 3;
						break;
					} else if (bingo1 == false && bingo2 == true) {
						SCORE[P2->name()] += 3;
						break;
					} else if (bingo1 == true && bingo2 == true) {
						SCORE[P1->name()] += 1;
						SCORE[P2->name()] += 1;
						break;
					}
				}
			}
		}
	}

	// show scores by rank
	multimap<int, string> RANK;
	map<string, int>::iterator it;
	for (it = SCORE.begin(); it != SCORE.end(); it++) {
		RANK.insert(make_pair(-(it->second), it->first));
	}
	multimap<int, string>::iterator it2;
	for (it2 = RANK.begin(); it2 != RANK.end(); it2++) {
		cout << it2->second << ": \t" << -(it2->first) << endl;
	}
	return 0;
}
