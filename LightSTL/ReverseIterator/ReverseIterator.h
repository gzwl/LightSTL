#ifndef REVERSEITERATOR_H
#define REVERSEITERATOR_H

#include <cstdlib>
#include "../Traits/Traits.h"

namespace LightSTL{

template<class T>
class reverse_iterator
{
public:
    typedef T value_type;
    typedef random_access_iterator iterator_type;

private:
    typedef reverse_iterator<T> self;
    T* node;

public:

    reverse_iterator():node(0){}
    reverse_iterator(T* rhs):node(rhs){}
    reverse_iterator(const self& rhs):node(rhs.node){}

    self& operator=(T* rhs){
        node = rhs;
        return *this;
    }
    self& operator=(const self& rhs){
        node = rhs.node;
        return *this;
    }

    T& operator*(){ return *node;}
    const T& operator*() const {    return *node;}
    T* operator->(){    return node;}
    T const* operator->()const {  return node;}

    //迭代器移动
    ssize_t operator-(const self& rhs) const{
        return rhs.node - node;
    }
    self operator-(ssize_t num) const{
        return node + num;
    }
    self operator+(ssize_t num) const{
        return node - num;
    }

    self& operator++(){
        --node;
        return *this;
    }
    self operator++(int){
        self tmp = *this;
        ++(*this);
        return tmp;
    }
    self& operator--(){
        ++node;
        return *this;
    }
    self operator--(int){
        self tmp = *this;
        --(*this);
        return *this;
    }

    //关系运算
    bool operator<(const self& rhs) const{
        return rhs.node < node;
    }
    bool operator>(const self& rhs) const{
        return rhs.node > node;
    }
    bool operator<=(const self& rhs) const{
        return rhs.node <= node;
    }
    bool operator>=(const self& rhs) const{
        return rhs.node >= node;
    }
    bool operator==(const self& rhs) const{
        return node == rhs.node;
    }
    bool operator!=(const self& rhs) const{
        return node != rhs.node;
    }

};



}




#endif
