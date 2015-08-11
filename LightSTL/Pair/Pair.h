#ifndef PAIR_H
#define PAIR_H

namespace LightSTL{

template<class T1,class T2>
class pair
{
public:
    T1 first;
    T2 second;

    pair():first(),second(){}
    pair(const T1& lhs,const T2& rhs):first(lhs),second(rhs){}
    template<class U1,class U2>
    pair(const pair<U1,U2>& rhs):first(rhs.first),second(rhs.second){}

    template<class U1,class U2>
    pair& operator=(const pair<U1,U2>& rhs){
        first = rhs.first;
        second = rhs.second;
        return *this;
    }

    bool operator==(const pair& rhs) const{
        return first == rhs.first && second == rhs.second;
    }
    bool operator!=(const pair& rhs) const{
        return first != rhs.first || second != rhs.second;
    }

    bool operator<(const pair& rhs) const{
        if(first != rhs.first)  return  first < rhs.first;
        return second < rhs.second;
    }
    bool operator<=(const pair& rhs) const{
        if(first != rhs.first)  return  first < rhs.first;
        return second <= rhs.second;
    }
    bool operator>(const pair& rhs) const{
        if(first != rhs.first)  return  first > rhs.first;
        return second > rhs.second;
    }
    bool operator>=(const pair& rhs) const{
        if(first != rhs.first)  return  first > rhs.first;
        return second >= rhs.second;
    }

};

template<class T1,class T2>
pair<T1,T2> make_pair(const T1& first,const T2& second)
{
    return pair<T1,T2>(first,second);
}

}

#endif
