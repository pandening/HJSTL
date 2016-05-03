#ifndef _HJSTL_DEQUE_H_
#define _HJSTL_DEQUE_H_
/*
  * Author:hujian
  * Time:2016/4/28
  * discription:this file is about deque structure.
  *
*/

#include "hjstl_alloc.h"
#include "hjstl_construct.h"
#include "hjstl_iterator.h"
#include "hjstl_uninitialized.h"

#define _HJSTL_DEQUE_PUBLIC_  public
#define _HJSTL_DEQUE_PRIVATE_ private 
#define _HJSTL_DEQUE_PROTECTED_ protected


//deque buffer size
inline size_t __HJSTL_deque_buf_size(size_t n, size_t sz){
	return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}


//the deque iterator.this is very complex.
template<class Type,class Ref,class Ptr,size_t BufSize/*you can change the size*/>
struct __HJSTL_deque_iterator{
    typedef 	__HJSTL_deque_iterator<Type, Ref&, Ptr*, BufSize>  iterator;
	typedef     __HJSTL_deque_iterator<Type, const Ref&, const Ptr*, BufSize> const_iterator;
	static size_t buffer_size(){
		//you want to set the buffer size 
		return __HJSTL_deque_buf_size(BufSize, sizeof(Type));
	}

	typedef hjstl_random_access_iterator_tag hjstl_iterator_category;
	typedef Type  hjstl_value_type;
	typedef Ptr   hjstl_pointer;
	typedef Ref   hjstl_reference;
	typedef size_t  size_type;
	typedef ptrdiff_t hjstl_difference_type;
	typedef Type** map_pointer;

	typedef __HJSTL_deque_iterator self;

	Type* cur; //the iterator's  buffer's current element.
	Type* first;//the iterator's buffer's head element
	Type* last;//the iterator's buffer's tail element

	map_pointer node;//this node pointer to the controller.

	//constructor
	__HJSTL_deque_iterator(Type* x,map_pointer y)
		:cur(x), first(*y), last(*y + buffer_size(), node(y)){}
	__HJSTL_deque_iterator()
		:cur(0), first(0), last(0), node(0){}
	__HJSTL_deque_iterator(const iterator& x)
		:cur(x.cur), first(x.first), last(x.last), node(x.node){}
	
	hjstl_reference operator*() const { return *cur; }

	hjstl_pointer  operator->() const { return &(operator*()); }

	hjstl_difference_type operator -(const self&x) const {
		return hjstl_difference_type(buffer_size())*(node - x.node - 1) +
			(cur - first) + (x.last - x.cur);
	}

	self& operator ++(){ //++iterator
		++cur;
		if (cur == last){
			set_node(node + 1);
			cur = first;
		}
		return *this;
	}

	self operator++(int) {//iterator++
		self tmp = *this;
		++*this;
		return tmp;
	}

	self& operator --(){//--iterator
		if (cur == first){
			set_node(node - 1);
			cur = last;
		}
		--cur;
		return *this;
	}

	self operator --(int){//iterator--
		self tmp = *this;
		--*this;
		return tmp;
	}

	self& operator +=(hjstl_difference_type n){//iterator += n
		hjstl_difference_type offset = n + (cur - first);
		//ok,aim index is at the same buffer,just pointer to..
		if (offset >= 0 && offset < hjstl_difference_type(buffer_size)){
			cur += n;
		}
		else{//difference buffer.so,we need to do more thing 
			hjstl_difference_type node_offset = offset>0/*forward*/ ?
				offset / hjstl_difference_type(buffer_size) :
				-hjstl_difference_type(-offset - 1) - 1;
			//goto the node.
			set_node(node + node_offset);
			//goto the cur we should.
			cur = first + (offset - node_offset*hjstl_difference_type(buffer_size()));
		}
		return *this;
	}

	//ok,we have implemented the +=,then the + is so easy to implement
	self operator +(hjstl_difference_type n) const {
		self tmp = *this;
		return tmp += n;
	}

	//yeah,do you know we can use add to implement minus..?
	self & operator -=(hjstl_difference_type n){
		return *this += -n;
	}

	//:>
	self operator -(hjstl_difference_type n) const {
		self tmp = *this;
		return tmp -= n;
	}

	//random put/get
	hjstl_reference operator[](hjstl_difference_type n) const
	{
		return *(*this + n);
	}

