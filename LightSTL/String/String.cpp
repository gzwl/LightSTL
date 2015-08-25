#include "String.h"
#include "../Traits/Traits.h"
#include <iostream>

namespace LightSTL{

/*************************构造，析构，赋值**************************/
string::string(const size_t n,const char val):end_of_storage(data.str + LOCALSIZE)
{
    if(n <= LOCALSIZE) {
        memset(begin(),val,n);
        finish = begin() + n;
    }
    else
        allocate_and_fill(n,val);
    *end() = '\0';
}

string::string(const char* rhs):end_of_storage(data.str + LOCALSIZE)
{
    size_t n = strlen(rhs);
    if(n > LOCALSIZE){
        data.start = allocate(n + 1);
        finish = data.start + n;
        end_of_storage = data.start + n;
        LightSTL::uninitialized_copy(rhs,rhs + n,begin());
    }
    else{
        finish = data.str + n;
        LightSTL::uninitialized_copy(rhs,rhs + n,begin());
    }
    *end() = '\0';
}

string::string(const char* rhs,size_t nsize):end_of_storage(data.str + LOCALSIZE)
{
    size_t n = nsize;
    if(n > LOCALSIZE){
        data.start = allocate(n + 1);
        finish = data.start + n;
        end_of_storage = data.start + n;
        LightSTL::uninitialized_copy(rhs,rhs + n,begin());
    }
    else{
        finish = data.str + n;
        LightSTL::uninitialized_copy(rhs,rhs + n,begin());
    }
    *end() = '\0';
}

string::string(const string& rhs,size_t pos):end_of_storage(data.str + LOCALSIZE)
{
    size_t n = rhs.size() - pos;
    if(n > LOCALSIZE){
        data.start = allocate(n + 1);
        finish = data.start + n;
        end_of_storage = data.start + n;
        LightSTL::uninitialized_copy(rhs.cbegin() + pos,rhs.cend(),begin());
    }
    else{
        finish = data.str + n;
        LightSTL::uninitialized_copy(rhs.cbegin() + pos,rhs.cend(),begin());
    }
    *end() = '\0';
}

string::string(const string& rhs,size_t pos,size_t nsize):end_of_storage(data.str + LOCALSIZE)
{
    size_t n = nsize;
    if(n > LOCALSIZE){
        data.start = allocate(n + 1);
        finish = data.start + n;
        end_of_storage = data.start + n;
        LightSTL::uninitialized_copy(rhs.cbegin() + pos,rhs.cend(),begin());
    }
    else{
        finish = data.str + n;
        LightSTL::uninitialized_copy(rhs.cbegin() + pos,rhs.cend(),begin());
    }
    *end() = '\0';
}

string::string(string && rhs):end_of_storage(data.str + LOCALSIZE)
{
    size_t n = rhs.capacity();
    if(n > LOCALSIZE){
        data.start = rhs.data.start;
        finish = rhs.finish;
        end_of_storage = rhs.end_of_storage;
        rhs.end_of_storage = rhs.data.str + LOCALSIZE;
    }
    else{
        finish = data.str + rhs.size();
        LightSTL::uninitialized_copy(rhs.cbegin(),rhs.cend(),begin());
    }
    *end() = '\0';
}

string::string(const_iterator first,const_iterator last):finish(data.str),end_of_storage(data.str + LOCALSIZE)
{
    insert(begin(),first,last);
}

string::string(const std::initializer_list<char>& rhs):end_of_storage(data.str + LOCALSIZE)
{
    size_t n = rhs.size();
    if(n > LOCALSIZE){
        data.start = allocate(n + 1);
        finish = data.start + n;
        end_of_storage = data.start + n;
        LightSTL::uninitialized_copy(rhs.begin(),rhs.end(),begin());
    }
    else{
        finish = data.str + n;
        LightSTL::uninitialized_copy(rhs.begin(),rhs.end(),begin());
    }
    *end() = '\0';
}

string::~string()
{
    if(end_of_storage != data.str + LOCALSIZE)      deallocate();
}

string& string::operator=(const char* s)
{
    size_t n = strlen(s);
    if(n > LOCALSIZE && n > size()){
        if(capacity() > LOCALSIZE)  deallocate();
        data.start = allocate(n + 1);
        finish = data.start + n;
        end_of_storage = data.start + n;
        LightSTL::uninitialized_copy(s,s + n,begin());
    }
    else{
        finish = data.str + n;
        LightSTL::uninitialized_copy(s,s + n,begin());
    }
    *end() = '\0';
    return *this;
}

string& string::operator=(const string& rhs)
{
    //赋值的右值为本身
    if(cbegin() == rhs.cbegin())  return *this;
    size_t n = rhs.size();
    if(n > LOCALSIZE && n > size()){
        if(capacity() > LOCALSIZE)  deallocate();
        data.start = allocate(n + 1);
        finish = data.start + n;
        end_of_storage = data.start + n;
        LightSTL::uninitialized_copy(rhs.cbegin(),rhs.cend(),begin());
    }
    else{
        finish = data.str + n;
        LightSTL::uninitialized_copy(rhs.cbegin(),rhs.cend(),begin());
    }
    *end() = '\0';
    return *this;
}

string& string::operator=(string&& rhs)
{
    if(begin() == rhs.begin())  return *this;
    LightSTL::swap(*this,rhs);
    return *this;
}

/*************************访问元素****************************/
string::reference string::front()
{
    return *begin();
}

string::const_reference string::front() const
{
    return *begin();
}

string::reference string::back()
{
    return *rbegin();
}

string::const_reference string::back() const
{
    return *rbegin();
}

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
    for(size_t i = pos;i < size();i++){
        if((*this)[i] == c)     return i;
    }
    return npos;
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
    if(pos == npos)     pos = size() - 1;
    for(size_t i = pos;i >= 0;i--){
        if((*this)[i] == c)     return i;
    }
    return npos;
}

