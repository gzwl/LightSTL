#include "List.h"

namespace LightSTL{

/*************************构造，析构**************************/
template<class T,class Alloc>
list<T,Alloc>::list()
{
    node = get_node();
    node->prev = node;
    node->next = node;
}

template<class T,class Alloc>
list<T,Alloc>::list(const list<T,Alloc>& rhs)
{
    node = get_node();
    insert(node,rhs.cbegin(),rhs.cend());
}

template<class T,class Alloc>
list<T,Alloc>::~list(){ clear();put_node(node);}

/*************************添加元素****************************/
template<class T,class Alloc>
void list<T,Alloc>::push_back(const T& val)
{
    pointer ptr = create_node(val);
    ptr->next = node;
    ptr->prev = node->prev;
    node->prev->next = ptr;
    node->prev = ptr;
}

template<class T,class Alloc>
void list<T,Alloc>::push_front(const T& val)
{
    pointer ptr = create_node(val);
    ptr->prev = node;
    ptr->next = node->next;
    node->next->prev = ptr;
    node->next = ptr;
}

template<class T,class Alloc>
typename list<T,Alloc>::iterator insert(typename list<T,Alloc>::iterator pos,const T& val)
{
    insert(pos,1,val);
}

template<class T,class Alloc>
typename list<T,Alloc>::iterator insert(typename list<T,Alloc>::iterator pos,size_t n,const T& val)
{
    if(n == 0)  return pos;
    pointer result = pos.node;
    pointer fa = pos.node->prev;
    while(n--){
        pointer ptr = create(val);
        result->prev = ptr;
        ptr->next = result;
        result = result->prev;
    }
    result->prev = fa;
    fa->next = result;
    return result;
}

template<class InputIterator> iterator insert(iterator pos,InputIterator lhs,InputIterator rhs);
void resize(size_t n,const T& val = T());

/*************************删除元素****************************/
template<class T,class Alloc>
void list<T,Alloc>::pop_back()
{
    pointer ptr = node->prev;
    node->prev = ptr->prev;
    ptr->prev->next = node;
    destroy_node(ptr);
}

template<class T,class Alloc>
void list<T,Alloc>::pop_front()
{
    pointer ptr = node->next;
    node->next = ptr->next;
    ptr->next->prev = node;
    destroy_node(ptr);
}

template<class T,class Alloc>
void list<T,Alloc>::clear()
{
    pointer ptr = node->next;
    while(ptr != node){
        pointer cur = ptr;
        ptr = ptr->next;
        destroy_node(cur);
    }
}





}
