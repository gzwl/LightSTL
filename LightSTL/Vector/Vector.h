#ifndef VECTOR_H
#define VECTOR_H

#include<cstdlib>
#include "../Traits/Traits.h"
#include "../Allocator/Allocator.h"
#include "../Allocator/Alloc.h"

namespace LightSTL{

//vector前置声明，swap参数所用
template<class T,class Alloc>
class vector;

//swap前置声明，在vector中特例化友元函数
template<class T,class Alloc>
void swap(vector<T,Alloc> &lhs,vector<T,Alloc> &rhs);

template<class T,class Alloc = LightSTL::alloc >
class vector
{
public:
	typedef T* iterator;
	typedef T* pointer;
	typedef const T* const_iterator;
	typedef T& reference;
	typedef const T& const_reference;
	typedef allocator<T,Alloc> data_allocator;
private:
	T* start;
	T* finish;
	T* end_of_storage;

	/*************************构造，析构**************************/
public:
	vector():start(0),finish(0),end_of_storage(0){}
	vector(const size_t n,const T& val);
	vector(const vector& rhs);
	explicit vector(const size_t n);
	~vector();

	/*************************迭代器相关**************************/
public:
	iterator begin(){	return start;}
	const_iterator cbegin() const {     return start;}
	iterator end(){	return finish;}
	const_iterator cend() const { return finish;}

	/*************************容量相关****************************/
public:
	bool empty() const {	return start == finish;}
	size_t size() const {	return finish - start;}
	size_t max_size() const {  return end_of_storage - start;}
	size_t capacity() const {	return end_of_storage - start;}

	/*************************访问元素****************************/
public:
	reference operator[](size_t n){	return *(begin() + n);}
	reference front() {	return *begin();}
	reference back() {	return *(end() - 1);}
	const_reference operator[](size_t n) const{	return *(cbegin() + n);}
	const_reference front() const{	return *cbegin();}
	const_reference back() const{	return *(cend() - 1);}

	/*************************添加元素****************************/
public:
	void push_back(const T& val);
	iterator insert(iterator pos,const T& val);
	iterator insert(iterator pos,size_t n,const T& val);
	template<class InputIterator>
	iterator insert(iterator pos,InputIterator lhs,InputIterator rhs);
	void resize(size_t n,const T& val = T());

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

	//被insert_aux调用
	template<class InputIterator> iterator insert_aux_final(iterator pos,InputIterator lhs,InputIterator rhs,size_t n);

	/*************************删除元素****************************/
public:
	void pop_back();
	void clear();
	iterator erase(iterator pos);
	iterator erase(iterator start,iterator finish);

	/*************************关系运算****************************/
public:
	template<class U,class Alloc_>
	friend bool operator==(const vector<U,Alloc_>& lhs,const vector<U,Alloc_>& rhs) ;
	template<class U,class Alloc_>
	friend bool operator!=(const vector<U,Alloc_>& lhs,const vector<U,Alloc_>& rhs) ;
	void operator=(const vector& rhs) ;
	template<class U,class Alloc_>
	friend void swap(vector<U,Alloc_>& lhs,vector<U,Alloc_>& rhs);

    /*************************空间管理****************************/
private:
	T* allocate(size_t n){	return data_allocator::allocate(n);}
	void deallocate(){  data_allocator::deallocate(start,capacity());}
	void allocate_and_fill(size_t n,const T& val);

};

}

#include "Vector.cpp"
#endif // VECTOR_H

