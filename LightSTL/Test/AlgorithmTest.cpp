#include "AlgorithmTest.h"
#include "../Algorithm/Algorithm.h"
#include <algorithm>
#include <iostream>
#include <cassert>

namespace LightSTL{

static bool cmp(int x,int y){
    return x > y;
}

void SortHeapTest()
{
    srand((unsigned)time(0));
    int a[10000];
    int b[10000];
    for(int i = 0;i < 10000;i++){
        int tmp = rand();
        a[i] = tmp;
        b[i] = tmp;
    }
    std::sort(a,a+10000);
    LightSTL::sort_heap(b,b+10000);
    for(int i = 0;i < 10000;i++)    assert(a[i] == b[i]);

}
void SortTest()
{
    int a[10000];
    int b[10000];
    srand((unsigned)time(0));
    for(int i = 0;i < 10000;i++){
        int tmp = rand();
        a[i] = tmp;
        b[i] = tmp;
    }
    std::sort(a,a+10000);
    LightSTL::sort(b,b+10000);
    for(int i = 0;i < 10000;i++)    assert(a[i] == b[i]);

    srand((unsigned)time(0));
    for(int i = 0;i < 10000;i++){
        int tmp = rand();
        a[i] = tmp;
        b[i] = tmp;
    }
    std::sort(a,a+10000,cmp);
    LightSTL::sort(b,b+10000,cmp);
    for(int i = 0;i < 10000;i++)    assert(a[i] == b[i]);

}

void AlgorithmTestAll()
{
    SortHeapTest();
    SortTest();
    std::cout << "Algorithm pass the test!" << std::endl;
}



}
