#ifndef __HJ_STL_INTERNAL_UNINITIALIZED_H
#define __HJ_STL_INTERNAL_UNINITIALIZED_H
/*
* Author:hujian
* Time:2016/4/6
* discription:this file is about uninitialzed.
*
*/

#include "hjstl_type_traits.h"
#include "hjstl_construct.h"
#include<iostream>


using namespace std;

// Valid if copy construction is equivalent to assignment, and if the
//  destructor is trivial.
template <class InputIterator, class ForwardIterator>
inline ForwardIterator
__hjstl_uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __hjstl_true_type) {
	return copy(first, last, result);
}

template <class InputIterator, class ForwardIterator>ForwardIterator
__hjstl_uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __hjstl_false_type) {
	ForwardIterator cur = result;
	for (; first != last; ++first, ++cur)
		construct(&*cur, *first);
	return cur;
}


template <class InputIterator, class ForwardIterator, class T>inline ForwardIterator
__hjstl_uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*) {
	typedef typename __type_traits<T>::is_POD_type is_POD;
	return __hjstl_uninitialized_copy_aux(first, last, result, is_POD());
}

template <class InputIterator, class ForwardIterator>inline ForwardIterator
hjstl_uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
	return __hjstl_uninitialized_copy(first, last, result, hjstl_value_type(result));
}

inline char* hjstl_uninitialized_copy(const char* first, const char* last, char* result) {
	memmove(result, first, last - first);
	return result + (last - first);
}

inline wchar_t* uninitialized_copy(const wchar_t* first, const wchar_t* last, wchar_t* result) {
	memmove(result, first, sizeof(wchar_t) * (last - first));
	return result + (last - first);
}

template <class InputIterator, class Size, class ForwardIterator>
pair<InputIterator, ForwardIterator>
__hjstl_uninitialized_copy_n(InputIterator first, Size count, ForwardIterator result, input_iterator_tag) {
	ForwardIterator cur = result;
	for (; count > 0; --count, ++first, ++cur)
		construct(&*cur, *first);
	return pair<InputIterator, ForwardIterator>(first, cur);
}

template <class RandomAccessIterator, class Size, class ForwardIterator>
inline pair<RandomAccessIterator, ForwardIterator>
__hjstl_uninitialized_copy_n(RandomAccessIterator first, Size count,
ForwardIterator result,
random_access_iterator_tag) {
	RandomAccessIterator last = first + count;
	return make_pair(last, hjstl_uninitialized_copy(first, last, result));
}

template <class InputIterator, class Size, class ForwardIterator>
inline pair<InputIterator, ForwardIterator>
hjstl_uninitialized_copy_n(InputIterator first, Size count,
ForwardIterator result) {
	return __hjstl_uninitialized_copy_n(first, count, result, hjstl_iterator_category(first));
}

// Valid if copy construction is equivalent to assignment, and if the
//  destructor is trivial.
template <class ForwardIterator, class T>
inline void
__hjstl_uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
const T& x, __hjstl_true_type)
{
	fill(first, last, x);
}

template <class ForwardIterator, class T>
void
__hjstl_uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
const T& x, __hjstl_false_type)
{
	ForwardIterator cur = first;
	for (; cur != last; ++cur)
		construct(&*cur, x);
}

template <class ForwardIterator, class T, class T1>
inline void __hjstl_uninitialized_fill(ForwardIterator first, ForwardIterator last,
	const T& x, T1*) {
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	__hjstl_uninitialized_fill_aux(first, last, x, is_POD());

}

template <class ForwardIterator, class T>
inline void hjstl_uninitialized_fill(ForwardIterator first, ForwardIterator last,
	const T& x) {
	__hjstl_uninitialized_fill(first, last, x, value_type(first));
}

// Valid if copy construction is equivalent to assignment, and if the
//  destructor is trivial.
template <class ForwardIterator, class Size, class T>
inline ForwardIterator
__hjstl_uninitialized_fill_n_aux(ForwardIterator first, Size n,
const T& x, __hjstl_true_type) {
	return fill_n(first, n, x);
}

template <class ForwardIterator, class Size, class T>
ForwardIterator
__hjstl_uninitialized_fill_n_aux(ForwardIterator first, Size n,
const T& x, __hjstl_false_type) {
	ForwardIterator cur = first;
	for (; n > 0; --n, ++cur)
		construct(&*cur, x);
	return cur;
}

template <class ForwardIterator, class Size, class T, class T1>
inline ForwardIterator __hjstl_uninitialized_fill_n(ForwardIterator first, Size n,
	const T& x, T1*) {
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	return __hjstl_uninitialized_fill_n_aux(first, n, x, is_POD());

}

template <class ForwardIterator, class Size, class T>
inline ForwardIterator hjstl_uninitialized_fill_n(ForwardIterator first, Size n,
	const T& x) {
	return __hjstl_uninitialized_fill_n(first, n, x, hjstl_value_type(first));
}

// Copies [first1, last1) into [result, result + (last1 - first1)), and
//  copies [first2, last2) into
//  [result, result + (last1 - first1) + (last2 - first2)).

template <class InputIterator1, class InputIterator2, class ForwardIterator>
inline ForwardIterator
__hjstl_uninitialized_copy_copy(InputIterator1 first1, InputIterator1 last1,
InputIterator2 first2, InputIterator2 last2,
ForwardIterator result) {
	ForwardIterator mid = hjstl_uninitialized_copy(first1, last1, result);
	return hjstl_uninitialized_copy(first2, last2, mid);
}

// Fills [result, mid) with x, and copies [first, last) into
//  [mid, mid + (last - first)).
template <class ForwardIterator, class T, class InputIterator>
inline ForwardIterator
__hjstl_uninitialized_fill_copy(ForwardIterator result, ForwardIterator mid,
const T& x,
InputIterator first, InputIterator last) {
	hjstl_uninitialized_fill(result, mid, x);
	return hjstl_uninitialized_copy(first, last, mid);
}

// Copies [first1, last1) into [first2, first2 + (last1 - first1)), and
//  fills [first2 + (last1 - first1), last2) with x.
template <class InputIterator, class ForwardIterator, class T>
inline void
__hjstl_uninitialized_copy_fill(InputIterator first1, InputIterator last1,
ForwardIterator first2, ForwardIterator last2,
const T& x) {
	ForwardIterator mid2 = hjstl_uninitialized_copy(first1, last1, first2);
	hjstl_uninitialized_fill(mid2, last2, x);
}
#endif /* __HJ_STL_INTERNAL_UNINITIALIZED_H */

