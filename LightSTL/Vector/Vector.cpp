#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "../Traits/Traits.h"
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
vector<T,Alloc>::vector(const vector<T,Alloc>& rhs)
{
    size_t n = rhs.size();
    start = allocate(n);
    finish = start + n;
    end_of_storage = start + n;
    LightSTL::uninitialized_copy(rhs.cbegin(),rhs.cend(),start);
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
		if(pos == end())	LightSTL::uninitialized_fill_n(pos,n,val);

		//插入的元素不会到达尾部
		else if(pos + n < end()){
			LightSTL::uninitialized_copy(end() - n,end(),end());
			LightSTL::copy(pos,end() - n,pos + n);
			LightSTL::fill(pos,pos + n,val);
		}

		//插入的元素会到达尾部
		else{
			LightSTL::uninitialized_copy(pos,end(),pos + n);
			LightSTL::uninitialized_fill(end(),pos + n,val);
			LightSTL::fill(pos,end(),val);
		}
		finish = finish + n;
	}

	//空间不够
	else{
		size_t new_capacity = n > capacity() ? n + capacity() : 2 * capacity();
		T* new_start = allocate(new_capacity);
		LightSTL::uninitialized_copy(begin(),pos,new_start);
		LightSTL::uninitialized_fill_n(new_start + static_cast<size_t>(pos - begin()),n,val);
		LightSTL::uninitialized_copy(pos,end(),new_start + static_cast<size_t>(pos - begin()) + n);
		destroy(begin(),end());
		deallocate();
		size_t old_size = size();
		start = new_start;
		finish = new_start + old_size + n;
		end_of_storage = start + new_capacity;
	}
}

template<class T,class Alloc>
template<class InputIterator>
typename vector<T,Alloc>::iterator vector<T,Alloc>::insert(typename vector<T,Alloc>::iterator pos,
                                                           InputIterator lhs,
                                                           InputIterator rhs)
{
    typedef typename iterator_traits<InputIterator>::iterator_type iterator_type;
    iterator_type fuck;
    return insert_aux(pos,lhs,rhs,fuck);
}

template<class T,class Alloc>
void vector<T,Alloc>::resize(size_t n,const T& val)
{
    if(n <=  size())
        erase(begin() + n,end());
    else
        insert(end(),n - size(),val);
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
    LightSTL::copy(pos + 1,end(),pos);
    destroy(--finish);
    return pos;
}

template<class T,class Alloc>
typename vector<T,Alloc>::iterator vector<T,Alloc>::erase(typename vector<T,Alloc>::iterator lhs,typename vector<T,Alloc>::iterator rhs)
{
    iterator ite = LightSTL::copy(rhs,end(),lhs);
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
void vector<T,Alloc>::operator=(const vector<T,Alloc>& rhs)
{
    //赋值的右值为本身
    if(start == rhs.start)  return ;
    destroy(start,finish);
    if(size() >= rhs.size()){
        finish = uninitialized_copy(rhs.start,rhs.finish,start);
    }
    else{
        destroy(begin(),end());
        deallocate();
        start = allocate(rhs.size());
        finish = uninitialized_copy(rhs.start,rhs.finish,start);
        end_of_storage = finish;
    }
}

template<class T,class Alloc>
void swap(vector<T,Alloc> &lhs,vector<T,Alloc> &rhs)
{
    LightSTL::swap(lhs.start,rhs.start);
    LightSTL::swap(lhs.finish,rhs.finish);
    LightSTL::swap(lhs.end_of_storage,rhs.end_of_storage);
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

template<class T,class Alloc>
template<class InputIterator>
typename vector<T,Alloc>::iterator vector<T,Alloc>::insert_aux(typename vector<T,Alloc>::iterator pos,
                                                               InputIterator lhs,
                                                               InputIterator rhs,
                                                               random_access_iterator)
{
    size_t n = rhs - lhs;
    //空间足够
	if(end_of_storage - end() >= n){

		//插入的元素位置在尾部
		if(pos == end())	LightSTL::uninitialized_copy(lhs,rhs,pos);

		//插入的元素不会到达尾部
		else if(pos + n < end()){
			LightSTL::uninitialized_copy(end() - n,end(),end());
			LightSTL::copy(pos,end() - n,pos + n);
			LightSTL::copy(lhs,rhs,pos);
		}

		//插入的元素会到达尾部
		else{
			LightSTL::uninitialized_copy(pos,end(),pos + n);
			LightSTL::copy(lhs,lhs + static_cast<size_t>(end() - pos),pos);
			LightSTL::uninitialized_copy(lhs + static_cast<size_t>(end() - pos),rhs,end());
		}
		finish = finish + n;
		return pos;
	}

	//空间不够
	else{
		size_t new_capacity = n > capacity() ? n + capacity() : 2 * capacity();
		T* new_start = allocate(new_capacity);
		size_t offset = static_cast<size_t>(pos - begin());
		LightSTL::uninitialized_copy(begin(),pos,new_start);
		LightSTL::uninitialized_copy(lhs,rhs,new_start + offset);
		LightSTL::uninitialized_copy(pos,end(),new_start + offset + n);
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
template<class InputIterator>
typename vector<T,Alloc>::iterator vector<T,Alloc>::insert_aux(typename vector<T,Alloc>::iterator pos,
                                                               InputIterator lhs,
                                                               InputIterator rhs,
                                                               forward_iterator)
{
    size_t n = 0;
    InputIterator tmp = lhs;
    while(tmp != rhs){
        ++tmp;++n;
    }
    //空间足够
	if(end_of_storage - end() >= n){

		//插入的元素位置在尾部
		if(pos == end())	LightSTL::uninitialized_copy(lhs,rhs,pos);

		//插入的元素不会到达尾部
		else if(pos + n < end()){
			LightSTL::uninitialized_copy(end() - n,end(),end());
			LightSTL::copy(pos,end() - n,pos + n);
			LightSTL::copy(lhs,rhs,pos);
		}

		//插入的元素会到达尾部
		else{
			LightSTL::uninitialized_copy(pos,end(),pos + n);
			LightSTL::copy(lhs,lhs + static_cast<size_t>(end() - pos),pos);
			LightSTL::uninitialized_copy(lhs + static_cast<size_t>(end() - pos),rhs,end());
		}
		finish = finish + n;
		return pos;
	}

	//空间不够
	else{
		size_t new_capacity = n > capacity() ? n + capacity() : 2 * capacity();
		T* new_start = allocate(new_capacity);
		size_t offset = static_cast<size_t>(pos - begin());
		LightSTL::uninitialized_copy(begin(),pos,new_start);
		LightSTL::uninitialized_copy(lhs,rhs,new_start + offset);
		LightSTL::uninitialized_copy(pos,end(),new_start + offset + n);
		destroy(begin(),end());
		deallocate();
		size_t old_size = size();
		start = new_start;
		finish = new_start + old_size + n;
		end_of_storage = start + new_capacity;
		return start + offset;
	}

}

}

#endif
