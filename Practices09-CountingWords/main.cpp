// Please note that MinGW32 compilers currently do not support <thread>. Use MinGW64 builds like TDM-GCC instead.

#include <thread>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <set>
#include <mutex>
using namespace std;

vector<string> words;
map<string, int> word_cnt;
struct ThreadItem {
	// could've used stringstream too, but don't like their syntax
	thread worker;
};

void* ThreadFunction(map<string, int> *word_cnt, int from, int to, mutex *mtx) {
	lock_guard<mutex> lck(*mtx);
	for(auto iterw = words.begin() + from ; iterw != words.begin() + to; ++iterw){
		//if(mtx) mtx->lock();
		auto iwc = word_cnt->find(*iterw);
		
		//if(mtx) mtx->unlock();
		if(iwc == word_cnt->end()){
			word_cnt->insert(pair<string,int>(*iterw,1));
		}
		else{
			iwc->second += 1;
		}
	}
}

bool read_a_word(ifstream& in, string& w){
	return(in >> w);
}

int main() {
	ifstream in("text1.txt");
	if(!in.is_open()) exit(1);
	string word;
	while(read_a_word(in, word)){
		// reading each word
		/*for(auto iter = word.begin(); iter != word.end(); ++iter){
			if( (*iter >= 'a' && *iter <= 'z') || (*iter >= 'A' && *iter <= 'Z')){
			}
			else{
				word.erase(iter);
			}
		}*/
		words.push_back(word);
	}
	// put your code here
	
	// Get the amount of "processing units"
	int n = std::thread::hardware_concurrency();
	
	// Create array of threads
	vector<ThreadItem> threadlist;
	threadlist.resize(n);
	mutex mtx;
	// Spawn a thread for each core
	for(int i = 0;i < n;i++) {
		int from = i * words.size() / n;
		int to = i == n-1 ? words.size() : (i+1) * words.size() /n ;
		threadlist[i].worker = thread(ThreadFunction,&word_cnt,from, to, &mtx); // pass rand() as data argument
	}
	
	// Wait for them all to finish
	for(int i = 0;i < n;i++) {
		threadlist[i].worker.join();
	}
	
	// Present their calculation results
	typedef function<bool(pair<string, int>, pair<string, int>)> Comparator;
	Comparator cmp = [](pair<string,int> const & a, pair<string,int> const & b) 
	{ 
     return a.second > b.second;
	};
	set<pair<string, int>,Comparator> word_sortedByValue(
		word_cnt.begin(), word_cnt.end(), cmp
	);
	int i=0;
	for(auto &wc : word_sortedByValue) {
		//if(i == 10) break;
		i++;
		cout << wc.first << ":	 " << wc.second <<endl;
	}
	int onlyone = 0;
	for(auto iter = word_sortedByValue.rbegin(); iter != word_sortedByValue.rend(); ++iter ){
		if( iter->second > 1) break;
		else onlyone++;
	}
	cout << onlyone << endl;
}
