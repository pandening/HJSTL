#ifndef __HJ_STL_ITERATOR_H
#define __HJ_STL_ITERATOR_H
/*
* Author:hujian
* Time:2016/4/11
* discription:this file is about hjstl iterator
*
*/

//the five type's iterators
struct hjstl_input_iterator_tag {}; //input iterator
struct hjstl_output_iterator_tag {}; //output iterator
struct hjstl_forward_iterator_tag : public hjstl_input_iterator_tag {};//forward iterator
struct hjstl_bidirectional_iterator_tag : public hjstl_forward_iterator_tag {};//double-forward iterator
struct hjstl_random_access_iterator_tag : public hjstl_bidirectional_iterator_tag {}; //random iterator

//input iterator
template <class T, class Distance> struct _HJSTL_input_iterator {
	typedef hjstl_input_iterator_tag hjstl_iterator_category; //category
	typedef T                  hjstl_value_type; //value type
	typedef Distance           hjstl_difference_type; //difference type
	typedef T*                 hjstl_pointer; //hjstl_pointer
	typedef T&                 hjstl_reference; //hjstl_reference
};

//output iterztor
struct _HJSTL_output_iterator {
	typedef hjstl_output_iterator_tag hjstl_iterator_category;
	typedef void                hjstl_value_type;
	typedef void                hjstl_difference_type;
	typedef void                hjstl_pointer;
	typedef void                hjstl_reference;
};

//forward iterztor
template <class T, class Distance> struct _HJSTL_forward_iterator {
	typedef hjstl_forward_iterator_tag hjstl_iterator_category;
	typedef T                    hjstl_value_type;
	typedef Distance             hjstl_difference_type;
	typedef T*                   hjstl_pointer;
	typedef T&                   hjstl_reference;
};

//double forward iterator
template <class T, class Distance> struct _HJSTL_bidirectional_iterator {
	typedef hjstl_bidirectional_iterator_tag hjstl_iterator_category;
	typedef T                          hjstl_value_type;
	typedef Distance                   hjstl_difference_type;
	typedef T*                         hjstl_pointer;
	typedef T&                         hjstl_reference;
};

//random iterator
template <class T, class Distance> struct _HJSTL_random_access_iterator {
	typedef hjstl_random_access_iterator_tag hjstl_iterator_category;
	typedef T                          hjstl_value_type;
	typedef Distance                   hjstl_difference_type;
	typedef T*                         hjstl_pointer;
	typedef T&                         hjstl_reference;
};

//if you want to impelment yourself iterator,you should extends this class
template <class Category, class T, class Distance = ptrdiff_t,
class hjstl_pointer = T*, class hjstl_reference = T&>
struct hjstl_iterator {
	typedef Category  hjstl_iterator_category;
	typedef T         hjstl_value_type;
	typedef Distance  hjstl_difference_type;
	typedef hjstl_pointer   hjstl_pointer;
	typedef hjstl_reference hjstl_reference;
};

//iterator traits,get the traits of object.
template <class Iterator>
struct _HJSTL_iterator_traits {
	typedef typename Iterator::hjstl_iterator_category hjstl_iterator_category;
	typedef typename Iterator::hjstl_value_type        hjstl_value_type;
	typedef typename Iterator::hjstl_difference_type   hjstl_difference_type;
	typedef typename Iterator::hjstl_pointer           hjstl_pointer;
	typedef typename Iterator::hjstl_reference         hjstl_reference;
};



//this is the partial specialization of iterator,so, the native pointer is ok.
template <class T>
struct _HJSTL_iterator_traits<T*> {
	typedef hjstl_random_access_iterator_tag hjstl_iterator_category;
	typedef T                          hjstl_value_type;
	typedef ptrdiff_t                  hjstl_difference_type;
	typedef T*                         hjstl_pointer;
	typedef T&                         hjstl_reference;
};