size_t string::rfind(const char *s,size_t pos) const
{
    if(pos == npos)     pos = size() - 1;
    return rfind_aux(begin() + pos,s,s + strlen(s));
}

size_t string::rfind(const char *s,size_t pos,size_t n) const
{
    if(pos == npos)     pos = size() - 1;
    return rfind_aux(begin() + pos,s,s + n);
}

size_t string::rfind(const string &s,size_t pos) const
{
    if(pos == npos)     pos = size() - 1;
    return rfind_aux(begin() + pos,s.begin(),s.end());
}

size_t string::find_first_of(const char c,size_t pos) const
{
    for(size_t i = pos;i < size();i++){
        if((*this)[i] == c)     return i;
    }
    return npos;
}

size_t string::find_first_of(const char *s,size_t pos) const
{
    return find_first_of_aux(begin() + pos,end(),s,s + strlen(s));
}

size_t string::find_first_of(const char *s,size_t pos,size_t n) const
{
    return find_first_of_aux(begin() + pos,end(),s,s + n);
}

size_t string::find_first_of(const string &s,size_t pos) const
{
    return find_first_of_aux(begin() + pos,end(),s.begin(),s.end());
}

size_t string::find_first_not_of(const char c,size_t pos) const
{
    for(size_t i = pos;i < size();i++){
        if((*this)[i] != c)     return i;
    }
    return npos;
}

size_t string::find_first_not_of(const char *s,size_t pos) const
{
    return find_first_not_of_aux(begin() + pos,end(),s,s + strlen(s));
}

size_t string::find_first_not_of(const char *s,size_t pos,size_t n) const
{
    return find_first_not_of_aux(begin() + pos,end(),s,s + n);
}

size_t string::find_first_not_of(const string &s,size_t pos) const
{
    return find_first_not_of_aux(begin() + pos,end(),s.begin(),s.end());
}