	bool operator ==(const self& x) const { return cur == x.cur; }
	bool operator !=(const self& x) const { return cur != x.cur; }
	bool operator<(const self&x)const {
		return (node == x.node) ? (cur < x.cur) : (node < x.node);
	}

	//set node.goto..
	void set_node(map_pointer new_node)
	{
		node = new_node;
		first = *new_node;
		last = first + hjstl_difference_type(buffer_size());
	}
};

template<class Type,class Ref,class Ptr,size_t BufSz>
inline hjstl_random_access_iterator_tag
hjstl_iterator_category(const __HJSTL_deque_iterator<Type, Ref, Ptr, BufSz>&){
	return hjstl_random_access_iterator_tag();
}

template<class Type,class Ref,class Ptr,size_t BufSz>
inline Type* hjstl_value_type(const __HJSTL_deque_iterator<Type, Ref, Ptr,BufSz>&){
	return 0;
}

template<class Type, class Ref, class Ptr,size_t BufSz>
inline ptrdiff_t* hjstl_distance_type(const __HJSTL_deque_iterator<Type, Ref, Ptr, BufSz>&){
	return 0;
}

//the follow codes is about the deque.
//you can set the block's size,the default block size is 512 bytes
template<class Type,class Alloc=HJSTL_Alloc::HJSTL_Allocate_default,size_t BufSize=0>
class _HJSTL_deque{
	_HJSTL_DEQUE_PUBLIC_:
	typedef Type   value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t  size_type;
	typedef ptrdiff_t difference_type;

	//the deque's iterator.
	typedef __HJSTL_deque_iterator<Type, Type&, Type*, BufSize> iterator;
	typedef __HJSTL_deque_iterator<Type, const Type&, const Type*, BufSize> const_iterator;

_HJSTL_DEQUE_PROTECTED_:
	//pointer of pointer of Type.
	typedef pointer* map_pointer;
	//the data allocator.
	typedef _HJSTL_simple_alloc<value_type, Alloc> data_allocator;
	//map node allocator
	typedef _HJSTL_simple_alloc<pointer, Alloc> map_allocator;
	//get the buffer size
	static size_type buffer_size(){
		return __HJSTL_deque_buf_size(BufSize, sizeof(value_type));
	}

	//the initialze map size(the nodes of the map in the beginning)
	static size_type initial_map_size(){
		return 8;//you can change here to adjust your map nodes.
	}

	//the data member.
	iterator start;//the first node of map.
	iterator finish;//the last node of map

	//the map.this is an array.stored the node pointer.
	//and the node is pointer too.
	map_pointer map;

	//the map size
	size_type  map_size;

_HJSTL_DEQUE_PUBLIC_://get member.
	iterator begin(){ return start; }
	iterator end(){ return finish; }
	const iterator begin() const { return start; }
	const iterator end() const { return finish; }

	reference operator[](size_type n){
		return start[difference_type(n)];
	}
	const reference operator[](size_type n) const{
		return start[difference_type(n)];
	}

	reference front(){
		return *start;//the first node's first element.
	}

	reference back(){
		iterator tmp = finish;
		//the finish is empry.
		--tmp;
		return *tmp;
	}

	const reference front() const{
		return *start;//the first node's first element.
	}

	const reference back() const{
		const_iterator tmp = finish;
		//the finish is empry.
		--tmp;
		return *tmp;
	}
	//the size of this eque
    //NOTICE:the operator '-' is not so simple.you need to know that.
	size_type size()const{ return finish - start; }
	//-1 is max number...
	size_type max_size()const { return size_type(-1); }
	//is empty?
	bool empty(){ return start == finish; }

_HJSTL_DEQUE_PUBLIC_://the follow is constructor
	_HJSTL_deque() : start(), finish(), map(0){
		//just set up an default deque for user.
		create_map_and_nodes(0);
	}
	_HJSTL_deque(const _HJSTL_deque&x)
		:start(), finish, map(0), map_size(0)
	{
		create_map_and_nodes(x.size());
		try{
			uninitialized_copy(x.begin(), x.end(), start);
		}
		catch (...){
			//error
			destroy_map_and_nodes();
		}
	}