//this is the partial specialization of iterator,so the const native pointer is ok.
template <class T>
struct _HJSTL_iterator_traits<const T*> {
	typedef hjstl_random_access_iterator_tag hjstl_iterator_category;
	typedef T                          hjstl_value_type;
	typedef ptrdiff_t                  hjstl_difference_type;
	typedef const T*                   hjstl_pointer;
	typedef const T&                   hjstl_reference;
};

//return the traits of iterator.<category of iterator>
template <class Iterator>
inline typename _HJSTL_iterator_traits<Iterator>::hjstl_iterator_category //this line is the return type.
hjstl_iterator_category(const Iterator&) {
	typedef typename _HJSTL_iterator_traits<Iterator>::hjstl_iterator_category category;
	return category();
}

//return the traits of iterator.<distance_type of iterator>
template <class Iterator>
inline typename _HJSTL_iterator_traits<Iterator>::hjstl_difference_type*
distance_type(const Iterator&) {
	return static_cast<typename _HJSTL_iterator_traits<Iterator>::hjstl_difference_type*>(0);
}

//return the traits of iterator.<value_type>
template <class Iterator>
inline typename _HJSTL_iterator_traits<Iterator>::hjstl_value_type*
hjstl_value_type(const Iterator&) {
	return static_cast<typename _HJSTL_iterator_traits<Iterator>::hjstl_value_type*>(0);
}

//return the tag.
template <class T, class Distance>
inline hjstl_input_iterator_tag
hjstl_iterator_category(const _HJSTL_input_iterator<T, Distance>&) {
	return hjstl_input_iterator_tag();
}

//return tag.
inline hjstl_output_iterator_tag hjstl_iterator_category(const _HJSTL_output_iterator&) {
	return hjstl_output_iterator_tag();
}

template <class T, class Distance>
inline hjstl_forward_iterator_tag
hjstl_iterator_category(const _HJSTL_forward_iterator<T, Distance>&) {
	return hjstl_forward_iterator_tag();
}

template <class T, class Distance>
inline hjstl_bidirectional_iterator_tag
hjstl_iterator_category(const _HJSTL_bidirectional_iterator<T, Distance>&) {
	return hjstl_bidirectional_iterator_tag();
}

template <class T, class Distance>
inline hjstl_random_access_iterator_tag
hjstl_iterator_category(const _HJSTL_random_access_iterator<T, Distance>&) {
	return hjstl_random_access_iterator_tag();
}

template <class T>
inline hjstl_random_access_iterator_tag hjstl_iterator_category(const T*) {
	return hjstl_random_access_iterator_tag();
}

template <class T, class Distance>
inline T* hjstl_value_type(const _HJSTL_input_iterator<T, Distance>&) {
	return (T*)(0);
}

template <class T, class Distance>
inline T* hjstl_value_type(const _HJSTL_forward_iterator<T, Distance>&) {
	return (T*)(0);
}

template <class T, class Distance>
inline T* hjstl_value_type(const _HJSTL_bidirectional_iterator<T, Distance>&) {
	return (T*)(0);
}

template <class T, class Distance>
inline T* hjstl_value_type(const _HJSTL_random_access_iterator<T, Distance>&) {
	return (T*)(0);
}

template <class T>
inline T* hjstl_value_type(const T*) { return (T*)(0); }

template <class T, class Distance>
inline Distance* hjstl_distance_type(const _HJSTL_input_iterator<T, Distance>&) {
	return (Distance*)(0);
}

template <class T, class Distance>
inline Distance* hjstl_distance_type(const _HJSTL_forward_iterator<T, Distance>&) {
	return (Distance*)(0);
}

template <class T, class Distance>
inline Distance*
hjstl_distance_type(const _HJSTL_bidirectional_iterator<T, Distance>&) {
	return (Distance*)(0);
}

template <class T, class Distance>
inline Distance*
hjstl_distance_type(const _HJSTL_random_access_iterator<T, Distance>&) {
	return (Distance*)(0);
}

template <class T>
inline ptrdiff_t* hjstl_distance_type(const T*) { return (ptrdiff_t*)(0); }


