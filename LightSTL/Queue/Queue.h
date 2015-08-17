#ifndef QUEUE_H
#define QUEUE_H

#include "../List/List.h"
#include "../Vector/Vector.h"
#include "../Algorithm/Algorithm.h"
#include "../Functor/Functor.h"

namespace LightSTL{

template<class T,class Container = LightSTL::list<T> >
class queue
{
public:
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;
private:
    Container c;

    /*************************构造，析构**************************/
public:
    queue():c(){}
    queue(const queue& rhs):c(rhs.c){}

    /*************************访问****************************/
public:
    bool empty() const {
        return c.empty();
    }
	size_t size() const {
        return c.size();
    }
	reference front() {
        return c.front();
	}
	const_reference front() const {
        return c.front();
	}
    reference back() {
        return c.back();
	}
	const_reference back() const {
        return c.back();
	}

	/*************************添加,删除****************************/
public:
    void push(const T& val){
        c.push_back(val);
    }
    void pop(){
        c.pop_front();
    }

    /*************************关系运算****************************/
public:
    friend bool operator==(const queue& lhs,const queue& rhs){
        return lhs.c == rhs.c;
    }
    friend bool operator!=(const queue& lhs,const queue& rhs){
        return lhs.c != rhs.c;
    }

	queue& operator=(const queue& rhs){
        c = rhs.c;
        return *this;
	}

	friend void swap(const queue& lhs,const queue& rhs){
        LightSTL::swap(lhs.c,rhs.c);
	}
};


template<class T,
         class Container = LightSTL::vector<T>,
         class Compare = LightSTL::less<T> >
class priority_queue
{
public:
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;
private:
    Container c;
    Compare cmp;

    /*************************构造，析构**************************/
public:
    priority_queue(const Compare& ccmp):c(),cmp(ccmp){}
    priority_queue(const Container& cc = Container(),const Compare& ccmp = Compare()):c(cc),cmp(ccmp){}
    priority_queue(const priority_queue& rhs):c(rhs.c),cmp(rhs.cmp){}

    /*************************访问****************************/
public:
    bool empty() const {
        return c.empty();
    }
	size_t size() const {
        return c.size();
    }
	reference top() {
        return c.front();
	}
	const_reference top() const {
        return c.front();
	}

	/*************************添加,删除****************************/
public:
    void push(const T& val){
        c.push_back(val);
        LightSTL::push_heap(c.begin(),c.end(),cmp);
    }
    void pop(){
        LightSTL::pop_heap(c.begin(),c.end(),cmp);
        c.pop_back();
    }

    /*************************关系运算****************************/
public:
	priority_queue& operator=(const priority_queue& rhs){
        c = rhs.c;
        cmp = rhs.cmp;
        return *this;
	}

	friend void swap(const priority_queue& lhs,const priority_queue& rhs){
        LightSTL::swap(lhs.c,rhs.c);
        LightSTL::swap(lhs.cmp,rhs.cmp);
	}
};



}


#endif
