#ifndef  _HJSTL_LIST_H_
#define  _HJSTL_LIST_H_
/*
* Author:hujian
* Time:2016/4/18
* discription:this file is about list of hjstl
*
*/

#include "hjstl_alloc.h"
#include "hjstl_iterator.h"
#include "hjstl_construct.h"
#include "hjstl_uninitialized.h"

#define _HJSTL_LIST_PUBLIC_  public
#define _HJSTL_LIST_PRIVATE_ private 
#define _HJSTL_LIST_PROTECTED_ protected


//this is the list node structure
template<class Type>
struct __hjstl_list_node{
	typedef void* void_pointer;//this is the pointer type.
	void_pointer  next;//the next pointer
	void_pointer  prev;//the prev pointer
	Type          data;//this is the node's data
};

//so,this is the list iterator,and the list's iterator is 
//bidirectional type's iterator.
template<class Type,class Reference,class Pointer>
struct __hjstl_list_iterator{
	//some typedefs
	typedef __hjstl_list_iterator<Type, Type&, Type*>  iterator;
	typedef __hjstl_list_iterator<Type, const Type&, const Type*> const_iterator;
	typedef __hjstl_list_iterator<Type, Reference, Pointer> self;

	typedef hjstl_bidirectional_iterator_tag hjstl_iterator_category;
	typedef Type    hjstl_value_type;
	typedef Pointer hjstl_pointer;
	typedef Reference hjstl_reference;
	typedef __hjstl_list_node<Type>* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t  hjstl_difference_type;

	//this is the pointer to pointer to the node.
	//and the node will store the infomation of node.
	link_type  hjstl_list_node;

	//the follow def is construct
	__hjstl_list_iterator(link_type x) :hjstl_list_node(x){}
	__hjstl_list_iterator(){}
	__hjstl_list_iterator(const iterator& x) :hjstl_list_node(x.hjstl_list_node){}

	//overload....
	bool operator==(const self&x) const { return hjstl_list_node == x.hjstl_list_node; }
	bool operator!=(const self&x) const { return hjstl_list_node != x.hjstl_list_node; }

	//get the iterator's value.
	hjstl_reference operator*()const { return (*hjstl_list_node).data; }
	hjstl_pointer   operator->()const{ return &(operator*()); }

	//increase the iterator,get the next iterator
	//++iterator
	self& operator++(){
		hjstl_list_node = (link_type)((*hjstl_list_node).next);
		return *this;
	}
	//iterator++
	self operator++(int){
		self tmp = *this;
		++(*this);
		return tmp;
	}

	//deincrease the iterator,and get the prev iterator
	//--iterator
	self& operator--(){
		hjstl_list_node = (link_type)((*hjstl_list_node).prev);
		return *this;
	}

	//iterator--
	self operator--(int){
		self tmp = *this;
		--(*this);
		return tmp;
	}

};//end of list iterator


template<class Type,class Ref,class Ptr>
inline hjstl_bidirectional_iterator_tag
hjstl_iterator_category(const __hjstl_list_iterator<Type, Ref, Ptr>&){
	return hjstl_bidirectional_iterator_tag();
}

template<class Type,class Ref,class Ptr>
inline Type* 
hjstl_value_type(const __hjstl_list_iterator<Type, Ref, Ptr>&){
	return 0;
}

template<class Type,class Ref,class Ptr>
inline ptrdiff_t*
hjstl_distance_type(const __hjstl_list_iterator<Type, Ref, Ptr>&){
	return 0;
}


//this is the list class
//the default allocate is the memory pool.
template<class Type,class Alloc=HJSTL_Alloc::Alloc_second>
class _HJSTL_list{
//_HJSTL_LIST_PROTECTED_:
	__HJSTL_PUBLIC_:
	typedef void* void_pointer;
	typedef __hjstl_list_node<Type> list_node;
	//the alloc.....
	typedef _HJSTL_simple_alloc<list_node, Alloc> hjstl_list_node_allocator;

__HJSTL_PUBLIC_:
	typedef Type   value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef list_node* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;


