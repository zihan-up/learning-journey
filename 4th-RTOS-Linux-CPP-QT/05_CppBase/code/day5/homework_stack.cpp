#include <iostream>
using std::cout;
using std::endl;

class Stack{
public:
    Stack(int capacity)
    :_capacity(capacity)
    ,_data(new int[capacity]())
    ,_index(-1)
    {

    }

    ~Stack(){
        if(_data){
            delete [] _data;
            _data = nullptr;
        }
    }
    bool empty();
    bool full();
    void push(const int & value);
    void pop();
    int top();


private:
    int _capacity;
    int * _data;
    int _index;
};
bool Stack::empty(){
    return _index == -1;
}
bool Stack::full(){
    return _index == _capacity - 1;
}
void Stack::push(const int & value){
    if(full()){
        cout << "the stack is full" << endl;
        return;
    }
    _data[++_index] = value;
}
void Stack::pop(){
    if(empty()){
        cout << "the stack is empty" << endl;
        return;
    }
    --_index;
}
int Stack::top(){
    return _data[_index];
}

void test(){
    Stack st(10);
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    st.push(6);
    st.push(7);
    st.push(8);
    st.push(9);
    st.push(10);
    st.push(5);
    for(int i = 0; i < 10; ++i){
        cout << st.top() << endl;
        st.pop();
    }
}

int main()
{
    test();
    return 0;
}

