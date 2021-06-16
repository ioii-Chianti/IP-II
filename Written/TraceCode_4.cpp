#include <iostream>
class Foo {
    public:
        /* virtual */ void print() { std::cout << "Foo\n"; }
};
class Bar : public Foo {
    public:
    void print() { std::cout << "Bar\n"; }
};
int main() {
    Foo a;
    a.print();
    Bar b;
    b.print();
    Foo* c = new Bar();
    c->print();
    return 0;
}