#include "Alloc.h"

namespace LightSTL{

char* alloc::free_start = 0;
char* alloc::free_finish = 0;
size_t alloc::heap_size = 0;
alloc::obj* alloc::freelist[NFREELIST] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//分配空间
void* alloc::allocate(size_t n)
{
	if(n >  MAX_BYTES)  return malloc(n);
	obj* result = freelist[freelist_index(n)];
	if(result == 0){
        return refill(round_up(n));
	}
	freelist[freelist_index(n)] = result->freelist_next;
	return result;
}

//回收空间
void alloc::deallocate(void *p,size_t n)
{
	if(n > MAX_BYTES)   free(p);
	else{
        obj* ins = (obj*)p;
        ins->freelist_next = freelist[freelist_index(n)];
        freelist[freelist_index(n)] = ins;
	}
}

//补充freelist
void* alloc::refill(size_t n)
{
    size_t num = 20;
    char* newspace = (char*)chunk_alloc(n,num);
    if(num == 1)    return newspace;
    else{
        char* result = newspace;
        size_t offset = freelist_index(n);
        while(num-- != 1){
            newspace += n;
            ((obj*)newspace)->freelist_next = freelist[offset];
            freelist[offset] = (obj*)newspace;
        }
        return result;
    }
}

//被refill调用
void* alloc::chunk_alloc(size_t space,size_t &num)
{
    size_t nleft = free_finish - free_start;
    size_t ntotal = num * space;

    //剩余空间完全够用
    if(nleft >= ntotal){
        char* result = free_start;
        free_start += ntotal;
        return (void*)result;
    }

    //剩余空间不能补充n个但能补充至少一个
    else if(nleft >= space){
        num = nleft / space;
        char* result = free_start;
        free_start += num * space;
        return (void*)result;
    }

    //剩余空间一个也不够
    else{
        //先把剩余空间分配给freelist
        size_t offset;
        if(nleft){
            offset = freelist_index(nleft);
            ((obj*)free_start)->freelist_next = freelist[offset];
            freelist[offset] = (obj*)free_start;
        }

        //再向heap分配新内存
        size_t new_total = 2 * ntotal + round_up(heap_size >> 4);
        free_start = (char*)malloc(new_total);
        if(free_start){
            heap_size += new_total;
            free_finish = free_start + new_total;
            char* result = free_start;
            free_start += ntotal;
            return result;
        }
        else{
            offset = freelist_index(ntotal);
            for(size_t i = offset + 1;i < NFREELIST;i++) if(freelist[i]){
                char* result = (char*)freelist[i];
                char* left = result + ntotal;
                freelist[i] = freelist[i]->freelist_next;
                offset = freelist_index(8*(i+1)-ntotal);
                ((obj*)left)->freelist_next = freelist[offset];
                freelist[offset] = (obj*)left;
                return result;
            }
        }
    }

}

}