	//so,this node will manage all list.
	//because the list is double list,so,just one pointer needed.
	link_type this_node;
	////test
	void* test_ptr;
	//the iterator of this list
	typedef __hjstl_list_iterator<Type, Type&, Type*>     iterator;
	typedef __hjstl_list_iterator<Type, const Type&, const Type*>   const_iterator;

//_HJSTL_LIST_PROTECTED_:
	_HJSTL_LIST_PUBLIC_:
	//alloc an node,and return the node
	link_type get_node(){
		return hjstl_list_node_allocator::allocate();
	}
	//free an node
	void     put_node(link_type p){
		hjstl_list_node_allocator::deallocate(p);
	}

	//create an new node,and with value
	link_type create_node(const Type& v){
		link_type p = get_node();
		try{
			construct(&p->data, v);
		}
		catch (...){
			//if error,free the node
			put_node(p);
		}
		return p;
	}

	//destroy an node
	void destroy_node(link_type p){
		destroy(&p->data);
		put_node(p);
	}

	//the initialze function,just set up the double circle list
	void _empty_initialze(){
		//circle and double director
		this_node = get_node();
		this_node->next = this_node;
		this_node->prev = this_node;
	}

	//create n node,and initialze with value
	void _fill_initialze(size_type n,const Type& value){
		//set up the list
		_empty_initialze();
		try{
			//insert node,and init the value
			insert(begin(), n, value);
		}
		catch (...){
			clear();
			put_node(this_node);
		}
	}

	//range initialze
	void range_initialze(const Type* first, const Type* last){
		//set up
		_empty_initialze();
		try{
			insert(begin(), first, last);
		}
		catch (...){
			clear();
			destroy_node(this_node);
		}
	}

	//set up the list
	_HJSTL_list() { _empty_initialze(); }

	_HJSTL_list(size_type n, const Type& value){ _fill_initialze(n, value); }
	_HJSTL_list(int n, const Type&value){ _fill_initialze(n, value); }
	_HJSTL_list(long n, const Type& value){ _fill_initialze(n, value); }
	_HJSTL_list(size_type n){ _fill_initialze(n, Type()); }
	_HJSTL_list(const Type* first, const Type* last){range_initialze(first, last);}
	_HJSTL_list(const _HJSTL_list<Type, Alloc>& x){range_initialze(x.begin(), x.end());}


	//the list's transfer.very magic function but so easy to write
	//move the [first,last) to before position
	void transfer(iterator position, iterator first, iterator last)
	{
		if (position != last)
		{
			(*(link_type((*last.hjstl_list_node).prev))).next = position.hjstl_list_node;
			(*(link_type((*first.hjstl_list_node).prev))).next = last.hjstl_list_node;
			(*(link_type((*position.hjstl_list_node).prev))).next = first.hjstl_list_node;

			link_type tmp = link_type((*position.hjstl_list_node).prev);
			(*position.hjstl_list_node).prev = (*last.hjstl_list_node).prev;
			(*last.hjstl_list_node).prev = (*first.hjstl_list_node).prev;
			(*first.hjstl_list_node).prev = tmp;
		}
	}

	//splice
	//different list
	void splice(iterator position, _HJSTL_list& x)
	{
		if (!x.empty()){
			transfer(position, x.begin(), x.end());
		}
	}
	//same list
	void splice(iterator position, _HJSTL_list&, iterator i)
	{
		iterator j = i;
		++j;
		if (position == i || position == j){
			return;
		}
		transfer(position, i, j);
	}

	void splice(iterator position, _HJSTL_list&, iterator first, iterator last)
	{
		if (first != last){
			transfer(position, first, last);
		}
	}

	//remove the value.
	void remove(const Type& value)
	{
		iterator first = begin();
		iterator last = end();
		while (first != last){
			iterator next = first;
			++next;//move to next,no influence the list operator<traversal>
			if (*first == value) erase(first);
			first = next;
		}
	}

