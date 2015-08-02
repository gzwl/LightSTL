#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include "VectorTest.h"
#include "../Vector/Vector.h"

namespace LightSTL{

//添加元素部分测试
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

//删除元素部分测试
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

//关系运算部分测试
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

void VectorTestAll()
{

    VectorTest1();
    VectorTest2();
    VectorTest3();
    VectorTest4();
    VectorTest5();
    VectorTest6();
    std::cout << "Vector pass the test!"  << std::endl;

}


}
