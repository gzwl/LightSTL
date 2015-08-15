#include <cassert>
#include <queue>
#include <string>
#include <iostream>
#include "QueueTest.h"
#include "../Queue/Queue.h"

namespace LightSTL{

void QueueTest1()
{
    LightSTL::queue<int> q1;
    std::queue<int> q2;
    for(int i = 0;i < 100;i++) {
        q1.push(i);
        q2.push(i);
    }
    assert(q1.size() == q2.size());
    while(!q1.empty()){
        assert(q1.front() == q2.front());
        q1.pop();
        q2.pop();
    }

}

void QueueTest2()
{
    LightSTL::queue<std::string> q1;
    std::queue<std::string> q2;
    for(int i = 0;i < 100;i++) {
        q1.push(std::string("Zhang Weiliang"));
        q2.push(std::string("Zhang Weiliang"));
    }
    assert(q1.size() == q2.size());
    while(!q1.empty()){
        assert(q1.front() == q2.front());
        q1.pop();
        q2.pop();
    }
}

void QueueTest3()
{
    LightSTL::queue<int> q1;
    for(int i = 0;i < 100;i++) {
        q1.push(i);
    }
    LightSTL::queue<int> q2(q1);
    assert(q1.size() == q2.size());
    while(!q1.empty()){
        assert(q1.front() == q2.front());
        q1.pop();
        q2.pop();
    }
}

void QueueTestAll()
{
    QueueTest1();
    QueueTest2();
    QueueTest3();
    std::cout << "Queue pass the test!"  << std::endl;
}
}