	//unique
	//this is about algorithm
	void unique()
	{
		iterator first = begin();
		iterator last = end();
		if (first == last) return;
		iterator next = first;
		while (++next != last){
			if (*first == *next){
				erase(next);
			}
			else{
				first = next;
			}
			next = first;
		}
	}

	//merge,you need to ensure the two list has sorted
	void merge(_HJSTL_list& x)
	{
		iterator first1 = begin();
		iterator last1 = end();

		iterator first2 = x.begin();
		iterator last2 = x.end();
		while (first1 != last1&&first2 != last2)
		{
			if (*first2 < *first1){
				iterator next = first2;
				//only first2 will be moved to---> ...[first2][first1]...
				transfer(first1, first2, ++next);
				first2 = next;
			}
			else{
				++first1;
			}
			if (first2 != last2){
				//more data
				transfer(last1, first2, last2);
			}
		}
	}

	//reserve the list
	//this is magic...
	void reserve()
	{
		//judge if this is a empty list,or just one elements
		if (this_node->next == this_node ||
			link_type(this_node->next)->next == this_node){
			return;
		}
		iterator first = begin();
		++first;
		while (first != end()){
			iterator old = first;
			++first;
			//only one elements will be moved
			transfer(begin(), old, first);
		}
	}

	//just fake.
	void sort()
	{
		if (this_node->next == this_node ||
			((link_type)(this_node->next))->next == this_node){
			return;
		}
		//sort
		iterator i = begin(),j;
		for (; i != end(); i++){
			iterator tt = i;
			for (j = tt++; j != end(); j++){
				if (*i>=*j){
					Type tmp = *i;
					*i = *j;
					*j = tmp;
				}
			}
		}
	}

	_HJSTL_LIST_PRIVATE_:
	//sort this list
	//quick sort
	//do not use this function
	void sort(bool)
	{
		//judge wether this list only one element or empty
		if (this_node->next == this_node ||
			((link_type)(this_node->next))->next == this_node){
			return;
		}
		cout << "i am ok.." << endl;
		_HJSTL_list<Type, Alloc> carry;
		_HJSTL_list<Type, Alloc> counter[64];
		int fill = 0;
		while (!empty())
		{
			carry.splice(carry.begin(), *this, begin());
			int i=0;
			while (i < fill&&!counter[i].empty()){
				counter[i].merge(carry);
				carry.swap(counter[i++]);
			}
			carry.swap(counter[i]);
			if (i == fill) ++fill;
		}
		for (int i = 1; i < fill; ++i){
			counter[i].merge(counter[i - 1]);
		}
		swap(counter[fill - 1]);
	}

	__HJSTL_PUBLIC_:

	//get the begin iterator
	iterator begin(){
		//cause the this_node is the flag of this list
		//so,the this_node is empty forever
		return (link_type)((*this_node).next);
	}

	//get the end iterator
	iterator end(){
		//and this is empty.
		return ((this_node));
	}

	//is empty?
	bool empty(){
		return this_node->next == this_node;
	}

	//the size of this list
	size_type size(){
		size_type result = 0;
		hjstl_distance(begin(), end(), result);
		return result;
	}

	//the max size
	size_type max_size() const{
		return size_type(-1);
	}

	//get the front's value
	reference front(){
		return *begin();
	}

	//get the back
	reference back(){
		return *(--end());
	}

	//swap
	void swap( _HJSTL_list<Type, Alloc>&x ){
		std::swap(this_node, x.this_node);
	}

	//insert a node,before position...
	iterator insert(iterator position, const Type& v)
	{
		/*
		  before insert
		  ....[]-[]-[position]-[]-[]-[].....
		
		  running
		  ....[]-[]-[position]-[]-[]-[]......
		            -[tmp]-
          after insert
		  ....[]-[]-[tmp]-[position]-[]-[]-[]......
		*/
		//this is the node will insert
		link_type tmp = create_node(v);
		tmp->next = position.hjstl_list_node;
		tmp->prev = position.hjstl_list_node->prev;
		((link_type)(position.hjstl_list_node->prev))->next = tmp;
		position.hjstl_list_node->prev = tmp;
		return tmp;
	}

