#include <iostream>
#include <string>
#include <sstream>    //for stringstream and its member functions
#include <cctype>     //for isdigit() && isalpha()
#include "function.h"
using namespace std;

void RleCodec::encode()
{
	stringstream ss;
	int count = 0;
	char temp = code_str.front();    //get code_str[0]
	for (auto c : code_str) {        //for(int i=0; code_str[i] != '\0'; i++)
		if (c == temp)           //c == code_str[i]
			count++;
		else {
			if (count == 1)
				ss << temp;
			else if (count == 2)
				ss << temp << temp;
			else if (count > 2)
				ss << count << temp;
			temp = c;
			count = 1;
		}
	}
	if (count == 1)
		ss << temp;
	else if (count == 2)
		ss << temp << temp;
	else if (count > 2)
		ss << count << temp;
	code_str = ss.str();
	encoded = true;
}

void RleCodec::decode()
{
	stringstream ss;
	stringstream int_ss;    //to convert numbers from string to int
	for (auto c : code_str) {
		if (isdigit(c))
			int_ss << c;
		else if (isalpha(c)) {
			int count = 0;
			int_ss >> count;
			if (count == 0)
				ss << c;
			else {
				while (count--) {
					ss << c;
				}
			}
			int_ss.str("");    //don't forget to clear int_ss
			int_ss.clear();    //don't forget to clear int_ss
		}
	}
	code_str = ss.str();
	encoded = false;
}