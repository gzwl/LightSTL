#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "VectorTest.h"
#include "../Vector/Vector.h"
#include "../Algorithm/Algorithm.h"

namespace LightSTL{

namespace Test{

void VectorTest1()
{
    LightSTL::vector<int> vec1;
    std::vector<int> vec2;
    for(int i = 0;i < 100;i++) {
        vec1.push_back(i);
        vec2.push_back(i);
    }
    assert(vec1.size() == vec2.size());
    for(int i = 0;i < vec1.size();i++)      assert(vec1[i] == vec2[i]);

    vec1.resize(50,15);
    vec2.resize(50,15);
    assert(vec1.size() == vec2.size());
    for(int i = 0;i < vec1.size();i++)      assert(vec1[i] == vec2[i]);

    vec1.resize(150,456456);
    vec2.resize(150,456456);
    assert(vec1.size() == vec2.size());
    for(int i = 0;i < vec1.size();i++)      assert(vec1[i] == vec2[i]);

    LightSTL::vector<int> vec3(vec1);
    vec1.clear();
    vec1.insert(vec1.begin(),vec3.begin(),vec3.end());
    assert(vec1 == vec3);
}

void VectorTest2()
{
    LightSTL::vector<std::string> vec1(100,std::string("Hello World"));
    std::vector<std::string> vec2(100,std::string("Hello World"));
    assert(vec1.size() == vec2.size());
    for(int i = 0;i < vec1.size();i++)      assert(vec1[i] == vec2[i]);

    vec1.resize(50,std::string("A test"));
    vec2.resize(50,std::string("A test"));
    assert(vec1.size() == vec2.size());
    for(int i = 0;i < vec1.size();i++)      assert(vec1[i] == vec2[i]);

    vec1.resize(150,std::string("A test too"));
    vec2.resize(150,std::string("A test too"));
    assert(vec1.size() == vec2.size());
    for(int i = 0;i < vec1.size();i++)      assert(vec1[i] == vec2[i]);

    LightSTL::vector<std::string> vec3(vec1);
    vec1.clear();
    vec1.insert(vec1.begin(),vec3.begin(),vec3.end());
    assert(vec1 == vec3);


}

void VectorTest3()
{
    LightSTL::vector<int> vec1;
    std::vector<int> vec2;
    for(int i = 0;i < 100;i++) {
        vec1.push_back(i);
        vec2.push_back(i);
    }
    vec1.erase(vec1.begin() + 5,vec1.end() - 5);
    vec2.erase(vec2.begin() + 5,vec2.end() - 5);
    assert(vec1.size() == vec2.size());
    for(int i = 0;i < vec1.size();i++)      assert(vec1[i] == vec2[i]);

    vec2.clear();
    assert(vec2.empty());

}

void VectorTest4()
{
    LightSTL::vector<std::string> vec1(100,std::string("Hello World"));
    std::vector<std::string> vec2(100,std::string("Hello World"));
    vec1.erase(vec1.begin() + 5,vec1.end() - 5);
    vec2.erase(vec2.begin() + 5,vec2.end() - 5);
    assert(vec1.size() == vec2.size());
    for(int i = 0;i < vec1.size();i++)      assert(vec1[i] == vec2[i]);

    vec2.clear();
    assert(vec2.empty());

}

void VectorTest5()
{
    LightSTL::vector<int> vec1(50,10);
    LightSTL::vector<int> vec2(vec1);
    assert(vec1 == vec2);

    vec1.push_back(5);
    assert(vec1 != vec2);

    LightSTL::vector<int> vec3(vec1);
    swap(vec1,vec2);
    assert(vec3 == vec2);
    assert(vec3 != vec1);
}

void VectorTest6()
{
    LightSTL::vector<std::string> vec1(100,std::string("Hello World"));
    LightSTL::vector<std::string> vec2(vec1);
    assert(vec1 == vec2);

    vec1.push_back(std::string("This is a test"));
    assert(vec1 != vec2);

    LightSTL::vector<std::string> vec3(vec1);
    swap(vec1,vec2);
    assert(vec3 == vec2);
    assert(vec3 != vec1);
}

void VectorTest7()
{
    std::vector<int> vec1 = {1,2,3,4,5,6,7,8,9,10};
    LightSTL::vector<int> vec2 = {1,2,3,4,5,6,7,8,9,10};
    LightSTL::vector<int> vec3(LightSTL::vector<int>{1,2,3,4,5,6,7,8,9,10});
    assert(vec1.size() == vec2.size());
    auto ite1 = vec1.crbegin();
    auto ite2 = vec2.crbegin();
    while(ite1 != vec1.crend() && ite2 != vec2.crend()){
        assert(*ite1++ == *ite2++);
        ite1++;
        ite2++;
    }
    std::sort(vec1.rbegin(),vec1.rend());
    LightSTL::sort(vec2.rbegin(),vec2.rend());
    LightSTL::sort(vec3.rbegin(),vec3.rend());
    assert(LightSTL::equal(vec1.begin(),vec1.end(),vec2.begin()));
    assert(LightSTL::equal(vec3.begin(),vec3.end(),vec2.begin()));
}

void VectorTestAll()
{

    VectorTest1();
    VectorTest2();
    VectorTest3();
    VectorTest4();
    VectorTest5();
    VectorTest6();
    VectorTest7();
    std::cout << "Vector pass the test!"  << std::endl;

}

}


}