//////////////////////////////////////////////////////////////////////////////////////////

//the distance of two iterator,for input iterator
template <class InputIterator, class Distance>
inline void __hjstl_distance(InputIterator first, InputIterator last, Distance& n,
	hjstl_input_iterator_tag) {
	while (first != last) { ++first; ++n; }
}

//the distance of two random iterators.
template <class RandomAccessIterator, class Distance>
inline void __hjstl_distance(RandomAccessIterator first, RandomAccessIterator last,
	Distance& n, hjstl_random_access_iterator_tag) {
	n += last - first;
}

//dispatch.
template <class InputIterator, class Distance>
inline void hjstl_distance(InputIterator first, InputIterator last, Distance& n) {
	__hjstl_distance(first, last, n, hjstl_iterator_category(first)/*get the category*/);
}

template <class InputIterator>
inline typename _HJSTL_iterator_traits<InputIterator>::hjstl_difference_type
__hjstl_distance(InputIterator first, InputIterator last, hjstl_input_iterator_tag) {
	_HJSTL_iterator_traits<InputIterator>::hjstl_difference_type n = 0;
	while (first != last) {
		++first; ++n;
	}
	return n;
}

template <class RandomAccessIterator>
inline typename _HJSTL_iterator_traits<RandomAccessIterator>::hjstl_difference_type
__hjstl_distance(RandomAccessIterator first, RandomAccessIterator last,
hjstl_random_access_iterator_tag) {
	return last - first;
}