size_t string::find_last_of(const char c,size_t pos) const
{
    if(pos == npos)     pos = size() - 1;
    for(size_t i = pos;i >= 0;i--){
        if((*this)[i] == c)     return i;
    }
    return npos;
}

size_t string::find_last_of(const char *s,size_t pos) const
{
    if(pos == npos)     pos = size() - 1;
    pos = size() - 1 - pos;
    return find_last_of_aux(rbegin() + pos,rend(),s,s + strlen(s));
}

size_t string::find_last_of(const char *s,size_t pos,size_t n) const
{
    if(pos == npos)     pos = size() - 1;
    pos = size() - 1 - pos;
    return find_last_of_aux(rbegin() + pos,rend(),s,s + n);
}

size_t string::find_last_of(const string &s,size_t pos) const
{
    if(pos == npos)     pos = size() - 1;
    pos = size() - 1 - pos;
    return find_last_of_aux(rbegin() + pos,rend(),s.begin(),s.end());
}

size_t string::find_last_not_of(const char c,size_t pos) const
{
    if(pos == npos)     pos = size() - 1;
    for(size_t i = pos;i >= 0;i--){
        if((*this)[i] != c)     return i;
    }
    return npos;
}

size_t string::find_last_not_of(const char *s,size_t pos) const
{
    if(pos == npos)     pos = size() - 1;
    pos = size() - 1 - pos;
    return find_last_not_of_aux(rbegin() + pos,rend(),s,s + strlen(s));
}

size_t string::find_last_not_of(const char *s,size_t pos,size_t n) const
{
    if(pos == npos)     pos = size() - 1;
    pos = size() - 1 - pos;
    return find_last_not_of_aux(rbegin() + pos,rend(),s,s + n);
}

size_t string::find_last_not_of(const string &s,size_t pos) const
{
    if(pos == npos)     pos = size() - 1;
    pos = size() - 1 - pos;
    return find_last_not_of_aux(rbegin() + pos,rend(),s.begin(),s.end());
}

size_t string::find_aux(const_iterator start,const_iterator first,const_iterator last) const
{
    size_t len = last - first;
    size_t i = start - begin();
    while(i + len <= size()){
        if(LightSTL::equal(first,last,begin() + i))   return i;
        ++i;
    }
    return npos;
}

size_t string::rfind_aux(const_iterator start,const_iterator first,const_iterator last) const
{
    size_t len = last - first;
    if(len > size())    return npos;
    size_t i = start - begin();
    while(i + len > size())     --i;
    while(1){
        if(LightSTL::equal(first,last,begin() + i))   return i;
        if(i == 0)  break;
        --i;
    }
    return npos;
}

size_t string::find_first_of_aux(const_iterator first0,const_iterator last0,const_iterator first1,const_iterator last1) const
{
    const static int CHARSIZE = 300;
    int vis[CHARSIZE] = {0};
    for(const_iterator ite = first1;ite != last1;++ite)     vis[*ite] = 1;
    for(const_iterator ite = first0;ite != last0;++ite){
        if(vis[*ite])   return ite - begin();
    }
    return npos;
}

size_t string::find_first_not_of_aux(const_iterator first0,const_iterator last0,const_iterator first1,const_iterator last1) const
{
    const static int CHARSIZE = 300;
    int vis[CHARSIZE] = {0};
    for(const_iterator ite = first1;ite != last1;++ite)     vis[*ite] = 1;
    for(const_iterator ite = first0;ite != last0;++ite){
        if(!vis[*ite])   return ite - begin();
    }
    return npos;
}

size_t string::find_last_of_aux(const_reverse_iterator first0,const_reverse_iterator last0,const_iterator first1,const_iterator last1) const
{
    const static int CHARSIZE = 300;
    int vis[CHARSIZE] = {0};
    for(const_iterator ite = first1;ite != last1;++ite)     vis[*ite] = 1;
    for(const_reverse_iterator ite = first0;ite != last0;++ite){
        if(vis[*ite])   return size() - 1 - (ite - rbegin());
    }
    return npos;
}

