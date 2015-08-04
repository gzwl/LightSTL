#ifndef LIST_H
#define LIST_H

#include "../Traits/Traits.h"
#include "../Allocator/Allocator.h"
#include "../Allocator/Alloc.h"
#include "../Algorithm/Algorithm.h"

namespace LightSTL{

//list节点
template<class T>
struct list_node
{
    T* prev;
    T* next;
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
    list_iterator& operator++()const {
        return const_cast<list_iterator&> operator++();
    }
    const list_iterator& operator++()const {
        node = node->next;
        return *this;
    }
    list_iterator operator++(int) {
        return const_cast<list_iterator> operator++(0);
    }
    const list_iterator operator++(int)const {
        list_iterator tmp = *this;
        ++*this;
        return tmp;
    }
    list_iterator& operator--(){
        return const_cast<list_iterator&> operator--();
    }
    const list_iterator& operator--() const {
        node = node->prev;
        return *this;
    }
    list_iterator operator--(int){
        return const_cast<list_iterator> operator--(0);
    }
    const list_iterator operator--(int) const{
        list_iterator tmp = *this;
        --*this;
        return tmp;
    }


    value_type& operator*(){
        return node->data;
    }
    const value_type& operator*()const{
        return node->data;
    }
    value_type* operator->(){
        return &(node->data);
    }
    const value_type* operator->()const{
        return &(node->data);
    }

};

template<class T,class Alloc = LightSTL::alloc>
class list
{
public:
    typedef list_iterator<T> iterator;
    typedef const list_iterator<T> const_iterator;
    typedef T& reference;
    typedef const T& const_reference;
    typedef list_node<T>* pointer;
    typedef allocator<list_node<T>,Alloc>  data_allocator;
private:
    pointer node;

public:
	/*************************构造，析构**************************/
	list();
	list(const list&);
	~list();

	/*************************迭代器相关**************************/
	iterator begin(){	return node->next;}
	iterator end(){	return node;}
	const_iterator cbegin() const{    return node->next;}
	const_iterator cend() const {  return node;}

	/*************************容量相关****************************/
	bool empty() const {	return node->next == node;}
	size_t size() const {	return distance(node->next,node);}
	size_t max_size() const {  return distance(node->next,node);}

	/*************************访问元素****************************/
	reference front() {	return *begin();}
	reference back() {	return *(end() - 1);}
	const_reference front() const{	return *cbegin();}
	const_reference back() const{	return *(cend() - 1);}

	/*************************添加元素****************************/
	void push_back(const T& val);
	void push_front(const T& val);
	iterator insert(iterator pos,const T& val);
	void insert(iterator pos,size_t n,const T& val);
	template<class InputIterator> iterator insert(iterator pos,InputIterator lhs,InputIterator rhs);
	void resize(size_t n,const T& val = T());

	/*************************删除元素****************************/
	void pop_back();
	void pop_front();
	void clear();
	iterator erase(iterator pos);
	iterator erase(iterator start,iterator finish);

	/*************************关系运算****************************/
	bool operator==(const list& rhs) const;
	bool operator!=(const list& rhs) const;
	void operator=(const list& rhs) ;
	friend void swap<T,Alloc>(vector<T,Alloc>& lhs,vector<T,Alloc>& rhs);


private:
    /*************************内存管理****************************/
    pointer get_node(){ return data_allocator::allocate(); }
    void put_node(pointer ptr){     return data_allocator::deallocate(ptr);}
    pointer create_node(const T& val)
    {
        pointer ptr = get_node();
        construct(&ptr->data,val);
        return ptr;
    }
    void destroy_node(pointer ptr)
    {
        destroy(&ptr->data);
        put_node(ptr);
    }


}

}


#endif
