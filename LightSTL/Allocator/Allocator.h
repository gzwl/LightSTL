#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include"Alloc.h"

namespace LightSTL{

template<class T>
class allocator
{
public:

	T* allocate(size_t n)
	{	
		if(n == 0)	return 0;
		else	return Alloc::allocate(n*sizeof(T));
	}

	T* allocate(){	return Alloc::allocate(sizeof(T);)}

	void deallocate(void *p,size_t n)
	{
		if(n == 0)	return ;
		else	Alloc::deallocate(p,n*sizeof(T));
	}
	
	void deallocate(void *p){	Alloc::deallocate(p,sizeof(T));}

}

}

#endif
