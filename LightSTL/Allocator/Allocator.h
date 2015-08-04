#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include"Alloc.h"

namespace LightSTL{

template<class T,class Alloc>
class allocator
{
public:

	static T* allocate(size_t n)
	{
		if(n == 0)	return 0;
		else	return static_cast<T*>(Alloc::allocate(n*sizeof(T)));
	}

	static T* allocate(){	return static_cast<T*>(Alloc::allocate(sizeof(T)));}

	static void deallocate(void *p,size_t n)
	{
		if(n == 0)	return ;
		else	Alloc::deallocate(p,n*sizeof(T));
	}

	static void deallocate(void *p){	Alloc::deallocate(p,sizeof(T));}

};

}

#endif
