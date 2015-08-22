#ifndef VECTOR_H
#define VECTOR_H

#include<cstddef>   //std::size_t
#include<initializer_list>
#include "../Traits/Traits.h"
#include "../Allocator/Allocator.h"
#include "../Allocator/Alloc.h"
#include "../ReverseIterator/ReverseIterator.h"

namespace LightSTL{


template<class T,class Alloc = LightSTL::alloc >
class vector
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef LightSTL::reverse_iterator<T> reverse_iterator;
	typedef LightSTL::reverse_iterator<const T> const_reverse_iterator;
	typedef T* pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef allocator<T,Alloc> data_allocator;
private:
	T* start;
	T* finish;
	T* end_of_storage;

	/*************************构造，析构,赋值**************************/
public:
	vector():start(0),finish(0),end_of_storage(0){}
	vector(const size_t n,const T& val);
	vector(const vector& rhs);
	vector(vector&& rhs);
	vector(const std::initializer_list<T>& rhs);
	explicit vector(const size_t n);
	~vector();
    vector& operator=(const vector& rhs) ;
    vector& operator=(vector&& rhs);

	/*************************迭代器相关**************************/
public:
	iterator begin(){	return start;}
	iterator end(){	return finish;}
	const_iterator cbegin() const {     return start;}
	const_iterator cend() const { return finish;}
	reverse_iterator rbegin(){  return finish - 1;}
	reverse_iterator rend(){    return start - 1;}
	const_reverse_iterator crbegin()const { return finish - 1;}
	const_reverse_iterator crend() const { return start - 1;}


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

