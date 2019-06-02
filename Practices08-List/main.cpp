#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <string>

using namespace std;

struct Champion {
	string name;
	int health;
	Champion operator+(int n){

	};
};

void show_list(list<Champion> &LIST) {
	list<Champion>::iterator iter;
	for (iter = LIST.begin(); iter != LIST.end(); iter++) {
		cout << "(" << (*iter).name << "," << (*iter).health << ")-";
	}
	cout << endl;
}

bool compCham(const Champion &a, const Champion &b) {
	return a.name < b.name;
}

void sort_by_name(list<Champion> &LIST) {
	LIST.sort(compCham);
}

void remove(char *cham, list<Champion> &LIST) {
	list<Champion>::iterator iter;
	for (iter = LIST.begin(); iter != LIST.end(); iter++) {
		if ((*iter).name == string(cham)) {
			LIST.erase(iter);
			break;
		}
	}
}
//template <typename T>
const list<Champion>::iterator operator+(list<Champion>::iterator iter, int n) {
	for (int i = 0; i < n; i++) {
		iter++;
	}
	return iter;
}

const list<Champion>::iterator operator-(list<Champion>::iterator iter, int n) {
	for (int i = 0; i < n; i++) {
		iter--;
	}
	return iter;
}

int main() {
	string name_list[] = {"Vayne", "Mundo", "Elise", "Kayle"};
	double health_list[] = {498, 582, 529, 574};
	list<Champion> LIST;
	for (int i = 0; i < 4; i++) {
		Champion C = {name_list[i], health_list[i]};
		LIST.push_back(C);
	}
	show_list(LIST);
	Champion C = {string("Ashe"), 527};
	LIST.insert(LIST.begin() + 2, C);
	show_list(LIST);

	Champion D = {string("Sona"), 482};
	LIST.insert(LIST.end() - 1, D);
	show_list(LIST);
	sort_by_name(LIST);
	show_list(LIST);

	remove("Mundo", LIST);
	show_list(LIST);
}
