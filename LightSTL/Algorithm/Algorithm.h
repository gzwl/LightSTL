#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstring>
#include "../Traits/Traits.h"
namespace LightSTL{

/**********fill函数**********/

//分支,迭代器为char*
void fill_branch(char* start,char* finish,const char val,random_access_iterator)
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

char* fill_n(char* start,size_t n,const char val)
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


}


#endif








