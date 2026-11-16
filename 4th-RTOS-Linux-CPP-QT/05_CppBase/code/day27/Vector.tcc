
template<typename T>
Vector<T>::Vector()
: _start(nullptr)
, _finish(nullptr)
, _end_of_storage(nullptr)
{
}

template<typename T>
Vector<T>::~Vector()
{
    if(_start)
    {
        //销毁空间上的对象，以及释放空间
        while(_start != _finish)
        {
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start, capacity());
    }
}

template<typename T>
void Vector<T>::push_back(const T &value)
{
    if(size() == capacity())
    {
        //需要扩容
        reallocate();
    }

    if(size() < capacity())
    {
        //在容器的尾部构建对象
        _alloc.construct(_finish++, value);
    }
}

template<typename T>
void Vector<T>::pop_back()
{
    if(size() > 0)
    {
        _alloc.destroy(--_finish);//销毁对象
    }
}

template<typename T>
int Vector<T>::size() const
{
    return _finish - _start;
}

template<typename T>
int Vector<T>::capacity() const
{
    return _end_of_storage  - _start;
}

template<typename T>
void Vector<T>::reallocate()//重新分配内存,动态扩容要用的
{
    //1、申请两倍的空间
    int oldCapacity = size();
    int newCapacity = 2 * oldCapacity > 0 ? 2 * oldCapacity : 1;
    T *ptmp = _alloc.allocate(newCapacity);

    if(_start)
    {
        //2、将老空间上的对象拷贝到新的空间来
        uninitialized_copy(_start, _finish, ptmp);
        //3、销毁老的空间上的对象，以及释放老的空间
        while(_start != _finish)
        {
            /* _alloc.destroy(_start++); */
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start, oldCapacity);
    }
    //4、将三个指针指向新的空间
    _start = ptmp;
    _finish = ptmp + oldCapacity;
    _end_of_storage = ptmp + newCapacity;
}

