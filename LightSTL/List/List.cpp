#ifndef LIST_CPP
#define LIST_CPP

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
    node->prev = node;
    node->next = node;
    insert(begin(),rhs.cbegin(),rhs.cend());
}

template<class T,class Alloc>
list<T,Alloc>::list(list<T,Alloc>&& rhs)
{
    node = get_node();
    node->prev = node;
    node->next = node;
    LightSTL::swap(*this,rhs);
}

template<class T,class Alloc>
list<T,Alloc>::list(size_t n,const T& val)
{
    node = get_node();
    node->prev = node;
    node->next = node;
    insert(begin(),n,val);
}

template<class T,class Alloc>
list<T,Alloc>::list(const std::initializer_list<T>& rhs)
{
    node = get_node();
    node->prev = node;
    node->next = node;
    insert(begin(),rhs.begin(),rhs.end());
}

template<class T,class Alloc>
list<T,Alloc>::~list(){ clear();put_node(node);}

template<class T,class Alloc>
list<T,Alloc>& list<T,Alloc>::operator=(const list<T,Alloc>& rhs)
{
    if(node == rhs.node)    return *this;
    clear();
    insert(begin(),rhs.cbegin(),rhs.cend());
    return *this;
}

template<class T,class Alloc>
list<T,Alloc>& list<T,Alloc>::operator=(list<T,Alloc>&& rhs)
{
    LightSTL::swap(*this,rhs);
    return *this;
}

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
typename list<T,Alloc>::iterator list<T,Alloc>::insert(typename list<T,Alloc>::iterator pos,const T& val)
{
    return insert(pos,1,val);
}

template<class T,class Alloc>
typename list<T,Alloc>::iterator list<T,Alloc>::insert(typename list<T,Alloc>::iterator pos,size_t n,const T& val)
{
    return insert_n(pos,n,val);
}

template<class T,class Alloc>
template<class InputIterator>
typename list<T,Alloc>::iterator list<T,Alloc>::insert(typename list<T,Alloc>::iterator pos,
                                                       InputIterator lhs,
                                                       InputIterator rhs)
{
    typedef typename integer_traits<InputIterator>::is_integer_type is_integer;
    return insert_integer(pos,lhs,rhs,is_integer());
}

//判断InputIterator是否为整数
template<class T,class Alloc>
template<class InputIterator>
typename list<T,Alloc>::iterator list<T,Alloc>::insert_integer(typename list<T,Alloc>::iterator pos,
                                                               InputIterator lhs,InputIterator rhs,true_type)
{
    return insert_n(pos,lhs,rhs);
}

template<class T,class Alloc>
template<class InputIterator>
typename list<T,Alloc>::iterator list<T,Alloc>::insert_integer(typename list<T,Alloc>::iterator pos,
                                                                 InputIterator lhs,InputIterator rhs,false_type)
{
    typedef typename iterator_traits<InputIterator>::iterator_type iterator_type;
    return insert_aux(pos,lhs,rhs,iterator_type());
}

//被insert(iterator,size_t,const T&)和insert_integer(iterator,InputIterator,InputIterator,true_type)调用
template<class T,class Alloc>
typename list<T,Alloc>::iterator list<T,Alloc>::insert_n(typename list<T,Alloc>::iterator pos,size_t n,const T& val)
{
    typedef typename list<T,Alloc>::pointer pointer;
    if(n == 0)  return pos;
    pointer fa = pos.node->prev;
    pointer tmp = pos.node->prev;
    while(n--){
        pointer ptr = create_node(val);
        ptr->prev = tmp;
        ptr->next = tmp->next;
        tmp->next->prev = ptr;
        tmp->next = ptr;

        tmp = tmp->next;
    }
    return fa->next;
}

//被insert_integer(iterator,InputIterator,InputIterator,false_type)调用
template<class T,class Alloc>
template<class InputIterator>
typename list<T,Alloc>::iterator list<T,Alloc>::insert_aux(typename list<T,Alloc>::iterator pos,
                                                           InputIterator lhs,
                                                           InputIterator rhs,
                                                           random_access_iterator)
{
    size_t n = rhs - lhs;
    if(n == 0)  return pos;
    pointer fa = pos.node->prev;
    pointer tmp = pos.node->prev;
    while(n--){
        pointer ptr = create_node(*lhs);
        ptr->prev = tmp;
        ptr->next = tmp->next;
        tmp->next->prev = ptr;
        tmp->next = ptr;

        tmp = tmp->next;
        ++lhs;
    }
    tmp->next = pos.node;
    pos.node->prev = tmp;
    return fa->next;
}

template<class T,class Alloc>
template<class InputIterator>
typename list<T,Alloc>::iterator list<T,Alloc>::insert_aux(typename list<T,Alloc>::iterator pos,
                                                           InputIterator lhs,
                                                           InputIterator rhs,
                                                           forward_iterator)
{
    if(lhs == rhs)  return pos;
    pointer fa = pos.node->prev;
    pointer tmp = pos.node->prev;
    while(lhs != rhs){
        pointer ptr = create_node(*lhs);
        ptr->prev = tmp;
        ptr->next = tmp->next;
        tmp->next->prev = ptr;
        tmp->next = ptr;
        tmp = tmp->next;
        ++lhs;
    }
    tmp->next = pos.node;
    pos.node->prev = tmp;
    return fa->next;
}

