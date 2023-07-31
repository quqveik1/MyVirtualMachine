#pragma once


class Stack
{
    std::stack<int> data;

public:
    std::stack<int>& getData();

    bool isEmpty() { return getData().empty(); };

    int peek();
    int get();
    void push(int obj);
};