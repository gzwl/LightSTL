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
template<class InputIterator,class OutputIterator,class T>
static InputIterator copy_branch2(InputIterator start,InputIterator finish,OutputIterator des,T*,true_type)
{
	size_t n = finish - start;
	memmove(des,start,n * sizeof(T));
	return des + n;
}

//分支2,value_type有nontrivial_assignment
template<class InputIterator,class OutputIterator,class T>
static OutputIterator copy_branch2(InputIterator start,InputIterator finish,OutputIterator des,T*,false_type)
{
	size_t n = finish - start;
	while(n--){
		*des++ = *start++;
	}
	return des;
}


//萃取出迭代器的value_type
template<class InputIterator,class OutputIterator,class T>
static OutputIterator copy_get_value_type(InputIterator start,InputIterator finish,OutputIterator des,T*)
{
	typedef typename type_traits<T>::has_trivial_assignment_type has_trivial_assignment;
	return copy_branch2(start,finish,des,static_cast<T*>(0),has_trivial_assignment());
}


//分支1，迭代器random_access_iterator
template<class InputIterator,class OutputIterator>
static OutputIterator copy_branch1(InputIterator start,InputIterator finish,OutputIterator des,random_access_iterator)
{
	return copy_get_value_type(start,finish,des,&*start);
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

//唯一对外接口
template<class InputIterator,class OutputIterator>
OutputIterator copy(InputIterator start,InputIterator finish,OutputIterator des)
{
	typedef typename iterator_traits<InputIterator>::iterator_type iterator_type;
	return copy_branch1(start,finish,des,iterator_type());
}

/**********swap函数**********/

template<class T>
void swap(T& lhs,T& rhs)
{
    T tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}


}
#endif








