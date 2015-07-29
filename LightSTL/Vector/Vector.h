#ifndef VECTOR_H
#define VECTOR_H

namespace LightSTL{

template<class T,class Alloc = allocator<T>>
class vector
{
public:
	typedef T* iterator;
	typedef T* pointer;
	typedef const T* const_iterator;
	typedef T& reference;
private:
	T* start;
	T* finish;
	T* end_of_storage;
public:

	/*************************构造，析构**************************/
	vector():start(0),finish(0),end_of_storage(0);
	vector(const size_t n,const T& val);
	explicit vector(const size_t n);
	~vector();
	
	/*************************迭代器相关**************************/
	iterator begin(){	return start;}
	iterator end(){	return finish;}

	/*************************容量相关****************************/
	bool empty(){	return start == finish;}
	size_t size(){	return finsih - start;}
	size_t capacity(){	return end_of_storage - start;}

	/*************************访问元素****************************/
	reference operator[](size_t n){	return *(begin() + n);}
	reference front(){	return *begin();}
	reference back(){	return *(end() - 1);}

	/*************************添加和删除元素***********************/
	void push_back(const T& val);
	iterator insert(iterator pos,const T& val);
	void insert(iterator pos,size_t n,const T& val);
	void pop_back();
	void clear();

private:
	iterator allocate(size_t n){	return Alloc::allocate(n);}
	void deallocate(){	Alloc::deallocate(start,capacity());}
	void allocate_and_fill(size_t n,const T& val);
}

}

