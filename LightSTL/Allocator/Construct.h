#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include "Traits.h"

namespace LightSTL{

template<class T1,class T2>
void construct(T1 *ptr,const T2& val)
{
	new (ptr)	T1(val);
}

template<class T>
void destroy(T *ptr)
{
	ptr->~T();
}

template<class iterator>
void destroy(iterator ite1,iterator ite2)
{
	destroy_get_type(ite1,ite2,&(*ite1));
}

template<class iterator,class T>
static void destroy_get_type(iterator ite1,iterator ite2,T*)
{
	typedef typename type_traits<T>::destructor_type destructor_type;
	destroy_final(ite1,ite2,destructor_type());
}

template<class iterator>
static void destroy_final(iterator ite1,iterator ite2,trivial_type){}

template<class iterator>
static void destroy_final(iterator ite1,iterator ite2,nontrival_type)
{
	while(ite1 != ite2){
		destroy(ite1++);
	}
}

}






#endif
