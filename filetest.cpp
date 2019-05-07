#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *arv[]){
    ifstream infile("input.txt");
    char s[3];
    infile.seekg(3,ios::beg);
    infile.read(s,3);
    cout << s[1] <<endl;

    string x="Hello";
    cout << x[1] << endl;
    cout << *(x.c_str()+1) << endl;
    cout << x[x.find("lo")-1] << endl;
    cout << x.substr(1,2)[0] << endl;
    cout << endl << x.find("lo") << endl;
    return 0;
}