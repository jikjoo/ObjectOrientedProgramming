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
#ifndef _PLAYER_2014170935_H_
#define _PLAYER_2014170935_H_

#include "setting.h"
#include "Player.h"

#ifndef _BOARD_H_
#include <map>
#include <vector>
#endif
// change "2017000000" to your real student id
class Player_2014170935: public Player
{
public:
	Player_2014170935() {
		mName = "Jikjoo"; 	// change "MyName" to your real name in English
		// add whatever
		initial_offer = MONEY_GIVEN * 0.50;
		initial_accept = MONEY_GIVEN * 0.10;
		cnt_offer = -1;
		
	}
	~Player_2014170935() { 
		// add whatever
		vMark.clear();
	}
 
	int offer(const string &itsname,int money,const History *myoffer,const History *itsoffer,int nmatch);
	bool accept(const string &itsname,int money,const History *myoffer,const History *itsoffer,int nmatch);

	
private:
	// declare whatever you want
	struct Mark {
		string name;
		int min_acc_offer; // current accepted minimum offer 
		int max_rej_offer; // maximum rejected offer
	};	
	vector<Mark> vMark;
	int initial_offer;
	int initial_accept;
	int cnt_offer; // count of total offer to other
	int num; // player number = vMark.size()
	int i; // current player number
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
int Player_2014170935::offer(const string &itsname,int money,const History *myoffer,const History *itsoffer,int nmatch)
{
	// implement your strategy
	//cout <<itsname << " offer "<< myoffer << " " << itsoffer <<"\n";
	
	int next_offer;
	cnt_offer++;
	if(nmatch == 0){	
		Mark mark;
		mark.name = itsname;
		mark.min_acc_offer = initial_offer;
		mark.max_rej_offer = 0;
		vMark.push_back(mark);
		next_offer =  initial_offer;
	}

	if(nmatch > 0 ) {
		num = vMark.size();
		i = cnt_offer % num;
		/*
		cout <<" i=" << i << itsname << " myoffer " << myoffer[i].offer << myoffer[i].accept << " itsoffer "
		 << itsoffer[i].offer << itsoffer[i].accept << endl;
		*/
	}
	if(itsname == "Colin Seok"){
		next_offer =  0;
	}
	else if(itsname == "Junhee Seok"){
		next_offer =  money/2;
	}
	else if(itsname == "Ebenezer Scrooge"){
		next_offer =  0;
	}
	else if(itsname == "Mother Teresa"){
		next_offer =  0;
	}
	else{
		if(nmatch > 0){
		
			Mark & it = vMark[i];
			int past_offer = myoffer[nmatch-1].offer;
			/*
			cout << it.name << it.min_acc_offer << it.max_rej_offer << endl;
			cout <<" i=" << i << itsname << " myoffer " << past_offer <<" " << myoffer[nmatch-1].accept << " diff "
				 << it.diff_offer << endl;
			*/
			if(myoffer[nmatch-1].accept){
				it.min_acc_offer = min(past_offer , it.min_acc_offer);
				if(next_offer < it.max_rej_offer) next_offer = past_offer;
				else next_offer = past_offer - 1;
			}
			else {
				it.max_rej_offer =  max( it.max_rej_offer , past_offer);
				next_offer = past_offer + 5;
			}
		}
	
	}
	
	return next_offer;
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
bool Player_2014170935::accept(const string &itsname,int money,const History *myoffer,const History *itsoffer,int nmatch)
{
	// implement your strategy
	if(itsname == "Colin Seok"){
		return true;
	}
	else if(itsname == "Junhee Seok"){
		return false;
	}
	else if(itsname == "Ebenezer Scrooge"){
		return false;
	}
	else if(itsname == "Mother Teresa"){
		return true;
	}
	else{
		if(nmatch == 0){
			if(money >= initial_accept)	return true;	
			else return false;
		}
		else{
			if(money >= vMark[i].min_acc_offer )	return true;	
			else return false;
		}
	}
		
		
	//cout << nmatch << endl;
	//cout <<itsname << " myoffer " << myoffer->offer << " myaccept " << myoffer->accept << endl;
	//cout <<itsname << " itsoffer " << itsoffer->offer << " itsaccept " << itsoffer->accept  <<"\n";
	

}


#endif
