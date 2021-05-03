#include <iostream>
#include <string>
#include "function.cpp"
using namespace std;

int n;   // # of days
Casino casino = {};

int main() {
	cin >> n;
	for (int i = 0; i < n; ++ i) {
		string op;   // Guest | Win
		int q, fee;   // # of events on current day, fee on current day
		
		cin >> op >> q >> fee;
		casino.Enterance(fee);
		for (int j = 0; j < q; ++ j) {
			cin >> op;
			if (op == "Guest") {
				string name; 
				int money, skill;
				cin >> name >> money >> skill;
				casino.GuestEnter(name, money, skill);
			} 
			else if (op == "Win") {
				string name;
				int money;
				cin >> name >> money;
				casino.Win(name, money);
			}
		}
		casino.EndDay();
	}
	casino.Result();
}
