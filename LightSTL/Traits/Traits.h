#ifndef TRAITS_H
#define TRAITS_H

namespace LightSTL{

/***************iterator_traits，用来萃取迭代器的性质***************/

struct normal_iterator{};
struct forward_iterator : public normal_iterator{};
struct bidirection_iterator : public forward_iterator{};
struct random_access_iterator : public bidirection_iterator{};

template<class Iterator>
struct iterator_traits
{
	typedef typename Iterator::iterator_type iterator_type;
	typedef typename Iterator::value_type value_type;	
};

template<class T>
struct iterator_traits<T*>
{
	typedef random_access_iterator iterator_type;
    typedef T value_type;	
};

/***************type_traits，用来萃取类的性质***************/

struct true_type{};
struct false_type{};

template<class T>
struct type_traits
{
	typedef false_type has_trival_destructor_type;
	typedef false_type has_trival_assignment_type;
   	typedef false_type is_POD_type;	
};



template<class T>
struct type_traits<T*>
{
	typedef true_type has_trival_destructor_type;
	typedef true_type has_trival_assignment_type;
	typedef true_type is_POD_type; 
};

template<>
struct type_traits<int>
{
	typedef true_type has_trival_destructor_type;
	typedef true_type has_trival_assignment_type;
	typedef true_type is_POD_type; 
};


template<>
struct type_traits<unsigned int>
{
	typedef true_type has_trival_destructor_type;
	typedef true_type has_trival_assignment_type;
	typedef true_type is_POD_type; 
};


template<>
struct type_traits<short>
{
	typedef true_type has_trival_destructor_type;
	typedef true_type has_trival_assignment_type;
	typedef true_type is_POD_type; 
};


template<>
struct type_traits<unsigned short>
{

	typedef true_type has_trival_destructor_type;
	typedef true_type has_trival_assignment_type;
	typedef true_type is_POD_type; 
};


template<>
struct type_traits<long>
{
	typedef true_type has_trival_destructor_type;
	typedef true_type has_trival_assignment_type;
	typedef true_type is_POD_type; 
};


template<>
struct type_traits<unsigned long>
{
	typedef true_type has_trival_destructor_type;
	typedef true_type has_trival_assignment_type;
	typedef true_type is_POD_type; 
};


template<>
struct type_traits<char>
{
	typedef true_type has_trival_destructor_type;
	typedef true_type has_trival_assignment_type;
	typedef true_type is_POD_type; 
};


template<>
struct type_traits<unsigned char>
{
	typedef true_type has_trival_destructor_type;
	typedef true_type has_trival_assignbment_type;
	typedef true_type is_POD_type; 
};


template<>
struct type_traits<float>
{
	typedef true_type has_trival_destructor_type;
	typedef true_type has_trival_assignment_type;
	typedef true_type is_POD_type; 
};


template<>
struct type_traits<double>
{
	typedef true_type has_trival_destructor_type;
	typedef true_type has_trival_assignment_type;
	typedef true_type is_POD_type; 
};


template<>
struct type_traits<long double>
{
	typedef true_type has_trival_destructor_type;
	typedef true_type has_trival_assignment_type;
	typedef true_type is_POD_type; 
};

}

#endif