size_t string::find_last_not_of_aux(const_reverse_iterator first0,const_reverse_iterator last0,const_iterator first1,const_iterator last1) const
{
    const static int CHARSIZE = 300;
    int vis[CHARSIZE] = {0};
    for(const_iterator ite = first1;ite != last1;++ite)     vis[*ite] = 1;
    for(const_reverse_iterator ite = first0;ite != last0;++ite){
        if(!vis[*ite])   return size() - 1 - (ite - rbegin());
    }
    return npos;
}

/*************************添加元素****************************/
string& string::insert(size_t pos,const char* s)
{
    return insert(begin() + pos,s,s + strlen(s));
}

string& string::insert(size_t pos,const char* s,size_t n)
{
    return insert(begin() + pos,s,s + n);
}

string& string::insert(size_t pos,size_t n,const char c)
{
    return insert(begin() + pos,n,c);
}

string& string::insert(size_t pos,const string& s)
{
    return insert(begin() + pos,s.begin(),s.end());
}

string& string::insert(size_t pos,const string& s,size_t pos2,size_t n)
{
    return insert(begin() + pos,s.begin() + pos2,s.begin() + pos2 + n);
}

string& string::insert(iterator pos,const char val)
{
	return insert(pos,1,val);
}

string& string::insert(iterator pos,size_t n,const char val)
{
	if(n == 0)	return *this;

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
		char* new_start = allocate(new_capacity + 1);
		size_t offset = pos - begin();
		LightSTL::uninitialized_copy(begin(),pos,new_start);
		LightSTL::uninitialized_fill_n(new_start + offset,n,val);
		LightSTL::uninitialized_copy(pos,end(),new_start + offset + n);
		if(end_of_storage != data.str + LOCALSIZE)      deallocate();
        size_t old_size = size();
		data.start = new_start;
		finish = new_start + old_size + n;
		end_of_storage = data.start + new_capacity;
	}
	*end() = '\0';
	return *this;
}

string& string::insert(iterator pos,const_iterator lhs,const_iterator rhs)
{
    size_t n = rhs - lhs;
    if(n == 0)  return *this;
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
	}

	//空间不够
	else{
		size_t new_capacity = n > capacity() ? n + capacity() : 2 * capacity();
		char* new_start = allocate(new_capacity + 1);
		size_t offset = static_cast<size_t>(pos - begin());
		LightSTL::uninitialized_copy(begin(),pos,new_start);
		LightSTL::uninitialized_copy(lhs,rhs,new_start + offset);
		LightSTL::uninitialized_copy(pos,end(),new_start + offset + n);
		if(end_of_storage != data.str + LOCALSIZE)  deallocate();
		size_t old_size = size();
		data.start = new_start;
		finish = new_start + old_size + n;
		end_of_storage = data.start + new_capacity;
	}
	*end() = '\0';
    return *this;
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
    string tmp;
    tmp += val;
    return tmp += s;
}

string operator+(const string& s,const char* str)
{
    string tmp(s);
    return tmp += str;
}

string operator+(const char* str,const string& s)
{
    string tmp(str);
    return tmp += s;
}

string operator+(const string& lhs,const string& rhs)
{
    string tmp(lhs);
    return tmp += rhs;
}

string& string::append(const char *s)
{
    return append(s,s + strlen(s));
}

string& string::append(const char *s,size_t n)
{
    return append(s,s + n);
}

string& string::append(const string &s)
{
    return append(s.begin(),s.end());
}

string& string::append(const string &s,size_t pos,size_t n)
{
    return append(s.begin() + pos,s.begin() + pos + n);
}

string& string::append(size_t n,const char c)
{
    insert(end(),n,c);
    return *this;
}

