#include <cassert>
#include <stack>
#include <string>
#include <iostream>
#include "StackTest.h"
#include "../Stack/Stack.h"

namespace LightSTL{

void StackTest1()
{
    LightSTL::stack<int> q1;
    std::stack<int> q2;
    for(int i = 0;i < 10000;i++) {
        q1.push(i);
        q2.push(i);
    }
    assert(q1.size() == q2.size());
    while(!q1.empty()){
        assert(q1.top() == q2.top());
        q1.pop();
        q2.pop();
    }

}

void StackTest2()
{
    LightSTL::stack<std::string> q1;
    std::stack<std::string> q2;
    for(int i = 0;i < 10000;i++) {
        q1.push(std::string("Zhang Weiliang"));
        q2.push(std::string("Zhang Weiliang"));
    }
    assert(q1.size() == q2.size());
    while(!q1.empty()){
        assert(q1.top() == q2.top());
        q1.pop();
        q2.pop();
    }
}

void StackTest3()
{
    LightSTL::stack<int> q1;
    for(int i = 0;i < 10000;i++) {
        q1.push(i);
    }
    LightSTL::stack<int> q2(q1);
    assert(q1.size() == q2.size());
    assert(q1 == q2);
    while(!q1.empty()){
        assert(q1.top() == q2.top());
        q1.pop();
        q2.pop();
    }
    assert(q1.empty());
}

void StackTestAll()
{
    StackTest1();
    StackTest2();
    StackTest3();
    std::cout << "Stack pass the test!"  << std::endl;
}
}
