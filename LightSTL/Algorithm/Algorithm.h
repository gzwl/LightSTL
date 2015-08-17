#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstring>
#include "../Traits/Traits.h"
namespace LightSTL{

/**********fill函数**********/

//分支,迭代器为char*
inline void fill_branch(char* start,char* finish,const char val,random_access_iterator)
{
	memset(start,val,finish - start);
}

//分支,迭代器为random_access
template<class InputIterator,class T>
void fill_branch(InputIterator start,InputIterator finish,const T& val,random_access_iterator)
{
	size_t n = finish - start;
	while(n--){
		*start++ = val;
	}
}

//分支,迭代器为forward
template<class InputIterator,class T>
void fill_branch(InputIterator start,InputIterator finish,const T& val,forward_iterator)
{
	while(start != finish){
		*start++ = val;
	}
}

//唯一对外接口
template<class InputIterator,class T>
void fill(InputIterator start,InputIterator finish,const T& val)
{
	typedef typename iterator_traits<InputIterator>::iterator_type iterator_type;
	fill_branch(start,finish,val,iterator_type());

}

/**********fill_n函数**********/

inline char* fill_n(char* start,size_t n,const char val)
{
	memset(start,val,n);
	return start + n;
}

template<class InputIterator,class T>
InputIterator fill_n(InputIterator start,size_t n,const T& val)
{
	while(n--){
		*start++ = val;
	}
	return start;
}

/**********copy函数**********/

//分支2,value_type有trivial_assignment
template<class InputIterator,class OutputIterator>
static OutputIterator copy_branch2(InputIterator start,InputIterator finish,OutputIterator des,true_type)
{
    typedef typename iterator_traits<InputIterator>::value_type T;
	size_t n = finish - start;
	memmove(des,start,n * sizeof(T));
	return des + n;
}

//分支2,value_type有nontrivial_assignment
template<class InputIterator,class OutputIterator>
static OutputIterator copy_branch2(InputIterator start,InputIterator finish,OutputIterator des,false_type)
{
	size_t n = finish - start;
	while(n--){
		*des++ = *start++;
	}
	return des;
}


//分支1，迭代器random_access_iterator
template<class InputIterator,class OutputIterator>
static OutputIterator copy_branch1(InputIterator start,InputIterator finish,OutputIterator des,random_access_iterator)
{
    size_t n = finish - start;
	while(n--){
		*des++ = *start++;
	}
	return des;
}

//分支1，迭代器为forward_iterator
template<class InputIterator,class OutputIterator>
static OutputIterator copy_branch1(InputIterator start,InputIterator finish,OutputIterator des,forward_iterator)
{
	while(start != finish){
		*des++ = *start++;
	}
	return des;
}

//三个对外接口
template<class InputIterator,class OutputIterator>
OutputIterator copy(InputIterator start,InputIterator finish,OutputIterator des)
{
	typedef typename iterator_traits<InputIterator>::iterator_type iterator_type;
	return copy_branch1(start,finish,des,iterator_type());
}

template<class T>
T* copy(T* start,T* finish,T* des)
{
	typedef typename type_traits<T>::has_trivial_assignment_type trivial_assignment;
	return copy_branch2(start,finish,des,trivial_assignment());
}

template<class T>
T* copy(const T* start,const T* finish,T* des)
{
	typedef typename type_traits<T>::has_trivial_assignment_type trivial_assignment;
	return copy_branch2(start,finish,des,trivial_assignment());
}

/**********copy_backward函数**********/

//分支2,value_type有trivial_assignment
template<class InputIterator,class OutputIterator>
static OutputIterator copy_backward_branch2(InputIterator start,InputIterator finish,OutputIterator des,true_type)
{
    typedef typename iterator_traits<InputIterator>::value_type T;
	size_t n = finish - start;
	memmove(des - n,start,n * sizeof(T));
	return des - n;
}

//分支2,value_type有nontrivial_assignment
template<class InputIterator,class OutputIterator>
static OutputIterator copy_backward_branch2(InputIterator start,InputIterator finish,OutputIterator des,false_type)
{
	size_t n = finish - start;
	while(n--){
		*--des = *--finish;
	}
	return des;
}


//分支1，迭代器random_access_iterator
template<class InputIterator,class OutputIterator>
static OutputIterator copy_backward_branch1(InputIterator start,InputIterator finish,OutputIterator des,random_access_iterator)
{
    size_t n = finish - start;
	while(n--){
		*--des = *--finish;
	}
	return des;
}

//分支1，迭代器为bidirection_iterator
template<class InputIterator,class OutputIterator>
static OutputIterator copy_backward_branch1(InputIterator start,InputIterator finish,OutputIterator des,bidirection_iterator)
{
	while(start != finish){
		*--des = *--finish;
	}
	return des;
}

//三个对外接口
template<class InputIterator,class OutputIterator>
OutputIterator copy_backward(InputIterator start,InputIterator finish,OutputIterator des)
{
	typedef typename iterator_traits<InputIterator>::iterator_type iterator_type;
	return copy_backward_branch1(start,finish,des,iterator_type());
}

template<class T>
T* copy_backward(T* start,T* finish,T* des)
{
	typedef typename type_traits<T>::has_trivial_assignment_type trivial_assignment;
	return copy_backward_branch2(start,finish,des,trivial_assignment());
}

template<class T>
T* copy_backward(const T* start,const T* finish,T* des)
{
	typedef typename type_traits<T>::has_trivial_assignment_type trivial_assignment;
	return copy_backward_branch2(start,finish,des,trivial_assignment());
}


/**********equal函数**********/
template<class InputIterator1,class InputIterator2>
bool equal(InputIterator1 start1,InputIterator1 finish1,InputIterator2 start2)
{
    while(start1 != finish1){
        if(*start1++ != *start2++)  return false;
    }
    return true;
}

template<class InputIterator1,class InputIterator2,class Compare>
bool equal(InputIterator1 start1,InputIterator1 finish1,InputIterator2 start2,Compare eq)
{
    while(start1 != finish1){
        if(eq(*start1++,*start2++))  return false;
    }
    return true;
}

/**********lower_bound函数**********/

//operator<版本
template<class InputIterator,class T>
InputIterator lower_bound_aux(InputIterator start,InputIterator finish,const T& val,random_access_iterator)
{
    while(finish - start > 0){
        size_t len = finish - start;
        InputIterator mid = start + len / 2;
        if(*mid >= val)     finish = mid;
        else    start = mid + 1;
    }
    return finish;
}


template<class InputIterator,class T>
InputIterator lower_bound(InputIterator start,InputIterator finish,const T& val)
{
    typedef typename iterator_traits<InputIterator>::iterator_type iterator_type;
    return lower_bound_aux(start,finish,val,iterator_type());
}

//仿函数版本
template<class InputIterator,class T,class Compare>
InputIterator lower_bound_aux(InputIterator start,InputIterator finish,const T& val,random_access_iterator,Compare smaller)
{
    while(finish - start > 0){
        size_t len = finish - start;
        InputIterator mid = start + len / 2;
        if(!smaller(*mid,val))     finish = mid;
        else    start = mid + 1;
    }
    return finish;
}


template<class InputIterator,class T,class Compare>
InputIterator lower_bound(InputIterator start,InputIterator finish,const T& val,Compare smaller)
{
    typedef typename iterator_traits<InputIterator>::iterator_type iterator_type;
    return lower_bound_aux(start,finish,val,iterator_type(),smaller);
}


/**********swap函数**********/

template<class T>
void swap(T& lhs,T& rhs)
{
    T tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

/**********插入排序**********/

template<class RandomAccessIterator>
void sort_insert(RandomAccessIterator first,RandomAccessIterator last)
{
    if(first == last)  return ;
    typedef typename iterator_traits<RandomAccessIterator>::value_type T;
    for(RandomAccessIterator i = first + 1;i < last;++i){
        T val = *i;
        if(val < *first){
            LightSTL::copy_backward(first,i,i + 1);
            *first = val;
        }
        else{
            RandomAccessIterator j = i;
            while(val < *(j - 1)){
                *j = *(j - 1);
                --j;
            }
            *j = val;
        }
    }
}

template<class RandomAccessIterator,class Compare>
void sort_insert(RandomAccessIterator first,RandomAccessIterator last,Compare cmp)
{
    if(first == last)  return ;
    typedef typename iterator_traits<RandomAccessIterator>::value_type T;
    for(RandomAccessIterator i = first + 1;i < last;++i){
        T val = *i;
        if(cmp(val , *first)){
            LightSTL::copy_backward(first,i,i + 1);
            *first = val;
        }
        else{
            RandomAccessIterator j = i;
            while(cmp(val , *(j - 1))){
                *j = *(j - 1);
                --j;
            }
            *j = val;
        }
    }
}

/**********堆排序**********/

template<class RandomAccessIterator>
void push_heap(RandomAccessIterator first,RandomAccessIterator last)
{
    if(first == last)   return ;
    typedef typename iterator_traits<RandomAccessIterator>::value_type T;
    size_t son = last - first - 1;
    const T val = *(first + son);
    while(son){
        size_t par = (son - 1)/2;
        if(*(first + par) < val) {
            *(first + son) = *(first + par);
            son = par;
        }
        else    break;
    }
    *(first + son) = val;
}

template<class RandomAccessIterator,class Compare>
void push_heap(RandomAccessIterator first,RandomAccessIterator last,Compare cmp)
{
    if(first == last)   return ;
    typedef typename iterator_traits<RandomAccessIterator>::value_type T;
    size_t son = last - first - 1;
    const T val = *(first + son);
    while(son){
        size_t par = (son - 1)/2;
        if(cmp(*(first + par) , val)) {
            *(first + son) = *(first + par);
            son = par;
        }
        else    break;
    }
    *(first + son) = val;
}

template<class RandomAccessIterator>
void pop_heap(RandomAccessIterator first,RandomAccessIterator last)
{
    LightSTL::swap(*first,*(last - 1));
    size_t max_range = last - first - 1;
    size_t self = 0;
    while(self < max_range){
        size_t next_pos = self;
        size_t son = 2 * self + 1;
        if(son < max_range && *(first + next_pos) < *(first + son)){
            next_pos = son;
        }
        son = 2 * self + 2;
        if(son < max_range && *(first + next_pos) < *(first + son)){
            next_pos = son;
        }
        if(next_pos != self){
            LightSTL::swap(*(first + self),*(first + next_pos));
            self = next_pos;
        }
        else   return ;
    }

}

template<class RandomAccessIterator,class Compare>
void pop_heap(RandomAccessIterator first,RandomAccessIterator last,Compare cmp)
{
    LightSTL::swap(*first,*(last - 1));
    size_t max_range = last - first - 1;
    size_t self = 0;
    while(self < max_range){
        size_t next_pos = self;
        size_t son = 2 * self + 1;
        if(son < max_range && cmp(*(first + next_pos) , *(first + son))){
            next_pos = son;
        }
        son = 2 * self + 2;
        if(son < max_range && cmp(*(first + next_pos) , *(first + son))){
            next_pos = son;
        }
        if(next_pos != self){
            LightSTL::swap(*(first + self),*(first + next_pos));
            self = next_pos;
        }
        else   return ;
    }

}

template<class RandomAccessIterator>
void make_heap(RandomAccessIterator first,RandomAccessIterator last)
{
    size_t len = last - first;
    if(len == 0 || len == 1)    return ;
    for(size_t i = 2;i <= len;i++)  LightSTL::push_heap(first,first + i);
}

template<class RandomAccessIterator,class Compare>
void make_heap(RandomAccessIterator first,RandomAccessIterator last,Compare cmp)
{
    size_t len = last - first;
    if(len == 0 || len == 1)    return ;
    for(size_t i = 2;i <= len;i++)  LightSTL::push_heap(first,first + i,cmp);
}

template<class RandomAccessIterator>
void sort_heap(RandomAccessIterator first,RandomAccessIterator last)
{
    LightSTL::make_heap(first,last);
    size_t n = last - first;
    while(n > 1){
        LightSTL::pop_heap(first,first + n);
        --n;
    }
}

template<class RandomAccessIterator,class Compare>
void sort_heap(RandomAccessIterator first,RandomAccessIterator last,Compare cmp)
{
    LightSTL::make_heap(first,last,cmp);
    size_t n = last - first;
    while(n > 1){
        LightSTL::pop_heap(first,first + n,cmp);
        --n;
    }
}

/**********快速排序**********/

template<class RandomAccessIterator>
static RandomAccessIterator get_mid(RandomAccessIterator first,
                                    RandomAccessIterator second,
                                    RandomAccessIterator third)
{
    if(*second < *first)
        if(*first < *third)     return first;
        else if(*third < *second)   return second;
        else    return third;
    else if(*second < *third)   return second;
    else if(*third < *first)    return first;
    else    return third;
}

template<class RandomAccessIterator,class Compare>
static RandomAccessIterator get_mid(RandomAccessIterator first,
                                    RandomAccessIterator second,
                                    RandomAccessIterator third,
                                    Compare cmp)
{
    if(cmp(*second , *first))
        if(cmp(*first , *third))     return first;
        else if(cmp(*third , *second))   return second;
        else    return third;
    else if(cmp(*second , *third))   return second;
    else if(cmp(*third , *first))    return first;
    else    return third;
}

template<class RandomAccessIterator,class T>
static RandomAccessIterator partition(RandomAccessIterator first,RandomAccessIterator last,const T val)
{
    --last;
    while(first < last){
        while(*first < val)     first++;
        while(val < *last)      last--;
        if(first == last)   break;
        LightSTL::swap(*first,*last);
        ++first;
        --last;
    }
    return first;
}

template<class RandomAccessIterator,class T,class Compare>
static RandomAccessIterator partition(RandomAccessIterator first,
                                      RandomAccessIterator last,
                                      const T val,
                                      Compare cmp)
{
    --last;
    while(first < last){
        while(cmp(*first , val))     first++;
        while(cmp(val , *last))      last--;
        if(first == last)   break;
        LightSTL::swap(*first,*last);
        ++first;
        --last;
    }
    return first;
}

template<class RandomAccessIterator>
void sort_quick(RandomAccessIterator first,RandomAccessIterator last)
{
    if(last - first > 1){
        RandomAccessIterator pivot= get_mid(first,first + (last - first)/2,last - 1);
        pivot = LightSTL::partition(first,last,*pivot);
        sort_quick(first,pivot);
        sort_quick(pivot + 1,last);
    }
}

template<class RandomAccessIterator,class Compare>
void sort_quick(RandomAccessIterator first,RandomAccessIterator last,Compare cmp)
{
    if(last - first > 1){
        RandomAccessIterator pivot= get_mid(first,first + (last - first)/2,last - 1,cmp);
        pivot = LightSTL::partition(first,last,*pivot,cmp);
        sort_quick(first,pivot,cmp);
        sort_quick(pivot + 1,last,cmp);
    }
}

/**********sort函数**********/

const int min_range= 16;

static size_t max_depth(size_t n)
{
    size_t res = 0;
    while(n){
        ++res;
        n >>= 1;
    }
    return res;
}

template<class RandomAccessIterator>
static void sort_aux(RandomAccessIterator first,RandomAccessIterator last,size_t depth)
{
    if(last - first > min_range){
        if(depth == 0){
            LightSTL::sort_heap(first,last);return ;
        }
        RandomAccessIterator pivot = get_mid(first,first + (last - first)/2,last - 1);
        pivot = LightSTL::partition(first,last,*pivot);
        sort_aux(first,pivot,depth - 1);
        sort_aux(pivot + 1,last,depth - 1);
    }
}

template<class RandomAccessIterator,class Compare>
static void sort_aux(RandomAccessIterator first,RandomAccessIterator last,size_t depth,Compare cmp)
{
    if(last - first > min_range){
        if(depth == 0){
            LightSTL::sort_heap(first,last,cmp);return ;
        }
        RandomAccessIterator pivot = get_mid(first,first + (last - first)/2,last - 1,cmp);
        pivot = LightSTL::partition(first,last,*pivot,cmp);
        sort_aux(first,pivot,depth - 1,cmp);
        sort_aux(pivot + 1,last,depth - 1,cmp);
    }
}

template<class RandomAccessIterator>
void sort(RandomAccessIterator first,RandomAccessIterator last)
{

    size_t depth = max_depth(last - first);
    sort_aux(first,last,2 * depth);
    sort_insert(first,last);
}

template<class RandomAccessIterator,class Compare>
void sort(RandomAccessIterator first,RandomAccessIterator last,Compare cmp)
{

    size_t depth = max_depth(last - first);
    sort_aux(first,last,2 * depth,cmp);
    sort_insert(first,last,cmp);
}

}
#endif








