#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "Vector.h"
#include "../Allocator/Construct.h"

namespace LightSTL{

/*************************构造，析构**************************/
template<class T,class Alloc>
vector<T,Alloc>::vector(const size_t n,const T& val)
{
	allocate_and_fill(n,val);
}

template<class T,class Alloc>
vector<T,Alloc>::vector(const size_t n)
{
	allocate_and_fill(n,T());
}

template<class T,class Alloc>
vector<T,Alloc>::vector(const vector& rhs)
{
    size_t n = rhs.size();
    start = allocate(n);
    finish = start + n;
    end_of_storage = start + n;
    uninitialized_copy(rhs.cbegin(),rhs.cend(),start);
}

template<class T,class Alloc>
vector<T,Alloc>::~vector()
{
    destroy(begin(),end());
	deallocate();
}

/*************************添加元素****************************/
template<class T,class Alloc>
void vector<T,Alloc>::push_back(const T& val)
{
	insert(end(),val);
}

template<class T,class Alloc>
typename vector<T,Alloc>::iterator vector<T,Alloc>::insert(typename vector<T,Alloc>::iterator pos,const T& val)
{
	insert(pos,1,val);
	return pos;
}

template<class T,class Alloc>
void vector<T,Alloc>::insert(typename vector<T,Alloc>::iterator pos,size_t n,const T& val)
{
	if(n == 0)	return ;

	//空间足够
	if(end_of_storage - end() >= n){

		//插入的元素位置在尾部
		if(pos == end())	uninitialized_fill_n(pos,n,val);

		//插入的元素不会到达尾部
		else if(pos + n < end()){
			uninitialized_copy(end() - n,end(),end());
			copy(pos,end() - n,pos + n);
			fill(pos,pos + n,val);
		}

		//插入的元素会到达尾部
		else{
			uninitialized_copy(pos,end(),pos + n);
			uninitialized_fill(end(),pos + n,val);
			fill(pos,end(),val);
		}
		finish = finish + n;
	}

	//空间不够
	else{
		size_t new_capacity = n > capacity() ? n + capacity() : 2 * capacity();
		T* new_start = allocate(new_capacity);
		uninitialized_copy(begin(),pos,new_start);
		uninitialized_fill_n(new_start + static_cast<size_t>(pos - begin()),n,val);
		uninitialized_copy(pos,end(),new_start + static_cast<size_t>(pos - begin()) + n);
		deallocate();
		size_t old_size = size();
		start = new_start;
		finish = new_start + old_size + n;
		end_of_storage = start + new_capacity;
	}
}

template<class T,class Alloc>
typename vector<T,Alloc>::iterator vector<T,Alloc>::insert(typename vector<T,Alloc>::iterator pos,
                                                           typename vector<T,Alloc>::iterator lhs,
                                                           typename vector<T,Alloc>::iterator rhs)
{
    size_t n = rhs - lhs;
    //空间足够
	if(end_of_storage - end() >= n){

		//插入的元素位置在尾部
		if(pos == end())	uninitialized_copy(lhs,rhs,pos);

		//插入的元素不会到达尾部
		else if(pos + n < end()){
			uninitialized_copy(end() - n,end(),end());
			copy(pos,end() - n,pos + n);
			copy(lhs,rhs,pos);
		}

		//插入的元素会到达尾部
		else{
			uninitialized_copy(pos,end(),pos + n);
			copy(lhs,lhs + static_cast<size_t>(end() - pos),pos);
			uninitialized_copy(lhs + static_cast<size_t>(end() - pos),rhs,end());
		}
		finish = finish + n;
		return pos;
	}

	//空间不够
	else{
		size_t new_capacity = n > capacity() ? n + capacity() : 2 * capacity();
		T* new_start = allocate(new_capacity);
		size_t offset = static_cast<size_t>(pos - begin());
		uninitialized_copy(begin(),pos,new_start);
		uninitialized_copy(lhs,rhs,new_start + offset);
		uninitialized_copy(pos,end(),new_start + offset + n);
		destroy(begin(),end());
		deallocate();
		size_t old_size = size();
		start = new_start;
		finish = new_start + old_size + n;
		end_of_storage = start + new_capacity;
		return start + offset;
	}
}

template<class T,class Alloc>
void vector<T,Alloc>::resize(size_t n,const T& val)
{
    if(n <=  size())
        erase(begin() + n,end());
    else
        insert(end(),n -  size(),val);
}

/*************************删除元素****************************/
template<class T,class Alloc>
void vector<T,Alloc>::pop_back()
{
	destroy(--finish);
}

template<class T,class Alloc>
void vector<T,Alloc>::clear()
{
	destroy(start,finish);
	finish = start;
}

template<class T,class Alloc>
typename vector<T,Alloc>::iterator vector<T,Alloc>::erase(typename vector<T,Alloc>::iterator pos)
{
    copy(pos + 1,end(),pos);
    destroy(--finish);
    return pos;
}

template<class T,class Alloc>
typename vector<T,Alloc>::iterator vector<T,Alloc>::erase(typename vector<T,Alloc>::iterator lhs,typename vector<T,Alloc>::iterator rhs)
{
    iterator ite = copy(rhs,end(),lhs);
    destroy(ite,end());
    finish = ite;
    return lhs;
}

/*************************关系运算****************************/

template<class T,class Alloc>
bool vector<T,Alloc>::operator==(const vector<T,Alloc>& rhs) const
{
    if(size() != rhs.size())      return false;
    for(size_t i = 0;i < rhs.size();i++){
        if((*this)[i] != rhs[i])      return false;
    }
    return true;
}

template<class T,class Alloc>
bool vector<T,Alloc>::operator!=(const vector<T,Alloc>& rhs) const
{
    return !operator==(rhs);
}

template<class T,class Alloc>
void swap(vector<T,Alloc> &lhs,vector<T,Alloc> &rhs)
{
    swap(lhs.start,rhs.start);
    swap(lhs.finish,rhs.finish);
    swap(lhs.end_of_storage,rhs.end_of_storage);
}

/*************************内存管理****************************/
template<class T,class Alloc>
void vector<T,Alloc>::allocate_and_fill(size_t n,const T& val)
{
	start = allocate(n);
	uninitialized_fill_n(start,n,val);
	finish = start + n;
	end_of_storage = start + n;
}


}

#endif
