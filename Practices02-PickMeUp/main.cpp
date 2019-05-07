#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "pmu.h"

#define NRUNS	1000
#define	NMEETS	50
#define DEBUG

using namespace std;

int main(int argc, char** argv) 
{
	// declare any variable you want

	srand(time(NULL));
	
	double total_score = 0;
	for( int n=0 ; n<NRUNS ; n++ ) {
		
		int score, my_pick = -1;
		pmu_init(NMEETS);
		for( int i=0 ; i<NMEETS ; i++ ) {
			int cs = pmu_next();
			bool pick_this = false;
			
			// put your code here
			// example dumm code always picking the last
			if( i == NMEETS-1 && pick_this == false ) pick_this = true;
			else pick_this = false;
			
			double pick_probability = 100 -  2* (100 - double(cs) );
			double probability = ((double)rand()/RAND_MAX)*100;
			//cout << probability << "  " << pick_probability << endl;
			if( probability <= pick_probability ) pick_this = true;
			if( pick_this == true ) {
				my_pick = cs; 
				break;
			}
			
		}
		score = pmu_evaluate_and_clear(my_pick);
		total_score += score;
		
#ifdef DEBUG		
		cout << n+1 << "th trial score is " << score << " for pick " << my_pick << endl;
#endif
	}
	cout << "Final score is " << total_score/NRUNS/NMEETS << endl;

	return 0;
}

