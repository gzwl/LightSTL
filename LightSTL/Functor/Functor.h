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

template<>
struct hash<char>
{
    size_t operator()(char key)const{
        return key;
    }
};

template<>
struct hash<unsigned char>
{
    size_t operator()(unsigned char key)const{
        return key;
    }
};

template<>
struct hash<signed char>
{
    size_t operator()(signed char key)const{
        return key;
    }
};

template<>
struct hash<char*>
{
    size_t operator()(char* key)const{
        size_t res = 0;
        while(*key){
            res = 5 * res + *key;
            ++key;
        }
        return res;
    }
};

template<>
struct hash<const char*>
{
    size_t operator()(const char* key)const{
        size_t res = 0;
        while(*key){
            res = 5 * res + *key;
            ++key;
        }
        return res;
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
template<class T>
struct identity
{
    const T& operator()(const T& val)const{
        return val;
    }
};

template<class Pair>
struct select1st
{
    const typename Pair::first_type& operator()(const Pair& rhs)const{
        return rhs.first;
    }
};

template<class Pair>
struct select2nd
{
    const typename Pair::second_type& operator()(const Pair& rhs)const{
        return rhs.second;
    }
};

}




#endif
