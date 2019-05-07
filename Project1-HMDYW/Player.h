#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>

using namespace std;

class History 
{
public:
	History(int o=0,bool a=false) { offer=o; accept=a; }
	~History() {}
	int offer; 		// amount of the offered money by Offeror 
	bool accept;	// decision of Responder
};

class Player
{
public:
	Player() { }
	~Player() {	}
	string name() { return mName; }

	virtual int offer(const string &itsname,int money,const History *myoffer,const History *itsoffer,int nmatch) = 0;
	virtual bool accept(const string &itsname,int money,const History *myoffer,const History *itsoffer,int nmatch) = 0;

protected:
	string mName;
};

#endif
