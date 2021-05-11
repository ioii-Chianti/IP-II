#include <string>
using namespace std;

class Guest {
public:
	Guest();   // default empty
	Guest(string s, int m, int ski);   // set private attributes
	~Guest();   // default empty
	string get_name();   // get private attribute: name
	int get_money();   // get private attribute: money
	int get_skill();   // get private attribute: skill
	void Win(int m);   // 
	
private:
	string name;
	int money;
	int skill;
};

class Casino {
public:
	Casino();
	~Casino();
	void Enterance(int f);
	void GuestEnter(string s, int m, int ski);
	void Win(string s, int m);
	void EndDay();
	void Result();
	
private:
	int fee;
	
	int guest_num;
	Guest *guest[1009];   // 陣列裡面都是 Guest 物件的指標
	
	int income;
	int list_num;
	string blacklist[1009];
};
