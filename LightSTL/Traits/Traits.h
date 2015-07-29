#ifndef TRAITS_H
#define TRAITS_H

namespace LightSTL{
}
struct trival_type{};
struct nontrival_type{};

template<class T>
struct type_traits
{
	typedef nontrival_type destructor_type; 
}



template<class T>
struct type_traits<T*>
{
	typedef trival_type destructor_type;
}

template<>
struct type_traits<int>
{
	typedef trival_type destructor_type;
}


template<>
struct type_traits<unsigned int>
{
	typedef trival_type destructor_type;
}


template<>
struct type_traits<short>
{
	typedef trival_type destructor_type;
}


template<>
struct type_traits<unsigned short>
{

	typedef trival_type destructor_type;
}


template<>
struct type_traits<long>
{
	typedef trival_type destructor_type;
}


template<>
struct type_traits<unsigned long>
{
	typedef trival_type destructor_type;
}


template<>
struct type_traits<char>
{
	typedef trival_type destructor_type;
}


template<>
struct type_traits<unsigned char>
{
	typedef trival_type destructor_type;
}


template<>
struct type_traits<float>
{
	typedef trival_type destructor_type;
}


template<>
struct type_traits<double>
{
	typedef trival_type destructor_type;
}


template<>
struct type_traits<long double>
{
	typedef trival_type destructor_type;
}



#endif
