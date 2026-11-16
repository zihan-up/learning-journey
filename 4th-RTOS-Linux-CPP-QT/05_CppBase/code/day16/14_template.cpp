#include <iostream>
#include <string>
using std::cout;
using std::string;
using std::endl;
//使用模板来对Stack进行重构
//之前实现stack的时候，设定了一个容量
//stack需要设定一个容量，
//之前的作业是使用构造函数来进行初始化
//现在也可以直接在模板中定义一个非类型参数
//类模板-------实例化---------->模板类(会是int、double等数据类型)
template <class T, int capacity = 10>
class Stack{
public:
    Stack()
    :_data(new T[capacity]())
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
    void push(const T & value);
    void pop();
    T top();

private:
    //int * _data;
    T * _data;
    int _index;
};

template <class T,int capacity>
bool Stack<T,capacity>::empty(){
    return _index == -1;
}
template <class T,int capacity>
bool Stack<T,capacity>::full(){
    return _index == capacity - 1;
}
    
template <class T,int capacity>
void Stack<T,capacity>::push(const T & value){
    if(full()){
        cout << "the stack is full" << endl;
        return;
    }
    _data[++_index] = value;
}
template <class T,int capacity>
void Stack<T,capacity>::pop(){
    if(empty()){
        cout << "the stack is empty" << endl;
        return;
    }
    --_index;
}

template <class T,int capacity>
T Stack<T,capacity>::top(){
    return _data[_index];
}


void test(){
    Stack<int,20> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    st.push(6);
    while(!st.empty()){
        cout << st.top() << endl;
        st.pop();
    }

    cout << "==============" << endl;
    Stack<string,15> st2;
    st2.push("hello");
    st2.push("world");
    st2.push("python");
    while(!st2.empty()){
        cout << st2.top() << endl;
        st2.pop();
    }
}

int main()
{
    test();
    return 0;
}

