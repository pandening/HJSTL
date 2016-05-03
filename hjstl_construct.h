#ifndef __HJ_STL__CONSTRUCT_H_
#define __HJ_STL__CONSTRUCT_H_

/*
* Author:hujian
* Time:2016/4/11
* discription:this file is about constructor of hjstl
*
*/

#include <new.h>   //using the placement new<an overload version of operate new>
#include "hjstl_type_traits.h"

#include <string>
#include<iostream>

using namespace std;

//need a pointer and distory  it.
template <class T>
inline void destroy(T* pointer) {
	pointer->~T();
}

//need two params.construct an new object.
//using the placement new,not new!
template <class T1, class T2>
inline void construct(T1* p,T2& value) {
	new (p)T1(value);
}

//destory,and need two iterator,the function will use the 
//__type_traits to find the most useful fucntion to do this.
template <class ForwardIterator>
inline void  //false type means we can do nothing in opt.
__destroy_aux(ForwardIterator first, ForwardIterator last, __hjstl_false_type) {
	for (; first < last; ++first)
		destroy(&*first);
}

template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator, ForwardIterator, __hjstl_true_type) {}

template <class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*) {
	typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor; //dispatch this job.
	__destroy_aux(first, last, trivial_destructor());
}
//this is the highest level function.
template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
	__destroy(first, last, hjstl_value_type(first));
}

inline void destroy(char*, char*) {}
inline void destroy(wchar_t*, wchar_t*) {}

#endif /* __HJ_STL__CONSTRUCT_H_ */