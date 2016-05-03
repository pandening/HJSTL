/*
* CopyRight (c) 2016
* HuJian in nankai edu.
*
* Permission to use, copy, modify, distribute and sell this software
* and its documentation for any purpose is hereby granted without fee,
* provided that the above copyright notice appear in all copies and
* that both that copyright notice and this permission notice appear
* in supporting documentation.  Silicon Graphics makes no
* representations about the suitability of this software for any
* purpose.  It is provided "as is" without express or implied warranty.
*
* This file is about HJSTL's memory allocate reference to SGI STL's allocate
* Time :2016/4/5 in nankai edu
*/
#ifndef _HJ_STL_ALLOC_H_
#define _HJ_STL_ALLOC_H_

#include "hjstl_memorypool.h"

#define  HJSTL_VERSION   "hjstl version 1.0.1,hujian,copyright C 2016"

//ok,in this file,we do nothing but define the alloc,for some reason,i will
//define some allocate,you can use the follow allocates when you need.
template<int inst>
class ___hjstl_allocate_{
public:
	//you can use the follow allocate.the follow allocate will use in hjstl
	typedef hjstl_first_malloc   Alloc_first;
	typedef hjstl_second_malloc  Alloc_second;
	typedef hjstl_first_malloc   Alloc_user_first;
	typedef hjstl_second_malloc  Alloc_user_second;

	//you should not use the follow allocate.the follow allocate will use in hjstl

	typedef hjstl_first_malloc   HJSTL_Allocate;
	typedef hjstl_second_malloc  HJSTL_Allocate_default;
	typedef HJSTL_Allocate_default Alloc;

};

//ok,you can use this in your project
typedef ___hjstl_allocate_<0> HJSTL_Alloc;


template<class Type,class Alloc>
class _HJSTL_simple_alloc{
public:
	//n.
	static Type* allocate(size_t n){
		return 0 == n ? 0 : (Type*)Alloc::hjstl_allocate(n*sizeof(Type));
	}
	//just one.
	static Type* allocate(){
		return (Type*)Alloc::hjstl_allocate(sizeof(Type));
	}
	static void deallocate(Type* ptr, size_t n){
		if (0 != n){
			Alloc::hjstl_deallocate(ptr, n*sizeof(Type));
		}
	}
	//just one
	static void deallocate(Type* ptr){
		Alloc::hjstl_deallocate(ptr, sizeof(Type));
	}
};
#endif  //end of _HJ_STL_ALLOC_H_