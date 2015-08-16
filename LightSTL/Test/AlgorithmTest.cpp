#include "AlgorithmTest.h"
#include "../Algorithm/Algorithm.h"
#include <algorithm>
#include <iostream>
#include <cassert>

namespace LightSTL{

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

void AlgorithmTestAll()
{
    SortHeapTest();
    std::cout << "Algorithm pass the test!" << std::endl;
}



}
