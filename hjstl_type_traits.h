#ifndef __HJSTL_TYPE_TRAITS_H
#define __HJSTL_TYPE_TRAITS_H

/*
* Author:hujian
* Time:2016/4/10
* discription:this file is about traits of hjstl
*
*/

struct __hjstl_true_type {};

struct __hjstl_false_type {};

template <class type>
struct __type_traits {
	typedef __hjstl_true_type     this_dummy_member_must_be_first;

	typedef __hjstl_false_type    has_trivial_default_constructor;
	typedef __hjstl_false_type    has_trivial_copy_constructor;
	typedef __hjstl_false_type    has_trivial_assignment_operator;
	typedef __hjstl_false_type    has_trivial_destructor;
	typedef __hjstl_false_type    is_POD_type;
};

template<> struct __type_traits<char> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template<> struct __type_traits<signed char> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template<>  struct __type_traits<unsigned char> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template<>  struct __type_traits<short> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template<>  struct __type_traits<unsigned short> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template<>  struct __type_traits<int> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template<>  struct __type_traits<unsigned int> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template<>  struct __type_traits<long> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template<>  struct __type_traits<unsigned long> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template<>  struct __type_traits<float> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template<>  struct __type_traits<double> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template<>  struct __type_traits<long double> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template <class T>
struct __type_traits<T*> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};


template<>struct __type_traits<char*> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template<>struct __type_traits<signed char*> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};

template<>struct __type_traits<unsigned char*> {
	typedef __hjstl_true_type    has_trivial_default_constructor;
	typedef __hjstl_true_type    has_trivial_copy_constructor;
	typedef __hjstl_true_type    has_trivial_assignment_operator;
	typedef __hjstl_true_type    has_trivial_destructor;
	typedef __hjstl_true_type    is_POD_type;
};


#endif /* __HJSTL_TYPE_TRAITS_H */
