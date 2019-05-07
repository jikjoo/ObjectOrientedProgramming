/********************************************************
 This is the code you need to modify.
 
 IMPORTANT NOTE
 1. Change "2017000000" in the filename, class name, 
   preprocessing statements to your real student id.
 2. Change "MyName" in the constructor to your real name.
 
 These two changes are very important to grade your submission.
 If you miss the changes, you will have a penalty.
 
**********************************************************/

// change "2017000000" to your real student id
#ifndef _PLAYER_TEST_H_
#define _PLAYER_TEST_H_

#include "setting.h"
#include "Player.h"
#include <sstream>

// change "2017000000" to your real student id
class Player_test: public Player
{
public:
  	int offer_test;
  	int accept_test;
	Player_test( int offering, int acceptlimit) {
		mName = "test "+ int2str(offering) +"_" + int2str(acceptlimit)  ; 	// change "MyName" to your real name in English
		// add whatever
    offer_test = offering;
    accept_test = acceptlimit;
	}
	~Player_test() { 
		// add whatever
	}

	int offer(const string &itsname,int money,const History *myoffer,const History *itsoffer,int nmatch);
	bool accept(const string &itsname,int money,const History *myoffer,const History *itsoffer,int nmatch);
		
private:
	// declare whatever you want
	//int myTotal= 0;
	string int2str(int num){
		std::stringstream ss;
		ss << num;
		return ss.str();
	}
};


/********************************************************
  this function is for the strategy when you offer.
  the returned value is the money you want to offer.

  itsname: the name of the other player
  money: the maximum money you can offer
  myoffer: a vector of pairs of your offer and the other's response
           showing results of games with "itsname" when you offered
  itsoffer: a vector of pairs of the other's offer and your response
           showing results of games with "itsname" when he/she offered
  nmatch: number of game sets, i.e. the length of "myoffer" and "itsoffer" vectors
**********************************************************/
int Player_test::offer(const string &itsname,int money,const History *myoffer,const History *itsoffer,int nmatch)
{
	// implement your strategy
	return offer_test+rand()%10-5;	
}

/********************************************************
  this function is for the strategy when you response for the offer.
  the returned value is true if you want to accept, or false if you want reject.

  itsname: the name of the other player
  money: offered money by "itsname"  
  myoffer: a vector of pairs of your offer and the other's response
           showing results of games with "itsname" when you offered
  itsoffer: a vector of pairs of the other's offer and your response
           showing results of games with "itsname" when he/she offered
  nmatch: number of game sets, i.e. the length of "myoffer" and "itsoffer" vectors
**********************************************************/
bool Player_test::accept(const string &itsname,int money,const History *myoffer,const History *itsoffer,int nmatch)
{
	// implement your strategy
	if(money >= accept_test+rand()%10-5)	return true;	
	else return false;
}

#endif
