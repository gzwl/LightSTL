#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../Allocator/Alloc.h"
#include "../Allocator/Allocator.h"
#include "../Algorithm/Algorithm.h"
#include "../Traits/Traits.h"
#include "../Vector/Vector.h"
#include "../Functor/Functor.h"

namespace LightSTL{

//hash_table节点
template<class T>
struct hashtable_node
{
    hashtable_node *next;
    T data;
};

template<class T,class HashFun ,class GetKey ,class EqualKey,class Alloc>
class hash_table;

//hash_table迭代器
template<class T,class HashFun,class GetKey ,class EqualKey,class Alloc>
class hashtable_iterator
{
public:
    typedef forward_iterator iterator_type;
    typedef T value_type;

private:
    friend class hash_table<T,HashFun,GetKey,EqualKey,Alloc>;
    typedef hashtable_node<T> node;
    typedef hash_table<T,HashFun,GetKey,EqualKey,Alloc> hashtable;
    typedef hashtable_iterator<T,HashFun,GetKey,EqualKey,Alloc> self;

    node* cur;
    hashtable* ht;

public:
    hashtable_iterator():cur(0),ht(0){}
    hashtable_iterator(node* curp,hashtable* htp):cur(curp),ht(htp){}
    hashtable_iterator(const self& rhs):cur(rhs.cur),ht(rhs.ht){}

    value_type& operator*(){return cur->data;}
    value_type* operator->(){return &(cur->data);}

    self& operator++()
    {
        if(!cur->next){
            size_t n = ht->get_id(cur->data) + 1;
            cur = cur->next;
            while(!cur && n < ht->buckets.size()){
                cur = ht->buckets[n++];
            }
        }
        else    cur = cur->next;
        return *this;
    }

    self operator++(int)
    {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const self& rhs)const
    {
        return cur == rhs.cur;
    }

    bool operator!=(const self& rhs)const
    {
        return cur != rhs.cur;
    }

};


template<class T,
         class HashFun = LightSTL::hash<T>,
         class GetKey = LightSTL::identity<T>,
         class EqualKey = LightSTL::equal_to<T>,
         class Alloc = LightSTL::alloc >
class hash_table
{
public:
    typedef T value_type;
    typedef hashtable_iterator<T,HashFun,GetKey,EqualKey,Alloc> iterator;
    typedef hashtable_iterator<const T,HashFun,GetKey,EqualKey,Alloc> const_iterator;

    /*************************扩充容器所需**************************/
private:
    static const size_t prime_list_size ;
    static const unsigned long prime_list[28];

    unsigned long get_next(unsigned long nsize)
    {
        return *LightSTL::lower_bound(prime_list,prime_list + prime_list_size,nsize);
    }

private:
    friend class hashtable_iterator<T,HashFun,GetKey,EqualKey,Alloc>;
    typedef hashtable_node<T> node;
    typedef hashtable_node<T>* pointer;
    typedef hashtable_node<const T>* const_pointer;
    typedef hash_table<T,HashFun,GetKey,EqualKey,Alloc> self;
    typedef hash_table<const T,HashFun,GetKey,EqualKey,Alloc> const_self;
    typedef LightSTL::allocator<node,Alloc> data_allocator;

    HashFun hash;
    GetKey get_key;
    EqualKey equal_key;


    LightSTL::vector<node*,Alloc> buckets;
    size_t num_elements;

    /*************************构造，析构**************************/
public:
    hash_table(size_t n = 0,
               const HashFun& hf = HashFun(),
               const GetKey& gk = GetKey(),
               const EqualKey& ek = EqualKey()):num_elements(0),hash(hf),get_key(gk),equal_key(ek)
    {
        buckets.resize(get_next(n),(node*)0);
    }
	hash_table(const hash_table& rhs);
	~hash_table();

	/*************************迭代器相关**************************/
public:
	iterator begin();
	const_iterator cbegin() const;
	iterator end()
	{
        return iterator((node*)0,this);
	}
	const_iterator cend() const
	{
        return const_iterator((const_pointer)0,(const_self*)this);
	}

	/*************************容量相关****************************/
public:
	bool empty() const {	return num_elements == 0;}
	size_t size() const {	return num_elements;}
	size_t bucket_count() const{    return buckets.size();}

	/*************************添加元素****************************/
public:
    iterator insert_unique(const T& val);
    iterator insert_equal(const T& val);
private:
    void resize(size_t new_size);
    iterator insert_unique_noresize(const T& val);
    iterator insert_equal_noresize(const T& val);

    /*************************删除元素****************************/
public:
    void clear();
    void erase(iterator pos);
    size_t erase(const T& val);

    /*************************访问元素****************************/
public:
    iterator find(const T& val);
    const_iterator find(const T& val)const;

    /*************************辅助函数****************************/
private:
    template<class Key>
    size_t get_id(const Key& val){    return get_id(val,buckets.size());}
    template<class Key>
    size_t get_id(const Key& val,size_t m){   return hash(val)%m;}

    /*************************空间管理****************************/
private:
    node* get_node(){ return data_allocator::allocate(); }
    void put_node(node* ptr){     return data_allocator::deallocate(ptr);}
    node* create_node(const T& val)
    {
        node* ptr = get_node();
        construct(&ptr->data,val);
        ptr->next = 0;
        return ptr;
    }
    void destroy_node(node* ptr)
    {
        destroy(&ptr->data);
        put_node(ptr);
    }

};



}



#include "HashTable.cpp"
#endif
