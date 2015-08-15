#include "HashTableTest.h"
#include "../HashTable/HashTable.h"
#include <cassert>
#include <iostream>

namespace LightSTL{

void HashTableTest1()
{
    LightSTL::hash_table<int> htb;
    for(int i = 0;i < 2000000;i++){
        if(i == 7 || i == 46 || i == 9589)  continue;
        htb.insert_unique(i);
    }
    assert(htb.size() == 1999997);
    LightSTL::hash_table<int>::iterator ite;
    for(int i = 0;i < 2000000;i++){
        if(i == 7 || i == 46 || i == 9589){
            assert(htb.find(i) == htb.end());
        }
        else    assert(*htb.find(i) == i);
    }
    ite = htb.begin();
    while(ite != htb.end()){
        htb.erase(ite++);
    }
    assert(htb.empty());

    htb.insert_equal(112);
    htb.insert_equal(112);
    assert(htb.size() == 2);
    htb.erase(htb.find(112));
    assert(htb.size() == 1);
}

void HashTableTest2()
{
    LightSTL::hash_table<int> htb1;
    for(int i = 0;i < 2000000;i++){
        if(i == 7 || i == 46 || i == 9589)  continue;
        htb1.insert_unique(i);
    }
    LightSTL::hash_table<int> htb2(htb1);
    LightSTL::hash_table<int>::iterator ite1 = htb1.begin();
    LightSTL::hash_table<int>::const_iterator ite2;
    assert(htb1.size() == htb2.size());
    for(ite2 = htb2.cbegin();ite2 != htb2.cend();ite2++){
        assert(*ite1++ == *ite2);
    }
}

void HashTableTestAll()
{
    HashTableTest1();
    HashTableTest2();
    std::cout << "HashTable pass the test!" << std::endl;
}

}