	_HJSTL_deque(size_type n, const value_type& value)
		:start(), finish(), map(0), map_size(0)
	{
		fill_initialze(n, value);
	}

	_HJSTL_deque(int n, const value_type& value)
		:start(), finish(), map(0), map_size(0)
	{
		fill_initialze(n, value);
	}
	
	_HJSTL_deque(long n, const value_type& value)
		:start(), finish(), map(0), map_size(0)
	{
		fill_initialze(n, value);
	}

	explicit _HJSTL_deque(size_type n)
		:start(), finish(), map(0), map_size(0)
	{
		fill_initialze(n, value_type());
	}
	template<class InputIterator>
	_HJSTL_deque(InputIterator first, InputIterator last)
		: start(), finish(), map(0), map_size(0)
	{
		range_initialze(first, last, hjstl_iterator_category(first));
	}

	_HJSTL_deque(const value_type* first, const value_type* last)
		:start(), finish(), map(0), map_size(0)
	{
		create_map_and_nodes(last-first);
		try{
			uninitialized_copy(first, last, start);
		}
		catch (...){
			destroy_map_and_nodes();
		}
	}

	_HJSTL_deque(const_iterator first, const_iterator last)
		:start(), finish(), map(0), map_size(0)
	{
		create_map_and_nodes(last - first);
		try{
			uninitialized_copy(first, last, start);
		}
		catch (...){
			destroy_map_and_nodes();
		}
	}

	//deconstructor
	~_HJSTL_deque(){
		destroy(start, finish);
		destroy_map_and_nodes();
	}
	//function.
	_HJSTL_deque& operator =(const _HJSTL_deque& x)
	{
		const size_type len = size();
		if (&x != this){//difference deque
			earse(copy(x.begin(), x.end(), start), finish);
		}
		else{
			const_iterator mid = x.begin() + difference_type(len);
			copy(x.begin(), mid, start);
			insert(finish, mid, x.end());
		}
		return *this;
	}

	//erase an iterator
	iterator erase(iterator pos)
	{
		iterator next = pos;
		++next;
		difference_type index = pos - start; //the length of before remove element.
		if (index < (size() >> 1/*just like size()/2*/)){//less 
			copy_backward(start, pos, next);
			pop_front();//delete the pos's value
		}
		else{//more.
			copy(next, finish, pos);
			pop_back();//delete the pos'value
		}
		//return the pos's value
		return start + index;
	}

	//erase the range [first,last)
	iterator erase(iterator first, iterator last)
	{
		//if you want to clear the deque.just use clear
		if (first == start&&last == finish){
			clear();
			return finish;
		}
		else{
			difference_type len = last - first;
			difference_type elements_before = first - start;
			if (elements_before < (size() - len) / 2)//the before elements less
			{
				copy_backward(start, first, last);
				//the new start
				iterator new_start = start + len;
				//destructor the elemenst we do not want to left
				destroy(start, new_start);
				//back the memory to the memeory pool
				for (map_pointer cur = start.node; cur < new_start.node; ++cur){
					data_allocator::deallocate(*cur, buffer_size());
				}
				//set the start
				start = new_start;
			}
			else{//the length of range [first,last) ->before>after
				copy(last, finish, first);
				iterator new_finish = finish - len;
				destroy(new_finish, finish);
				for (map_pointer cur = new_finish.node + 1; cur <= finish.node; ++cur){
					data_allocator::deallocate(*cur, buffer_size());
				}
				//set the new finish
				finish = new_finish;
			}
			return start + elements_before;
		}
	}

	//insert an item into the deque.
	//this is the insert aux
	iterator insert_aux(iterator pos, const value_type& value)
	{
		difference_type index = pos - start;
		value_type copy_v = value;
		if (index < size() / 2){//before<after
			//insert into the front values(front()) 
			push_back(front());
			//move the elements.
			iterator front_1 = start;
			++front_1;
			iterator front_2 = front_1;
			++front_2;
			//re get-the pos's iterator
			pos = start + index;
			iterator pos_1 = pos;
			++pos_1;
			//copy data.
			copy(front_2, pos, front_1);
		}
		else{//before>=after
			push_back(back());
			iterator back_1 = finish;
			--back_1;
			iterator back_2 = back_1;
			--back_2;
			pos = start + index;
			copy(pos, back_2, back_1);
		}
		//assignment.
		*pos = copy_v;
		return pos;
	}

