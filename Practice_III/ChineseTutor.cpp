#include <iostream>
#include <string>
#include <map>
using namespace std;

// Dict[it->first] equals to it->second
// pair: it->first, it->second

map<string, string> Dict = {{"Wa", "Waninoko"}, {"Mi", "Milotic"}, {"Ma", "Magikarp"},\
                            {"Va", "Vaporeon"}, {"Sh", "Sharpedo"}, {"Tapu", "Tapu Fini"},\
                            {"Em", "Empoleon"}, {"La", "Lapras"}, {"Pi", "Pikachu"},\
                            {"Pe", "Pikachu"}, {"Me", "Mega Gyarados"}};
int main() {
    int T;
    cin >> T;
    while (T--) {
        string name, school, Key;
        cin >> name >> school;
        // cin.ignore();  加不加沒差
        Key.push_back(name[0]);
        Key.push_back(name[1]);
        if (Key == "Ta" && name.length() >= 4) {
            Key.push_back(name[2]);
            Key.push_back(name[3]);
        }
        // cout << "- Key: " << Key << endl;

        map<string, string>::iterator it = Dict.find(Key);
        if (it != Dict.end())
            cout << name << " the " << school << ' ' << it->second << endl;
        else
            cout << name << " is looking for a Chinese tutor, too!" << endl;
    }
}