string& string::append(const_iterator first,const_iterator last)
{
    insert(end(),first,last);
    return *this;
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
	*end() = '\0';
}

string& string::erase(size_t pos,size_t nsize)
{
    erase(begin() + pos,begin() + pos + nsize);
    return *this;
}

string::iterator string::erase(iterator pos)
{
    LightSTL::copy(pos + 1,end(),pos);
    --finish;
    *end() = '\0';
    return pos;
}

string::iterator string::erase(iterator lhs,iterator rhs)
{
    iterator ite = LightSTL::copy(rhs,end(),lhs);
    finish = ite;
    *end() = '\0';
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
    return replace(begin() + pos,begin() + pos + nsize,s.begin(),s.end());
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
int string::compare(const string &s) const
{
    return compare(0,size(),s,0,s.size());
}

int string::compare(size_t pos,size_t n,const string &s)const
{
    return compare(pos,n,s,0,s.size());
}

int string::compare(size_t pos,size_t n,const string &s,size_t pos2,size_t n2)const
{
    if(n == n2)     return memcmp(begin() + pos,s.begin() + pos2,n);
    int res = memcmp(begin() + pos,s.begin() + pos2,LightSTL::min(n,n2));
    if(res != 0)    return res;
    return n < n2 ? -1 : 1;
}

int string::compare(const char *s) const
{
    return compare(0,size(),s,0);
}

int string::compare(size_t pos,size_t n,const char *s) const
{
    return compare(pos,n,s,0);
}

int string::compare(size_t pos,size_t n,const char *s,size_t pos2) const
{
    size_t n2 = strlen(s + pos2);
    if(n == n2)     return memcmp(begin() + pos,s + pos2,n);
    int res = memcmp(begin() + pos,s + pos2,LightSTL::min(n,n2));
    if(res != 0)    return res;
    return n < n2 ? -1 : 1;
}

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
    if(lhs.size() != rhs.size())    return memcmp(lhs.cbegin(),rhs.cbegin(),lhs.size()) > 0;
    int res = memcmp(lhs.cbegin(),rhs.cbegin(),LightSTL::min(lhs.size(),rhs.size()));
    if(res > 0 || (res == 0 && lhs.size() > rhs.size()))    return true;
    return false;
}

bool operator>=(const string& lhs,const string& rhs)
{
    return lhs > rhs || lhs == rhs;
}

bool operator<(const string& lhs,const string& rhs)
{
    if(lhs.size() != rhs.size())    return memcmp(lhs.cbegin(),rhs.cbegin(),lhs.size()) < 0;
    int res = memcmp(lhs.cbegin(),rhs.cbegin(),LightSTL::min(lhs.size(),rhs.size()));
    if(res < 0 || (res == 0 && lhs.size() < rhs.size()))    return true;
    return false;
}

bool operator<=(const string& lhs,const string& rhs)
{
    return lhs < rhs || lhs == rhs;
}

void string::swap(string& rhs)
{
    size_t lnewsize = rhs.size();
    size_t lnewcap = rhs.capacity();
    size_t rnewsize = size();
    size_t rnewcap = capacity();
    LightSTL::swap(data,rhs.data);
    if(lnewcap > LOCALSIZE){
        finish = data.start + lnewsize;
        end_of_storage = data.start + lnewcap;
    }
    else{
        finish = data.str + lnewsize;
        end_of_storage = data.str + lnewcap;
    }
    if(rnewcap > LOCALSIZE){
        rhs.finish = rhs.data.start + rnewsize;
        rhs.end_of_storage = rhs.data.start + rnewcap;
    }
    else{
        rhs.finish = rhs.data.str + rnewsize;
        rhs.end_of_storage = rhs.data.str + rnewcap;
    }
}

void swap(string& lhs,string& rhs)
{
    lhs.swap(rhs);
}

std::ostream& operator<<(std::ostream& os,const string& rhs)
{
    os << rhs.cbegin() ;
    return os;
}



}
