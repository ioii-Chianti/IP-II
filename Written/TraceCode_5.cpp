#include <iostream>
#include <cmath> 
using namespace std;

template<typename T, class Func>   // 使用的 class 也可參數化，因有同名不同類的成員
void ForEach(T _begin, T _end, Func _func) {   // 叫一個 Func class 的物件
    for (; _begin != _end; _begin++) {
        _func(*_begin);    // 物件呼叫 operator()
    }
};
struct Power {
    int exp = 2;
    void operator() (double& base) {
        cout << "base: " << base << endl;
        base = std::pow(base, exp);
    }
};
class Test {
    public:   // struct 預設是 public，class 則是 private
        void operator() (int& hello) {
            cout << "hello: " << hello << endl;
        }
};
// 可以被當成 class 傳入 template，生成 function object
void Hello() { cout << "HHHELO" << endl; }

int main() {
    double A[] = {1, 2, 3, 4, 5};
    ForEach(A, A + 5, Power());
    for (auto v : A)
        std::cout << v << ' ';
    std::cout << std::endl;
    return 0;
}