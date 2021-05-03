#include <iostream>
#include <string>
#include "function.h"
using namespace std;

#define DEBUG 1
// if (DEBUG) { cout << "---  " << "FK" << endl; }

/* Class Guest */
Guest::Guest() {}
Guest::Guest(string s, int m, int ski) { name = s, money = m, skill = ski; }
Guest::~Guest() {}
string Guest::get_name() { return name; }
int Guest::get_money() { return money; }
int Guest::get_skill() { return skill; }
void Guest::Win(int m) { money += m;
    if (DEBUG) { cout << "---  " << money << endl; } }

/* Class Casino */
Casino::Casino() { fee = income = guest_num = list_num = 0; }
Casino::~Casino() {}
void Casino::Enterance(int f) { fee = f; }
void Casino::GuestEnter(string s, int m, int ski) {
    // check exist
    for (int i = 0; i < guest_num; i++) {
        if (guest[i]->get_name() == s) {
            if (DEBUG) { cout << "---  " << "exist" << endl; }
            return;
        }
    }

    // check blacklist
    for (int i = 0; i < list_num; i++)
        if (blacklist[i] == s) {
            if (DEBUG) { cout << "---  " << "already in black." << endl; }
            return;
        }
    
    // check bankrupt
    if (m <= fee) {
        income += m;
        blacklist[list_num++] = s;
    } else {
        income += fee;
        Guest *newGuest = new Guest(s, m - fee, ski);
        guest[guest_num++] = newGuest;
    }
    if (DEBUG) { cout << "---  " << "Income: " << income << endl; }
}

void Casino::Win(string s, int m) {
    // check exist
    int idx = -1;
    for (int i = 0; i < guest_num; i++) {
        if (guest[i]->get_name() == s) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        if (DEBUG) { cout << "---  " << "not found" << endl; }
        return;
    }
    // check blacklist
    for (int i = 0; i < list_num; i++) {
        if (blacklist[i] == s) {
            if (DEBUG) { cout << "---  "<< s << " invalid win, black." << endl; }
            return;
        }
    }
    // out skill
    if (m > guest[idx]->get_skill() * 2) {
        if (DEBUG) { cout << "---  "<< s << " valid win, but out skill." << endl; }
        blacklist[list_num++] = s;
        income -= m;
    } else {   // not out
        if (DEBUG) { cout << "---  "<< "valid win" << endl; }
        int origin = guest[idx]->get_money();
        guest[idx]->Win(m);
        if (guest[idx]->get_money() > 0)
            income -= m;
        else {
            income = income - m + guest[idx]->get_money();
            blacklist[list_num++] = s;
        }
    }
    if (DEBUG) { cout << "---  " << "Income: " << income << endl; }
}

void Casino::EndDay() {
    // for (int i = 0; i < guest_num; i++)
    //     delete guest[i];
    guest_num = 0;
}

void Casino::Result() {
    cout << income << endl;
    for (int i = 0; i < list_num; i++)
        cout << blacklist[i] << endl;
}