	//insert null before position
	iterator insert(iterator position){
		return insert(position, Type());
	}
	///push....
	void push_front(const Type& v){ insert(begin(), v); }
	void push_back(const Type& v){ insert(end(), v); }

	//pop...
	void pop_front(){erase(begin());}
	void pop_back(){
		iterator tmp = end();
		erase(--tmp);
	}
	template<class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last)
	{
		for (; first != last; ++first){
			insert(position, *first);
		}
	}
	void insert(iterator position, const Type* first, const Type* last)
	{
		for (; first != last; ++first){
			insert(position, *first);
		}
	}

	void insert(iterator position, const_iterator first, const_iterator last)
	{
		for (; first != last; ++first){
			insert(position, *first);
		}
	}

	void insert(iterator pos, size_type n, const Type& x)
	{
		for (; n > 0; --n){
			insert(pos, x);
		}
	}
	void insert(iterator pos, int n, const Type& x)
	{
		insert(pos, (size_type)n, x);
	}
	void insert(iterator pos, long n, const Type& x)
	{
		insert(pos, (size_type)n, x);
	}

	//erase
	iterator erase(iterator position)
	{
		/*
		    before erase
			...[]-[position]-[]...
			running
			...[]-...-[]...
			after
			...[]-[]...
		*/
		link_type next_node = link_type(position.hjstl_list_node->next);
		link_type prev_node = link_type(position.hjstl_list_node->prev);

		prev_node->next = next_node;
		next_node->prev = prev_node;
		//destroy this node
		destroy_node(position.hjstl_list_node);
		return iterator(position.hjstl_list_node);
	}


	//another erase function
	//[first,last)
	iterator erase(iterator first, iterator last)
	{
		//erase range...iterators
		while (first != last){
			erase(first++);
		}
		return last;
	}

	//resize
	void resize(size_type new_szie, const Type& v)
	{
		iterator it = begin();
		size_type len = 0;
		for (; it != end() && len < new_szie; i++, len++);
		//more space left
		if (len == new_szie){
			erase(it, end());
		}
		else{//no so many nodes.
			insert(end(), new_szie - len, v);
		}
	}
	//resize and no initialze
	void resize(size_type new_size){ resize(new_size, Type()); }



	//clear the list
	void clear()
	{
		//this_node is the flag,and it's null
		link_type curr = (link_type)this_node->next;
		while (curr != this_node){
			link_type tmp = curr;
			curr = (link_type)curr->next;
			destroy_node(tmp);
		}
		//reset the list
		this_node->next = this_node;
		this_node->prev = this_node;
	}

	//operator =
	_HJSTL_list<Type, Alloc>& operator=(const _HJSTL_list<Type, Alloc>& x)
	{
		//if same obj,just return
		if (this != &x){
			iterator first1 = begin();
			iterator last1 = end();

			const_iterator first2 =(const_iterator)x.begin();
			const_iterator last2 = (const_iterator)x.end();

			while (first1 != last1&&first2 != last2){
				*first1++ = *first2++;
			}
			//check
			if (first2 == last2){
				//more....
				erase(first1, last1);
			}
			else{//no so many nodes,so insert some empty nodes
				insert(last1, first2, last2);
			}
		}
		return *this;
	}
	//deconstruct
	~_HJSTL_list()
	{
		clear();
		put_node(this_node);
	}
};//end of hjstl list


template<class Type,class Alloc>
inline void swap(_HJSTL_list<Type, Alloc>&x, _HJSTL_list<Type, Alloc>&y){
	x.swap(y);
}
#endif  //end of _HJSTL_LIST_H_