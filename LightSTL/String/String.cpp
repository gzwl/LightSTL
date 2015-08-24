#include "String.h"
#include "../Traits/Traits.h"


namespace LightSTL{

/*************************构造，析构，赋值**************************/
string::string(const size_t n,const char val):end_of_storage(data.str + LOCALSIZE)
{
    if(n <= LOCALSIZE) {
        memset(begin(),n,val);
        finish = begin() + n;
    }
    else
        allocate_and_fill(n,val);
}

string::string(const char* rhs):end_of_storage(data.str + LOCALSIZE)
{
    size_t n = strlen(rhs);
    if(n > LOCALSIZE){
        data.start = allocate(n);
        finish = data.start + n;
        end_of_storage = data.start + n;
        LightSTL::uninitialized_copy(rhs,rhs + n,begin());
    }
    else{
        finish = data.str + n;
        LightSTL::uninitialized_copy(rhs,rhs + n,begin());
    }
}

string::string(const string& rhs):end_of_storage(data.str + LOCALSIZE)
{
    size_t n = rhs.size();
    if(n > LOCALSIZE){
        data.start = allocate(n);
        finish = data.start + n;
        end_of_storage = data.start + n;
        LightSTL::uninitialized_copy(rhs.cbegin(),rhs.cend(),begin());
    }
    else{
        finish = data.str + n;
        LightSTL::uninitialized_copy(rhs.cbegin(),rhs.cend(),begin());
    }

}

string::string(string && rhs):end_of_storage(data.str + LOCALSIZE)
{
    size_t n = rhs.size();
    if(n > LOCALSIZE){
        data.start = rhs.data.start;
        finish = rhs.finish;
        end_of_storage = rhs.end_of_storage;
        rhs.end_of_storage = rhs.data.str + LOCALSIZE;
    }
    else{
        finish = data.str + n;
        LightSTL::uninitialized_copy(rhs.cbegin(),rhs.cend(),begin());
    }
}

string::string(const_iterator first,const_iterator last):finish(data.str),end_of_storage(data.str + LOCALSIZE)
{
    insert(begin(),first,last);
}

string::string(const std::initializer_list<char>& rhs):end_of_storage(data.str + LOCALSIZE)
{
    size_t n = rhs.size();
    if(n > LOCALSIZE){
        data.start = allocate(n);
        finish = data.start + n;
        end_of_storage = data.start + n;
        LightSTL::uninitialized_copy(rhs.begin(),rhs.end(),begin());
    }
    else{
        finish = data.str + n;
        LightSTL::uninitialized_copy(rhs.begin(),rhs.end(),begin());
    }
}

string::~string()
{
    if(end_of_storage != data.str + LOCALSIZE)      deallocate();
}

string& string::operator=(const string& rhs)
{
    //赋值的右值为本身
    if(cbegin() == rhs.cbegin())  return *this;
    size_t n = rhs.size();
    if(n > LOCALSIZE && n > size()){
        if(capacity() <= LOCALSIZE)  deallocate();
        data.start = allocate(n);
        finish = data.start + n;
        end_of_storage = data.start + n;
        LightSTL::uninitialized_copy(rhs.cbegin(),rhs.cend(),begin());
    }
    else{
        finish = data.str + n;
        LightSTL::uninitialized_copy(rhs.cbegin(),rhs.cend(),begin());
    }
    return *this;
}

string& string::operator=(string&& rhs)
{
    if(begin() == rhs.begin())  return *this;
    swap(*this,rhs);
    return *this;
}

/*************************访问元素****************************/
string::reference string::operator[](size_t n)
{
    return *(begin() + n);
}

string::const_reference string::operator[](size_t n) const
{
    return *(cbegin() + n);
}

string string::substr(size_t pos) const
{
    return string(cbegin() + pos,cend());
}

string string::substr(size_t pos,size_t len) const
{
    return string(cbegin() + pos,cbegin() + pos + len);
}

size_t string::find(const char c,size_t pos) const
{
    return find_aux(begin() + pos,&c,&c + 1);
}

size_t string::find(const char *s,size_t pos) const
{
    return find_aux(begin() + pos,s,s + strlen(s));
}

size_t string::find(const char *s,size_t pos,size_t n) const
{
    return find_aux(begin() + pos,s,s + n);
}

size_t string::find(const string &s,size_t pos) const
{
    return find_aux(begin() + pos,s.begin(),s.end());
}

size_t string::rfind(const char c,size_t pos) const
{
    return rfind_aux(rbegin() + pos,&c,&c + 1);
}

size_t string::rfind(const char *s,size_t pos) const
{
    return rfind_aux(rbegin() + pos,s,s + strlen(s));
}

size_t string::rfind(const char *s,size_t pos,size_t n) const
{
    return rfind_aux(rbegin() + pos,s,s + n);
}

size_t string::rfind(const string &s,size_t pos) const
{
    return rfind_aux(rbegin() + pos,s.begin(),s.end());
}

size_t string::find_aux(const_iterator start,const_iterator first,const_iterator last) const
{
    size_t len = last - first;
    size_t i = start - begin();
    while(i + len <= size()){
        if(LightSTL::equal(first,last,begin() + i))   break;
        ++i;
    }
    return i;
}

size_t string::rfind_aux(const_reverse_iterator start,const_iterator first,const_iterator last) const
{
    size_t len = last - first;
    size_t i = start - rbegin();
    while(i + len <= size()){
        if(LightSTL::equal(first,last,rbegin() + i))   return size() - i - 1;
        ++i;
    }
    return i;
}

/*************************添加元素****************************/

string::iterator string::insert(iterator pos,const char val)
{
	return insert(pos,1,val);
}

string::iterator string::insert(iterator pos,size_t n,const char val)
{
	if(n == 0)	return pos;

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
		return pos;
	}

