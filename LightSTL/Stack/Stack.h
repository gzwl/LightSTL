#ifndef STACK_H
#define STACK_H

#include "../List/List.h"
#include "../Algorithm/Algorithm.h"

namespace LightSTL{

template<class T,class Container = LightSTL::list<T> >
class stack
{
public:
    typedef typename Container::reference reference;
    typedef typename Container::const_reference const_reference;
private:
    Container c;

    /*************************构造，析构**************************/
public:
    stack():c(){}
    stack(const stack& rhs):c(rhs.c){}

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
        c.push_front(val);
    }
    void pop(){
        c.pop_front();
    }

    /*************************关系运算****************************/
public:
    friend bool operator==(const stack& lhs,const stack& rhs){
        return lhs.c == rhs.c;
    }
    friend bool operator!=(const stack& lhs,const stack& rhs){
        return lhs.c != rhs.c;
    }

	stack& operator=(const stack& rhs){
        c = rhs.c;
        return *this;
	}

	friend void swap(const stack& lhs,const stack& rhs){
        LightSTL::swap(lhs.c,rhs.c);
	}
};


}


#endif
