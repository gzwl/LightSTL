#ifndef ALLOC_H
#define ALLOC_H

#include<cstdlib>

namespace LightSTL{

class alloc
{
private:
    enum {ALIGN = 8};//小型区块的上调边界
    enum {MAX_BYTES = 128};//小型区块的上限
    enum {NFREELIST = MAX_BYTES / ALIGN};//freelist的个数

    union obj{
        union obj* freelist_next;
        char client_data[1];
    };
    static obj* freelist[NFREELIST];//freelist,维护16个链表

    //chunk_alloc中用来补充freelist
    static char* free_start;
    static char* free_finish;
    static size_t heap_size;

    static size_t round_up(size_t n)
    {
        if(n % ALIGN == 0)   return  n;
        else    return n + ALIGN - n % ALIGN;
    }

    static size_t freelist_index(size_t n)
    {
        return (n + ALIGN - 1) / ALIGN - 1;
    }
	static void* refill(size_t n);
	static void* chunk_alloc(size_t space,size_t &num);
public:
	static void* allocate(size_t n);
	static void deallocate(void *p,size_t n);

};

}

#endif
