#pragma once

#include <vector>

template<typename T>
class StackVector
{
    std::vector<T> data;

public:
    std::vector<T>& getData();

    bool isEmpty() { return getData().empty(); };

    T    peek ();
    void pop  ();
    T    get  ();
    void push (T obj);

    T* at  (int pos);
};