#include "Alloc.h"

namespace LightSTL{

void* alloc::allocate(size_t n)
{
	return malloc(n);
}

void alloc::deallocate(void *p,size_t n)
{
	free(p);
}

}
