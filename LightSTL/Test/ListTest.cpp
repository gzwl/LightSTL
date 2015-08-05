#include <cassert>
#include <list>
#include <string>
#include <iostream>
#include "ListTest.h"
#include "../List/List.h"

namespace LightSTL{

//添加元素部分测试
void ListTest1()
{
    LightSTL::list<int> lt1;
    std::list<int> lt2;
    for(int i = 0;i < 100;i++) {
        lt1.push_back(i);
        lt2.push_back(i);
    }
    assert(lt1.size() == lt2.size());

    LightSTL::list<int>::iterator ite1 = lt1.begin();
    std::list<int>::iterator ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }

    lt1.resize(50,15);
    lt2.resize(50,15);
    assert(lt1.size() == lt2.size());
    ite1 = lt1.begin();
    ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }

    lt1.insert(lt1.begin(),50,15);
    lt2.insert(lt2.begin(),50,15);
    assert(lt1.size() == lt2.size());
    ite1 = lt1.begin();
    ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }

    lt1.resize(150,456456);
    lt2.resize(150,456456);
    assert(lt1.size() == lt2.size());
    ite1 = lt1.begin();
    ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }
    LightSTL::list<int> lt3(lt1);
    lt1.clear();
    lt1.insert(lt1.begin(),lt3.begin(),lt3.end());
    assert(lt1 == lt3);
}

void ListTest2()
{
    LightSTL::list<std::string> lt1(100,std::string("Hello World"));
    std::list<std::string> lt2(100,std::string("Hello World"));
    assert(lt1.size() == lt2.size());
    LightSTL::list<std::string>::iterator ite1 = lt1.begin();
    std::list<std::string>::iterator ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }

    lt1.resize(50,std::string("A test"));
    lt2.resize(50,std::string("A test"));
    assert(lt1.size() == lt2.size());
    ite1 = lt1.begin();
    ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }

    lt1.resize(150,std::string("A test too"));
    lt2.resize(150,std::string("A test too"));
    assert(lt1.size() == lt2.size());
    ite1 = lt1.begin();
    ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }

    LightSTL::list<std::string> lt3(lt1);
    lt1.clear();
    lt1.insert(lt1.begin(),lt3.begin(),lt3.end());
    assert(lt1 == lt3);

}

//删除元素部分测试
void ListTest3()
{
    LightSTL::list<int> lt1;
    std::list<int> lt2;
    for(int i = 0;i < 100;i++) {
        lt1.push_back(i);
        lt2.push_back(i);
    }

    lt1.remove(5);
    lt2.remove(5);
    assert(lt1.size() == lt2.size());
    LightSTL::list<int>::iterator ite1 = lt1.begin();
    std::list<int>::iterator ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }

    lt1.erase(++lt1.begin(),--lt1.end());
    lt2.erase(++lt2.begin(),--lt2.end());
    assert(lt1.size() == lt2.size());
    ite1 = lt1.begin();
    ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }

    lt2.clear();
    assert(lt2.empty());

}

void ListTest4()
{
    LightSTL::list<std::string> lt1(100,std::string("Hello World"));
    std::list<std::string> lt2(100,std::string("Hello World"));
    lt1.erase(++lt1.begin() ,--lt1.end() );
    lt2.erase(++lt2.begin() ,--lt2.end() );
    assert(lt1.size() == lt2.size());
    LightSTL::list<std::string>::iterator ite1 = lt1.begin();
    std::list<std::string>::iterator ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }

    lt2.clear();
    assert(lt2.empty());

}

//关系运算部分测试
void ListTest5()
{
    LightSTL::list<int> lt1(50,10);
    LightSTL::list<int> lt2(lt1);
    assert(lt1 == lt2);

    lt1.push_back(5);
    assert(lt1 != lt2);

    LightSTL::list<int> lt3(lt1);
    swap(lt1,lt2);
    assert(lt3 == lt2);
    assert(lt3 != lt1);
}

void ListTest6()
{
    LightSTL::list<std::string> lt1(100,std::string("Hello World"));
    LightSTL::list<std::string> lt2(lt1);
    assert(lt1 == lt2);

    lt1.push_back(std::string("This is a test"));
    assert(lt1 != lt2);

    LightSTL::list<std::string> lt3(lt1);
    swap(lt1,lt2);
    assert(lt3 == lt2);
    assert(lt3 != lt1);
}

//移动元素部分测试
void ListTest7()
{
    LightSTL::list<int> lt1;
    std::list<int> lt2;
    for(int i = 0;i < 100;i++) {
        lt1.push_back(i%7);
        lt2.push_back(i%7);
    }
    lt1.sort();
    lt2.sort();
    assert(lt1.size() == lt2.size());
    LightSTL::list<int>::iterator ite1 = lt1.begin();
    std::list<int>::iterator ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }

    lt1.reverse();
    lt2.reverse();

    assert(lt1.size() == lt2.size());
    ite1 = lt1.begin();
    ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }

}

void ListTest8()
{
    LightSTL::list<std::string> lt1;
    std::list<std::string> lt2;
    for(int i = 0;i < 100;i++) {
        lt1.push_back("Hello World");
        lt2.push_back("Hello World");
    }
    for(int i = 0;i < 100;i++) {
        lt1.push_back("a little test");
        lt2.push_back("a little test");
    }
    for(int i = 0;i < 100;i++) {
        lt1.push_back("Zhang Weiliang");
        lt2.push_back("Zhang Weiliang");
    }
    lt1.sort();
    lt2.sort();
    assert(lt1.size() == lt2.size());
    LightSTL::list<std::string>::iterator ite1 = lt1.begin();
    std::list<std::string>::iterator ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }

    lt1.reverse();
    lt2.reverse();

    assert(lt1.size() == lt2.size());
    ite1 = lt1.begin();
    ite2 = lt2.begin();
    while(ite1 != lt1.end() && ite2 != lt2.end()){
        assert(*ite1++ == *ite2++);
    }
}

void ListTestAll()
{

    ListTest1();
    ListTest2();
    ListTest3();
    ListTest4();
    ListTest5();
    ListTest6();
    ListTest7();
    ListTest8();
    std::cout << "List pass the test!"  << std::endl;

}


}