	//this is the insert 
	iterator insert(iterator position, const value_type& value)
	{
		//front or back?
		if (position.cur == start.cur){
			push_front(value);
			return start;
		}
		else if (position.cur == finish.cur){
			push_back(value);
			iterator tmp = finish;
			--tmp;
			return tmp;
		}
		else{
			return insert_aux(position, value);
		}
	}

	//insert
	iterator insert(iterator position){
		//empty initialze
		return insert(position, value_type());
	}
	//realloc the map
	void reallocate_map(size_type nodes_to_add, bool add_at_front/*opt*/)
	{
		size_type old_num_nodes = finish - start + 1;
		size_type new_num_nodes = old_num_nodes + nodes_to_add;
		map_pointer new_nstart;
		if (map_size > 2 * new_num_nodes){
			new_nstart = map + (map_size - new_num_nodes) / 2 +
				(add_at_front ? nodes_to_add : 0);
			if (new_nstart < start.node){
				copy(start.node, finish.node + 1, new_nstart);
			}
			else{
				copy_backward(start.node, finish.node + 1,new_nstart+ old_num_nodes);
			}
		}
		else{
			size_type new_map_size = map_size + (map_size > nodes_to_add ? map_size : nodes_to_add) + 1;
			map_pointer new_map = map_allocator::allocate(new_map_size);
			new_nstart = new_map + (new_map_size - new_num_nodes) / 2 +
				(add_at_front ? nodes_to_add : 0);
			copy(start.node, finish.node + 1, new_nstart);
			map_allocator::deallocate(map, map_size);
			//set the new map.attr
			map = new_map;
			map_size = new_map_size;
		}
		start.set_node(new_nstart);
		finish.set_node(new_nstart + old_num_nodes + 1);
	}

	//reserve map at back
	//default add 1 node
	void reserver_map_at_back(size_type nodes_to_add = 1)
	{
		if (nodes_to_add + 1 > map_size - (finish.node - map)){
			reallocate_map(nodes_to_add, false);
		}
	}

	void reserver_map_at_front(size_type nodes_to_add = 1)
	{
		if (nodes_to_add > start.node - map){
			reallocate_map(nodes_to_add, true);
		}
	}

	//just swap
	void swap(_HJSTL_deque& x)
	{
		std::swap(start, x.start);
		std::swap(finish, x.finish);
		std::swap(map, x.map);
		std::swap(map_size, x.map_size);
	}

	//push_back
	void push_back(const value_type& value)
	{
		if (finish.cur != finish.last - 1){
			construct(finish.cur, value);
			++finish.cur;
		}
		else{//i let the another function do this
			push_back_aux(value);
		}
	}

	//push_back_aux
	void push_back_aux(const value_type& value)
	{
		value_type copy_v = value;
		reserver_map_at_back();
		//alloc an new node
		*(finish.node + 1) = allocate_node();
		try{
			construct(finish.cur, copy_v);
			finish.set_node(finish.node + 1);
			finish.cur = finish.first;
		}
		catch (...){
			//if error,just deallocate the alloc-ed memory.
			deallocate_node(*(finish.node + 1));
		}
	}

	//push_front_aux
	void push_front_aux(const value_type& value)
	{
		value_type copy_v = value;
		reserver_map_at_front();
		//allocate an new node 
		*(start.node-1)=allocate_node();
		try{
			start.set_node(start.node - 1);
			start.cur = start.last - 1;
			construct(start.cur, copy_v);
		}
		catch (...){
			//error
			start.set_node(start.node + 1);
			start.cur = start.first;
			deallocate_node(*(start.node - 1));
		}
	}
	//push_front
	void push_front(const value_type& value)
	{
		if (start.cur != start.first){
			construct(start.cur, value);
			--start.cur;
		}
		else{
			push_front_aux(value);
		}
	}

	//pop_front_aux
	//edge...
	void pop_front_aux()
	{
		destroy(start.cur);
		deallocate_node(start.first);
		start.set_node(start.node + 1);
		start.cur = start.first;
	}

	//pop_back_aux
	//edge
	void pop_back_aux()
	{
		deallocate_node(finish.first);
		finish.set_node(finish.node - 1);
		finish.cur = finish.last - 1;
		destroy(finish.cur);
	}
	//pop_back
	void pop_back()
	{
		if (finish.cur != finish.first){
			--finish.cur;
			destroy(finish.cur);
		}
		else{
			pop_back_aux();
		}
	}