	//空间不够
	else{
		size_t new_capacity = n > capacity() ? n + capacity() : 2 * capacity();
		char* new_start = allocate(new_capacity);
		size_t offset = pos - begin();
		LightSTL::uninitialized_copy(begin(),pos,new_start);
		LightSTL::uninitialized_fill_n(new_start + offset,n,val);
		LightSTL::uninitialized_copy(pos,end(),new_start + offset + n);
		if(end_of_storage != data.str + LOCALSIZE)      deallocate();
        size_t old_size = size();
		data.start = new_start;
		finish = new_start + old_size + n;
		end_of_storage = data.start + new_capacity;
		return data.start + offset;
	}
}

string::iterator string::insert(iterator pos,const_iterator lhs,const_iterator rhs)
{
    size_t n = rhs - lhs;
    if(n == 0)  return pos;
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
		char* new_start = allocate(new_capacity);
		size_t offset = static_cast<size_t>(pos - begin());
		LightSTL::uninitialized_copy(begin(),pos,new_start);
		LightSTL::uninitialized_copy(lhs,rhs,new_start + offset);
		LightSTL::uninitialized_copy(pos,end(),new_start + offset + n);
		if(end_of_storage != data.str + LOCALSIZE)  deallocate();
		size_t old_size = size();
		data.start = new_start;
		finish = new_start + old_size + n;
		end_of_storage = data.start + new_capacity;
		return begin() + offset;
	}
}

string& string::operator+=(const char val)
{
    insert(end(),val);
    return *this;
}

string& string::operator+=(const char* str)
{
    size_t len = strlen(str);
    insert(end(),str,str + len);
    return *this;
}

string& string::operator+=(const string& rhs)
{
    insert(end(),rhs.begin(),rhs.end());
    return *this;
}

string operator+(const string& s,const char val)
{
    string tmp(s);
    return tmp += val;
}

string operator+(const char val,const string& s)
{
    string tmp(s);
    return tmp += val;
}

string operator+(const string& s,const char* str)
{
    string tmp(s);
    return tmp += str;
}

string operator+(const char* str,const string& s)
{
    string tmp(s);
    return tmp += str;
}

string operator+(const string& lhs,const string& rhs)
{
    string tmp(lhs);
    return tmp += rhs;
}

void string::resize(size_t n,const char val)
{
    if(n <=  size())
        erase(begin() + n,end());
    else
        insert(end(),n - size(),val);
}

/*************************删除元素****************************/
void string::clear()
{
	finish = begin();
}

string::iterator string::erase(iterator pos)
{
    LightSTL::copy(pos + 1,end(),pos);
    --finish;
    return pos;
}

string::iterator string::erase(iterator lhs,iterator rhs)
{
    iterator ite = LightSTL::copy(rhs,end(),lhs);
    finish = ite;
    return lhs;
}

/*************************替换元素****************************/
string& string::replace(size_t pos,size_t nsize,const char *s)
{
    return replace(begin() + pos,begin() + pos + nsize,s,s + strlen(s));
}

string& string::replace(size_t pos,size_t nsize,const char *s, int n)
{
    return replace(begin() + pos,begin() + pos + nsize,s,s + n);
}
string& string::replace(size_t pos,size_t nsize,const string &s)
{
    return replace(begin() + pos,begin() + pos + nsize,s.begin(),s.begin());
}

string& string::replace(size_t pos,size_t nsize,const string &s,size_t newpos,size_t newnsize)
{
    return replace(begin() + pos,begin() + pos + nsize,s.begin() + newpos,s.begin() + newpos + newnsize);
}

string& string::replace(size_t pos,size_t nsize,size_t n,const char c)
{
    return replace(begin() + pos,begin() + pos + nsize,n,c);
}

string& string::replace(iterator first,iterator last,const char *s)
{
    return replace(first,last,s,s + strlen(s));
}

string& string::replace(iterator first,iterator last,const char *s,size_t n)
{
    return replace(first,last,s,s + n);
}

string& string::replace(iterator first,iterator last,const string &s)
{
    return replace(first,last,s.begin(),s.end());
}

string& string::replace(iterator first,iterator last,size_t n,const char c)
{
    erase(first,last);
    insert(first,n,c);
    return *this;
}

string& string::replace(iterator first,iterator last,const_iterator newfirst,const_iterator newlast)
{
    erase(first,last);
    insert(first,newfirst,newlast);
    return *this;
}

/*************************关系运算****************************/
bool operator==(const string& lhs,const string& rhs)
{
    if(lhs.size() != rhs.size())    return false;
    return memcmp(lhs.cbegin(),rhs.cbegin(),lhs.size()) == 0;
}

bool operator!=(const string& lhs,const string& rhs)
{
    return !(lhs == rhs);
}

bool operator>(const string& lhs,const string& rhs)
{
    return memcmp(lhs.cbegin(),rhs.cbegin(),lhs.size() < rhs.size() ? lhs.size() : rhs.size()) > 0;
}

bool operator>=(const string& lhs,const string& rhs)
{
    return lhs > rhs || lhs == rhs;
}

bool operator<(const string& lhs,const string& rhs)
{
    return memcmp(lhs.cbegin(),rhs.cbegin(),lhs.size() < rhs.size() ? lhs.size() : rhs.size()) < 0;
}

bool operator<=(const string& lhs,const string& rhs)
{
    return lhs < rhs || lhs == rhs;
}

void swap(string& lhs,string& rhs)
{
    swap(lhs.finish,rhs.finish);
    swap(lhs.end_of_storage,rhs.end_of_storage);
    swap(lhs.data,rhs.data);
}

std::ostream& operator<<(std::ostream& os,const string& rhs)
{
    os << rhs.cbegin() ;
    return os;
}



}
