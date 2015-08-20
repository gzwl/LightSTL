#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include "../Traits/Traits.h"
#include "../Allocator/Allocator.h"
#include "../Allocator/Construct.h"
#include "../Allocator/Alloc.h"
#include "../Algorithm/Algorithm.h"

namespace LightSTL{

//list节点
template<class T>
struct list_node
{
    list_node<T>* prev;
    list_node<T>* next;
    T data;
};

//list迭代器
template<class T>
struct list_iterator
{
    typedef bidirection_iterator iterator_type;
    typedef T value_type;

    list_node<T>* node;

    //构造函数
    list_iterator(){}
    list_iterator(list_node<T> *ptr):node(ptr){}
    list_iterator(const list_iterator &rhs):node(rhs.node){}

    //关系赋值运算符
    list_iterator& operator=(const list_iterator &rhs){
        node = rhs.node;
        return *this;
    }
    bool operator==(const list_iterator &rhs)const {
        return node == rhs.node;
    }
    bool operator!=(const list_iterator &rhs)const {
        return node != rhs.node;
    }

    //自增自减运算符
    list_iterator& operator++() {
        node = node->next;
        return *this;
    }
    list_iterator operator++(int) {
        list_iterator tmp = *this;
        ++*this;
        return tmp;
    }
    list_iterator& operator--(){
        node = node->prev;
        return *this;
    }
    list_iterator operator--(int){
        list_iterator tmp = *this;
        --*this;
        return tmp;
    }


    value_type& operator*(){
        return node->data;
    }
    value_type* operator->(){
        return &(node->data);
    }

};

//list反向迭代器
template<class T>
struct list_rev_iterator
{
    typedef bidirection_iterator iterator_type;
    typedef T value_type;

    list_node<T>* node;

    //构造函数
    list_rev_iterator(){}
    list_rev_iterator(list_node<T> *ptr):node(ptr){}
    list_rev_iterator(const list_rev_iterator &rhs):node(rhs.node){}

    //关系赋值运算符
    list_rev_iterator& operator=(const list_rev_iterator &rhs){
        node = rhs.node;
        return *this;
    }
    bool operator==(const list_rev_iterator &rhs)const {
        return node == rhs.node;
    }
    bool operator!=(const list_rev_iterator &rhs)const {
        return node != rhs.node;
    }

    //自增自减运算符
    list_rev_iterator& operator++() {
        node = node->prev;
        return *this;
    }
    list_rev_iterator operator++(int) {
        list_rev_iterator tmp = *this;
        ++*this;
        return tmp;
    }
    list_rev_iterator& operator--(){
        node = node->next;
        return *this;
    }
    list_rev_iterator operator--(int){
        list_rev_iterator tmp = *this;
        --*this;
        return tmp;
    }


    value_type& operator*(){
        return node->data;
    }
    value_type* operator->(){
        return &(node->data);
    }

};

template<class T,class Alloc = LightSTL::alloc>
class list
{
public:
    typedef list_iterator<T> iterator;
    typedef list_iterator<const T> const_iterator;
    typedef list_rev_iterator<T> reverse_iterator;
    typedef list_rev_iterator<const T> const_reverse_iterator;
    typedef T& reference;
    typedef const T& const_reference;
    typedef list_node<T>* pointer;
    typedef list_node<const T>* const_pointer;
    typedef allocator<list_node<T>,Alloc>  data_allocator;
private:
    pointer node;

	/*************************构造，析构**************************/
public:
	list();
	list(const list&);
	list(list&&);
	list(size_t n,const T& val);
	list(const std::initializer_list<T>& rhs);
	~list();
    list& operator=(const list& rhs) ;
    list& operator=(list&& rhs);

	/*************************迭代器相关**************************/
public:
	iterator begin(){	return node->next;}
	iterator end(){	return node;}
	const_iterator cbegin() const{    return (const_pointer)(node->next);}
	const_iterator cend() const {  return (const_pointer)(node);}
	reverse_iterator rbegin(){	return node->prev;}
	reverse_iterator rend(){	return node;}
	const_reverse_iterator crbegin() const{    return (const_pointer)(node->prev);}
	const_reverse_iterator crend() const {  return (const_pointer)(node);}

	/*************************容量相关****************************/
public:
	bool empty() const {	return node->next == node;}
	size_t size() const
	{
        const_iterator ite = cbegin();
        size_t n = 0;
        while(ite != cend()){
            ++ite;++n;
        }
        return  n;
    }
	size_t max_size() const {  return size();}

	/*************************访问元素****************************/
public:
	reference front() {	return *begin();}
	reference back() {	return *(--end());}
	const_reference front() const{	return *cbegin();}
	const_reference back() const{	return *(--cend());}

	/*************************添加元素****************************/
public:
	void push_back(const T& val);
	void push_front(const T& val);
	iterator insert(iterator pos,const T& val);
	iterator insert(iterator pos,size_t n,const T& val);
	template<class InputIterator>
	iterator insert(iterator pos,InputIterator lhs,InputIterator rhs);
	void resize(size_t n,const T& val );

private:
    //判断InputIterator是否为整数
    template<class InputIterator>
    iterator insert_integer(iterator pos,InputIterator lhs,InputIterator rhs,true_type);
    template<class InputIterator>
    iterator insert_integer(iterator pos,InputIterator lhs,InputIterator rhs,false_type);

    //被insert(iterator,size_t,const T&)和insert_integer(iterator,InputIterator,InputIterator,true_type)调用
    iterator insert_n(iterator pos,size_t n,const T& val);

    //被insert_integer(iterator,InputIterator,InputIterator,false_type)调用
	template<class InputIterator> iterator insert_aux(iterator pos,InputIterator lhs,InputIterator rhs,random_access_iterator);
	template<class InputIterator> iterator insert_aux(iterator pos,InputIterator lhs,InputIterator rhs,forward_iterator);

	/*************************删除元素****************************/
public:
	void pop_back();
	void pop_front();
	void clear();
	void remove(const T& val);
	iterator erase(iterator pos);
	iterator erase(iterator start,iterator finish);

	/*************************关系运算****************************/
public:
	template<class U,class Alloc_>
	friend bool operator==(const list<U,Alloc_>& lhs,const list<U,Alloc_>& rhs) ;
	template<class U,class Alloc_>
	friend bool operator!=(const list<U,Alloc_>& lhs,const list<U,Alloc_>& rhs) ;
	template<class U,class Alloc_>
	friend void swap(list<U,Alloc_>& lhs,list<U,Alloc_>& rhs);

	/*************************移动元素****************************/
private:
    void transfer(iterator pos,iterator start,iterator finish);
public:
    void splice(iterator pos,list& rhs);
    void splice(iterator pos,iterator ite);
    void splice(iterator pos,iterator start,iterator finish);
    void reverse();
    void merge(list& rhs);
    void sort();

    /*************************内存管理****************************/
private:
    pointer get_node(){ return data_allocator::allocate(); }
    void put_node(pointer ptr){     if(ptr) data_allocator::deallocate(ptr);}
    pointer create_node(const T& val)
    {
        pointer ptr = get_node();
        construct(&ptr->data,val);
        return ptr;
    }
    void destroy_node(pointer ptr)
    {
        if(ptr == NULL) return ;
        destroy(&ptr->data);
        put_node(ptr);
    }

};

}

#include "List.cpp"
#endif
