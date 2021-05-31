#include <iostream>
using namespace std;

template <class T>
class circular_buffer {
    public:
        circular_buffer(int);
        ~circular_buffer();   // delete [] arr;
        void push_back(T);
        void pop_front();
        int size();
        T operator[](int);

    private:
        int front, rear, capacity, sz;
        T *arr;
};

int main() {
    int capacity;
    cin >> capacity;
    circular_buffer<int> cbi(capacity);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "push_back") {
            int data;
            cin >> data;
            cbi.push_back(data);
        } else if (cmd == "pop_front")
            cbi.pop_front();
        else if (cmd == "print") {
            for (int j = 0; j < cbi.size(); j++)
                cout << cbi[j] << endl;
            cout << "----" << endl;
        }
    } return 0;
}

/* 寫在外面每次都要 !!!
    template <class T>
    retType className<T>::function() */
template <class T>
circular_buffer<T>::circular_buffer(int capacity) {
    this->capacity = capacity;
    front = rear = sz = 0;
    arr = new T[capacity];
}

template <class T>
circular_buffer<T>::~circular_buffer() { delete [] arr; }

template <class T>
void circular_buffer<T>::push_back(T input) {
    if (sz == capacity)
        pop_front();   // if buffer if full
    arr[rear++] = input;
    rear = (rear == capacity) ? 0 : rear;
    sz++;
}   // check boundary

template <class T>
void circular_buffer<T>::pop_front() {
    if (sz) {
        front = front + 1 != capacity ? front + 1 : 0;
        sz--;
    }   // check boundary
}

template <class T>
int circular_buffer<T>::size() { return sz; }

template <class T>
T circular_buffer<T>::operator[](int index) {
    int idx = front + index >= capacity ? front + index - capacity : front + index;
    return arr[idx];        // check if out of range
}