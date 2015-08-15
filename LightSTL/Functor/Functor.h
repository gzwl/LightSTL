#ifndef FUNCTOR_H
#define FUNCTOR_H

namespace LightSTL{

/***************哈希函数***************/
template<class T>
struct hash{
};

template<>
struct hash<int>
{
    size_t operator()(int key)const{
        return key;
    }
};

template<>
struct hash<unsigned int>
{
    size_t operator()(unsigned int key)const{
        return key;
    }
};

template<>
struct hash<short>
{
    size_t operator()(short key)const{
        return key;
    }
};
template<>
struct hash<unsigned short>
{
    size_t operator()(unsigned short key)const{
        return key;
    }
};
template<>
struct hash<long>
{
    size_t operator()(long key)const{
        return key;
    }
};

template<>
struct hash<unsigned long>
{
    size_t operator()(unsigned long key)const{
        return key;
    }
};

template<class T>
struct identity
{
    const T& operator()(const T& val)const{
        return val;
    }
};
/***************关系运算类仿函数***************/
template<class T>
struct equal_to
{
    bool operator()(const T& lhs,const T&rhs)const{
        return lhs == rhs;
    }
};

template<class T>
struct not_equal_to
{
    bool operator()(const T& lhs,const T&rhs)const{
        return lhs != rhs;
    }
};

template<class T>
struct greater
{
    bool operator()(const T& lhs,const T&rhs)const{
        return lhs > rhs;
    }
};

template<class T>
struct greater_equal
{
    bool operator()(const T& lhs,const T&rhs)const{
        return lhs >= rhs;
    }
};

template<class T>
struct less
{
    bool operator()(const T& lhs,const T&rhs)const{
        return lhs < rhs;
    }
};

template<class T>
struct less_equal
{
    bool operator()(const T& lhs,const T&rhs)const{
        return lhs <= rhs;
    }
};

/***************选择类仿函数***************/
template<class Pair>
struct select1st
{
    const typename Pair::first_type& operator()(const Pair& rhs){
        return rhs.first;
    }
};

template<class Pair>
struct select2nd
{
    const typename Pair::second_type& operator()(const Pair& rhs){
        return rhs.second;
    }
};

}




#endif
