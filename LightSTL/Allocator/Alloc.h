#ifndef ALLOC_H
#define ALLOC_H

#include<cstdlib>

namespace LightSTL{

class alloc
{
public:
	static void* allocate(size_t n);
	static void deallocate(void *p,size_t n);
};

}

#endif