	//pop_front
	void pop_front()
	{
		if (start.cur != start.last - 1){
			destroy(start.cur);
			++start.cur;
		}
		else
		{
			pop_front_aux();
		}
	}

_HJSTL_DEQUE_PROTECTED_://some useful function
	//allocate an node
	pointer allocate_node(){
		return data_allocator::allocate(buffer_size());
	}
	//deallocate an node
	void deallocate_node(pointer ptr){
		data_allocator::deallocate(ptr, buffer_size());
	}

	//set up a deque with num_elements.
	void create_map_and_nodes(size_type num_elements)
	{
		//the needed nodes
		size_type num_nodes = num_elements / buffer_size() + 1;
		//get the map size
		map_size = initial_map_size()> (num_nodes+2) ? initial_map_size() : num_nodes+2;
		//alloc map_size's nodes for map.
		map = map_allocator::allocate(map_size);
		//in the mid.
		map_pointer nstart, nfinish;
		nstart = map + (map_size - num_nodes) / 2;
		nfinish = nstart + num_nodes - 1;
		map_pointer cur;
		try{
			//alloc for each node
			for (cur = nstart; cur<=nfinish; cur++){
				*cur = allocate_node();
			}
		}
		catch (...){
			//deallocate.
			for (map_pointer n = nstart; n < cur; n++){
				deallocate_node(*n);
			}
			map_allocator::deallocate(map, map_size);
		}
		//set the start and finish
		start.set_node(nstart);
		finish.set_node(nfinish);
		start.cur = start.first;
		//make sure you can understand the follow code.
		finish.cur = finish.first + num_elements%buffer_size();
	}

	//destroy map and nodes
	void destroy_map_and_nodes(){
		for (map_pointer cur = start.node; cur <= finish.node; ++cur){
			deallocate_node(*cur);
		}
		map_allocator::deallocate(map, map_size);
	}
	//fill initialze
	void fill_initialze(size_type n, const value_type& value)
	{
		create_map_and_nodes(n);
		map_pointer cur;
		try{
			for (cur = start.node; cur < finish.node; ++cur){
				uninitialized_fill(*cur, *cur + buffer_size(), value);
			}
			//finish node initialze
			uninitialized_fill(finish.first, finish.cur, value);
		}
		catch (...){
			//if not succeed,destory the old..
			for (map_pointer n = start.node; n < cur; ++n){
				destroy(*n, *n + buffer_size());
			}
			destroy_map_and_nodes();
		}
	}

	//range initialze
	template<class InputIterator>
	void range_initialze(InputIterator first, InputIterator last, hjstl_input_iterator_tag)
	{
		create_map_and_nodes(0);
		while (first != last){
			push_back(*first++);
		}
	}

	template<class ForwardIterator>
	void range_initialze(ForwardIterator first, ForwardIterator last, hjstl_forward_iterator_tag)
	{
		size_type n = 0;
		hjstl_distance(first, last, n);
		create_map_and_nodes(n);
		try{
			uninitialized_copy(first, last, start);
		}
		catch (...){
			destroy_map_and_nodes();
		}
	}

	_HJSTL_DEQUE_PUBLIC_:
	//clear this deque
	//we need to left one buffer for this empty deque.
	//
	void clear()
	{
		for (map_pointer node = start.node + 1; node < finish.node; ++node){
			destroy(*node, *node + buffer_size());
			data_allocator::deallocate(*node, buffer_size());
		}
		//if we have at least 2 buffer left,just left the head buffer
		if (start.node != finish.node){
			destroy(start.cur, start.last);
			destroy(finish.first, finish.cur);
			data_allocator::deallocate(finish.first, buffer_size());
		}
		//else,just one buffer left now.
		//NOTICE:do not back the memory to memory pool.
		//this is the must-left buffer in an empty deue.
		else{
			destroy(start.cur, finish.cur);
		}
		//set the finish
		finish = start;//means this is an empty deque,you can look up the
		//function empty() to check the algorithm
	}
};//end of hjstl deque
///<2016/4/28 hujian deque>
#endif //end of _HJSTL_DEQUE_H_