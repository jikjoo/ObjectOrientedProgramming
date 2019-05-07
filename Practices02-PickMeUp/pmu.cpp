#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "pmu.h"

using namespace std;

static int *gData;
static int gIdx;
static int gSize;

static double randn(double mu, double sigma);
static void pmu_clear();

/******************************************************
 * global functions
 ******************************************************/

bool pmu_init(int num)
{
	if( num <= 0 ) return false;
	gData = new int[num];
	if( gData == NULL ) return false;
	gIdx = 0;
	gSize = num;
	
	for( int i=0 ; i<100 ; i++ ) rand();
	
	double mu = ((double)rand()/RAND_MAX)*100 - 50;
	double sigma = ((double)rand()/RAND_MAX)*50;
	//cout << mu << "  " << sigma << endl;
	for( int i=0 ; i<num ; i++ ) {
		gData[i] = abs((int)randn(mu,sigma));
	}
	
	return true;
}

int pmu_next()
{
	if( gIdx >= gSize ) return -1;
	return( gData[gIdx++] );
}

int pmu_evaluate_and_clear(int pick)
{
	int cnt = 0;
	bool is_in = false;
	for( int i=0 ; i<gSize ; i++ ) {
		if( gData[i] == pick ) is_in = true;
		if( gData[i] > pick ) cnt++;
	}
	if( is_in == false ) cnt = gSize;
	pmu_clear();
	return cnt;
}

/******************************************************
 * local static functions
 ******************************************************/

// randomly generate a number from a normal distirbution N(mu,sigma^2)
static double randn(double mu, double sigma)
{
	double U1, U2, W, mult;
	static double X1, X2;
	static int call = 0;
	
	if (call == 1) {
		call = !call;
		return (mu + sigma * (double) X2);
	}
 
 	do {
		U1 = -1 + ((double) rand () / RAND_MAX) * 2;
		U2 = -1 + ((double) rand () / RAND_MAX) * 2;
		W = pow (U1, 2) + pow (U2, 2);
	} while (W >= 1 || W == 0);
	
	mult = sqrt ((-2 * log (W)) / W);
	X1 = U1 * mult;
	X2 = U2 * mult;
	call = !call;
	return (mu + sigma * (double) X1);
}

static void pmu_clear()
{
	delete[] gData;
	gData = NULL;
	gIdx = 0;
	gSize = 0;
}


