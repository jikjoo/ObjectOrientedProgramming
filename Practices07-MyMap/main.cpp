//define MyMap template claass here
#include <iostream>
#include <string>
using namespace std;

template <typename Tkey, typename Tval>
class MyMap {
public:
	MyMap(int size) {
		msize = size;
        keys = new Tkey[msize];
        vals = new Tval[msize];
        idx = 0;
	}
	~MyMap(){
        if(keys) delete [] keys;
        if(vals) delete[] vals;
        idx = 0;
    };
	void insert(Tkey key, Tval value);
	Tval* operator[](Tkey key);

private:
	int msize;
    Tkey *keys;
    Tval *vals;
    int idx;

};
template <typename Tkey, typename Tval>
void MyMap<Tkey, Tval>::insert(Tkey key, Tval value) {
    keys[idx] = key;
    vals[idx] = value;
    idx += 1;
}

template <typename Tkey, typename Tval>
Tval* MyMap<Tkey, Tval>::operator[](Tkey key) {
    for(int i=0; i<idx; i++ ){
        if(keys[i] == key) return &vals[i];
    }
    return NULL;
}

int main() {
	MyMap<string, int> M1(10);
	M1.insert("one", 1);
	M1.insert("two", 2);
	M1.insert("three", 3);
	if (M1["two"])
		cout << *M1["two"] << endl;
	else
		cout << "No Match" << endl;
	if(M1["ten"])
		cout << *M1["ten"] << endl;
	else
		cout << "No Match" << endl;
	MyMap<int, string> M2(10);
	M2.insert(10, "ten");
	M2.insert(20, "twenty");
	M2.insert(30, "thirty");
	if (M2[30])
		cout << *M2[30] << endl;
	else
		cout << "No matcch" << endl;
}