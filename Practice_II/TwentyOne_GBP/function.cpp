#include <iostream>
#include <string>
#include "function.h"
using namespace std;

#define DEBUG 0

/* class Human */
// - init attributes
Human::Human(string n, int m, int ski) {
    name = n;
    money = m;
    skill = ski;
    kicked = false;
    cards = bets = 0;
}
int Human::get_money() { return money; }
Human::~Human() {}

/* class Guard */
// - init Guard by reusing Human constructor
Guard::Guard(int ski) : Human("_Guard", 0, ski) {}
// - 守衛技能小於玩家技能，需要付費讓他離場
void Guard::Pay(Human *human) {
    if (this->skill < human->skill) {
        int toPay = human->skill - this->skill;
        this->money -= toPay;
        human->money += toPay;
        if (DEBUG) cout << "--- guard pay " << toPay << endl;
    }
}
// - 踢出玩家，flag 判斷是作弊踢出或破產踢出，破產須付費
void Guard::Kick(Human *human, int flag) {
    human->kicked = true;
    if (flag) this->Pay(human);
    if (DEBUG) cout << "--- kick " << human->name << endl;
}

/* class Banker */
// - init Banker by reusing Human constructor
Banker::Banker(int ski) : Human("_Banker", 0, ski) {}
void Banker::Pay(Human *human) {
    if (human->name == "_Guard") {   // 叫守衛
        human->money += 100;
        this->money -= 100;
        if (DEBUG) cout << "--- call guard, guard money: " << human->money << endl;
    } else {   // 付錢給玩家
        int bonus = human->skill < this->skill ? 10 * human->cards : 0;
        int toPay = human->bets + bonus;
        if (human->cards == 21)
            toPay *= 2;
        this->money -= toPay;
        human->money += toPay;
        if (DEBUG) cout << "--- banker pay player " << human->name << toPay << endl;
    }
}
int Banker::Win(Human *human) {
    if (this->cards > 21 && human->cards > 21)
        return -1;   // 無視發生
    if (this->cards <= 21 && (human->cards > 21 || human->cards <= this->cards))
        return 1;    // 莊家贏
    if (human->cards <= 21 && (this->cards > 21 || human->cards > this->cards))
        return 0;    // 玩家營
}
void Banker::Draw() {
    int cards = 0, input;
    while (cin >> input) {
        cards += input;
        char ch = getchar();
        if (ch == '\n') break;
    }
    this->cards = cards;
    if (DEBUG) cout << "--- banker cards points " << this->cards << endl;
}
Banker::~Banker() {}


// class Player
Player::Player(string name, int m, int ski) : Human(name, m, ski) {}
void Player::Pay(Human *human) {
    if (this->money > this->bets) {
        human->money += this->bets;
        this->money -= this->bets;
        if (DEBUG) cout << "--- player pay, cur: " << this->money << endl;
    } else {
        human->money += this->money;
        this->money = 0;
        if (DEBUG) cout << "--- player pay, cur: " << this->money << endl;
    }
}
void Player::Bet() {
    string name;
    cin >> name;
    int bets;
    cin >> bets;
    this->bets = bets;
    if (DEBUG) cout << "--- init bet " << this->bets << endl;
}
void Player::Draw() {
    int cards = 0, input;
    while (cin >> input) {
        cards += input;
        char ch = getchar();
        if (ch == '\n') break;
    }
    this->cards = cards;
    if (DEBUG) cout << "--- player cards points " << this->cards << endl;
}
bool Player::Kicked() { if (DEBUG) cout << "*** kicked? " << kicked << endl; return kicked; }
bool Player::Bankrupt() { if (DEBUG) cout << "--- bankrupt? " << (this->money <= 0) << endl; return this->money <= 0; }
bool Player::Cheat(Human *human) {
    int bonus = this->skill < human->skill ? 10 * this->cards : 0;
    int toCheck = this->bets + bonus;
    if (this->cards == 21)
        toCheck *= 2;
    if (DEBUG) cout << "--- toCkeck " << toCheck << endl;
    return toCheck > 2 * this->skill;
}
Player::~Player() {}