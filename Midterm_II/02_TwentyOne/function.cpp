#include <sstream>
#include <cstring>
#include <iostream>
#include <string.h>
#include "function.h"
#define DEBUG 0
using namespace std;

/* HUMAN */
Human::Human(string n, int m, int ski) : name(n), money(m), skill(ski), bets(-1), cards(-1) {}
Human::~Human() {}
void Human::Draw() {
    this->cards = 0;
    string res = "";
    while (res.size() <= 0)
        getline(cin, res);
    stringstream ss(res);
    while (ss >> res) {
        int temp = 0;
        for (auto i : res)
            temp = temp * 10 + i - '0';
        this->cards += temp;
    }
}

/* GUARD */
Guard::Guard(int ski) : Human("_Guard", 0, ski) {}
void Guard::Pay(Human *human) {
    if (this->skill < human->skill && !human->Bankrupt()) {
        int toPay = human->skill - this->skill;
        human->money += toPay;
        this->money -= toPay;
        if (DEBUG) { cout << "--- guard money: " << this->money << endl; }
    }
}

/* BANKER */
Banker::Banker(int ski) : Human("_Banker", 0, ski) {}
Banker::~Banker() {}
void Banker::Pay(Human *human) {
    if (human->name == "_Guard") {
        human->money += 100;
        this->money -= 100;
    } else {
        int bonus = human->skill < this->skill ? 10 * human->cards : 0;
        int toPay = human->bets + bonus;
        if (human->cards == 21)
            toPay *= 2;
        this->money -= toPay;
        human->money += toPay;
        if (DEBUG) { cout << "--- banker money: " << this->money << endl; }
    }
}
int Banker::Win(Human *human) {
    if (human->cards > 21 && this->cards > 21)
        return -1;
    if (this->cards <= 21 && (human->cards > 21 || this->cards >= human->cards))
        return 1;
    if (human->cards <= 21 && (this->cards > 21 || human->cards > this->cards))
        return 0;
}


/* SERVER */
Server::Server(int ski) : Human("_Server", 0, ski) {}
Server::~Server() {}

/*PLAYER*/
Player::Player(string name, int m, int ski) : Human(name, m, ski) {}
Player::~Player() {}
void Player::Pay(Human *human) {
    int toPay = bets < money ? bets : money;
    this->money -= toPay;
    human->money += toPay;
    if (DEBUG) { cout << "--- player money: " << this->money << endl; }
    if (DEBUG) { cout << "--- banker money: " << human->money << endl; }
}
void Player::Bet() {
    int bets;
    cin >> bets;
    this->bets = bets;
}
bool Player::Bankrupt() { return money <= 0; }
bool Player::Cheat(Human *human) {
    int bonus = this->skill < human->skill ? 10 * this->cards : 0;
    int toPay = this->bets + bonus;
    if (this->cards == 21)
        toPay *= 2;
    return 3 * this->skill < toPay;
}
void Player::Order(Human *banker, Human *server) {
    this->money -= 3000;
    banker->money += 2000;
    server->money += 1000;
}

/* CASINO */
Casino::Casino() { fee = U = total_income = today_income = player_num = blacklist_num = 0; }
Casino::~Casino () {}
void Casino::Enterance(int f, int u) { fee = f, U = u; }
void Casino::Guest(string s, int m, int ski) {
    for (int i = 0; i < player_num; i++)
        if (player[i]->name == s)
            return;
    for (int i = 0; i < blacklist_num; i++)
        if (blacklist[i] == s)
            return;
    if (m <= this->fee) {
        blacklist[blacklist_num++] = s;
        return;
    }
    player[player_num++] = new Player(s, m - fee, ski);
    total_income += fee;
    if (DEBUG) { cout << "--- enter casino: " << s << endl; }
}
void Casino::TwentyOne() {
    int banker_ski, guard_ski, server_ski, K;
    cin >> banker_ski >> guard_ski >> server_ski >> K;
    banker = new Banker(banker_ski);
    guard = new Guard(guard_ski);
    server = new Guard(server_ski);

    string str;
    int joined[1009] = {};
    for (int i = 0; i < K; i++) {
        cin >> str;
        int flag = 1;
        Player* new_player = new Player(str, 0, 0);
        new_player->Bet();
        new_player->Draw();

        for (int j = 0; j < this->blacklist_num; j++) {
            if (this->blacklist[j] == str) {
                flag = 0;
                break;
            }
        }
        if (flag)
            for (int j = 0; j < this->player_num; j++) {
                if (this->player[j]->name == str) {
                    joined[j] = 1;
                    this->player[j]->bets = new_player->bets;
                    this->player[j]->cards = new_player->cards;
                }
            }
        delete new_player;
    }
    this->banker->Draw();

    // your twnety one rule
    for (int i = 0; i < this->player_num; i++) {
        if (joined[i] == 1) {
            // nobody wins
            if (banker->Win(player[i]) == -1)
                continue;

            // Banker wins
            if (banker->Win(player[i])) {
                player[i]->Pay(banker);
                if (player[i]->Bankrupt()) {
                    blacklist[blacklist_num++] = player[i]->name;
                    banker->Pay(guard);
                    guard->Pay(player[i]);
                }
            } else {   // player wins
                banker->Pay(player[i]);
                if (player[i]->Cheat(banker)) {
                    blacklist[blacklist_num++] = player[i]->name;
                    banker->Pay(guard);
                    guard->Pay(player[i]);
                }
                if (player[i]->money > server->skill)
                    player[i]->Order(banker, server);
            }
        }
    }
    // print out result
    cout << banker->money << " " << guard->money << " " << server->money << endl;
    for (int i = 0; i < player_num; i++)
        if (joined[i])
            cout << player[i]->name << " " << player[i]->money << endl;
    today_income += banker->money;

    delete banker;
    delete guard;
    delete server;
}
void Casino::EndDay() {
    total_income += today_income;
    if (today_income >= U) 
        blacklist_num = 0;
    player_num = 0;
    today_income = 0;
}
void Casino::Result() {
    cout << total_income << endl;
    for (int i = 0; i < blacklist_num; i++)
        cout << blacklist[i] << endl;
}