template<class T,class Alloc>
void list<T,Alloc>::resize(size_t n,const T& val = T())
{
    iterator ite = begin();
    size_t old_size = 0;
    while(ite != end()){
        ++old_size;
        if(old_size > n){
            erase(ite,end());
            return ;
        }
        ++ite;
    }
    insert(end(),n - old_size,val);
}

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
    erase(begin(),end());
}

template<class T,class Alloc>
void list<T,Alloc>::remove(const T& val)
{
    iterator ite = begin();
    while(ite != end()){
        if(*ite == val)     erase(ite++);
        else    ++ite;
    }

}

template<class T,class Alloc>
typename list<T,Alloc>::iterator list<T,Alloc>::erase(typename list<T,Alloc>::iterator ite)
{
    ite.node->next->prev = ite.node->prev;
    ite.node->prev->next = ite.node->next;
    pointer result = ite.node->next;
    destroy_node(ite.node);
    return result;
}

template<class T,class Alloc>
typename list<T,Alloc>::iterator list<T,Alloc>::erase(typename list<T,Alloc>::iterator lhs,typename list<T,Alloc>::iterator rhs)
{
    lhs.node->prev->next = rhs.node;
    rhs.node->prev = lhs.node->prev;
    pointer tmp = lhs.node;
    while(tmp != rhs.node){
        pointer cur = tmp;
        tmp = tmp->next;
        destroy_node(cur);
    }
    return rhs;
}

/*************************关系运算****************************/
template<class T,class Alloc>
bool operator==(const list<T,Alloc>& lhs,const list<T,Alloc>& rhs)
{
    typedef typename list<T,Alloc>::const_iterator const_iterator;
    const_iterator ite1 = lhs.cbegin();
    const_iterator ite2 = rhs.cbegin();
    while(ite1 != lhs.cend() && ite2 != rhs.cend()){
        if(*ite1++ != *ite2++)  return false;

    }
    if(ite1 == lhs.cend() && ite2 == rhs.cend())     return true;
    return false;
}

template<class T,class Alloc>
bool operator!=(const list<T,Alloc>& lhs,const list<T,Alloc>& rhs)
{
    return !operator==(lhs,rhs);
}


template<class T,class Alloc>
void swap(list<T,Alloc>& lhs,list<T,Alloc>& rhs)
{
    LightSTL::swap(lhs.node,rhs.node);
}

/*************************移动元素****************************/
template<class T,class Alloc>
void list<T,Alloc>::transfer(typename list<T,Alloc>::iterator pos,
                             typename list<T,Alloc>::iterator start,
                             typename list<T,Alloc>::iterator finish)
{
    pointer prevpos = pos.node->prev;
    pointer prevfinish = finish.node->prev;

    //连接start->prev和finish
    start.node->prev->next = finish.node;
    finish.node->prev = start.node->prev;

    //连接prevpos和start
    start.node->prev = prevpos;
    prevpos->next = start.node;

    //连接pos和prevfinish
    pos.node->prev = prevfinish;
    prevfinish->next = pos.node;
}

template<class T,class Alloc>
void list<T,Alloc>::splice(typename list<T,Alloc>::iterator pos,list<T,Alloc>& rhs)
{
    if(rhs.empty())     return ;
    splice(pos,rhs.begin(),rhs.end());
}

template<class T,class Alloc>
void list<T,Alloc>::splice(typename list<T,Alloc>::iterator pos,typename list<T,Alloc>::iterator ite)
{
    if(pos == ite)  return ;
    iterator ite2 = ite;
    splice(pos,ite,++ite2);
}

template<class T,class Alloc>
void list<T,Alloc>::splice(typename list<T,Alloc>::iterator pos,
                           typename list<T,Alloc>::iterator start,
                           typename list<T,Alloc>::iterator finish)
{
    if(start == finish) return ;
    transfer(pos,start,finish);
}

template<class T,class Alloc>
void list<T,Alloc>::reverse()
{
    iterator ite = begin();
    while(ite != end())     splice(begin(),ite++);
}

template<class T,class Alloc>
void list<T,Alloc>::merge(list<T,Alloc>& rhs)
{
    iterator ite = begin();
    iterator rhsite = rhs.begin();
    while(ite != end() && rhsite != rhs.end()){
        if(*ite > *rhsite)  splice(ite,rhsite++);
        else    ite++;
    }
    splice(end(),rhsite,rhs.end());
}

template<class T,class Alloc>
void list<T,Alloc>::sort()
{
     if(empty())    return ;
     list<T,Alloc> carry;
     list<T,Alloc> space[64];

     int n = 0;
     while(!empty()){
        carry.splice(carry.begin(),begin());
        int i = 0;
        while(i < n && !space[i].empty()){
            carry.merge(space[i++]);
        }
        swap(carry,space[i]);
        if(i == n)  ++n;
     }
     for(int i = 0;i < n;i++)   carry.merge(space[i]);
     swap(*this,carry);
}


}


#endif

