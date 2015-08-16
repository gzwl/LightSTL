#include "HashMapTest.h"
#include "../HashMap/HashMap.h"
#include "../Pair/Pair.h"
#include <cassert>
#include <iostream>

namespace LightSTL{

void HashMapTest1()
{
    LightSTL::hash_map<int,int> mapint;
    for(int i = 0;i < 2000000;i++){
        if(i == 7 || i == 46 || i == 9589)  continue;
        mapint.insert(LightSTL::make_pair(i,i+1));
    }
    assert(mapint.size() == 1999997);
    assert(mapint.count(5) == 1);
    assert(mapint.count(7) == 0);
    LightSTL::hash_map<int,int>::iterator ite;
    for(int i = 0;i < 2000000;i++){
        if(i == 7 || i == 46 || i == 9589){
            assert(mapint.find(i) == mapint.end());
        }
        else    assert(*mapint.find(i) == LightSTL::make_pair(i,i+1));
    }
    ite = mapint.begin();
    while(ite != mapint.end()){
        mapint.erase(ite++);
    }
    assert(mapint.empty());

    mapint[112] = 112;
    mapint[113] = 113;
    assert(mapint.size() == 2);
    mapint.erase(mapint.find(112));
    assert(mapint.size() == 1);

}

void HashMapTest2()
{
    LightSTL::hash_map<int,int> map1;
    for(int i = 0;i < 2000000;i++){
        if(i == 7 || i == 46 || i == 9589)  continue;
        map1[i] = i+1;
    }
    LightSTL::hash_map<int,int> map2(map1);
    LightSTL::hash_map<int,int>::iterator ite1 = map1.begin();
    LightSTL::hash_map<int,int>::const_iterator ite2;
    assert(map1.size() == map2.size());
    for(ite2 = map2.cbegin();ite2 != map2.cend();ite2++){
        assert(*ite1++ == *ite2);
    }

}

void HashMapTestAll()
{
    HashMapTest1();
    HashMapTest2();
    std::cout << "HashMap pass the test!" << std::endl;
}

}
