#ifndef STRING_H
#define STRING_H

#include <cstddef>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include "../ReverseIterator/ReverseIterator.h"
#include "../Allocator/Alloc.h"
#include "../Allocator/Allocator.h"
#include "../Allocator/Construct.h"

namespace LightSTL{

class string
{
public:
    typedef char value_type;
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef LightSTL::reverse_iterator<char> reverse_iterator;
    typedef LightSTL::reverse_iterator<const char> const_reverse_iterator;
    typedef char& reference;
    typedef const char& const_reference;
    typedef allocator<char,LightSTL::alloc> data_allocator;

private:
    char* finish;
    char* end_of_storage;
    const static int LOCALSIZE = 16;
    union
    {
        char str[LOCALSIZE];
        char* start;
    }data;

    /*************************构造，析构,赋值**************************/
public:
    string():finish(data.str),end_of_storage(data.str + LOCALSIZE){}
    string(size_t n,const char);
    string(const char*);
    string(const string& rhs);
    string(string&& rhs);
    string(const_iterator first,const_iterator last);
    string(const std::initializer_list<char>& rhs);
    ~string();
    string& operator=(const string& rhs);
    string& operator=(string&& rhs);

	/*************************迭代器相关**************************/
public:
	iterator begin()
	{	return end_of_storage == data.str + LOCALSIZE ? data.str : data.start;}
	iterator end()
	{	return finish;}
	const_iterator begin() const
	{	return end_of_storage == data.str + LOCALSIZE ? data.str : data.start;}
	const_iterator end() const
	{	return finish;}
	const_iterator cbegin() const
	{	return end_of_storage == data.str + LOCALSIZE ? data.str : data.start;}
	const_iterator cend() const
	{ return finish;}
	reverse_iterator rbegin()
	{  return finish - 1;}
	reverse_iterator rend()
	{	return end_of_storage == data.str + LOCALSIZE ? data.str - 1: data.start - 1;}
	const_reverse_iterator rbegin() const
	{  return finish - 1;}
	const_reverse_iterator rend() const
	{	return end_of_storage == data.str + LOCALSIZE ? data.str - 1: data.start - 1;}
	const_reverse_iterator crbegin() const
	{ return finish - 1;}
	const_reverse_iterator crend() const
	{	return end_of_storage == data.str + LOCALSIZE ? data.str - 1: data.start - 1;}

	/*************************容量相关****************************/
public:
	bool empty() const {	return cbegin() == cend();}
	size_t size() const {	return cend() - cbegin();}
	size_t max_size() const {  return end_of_storage - cbegin();}
	size_t capacity() const {	return end_of_storage - cbegin();}

	/*************************访问元素****************************/
public:
	reference operator[](size_t n);
	const_reference operator[](size_t n) const;
	string substr(size_t pos = 0) const;
	string substr(size_t pos ,size_t len) const;

	size_t find(const char c,size_t pos = 0) const;
    size_t find(const char *s,size_t pos = 0) const;
    size_t find(const char *s,size_t pos,size_t n) const;
    size_t find(const string& s,size_t pos = 0) const;

	size_t rfind(const char c,size_t pos = 0) const;
    size_t rfind(const char *s,size_t pos = 0) const;
    size_t rfind(const char *s,size_t pos,size_t n) const;
    size_t rfind(const string& s,size_t pos = 0) const;

private:
    size_t find_aux(const_iterator start,const_iterator first,const_iterator last) const;
    size_t rfind_aux(const_reverse_iterator start,const_iterator first,const_iterator last) const;

	/*************************添加元素****************************/
public:
	iterator insert(iterator pos,const char val);
	iterator insert(iterator pos,size_t n,const char val);
	iterator insert(iterator pos,const_iterator lhs,const_iterator rhs);

	string& operator+=(const char val);
	string& operator+=(const char* str);
	string& operator+=(const string& rhs);

    friend string operator+(const string& s,const char val);
    friend string operator+(const char val,const string& s);
    friend string operator+(const string& s,const char* str);
    friend string operator+(const char* str,const string& s);
    friend string operator+(const string& lhs,const string& rhs);

	void resize(size_t n,const char val);

	/*************************删除元素****************************/
public:
	void clear();
	iterator erase(iterator pos);
	iterator erase(iterator start,iterator finish);

	/*************************替换元素****************************/
public:
    string& replace(size_t pos,size_t nsize,const char *s);
    string& replace(size_t pos,size_t nsize,const char *s, int n);
    string& replace(size_t pos,size_t nsize,const string &s);
    string& replace(size_t pos,size_t nsize,const string &s,size_t newpos,size_t newnsize);
    string& replace(size_t pos,size_t nsize,size_t n,const char c);
    string& replace(iterator first,iterator last,const char *s);
    string& replace(iterator first,iterator last,const char *s,size_t n);
    string& replace(iterator first,iterator last,const string &s);
    string& replace(iterator first,iterator last,size_t n,const char c);
    string& replace(iterator first,iterator last,const_iterator newfirst,const_iterator newlast);

	/*************************关系运算****************************/
public:
	friend bool operator==(const string& lhs,const string& rhs);
    friend bool operator!=(const string& lhs,const string& rhs);
    friend bool operator>(const string& lhs,const string& rhs);
    friend bool operator>=(const string& lhs,const string& rhs);
    friend bool operator<(const string& lhs,const string& rhs);
    friend bool operator<=(const string& lhs,const string& rhs);

    friend void swap(string& lhs,string& rhs);

    friend std::ostream& operator<<(std::ostream& os,const string& rhs);


    /*************************空间管理****************************/
private:
	char* allocate(size_t n){	return data_allocator::allocate(n);}
	void deallocate(){  data_allocator::deallocate(data.start,capacity());}
	void allocate_and_fill(size_t n,const char val)
	{
        data.start = allocate(n);
        uninitialized_fill_n(data.start,n,val);
        finish = data.start + n;
        end_of_storage = data.start + n;
	}


};





}




#endif
