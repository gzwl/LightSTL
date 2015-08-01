#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include "../Traits/Traits.h"
#include "../Algorithm/Algorithm.h"

namespace LightSTL{

/************构造工具*************/
template<class T1,class T2>
void construct(T1 *ptr,const T2& val)
{
	new (ptr)	T1(val);
}

/************析构工具*************/
template<class T>
void destroy(T *ptr)
{
	ptr->~T();
}

template<class InputIterator>
static void destroy_final(InputIterator ite1,InputIterator ite2,true_type){}

template<class InputIterator>
static void destroy_final(InputIterator ite1,InputIterator ite2,false_type)
{
	while(ite1 != ite2){
		destroy(ite1++);
	}
}

template<class InputIterator,class T>
static void destroy_get_type(InputIterator ite1,InputIterator ite2,T*)
{
	typedef typename type_traits<T>::has_trival_destructor_type trival_destructor;
	destroy_final(ite1,ite2,trival_destructor());
}


template<class InputIterator>
void destroy(InputIterator ite1,InputIterator ite2)
{
	destroy_get_type(ite1,ite2,&(*ite1));
}

/*************空间管理工具*************/



//uninitialized_fill_n
template<class InputIterator,class T>
static void uninitialized_fill_n_aux(InputIterator des,size_t n,const T& val,true_type)
{
	fill_n(des,n,val);
}

template<class InputIterator,class T>
static void uninitialized_fill_n_aux(InputIterator des,size_t n,const T& val,false_type)
{
	while(n--){
		construct(&*des++,val);
	}
}

template<class InputIterator,class T>
void uninitialized_fill_n(InputIterator des,size_t n,const T& val)
{
	typedef typename type_traits<T>::is_POD_type is_POD_type;
	uninitialized_fill_n_aux(des,n,val,is_POD_type());
}

//uninitialized_fill
template<class InputIterator,class T>
static void uninitialized_fill_aux(InputIterator start,InputIterator finish,const T& val,true_type)
{
	fill(start,finish,val);
}

template<class InputIterator,class T>
static void uninitialized_fill_aux(InputIterator start,InputIterator finish,const T& val,false_type)
{
	while(start != finish){
		construct(&*start++,val);
	}
}

template<class InputIterator,class T>
void uninitialized_fill(InputIterator start,InputIterator finish,const T& val)
{
	typedef typename type_traits<T>::is_POD_type is_POD_type;
	uninitialized_fill_aux(start,finish,val,is_POD_type());
}


//uninitialized_copy

template<class InputIterator>
static InputIterator uninitialized_copy_aux(InputIterator start,InputIterator finish,InputIterator des,true_type)
{
	return copy(start,finish,des);
}

template<class InputIterator>
static InputIterator uninitialized_copy_aux(InputIterator start,InputIterator finish,InputIterator des,false_type)
{
	while(start != finish){
		*des++ = *start++;
	}
	return des;
}

template<class InputIterator,class T>
static InputIterator uninitialized_copy_get_type(InputIterator start,InputIterator finish,InputIterator des,T*)
{
	typedef typename type_traits<T>::is_POD_type is_POD_type;
	return uninitialized_copy_aux(start,finish,des,is_POD_type());
}

template<class InputIterator>
InputIterator uninitialized_copy(InputIterator start,InputIterator finish,InputIterator des)
{
	return uninitialized_copy_get_type(start,finish,des,&*start);
}

}








#endif
