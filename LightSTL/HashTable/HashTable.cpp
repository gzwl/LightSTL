#ifndef HASHTABLE_CPP
#define HASHTABLE_CPP

#include "HashTable.h"

namespace LightSTL{

template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
const size_t hash_table<T,HashFun,GetKey,EqualKey,Alloc>::prime_list_size = 28;

template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
const unsigned long hash_table<T,HashFun,GetKey,EqualKey,Alloc>::prime_list[28] = {
        53,         97,           193,          389,        769,
        1543,       3079,         6151,         12289,      24593,
        49157,      98317,        196613,       393241,     786433,
        1572869,    3145739,      6291469,      12582917,   25165843,
        50331653,   100663319,    201326611,    402653189,  805306457,
        1610612741, 3221225473ul, 4294967291ul
};

/*************************构造，析构**************************/

template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
hash_table<T,HashFun,GetKey,EqualKey,Alloc>::hash_table(const hash_table<T,HashFun,GetKey,EqualKey,Alloc> &rhs)
{
    num_elements = rhs.num_elements;
    buckets.resize(rhs.buckets.size(),(node*)0);
    for(size_t i = 0;i < rhs.buckets.size();i++) if(rhs.buckets[i]){
        buckets[i] = create_node(rhs.buckets[i]->data);
        node* cur = buckets[i];
        node* rhscur = rhs.buckets[i];
        while(rhscur->next){
            cur->next = create_node(rhscur->next->data);
            cur = cur->next;
            rhscur = rhscur->next;
        }
    }
}

template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
hash_table<T,HashFun,GetKey,EqualKey,Alloc>::~hash_table()
{
    clear();
}

/*************************迭代器相关**************************/
template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
typename hash_table<T,HashFun,GetKey,EqualKey,Alloc>::iterator
hash_table<T,HashFun,GetKey,EqualKey,Alloc>::begin()
{
    for(size_t i = 0;i < buckets.size();i++){
        if(buckets[i]){
            return iterator(buckets[i],this);
        }
    }
    return iterator((node*)(0),this);
}

template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
typename hash_table<T,HashFun,GetKey,EqualKey,Alloc>::const_iterator
hash_table<T,HashFun,GetKey,EqualKey,Alloc>::cbegin() const
{
    for(size_t i = 0;i < buckets.size();i++){
        if(buckets[i]){
            return const_iterator((const_pointer)buckets[i],(const_self*)this);
        }
    }
    return const_iterator((const_pointer)(0),(const_self*)this);
}

/*************************添加元素****************************/
template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
typename hash_table<T,HashFun,GetKey,EqualKey,Alloc>::iterator
hash_table<T,HashFun,GetKey,EqualKey,Alloc>::insert_unique(const T& val)
{
    resize(num_elements + 1);
    return insert_unique_noresize(val);
}

template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
typename hash_table<T,HashFun,GetKey,EqualKey,Alloc>::iterator
hash_table<T,HashFun,GetKey,EqualKey,Alloc>::insert_equal(const T& val)
{
    resize(num_elements + 1);
    return insert_equal_noresize(val);
}

template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
void hash_table<T,HashFun,GetKey,EqualKey,Alloc>::resize(size_t new_size)
{
    if(new_size <= buckets.size())  return ;
    size_t real_new_size = get_next(new_size);
    vector<node*> tmp(real_new_size,(node*)0);
    for(size_t i = 0;i < buckets.size();++i) {
        while(buckets[i]){
            node* cur = buckets[i];
            buckets[i] = cur->next;
            size_t id = get_id(get_key(cur->data),real_new_size);
            cur->next = tmp[id];
            tmp[id] = cur;
        }
    }
    swap(buckets,tmp);
}

template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
typename hash_table<T,HashFun,GetKey,EqualKey,Alloc>::iterator
hash_table<T,HashFun,GetKey,EqualKey,Alloc>::insert_unique_noresize(const T& val)
{
    size_t id = get_id(get_key(val));
    node *cur = buckets[id];
    while(cur){
        if(equal_key(get_key(val),get_key(cur->data))){
            return iterator(cur,this);
        }
        if(cur->next)   cur = cur->next;
        else{
            cur->next = create_node(val);
            num_elements++;
            return iterator(cur->next,this);
        }
    }
    buckets[id] = create_node(val);
    num_elements++;
    return iterator(buckets[id],this);
}

template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
typename hash_table<T,HashFun,GetKey,EqualKey,Alloc>::iterator
hash_table<T,HashFun,GetKey,EqualKey,Alloc>::insert_equal_noresize(const T& val)
{
    size_t id = get_id(get_key(val));
    node *cur = buckets[id];
    while(cur){
        if(equal_key(get_key(val),get_key(cur->data))){
            node* tmp = create_node(val);
            tmp->next = cur->next;
            cur->next = tmp;
            num_elements++;
            return iterator(cur->next,this);
        }
        cur = cur->next;
    }
    buckets[id] = create_node(val);
    num_elements++;
    return iterator(buckets[id],this);
}

/*************************删除元素****************************/
template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
void hash_table<T,HashFun,GetKey,EqualKey,Alloc>::clear()
{
    for(size_t i = 0;i < buckets.size();i++){
        while(buckets[i]){
            node *cur = buckets[i];
            buckets[i] = cur->next;
            destroy_node(cur);
        }
    }
    num_elements = 0;
}

template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
void hash_table<T,HashFun,GetKey,EqualKey,Alloc>::erase(hash_table<T,HashFun,GetKey,EqualKey,Alloc>::iterator pos)
{
    size_t id = get_id(get_key(*pos));
    if(buckets[id] == pos.cur){
        buckets[id] = buckets[id]->next;
        destroy_node(pos.cur);
        num_elements--;
        return ;
    }
    node* cur = buckets[id];
    while(cur->next){
        if(cur->next == pos.cur){
            cur->next = pos.cur->next;
            destroy_node(pos.cur);
            num_elements--;
            return ;
        }
        cur = cur->next;
    }
}

template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
size_t hash_table<T,HashFun,GetKey,EqualKey,Alloc>::erase(const T& val)
{
    size_t id = get_id(get_key(val));
    size_t num = 0;
    while(buckets[id] && equal_key(get_key(val),get_key(buckets[id]->data))){
        num++;
        node *tmp = buckets[id];
        buckets[id] = buckets[id]->next;
        destroy_node(tmp);
    }
    node* cur = buckets[id];
    while(cur && cur->next){
        if(equal_key(get_key(val),get_key(cur->next->data))){
            num++;
            node *tmp = cur->next;
            cur->next = tmp->next;
            destroy_node(tmp);
        }
        else cur = cur->next;
    }
    num_elements -= num;
    return num;
}


/*************************访问元素****************************/
template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
typename hash_table<T,HashFun,GetKey,EqualKey,Alloc>::iterator
hash_table<T,HashFun,GetKey,EqualKey,Alloc>::find(const T& val)
{
    size_t id = get_id(get_key(val));
    node* cur = buckets[id];
    while(cur){
        if(equal_key(get_key(val),get_key(cur->data))){
            return iterator(cur,this);
        }
        cur = cur->next;
    }
    return end();
}

template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
typename hash_table<T,HashFun,GetKey,EqualKey,Alloc>::const_iterator
hash_table<T,HashFun,GetKey,EqualKey,Alloc>::find(const T& val) const
{
    size_t id = get_id(get_key(val));
    hashtable_node<const T>* cur = buckets[id];
    while(cur){
        if(equal_key(get_key(val),get_key(cur->data))){
            return const_iterator(cur,this);
        }
        cur = cur->next;
    }
    return cend();
}

}

#endif