template <class InputIterator>
inline typename _HJSTL_iterator_traits<InputIterator>::hjstl_difference_type
hjstl_distance(InputIterator first, InputIterator last) {
	typedef typename _HJSTL_iterator_traits<InputIterator>::hjstl_iterator_category category;
	return __hjstl_distance(first, last, category());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class InputIterator, class Distance>
inline void __hjstl_advance(InputIterator& i, Distance n, hjstl_input_iterator_tag) {
	while (n--) ++i;//move n steps.
}

template <class BidirectionalIterator, class Distance>
inline void __hjstl_advance(BidirectionalIterator& i, Distance n,hjstl_bidirectional_iterator_tag) {
	//can double directions move.
	if (n >= 0)
		while (n--) ++i;
	else
		while (n++) --i;
}

template <class RandomAccessIterator, class Distance>
inline void __hjstl_advance(RandomAccessIterator& i, Distance n,hjstl_random_access_iterator_tag) {
	i += n;//haha,you can operator random iterator just like array.
}

template <class InputIterator, class Distance>
inline void hjstl_advance(InputIterator& i, Distance n) {
	__hjstl_advance(i, n, hjstl_iterator_category(i)/*get the category,and dispatch.*/);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Container>
class _HJSTL_back_insert_iterator {
protected:
	Container* container;
public:
	typedef hjstl_output_iterator_tag hjstl_iterator_category;
	typedef void                hjstl_value_type;
	typedef void                hjstl_difference_type;
	typedef void                hjstl_pointer;
	typedef void                hjstl_reference;

	explicit _HJSTL_back_insert_iterator(Container& x) : container(&x) {}
	_HJSTL_back_insert_iterator<Container>&
		operator=(const typename Container::hjstl_value_type& value) {
		container->push_back(value);
		return *this;
	}
	_HJSTL_back_insert_iterator<Container>& operator*() { return *this; }
	_HJSTL_back_insert_iterator<Container>& operator++() { return *this; }
	_HJSTL_back_insert_iterator<Container>& operator++(int) { return *this; }
};

template <class Container>
inline hjstl_output_iterator_tag
hjstl_iterator_category(const _HJSTL_back_insert_iterator<Container>&)
{
	return hjstl_output_iterator_tag();
}


template <class Container>
inline _HJSTL_back_insert_iterator<Container> back_inserter(Container& x) {
	return _HJSTL_back_insert_iterator<Container>(x);
}

template <class Container>
class _HJSTL_front_insert_iterator {
protected:
	Container* container;
public:
	typedef hjstl_output_iterator_tag hjstl_iterator_category;
	typedef void                hjstl_value_type;
	typedef void                hjstl_difference_type;
	typedef void                hjstl_pointer;
	typedef void                hjstl_reference;

	explicit _HJSTL_front_insert_iterator(Container& x) : container(&x) {}
	_HJSTL_front_insert_iterator<Container>&
		operator=(const typename Container::hjstl_value_type& value) {
		container->push_front(value);
		return *this;
	}
	_HJSTL_front_insert_iterator<Container>& operator*() { return *this; }
	_HJSTL_front_insert_iterator<Container>& operator++() { return *this; }
	_HJSTL_front_insert_iterator<Container>& operator++(int) { return *this; }
};


template <class Container>
inline hjstl_output_iterator_tag
hjstl_iterator_category(const _HJSTL_front_insert_iterator<Container>&)
{
	return hjstl_output_iterator_tag();
}


template <class Container>
inline _HJSTL_front_insert_iterator<Container> front_inserter(Container& x) {
	return _HJSTL_front_insert_iterator<Container>(x);
}

template <class Container>
class _HJSTL_insert_iterator {
protected:
	Container* container;
	typename Container::hjstl_iterator iter;
public:
	typedef hjstl_output_iterator_tag hjstl_iterator_category;
	typedef void                hjstl_value_type;
	typedef void                hjstl_difference_type;
	typedef void                hjstl_pointer;
	typedef void                hjstl_reference;

	_HJSTL_insert_iterator(Container& x, typename Container::iterator i): container(&x), iter(i) {}
	_HJSTL_insert_iterator<Container>&
		operator=(const typename Container::hjstl_value_type& value) {
		iter = container->insert(iter, value);
		++iter;
		return *this;
	}
	_HJSTL_insert_iterator<Container>& operator*() { return *this; }
	_HJSTL_insert_iterator<Container>& operator++() { return *this; }
	_HJSTL_insert_iterator<Container>& operator++(int) { return *this; }
};

template <class Container>
inline hjstl_output_iterator_tag
hjstl_iterator_category(const _HJSTL_insert_iterator<Container>&)
{
	return hjstl_output_iterator_tag();
}


template <class Container, class Iterator>
inline _HJSTL_insert_iterator<Container> inserter(Container& x, Iterator i) {
	typedef typename Container::hjstl_iterator iter;
	return _HJSTL_insert_iterator<Container>(x, iter(i));
}

template <class BidirectionalIterator, class T, class hjstl_reference,class Distance>
class _HJSTL_reverse_bidirectional_iterator {
	typedef _HJSTL_reverse_bidirectional_iterator<BidirectionalIterator, T, hjstl_reference,
		Distance> self;
protected:
	BidirectionalIterator current;
public:
	typedef hjstl_bidirectional_iterator_tag hjstl_iterator_category;
	typedef T                          hjstl_value_type;
	typedef Distance                   hjstl_difference_type;
	typedef T*                         hjstl_pointer;
	typedef hjstl_reference                  hjstl_reference;

	_HJSTL_reverse_bidirectional_iterator() {}
	explicit _HJSTL_reverse_bidirectional_iterator(BidirectionalIterator x): current(x) {}
	BidirectionalIterator base() const { return current; }
	hjstl_reference operator*() const {
		BidirectionalIterator tmp = current;
		return *--tmp;
	}
	hjstl_pointer operator->() const { return &(operator*()); }
	self& operator++() {
		--current;
		return *this;
	}
	self operator++(int) {
		self tmp = *this;
		--current;
		return tmp;
	}
	self& operator--() {
		++current;
		return *this;
	}
	self operator--(int) {
		self tmp = *this;
		++current;
		return tmp;
	}
};

template <class BidirectionalIterator, class T, class hjstl_reference,
class Distance>
	inline hjstl_bidirectional_iterator_tag
	hjstl_iterator_category(const _HJSTL_reverse_bidirectional_iterator<BidirectionalIterator,
	T,
	hjstl_reference, Distance>&) {
	return hjstl_bidirectional_iterator_tag();
}

template <class BidirectionalIterator, class T, class hjstl_reference,class Distance>
	inline T*
	hjstl_value_type(const _HJSTL_reverse_bidirectional_iterator<BidirectionalIterator, T,
	hjstl_reference, Distance>&) {
	return (T*)0;
}

template <class BidirectionalIterator, class T, class hjstl_reference,
class Distance>
	inline Distance*
	hjstl_distance_type(const _HJSTL_reverse_bidirectional_iterator<BidirectionalIterator, T,
	hjstl_reference, Distance>&) {
	return (Distance*)0;
}


template <class BidirectionalIterator, class T, class hjstl_reference,
class Distance>
	inline bool operator==(
	const _HJSTL_reverse_bidirectional_iterator<BidirectionalIterator, T, hjstl_reference,
	Distance>& x,
	const _HJSTL_reverse_bidirectional_iterator<BidirectionalIterator, T, hjstl_reference,
	Distance>& y) {
	return x.base() == y.base();
}

// This is the new version of reverse_iterator, as defined in the
//  draft C++ standard.  It relies on the iterator_traits template,
//  which in turn relies on partial specialization.  The class
//  reverse_bidirectional_iterator is no longer part of the draft
//  standard, but it is retained for backward compatibility.

template <class Iterator>
class _HJSTL_reverse_iterator
{
protected:
	Iterator current;
public:
	typedef typename _HJSTL_iterator_traits<Iterator>::hjstl_iterator_category
		hjstl_iterator_category;
	typedef typename _HJSTL_iterator_traits<Iterator>::hjstl_value_type
		hjstl_value_type;
	typedef typename _HJSTL_iterator_traits<Iterator>::hjstl_difference_type
		hjstl_difference_type;
	typedef typename _HJSTL_iterator_traits<Iterator>::hjstl_pointer
		hjstl_pointer;
	typedef typename _HJSTL_iterator_traits<Iterator>::hjstl_reference
		hjstl_reference;

	typedef Iterator iterator_type;
	typedef _HJSTL_reverse_iterator<Iterator> self;

public:
	_HJSTL_reverse_iterator() {}
	explicit _HJSTL_reverse_iterator(iterator_type x) : current(x) {}

	_HJSTL_reverse_iterator(const self& x) : current(x.current) {}
	template <class Iter>
	_HJSTL_reverse_iterator(const _HJSTL_reverse_iterator<Iter>& x) : current(x.current) {}

	iterator_type base() const { return current; }
	hjstl_reference operator*() const {
		Iterator tmp = current;
		return *--tmp;
	}
	hjstl_pointer operator->() const { return &(operator*()); }

	self& operator++() {
		--current;
		return *this;
	}
	self operator++(int) {
		self tmp = *this;
		--current;
		return tmp;
	}
	self& operator--() {
		++current;
		return *this;
	}
	self operator--(int) {
		self tmp = *this;
		++current;
		return tmp;
	}

	self operator+(hjstl_difference_type n) const {
		return self(current - n);
	}
	self& operator+=(hjstl_difference_type n) {
		current -= n;
		return *this;
	}
	self operator-(hjstl_difference_type n) const {
		return self(current + n);
	}
	self& operator-=(hjstl_difference_type n) {
		current += n;
		return *this;
	}
	hjstl_reference operator[](hjstl_difference_type n) const { return *(*this + n); }
};

template <class Iterator>
inline bool operator==(const _HJSTL_reverse_iterator<Iterator>& x,
	const _HJSTL_reverse_iterator<Iterator>& y) {
	return x.base() == y.base();
}

template <class Iterator>
inline bool operator<(const _HJSTL_reverse_iterator<Iterator>& x,
	const _HJSTL_reverse_iterator<Iterator>& y) {
	return y.base() < x.base();
}

template <class Iterator>
inline typename _HJSTL_reverse_iterator<Iterator>::hjstl_difference_type
operator-(const _HJSTL_reverse_iterator<Iterator>& x,
const _HJSTL_reverse_iterator<Iterator>& y) {
	return y.base() - x.base();
}

template <class Iterator>
inline typename _HJSTL_reverse_iterator<Iterator>::hjstl_difference_type
operator+(typename _HJSTL_reverse_iterator<Iterator>::hjstl_difference_type n,
const _HJSTL_reverse_iterator<Iterator>& x) {
	return _HJSTL_reverse_iterator<Iterator>(x.base() - n);
}


template <class T, class Distance = ptrdiff_t>
class _HJSTL_istream_iterator {
	friend bool
		operator==<>(const _HJSTL_istream_iterator<T, Distance>& x,
		const _HJSTL_istream_iterator<T, Distance>& y);
protected:
	istream* stream;
	T value;
	bool end_marker;
	void read() {
		end_marker = (*stream) ? true : false;
		if (end_marker) *stream >> value;
		end_marker = (*stream) ? true : false;
	}
public:
	typedef hjstl_input_iterator_tag hjstl_iterator_category;
	typedef T                  hjstl_value_type;
	typedef Distance           hjstl_difference_type;
	typedef const T*           hjstl_pointer;
	typedef const T&           hjstl_reference;

	_HJSTL_istream_iterator() : stream(&cin), end_marker(false) {}
	_HJSTL_istream_iterator(istream& s) : stream(&s) { read(); }
	hjstl_reference operator*() const { return value; }
	hjstl_pointer operator->() const { return &(operator*()); }
	_HJSTL_istream_iterator<T, Distance>& operator++() {
		read();
		return *this;
	}
	_HJSTL_istream_iterator<T, Distance> operator++(int)  {
		istream_iterator<T, Distance> tmp = *this;
		read();
		return tmp;
	}
};

template <class T, class Distance>
inline hjstl_input_iterator_tag
hjstl_iterator_category(const _HJSTL_istream_iterator<T, Distance>&) {
	return hjstl_input_iterator_tag();
}

template <class T, class Distance>
inline T* hjstl_value_type(const _HJSTL_istream_iterator<T, Distance>&) { return (T*)0; }

template <class T, class Distance>
inline Distance* distance_type(const _HJSTL_istream_iterator<T, Distance>&) {
	return (Distance*)0;
}
template <class T, class Distance>
inline bool operator==(const _HJSTL_istream_iterator<T, Distance>& x,
	const _HJSTL_istream_iterator<T, Distance>& y) {
	return x.stream == y.stream && x.end_marker == y.end_marker ||
		x.end_marker == false && y.end_marker == false;
}

template <class T>
class _HJSTL_ostream_iterator {
protected:
	ostream* stream;
	const char* string;
public:
	typedef hjstl_output_iterator_tag hjstl_iterator_category;
	typedef void                hjstl_value_type;
	typedef void                hjstl_difference_type;
	typedef void                hjstl_pointer;
	typedef void                hjstl_reference;

	_HJSTL_ostream_iterator(ostream& s) : stream(&s), string(0) {}
	_HJSTL_ostream_iterator(ostream& s, const char* c) : stream(&s), string(c)  {}
	_HJSTL_ostream_iterator<T>& operator=(const T& value) {
		*stream << value;
		if (string) *stream << string;
		return *this;
	}
	_HJSTL_ostream_iterator<T>& operator*() { return *this; }
	_HJSTL_ostream_iterator<T>& operator++() { return *this; }
	_HJSTL_ostream_iterator<T>& operator++(int) { return *this; }
};

template <class T>
inline hjstl_output_iterator_tag
hjstl_iterator_category(const _HJSTL_ostream_iterator<T>&) {
	return hjstl_output_iterator_tag();
}
#endif /* __HJ_STL_ITERATOR_H */

