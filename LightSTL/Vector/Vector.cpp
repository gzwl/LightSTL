#include "Vector.h"

namespace LightSTL{

template<class T>
vector<T>::vector(const size_t n,const T& val)
{
	allocate_and_fill(n,val);
}

template<class T>
vector<T>::vector(const size_t n)
{
	allocate_and_fill(n,T());
}

template<class T>
vector<T>::~vector()
{	
	deallocate();
}

template<class T>
void vector<T>::push_back(const T& val)
{
	insert(end(),val);
}

template<class T>
iterator vector<T>::insert(iterator pos,const T& val)
{
	insert(pos,1,val);
	return pos;
}

template<class T>
void vector<T>::insert(iterator pos,size_t n,const T& val)
{
	if(n == 0)	return ;

	//空间足够
	if(end_of_storage - end() >= n){

		//插入的元素位置在尾部
		if(pos == end())	uninitialized_fill_n(pos,n,val);

		//插入的元素不会到达尾部
		else if(pos + n < end()){
			uninitialized_copy(end() - n,end(),end());
			initialized_copy(pos,end() - n,pos + n);
			initialized_fill(pos,pos + n,val);
		}

		//插入的元素会到达尾部
		else{
			uninitialized_copy(pos,end(),pos + n);
			uninitialized_fill(end(),pos + n,val);
			initialized_fill(pos,end(),val);
		}
	}

	//空间不够
	else{
		size_t new_capacity = n > capacity() ? n + capacity() : 2 * capacity();
		iterator new_start = allocate(new_capacity);
		uninitialized_copy(begin(),pos,new_start);
		uninitialized_fill_n(new_start + pos - begin(),n,val);
		uninitialized_copy(pos,end(),new_start + pos - begin + n);
		deallocate();
		size_t old_size = size();
		start = new_start;
		finish = new_start + old_size + n;
		end_of_storage = start + new_capacity;
	}
}

template<class T>
void vector<T>::pop_back()
{
	destroy(--finish);
}

template<class T>
void vector<T>::clear()
{
	destroy(start,finish);
	finish = start;
}

template<class T>
void vector<T>::allocate_and_fill(size_t n,const T& val)
{
	start = allocate(n);
	uninitialized_fill_n(start,n,val);
	finish = start + n;
	end_of_storage = start + n;
}


}
