#include <fstream>
#include <iostream>

using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int find_subseq(string & genome,string&  subseq, int * loc, int mm);

int main(int argc, char** argv) {
  ifstream infile("tp53.txt");
  if (!infile.is_open()) {
    cout << "cannot open file" << endl;
    exit(-1);
  }

  string line;
  string genome = "";
  while (getline(infile, line)) {
    if (line[0] != '>') genome += line;
  }
  infile.close();

  int num[4] = {0, 0, 0, 0};
  for (int i = 0; i < genome.length(); i++) {
    if (genome[i] == 'A')
      num[0]++;
    else if (genome[i] == 'C')
      num[1]++;
    else if (genome[i] == 'T') num[2]++;
	else if (genome[i]=='G') num[3]++;
  }
  for(int i=0; i< 4; i++) cout << num[i] << " ";
  cout << endl;

  int loc[genome.length()], nloc;
  string subseq = "TTCCTAGCG";
  int mm = 3;
  nloc = find_subseq(genome,subseq,loc,mm);
  cout << "matches with " << subseq;
  cout << " allowing " << mm;
  cout << " mismatches are " << nloc << endl;
  return 0;
}

int find_subseq(string & genome,string & subseq, int * loc, int mm){
	int nloc = 0;
  int size = subseq.size();
  int current = 0;
  string  substr;
  for( ; current < genome.size() ; current+=1){
    substr = genome.substr(current,current+size);
    int notmatch = 0;
    for(int t=0; t<size ; t++){
      if(substr[t] != subseq[t]) notmatch++;
    }
    if(notmatch <= mm){
      loc[current] = notmatch;  
      nloc += 1;
    } 
  }
  
	return nloc;
}
