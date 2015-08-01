#ifndef VECTOR_H
#define VECTOR_H

#include<cstdlib>
#include "../Allocator/Allocator.h"

namespace LightSTL{

//vector前置声明，swap参数所用
template<class T,class Alloc>
class vector;

//swap前置声明，在vector中特例化友元函数
template<class T,class Alloc>
void swap(vector<T,Alloc> &lhs,vector<T,Alloc> &rhs);

template<class T,class Alloc = allocator<T> >
class vector
{
public:
	typedef T* iterator;
	typedef T* pointer;
	typedef const T* const_iterator;
	typedef T& reference;
	typedef const T& const_reference;
private:
	T* start;
	T* finish;
	T* end_of_storage;
public:

	/*************************构造，析构**************************/
	vector():start(0),finish(0),end_of_storage(0){}
	vector(const size_t n,const T& val);
	vector(const vector& rhs);
	explicit vector(const size_t n);
	~vector();

	/*************************迭代器相关**************************/
	iterator begin(){	return start;}
	const_iterator cbegin() const {     return start;}
	iterator end(){	return finish;}
	const_iterator cend() const { return finish;}

	/*************************容量相关****************************/
	bool empty() const {	return start == finish;}
	size_t size() const {	return finish - start;}
	size_t max_size() const {  return end_of_storage - start;}
	size_t capacity() const {	return end_of_storage - start;}

	/*************************访问元素****************************/
	reference operator[](size_t n){	return *(begin() + n);}
	reference front() {	return *begin();}
	reference back() {	return *(end() - 1);}
	const_reference operator[](size_t n) const{	return *(cbegin() + n);}
	const_reference front() const{	return *cbegin();}
	const_reference back() const{	return *(cend() - 1);}

	/*************************添加元素****************************/
	void push_back(const T& val);
	iterator insert(iterator pos,const T& val);
	void insert(iterator pos,size_t n,const T& val);
	iterator insert(iterator pos,iterator lhs,iterator rhs);
	void resize(size_t n,const T& val = T());

	/*************************删除元素****************************/
	void pop_back();
	void clear();
	iterator erase(iterator pos);
	iterator erase(iterator start,iterator finish);

	/*************************关系运算****************************/
	bool operator==(const vector& rhs) const;
	bool operator!=(const vector& rhs) const;
	friend void swap<T,Alloc>(vector<T,Alloc>& lhs,vector<T,Alloc>& rhs);

private:
    /*************************内存管理****************************/
	T* allocate(size_t n){	return Alloc::allocate(n);}
	void deallocate(){	Alloc::deallocate(start,capacity());}
	void allocate_and_fill(size_t n,const T& val);
};

}

#include "Vector.cpp"
#endif // VECTOR_H

