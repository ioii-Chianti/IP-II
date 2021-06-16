#include <string>
#include <iostream>
using namespace std;

class Human {
    public:
        Human(string name, int age): Name(name), Age(age) {
            cout << "Human " << name << " created" << endl;
        }

        virtual void SelfIntroduce() {
            cout << "Hello! My name is " << this->Name;
            cout << ", " << this->Age << " years old." << endl;
        }
    protected:
        string Name;
        int Age;
};

class Engineer : public Human {
    public:
        Engineer(string name, int age): Human(name, age) {}
        virtual void WriteCode() {
            cout << "Coding..." << endl;
        }
};
class Poorgramer : public Engineer{
    public:
        Poorgramer(string name, int age): Engineer(name, age) {}
        virtual void SelfIntroduce() {
            cout << "Hello! My name is " << this->Name;
            cout << ", " << this->Age << " years old." << endl;
            cout << "As a poorgramer, I have to write code day and night." << endl;
        }
};

int main(){
    Poorgramer Mike("Mike", 18);
    Mike.SelfIntroduce();
    Mike.WriteCode();
    return 0;
}