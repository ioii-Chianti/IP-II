#include <iostream>
#include <sstream>
#include <string>
#include "function.h"
using namespace std;

/* class Human */

// init attributes
Human::Human(string n, int m, int ski) {
    name = n;
    money = m;
    skill = ski;
    kicked = false;
    cards = bets = -1;
}

int Human::get_money() { return money; }

Human::~Human() {}


/* class Guard */

// init Guard by reusing Human constructor
Guard::Guard(int ski) : Human("_Guard", 0, ski) {}

// 守衛技能小於玩家技能，需要付費讓他離場
void Guard::Pay(Human *human) {
    if (this->skill < human->skill) {
        int toPay = human->skill - this->skill;
        this->money -= toPay;
        human->money += toPay;
    }
}

// 踢出玩家，flag 判斷是作弊則確認要不要付費
void Guard::Kick(Human *human, int flag) {
    human->kicked = true;
    if (flag) this->Pay(human);
}

/* class Banker */

// init Banker by reusing Human constructor
Banker::Banker(int ski) : Human("_Banker", 0, ski) {}

void Banker::Pay(Human *human) {
    if (human->name == "_Guard") {   // call and pay guard
        human->money += 100;
        this->money -= 100;
    } else {   // pay to player
        int bonus = human->skill < this->skill ? 10 * human->cards : 0;
        int toPay = human->bets + bonus;
        if (human->cards == 21)
            toPay *= 2;
        this->money -= toPay;
        human->money += toPay;
    }
}

int Banker::Win(Human *human) {
    if (this->cards > 21 && human->cards > 21)
        return -1;   // nothing happens
    if (this->cards <= 21 && (human->cards > 21 || human->cards <= this->cards))
        return 1;    // Banker wins
    if (human->cards <= 21 && (this->cards > 21 || human->cards > this->cards))
        return 0;    // Player wins
}

void Banker::Draw() {
    string input;
    getline(cin, input);
    stringstream buf(input);   // make input a string buffer

    int point, cards = 0;
    while (buf >> point)   // then take int data from buffer
        cards += point;
    this->cards = cards;
}

Banker::~Banker() {}


/* class Player */

Player::Player(string name, int m, int ski) : Human(name, m, ski) {}

void Player::Pay(Human *human) {
    if (this->money > this->bets) {
        human->money += this->bets;
        this->money -= this->bets;
    } else {   // money <= bet
        int toPay = this->money;
        this->money = 0;
        human->money += toPay;
    }
}

void Player::Bet() {
    string name;
    cin >> name;
    // cin.ignore();
    int bets;
    cin >> bets;
    this->bets = bets;
}

void Player::Draw() {
    string input, ignore;
    getline(cin, ignore);   // ignore last '\n'
    // cin.ignore();
    getline(cin, input);
    stringstream buf(input);   // make input a buffer

    int point, cards = 0;
    while (buf >> point)   // then take int data from buffer
        cards += point;
    this->cards = cards;
}

bool Player::Kicked() { return kicked; }

bool Player::Bankrupt() { return money <= 0; }

bool Player::Cheat(Human *human) {
    int bonus = this->skill < human->skill ? 10 * this->cards : 0;
    int toCheck = this->bets + bonus;
    if (this->cards == 21)
        toCheck *= 2;
    return toCheck > 2 * this->skill;
}

Player::~Player() {}