#ifndef HASHMAP_H
#define HASHMAP_H

#include "../HashTable/HashTable.h"
#include "../Functor/Functor.h"
#include "../Pair/Pair.h"

namespace LightSTL{

template<class Key,
         class Val,
         class HashFun = LightSTL::hash<Key>,
         class GetKey = LightSTL::select1st<LightSTL::pair<Key,Val> >,
         class EqualKey = LightSTL::equal_to<Key>,
         class Alloc = LightSTL::alloc>
class hash_map
{
private:
    typedef LightSTL::hash_table<LightSTL::pair<Key,Val>,HashFun,GetKey,EqualKey ,Alloc>  Container;
public:
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;
private:
    Container c;

    /*************************构造，析构**************************/
public:
    hash_map(size_t n = 0,
             const HashFun& hf = HashFun(),
             const GetKey& gk = GetKey(),
             const EqualKey& ek = EqualKey()):c(n,hf,gk,ek){}
    hash_map(const hash_map& rhs):c(rhs.c){}


	/*************************迭代器相关**************************/
public:
	iterator begin(){
        return c.begin();
    }
	const_iterator cbegin() const{
        return c.cbegin();
    }
	iterator end() {
        return c.end();
    }
	const_iterator cend() const{
        return c.cend();
	}

	/*************************容量相关****************************/
public:
	bool empty() const {
        return c.empty();
    }
	size_t size() const {
        return c.size();
    }

	/*************************添加元素****************************/
public:
    iterator insert(const LightSTL::pair<Key,Val>& rhs){
        return c.insert_unique(rhs);
    }

    /*************************删除元素****************************/
public:
    void clear(){
        c.clear();
    }
    void erase(iterator pos){
        c.erase(pos);
    }
    size_t erase(const Key& rhs){
        return c.erase(make_pair(rhs,Val()));
    }

    /*************************访问元素****************************/
public:
    iterator find(const Key& rhs) {
        return c.find(make_pair(rhs,Val()));
    }
    const_iterator find(const Key& rhs) const{
        return c.find(make_pair(rhs,Val()));
    }
    Val& operator[](const Key& rhs){
        iterator ite = find(rhs);
        if(ite != c.end()){
            return (*ite).second;
        }
        else{
            return (*insert(make_pair(rhs,Val()))).second;
        }
    }

};


}


#endif
