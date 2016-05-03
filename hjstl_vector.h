#ifndef _HJ_STL_VECTOR_H_
#define _HJ_STL_VECTOR_H_
/*
* Author:hujian
* Time:2016/4/12
* discription:this file is about vector.
*
* to much bugs.
*/

#include "hjstl_alloc.h"
#include "hjstl_iterator.h"
#include "hjstl_construct.h"
#include "hjstl_uninitialized.h"

#define _HJSTL_VECTOR_PUBLIC_  public
#define _HJSTL_VECTOR_PRIVATE_ private 
#define _HJSTL_VECTOR_PROTECTED_ protected


//i will use the second allocate.you can use yourself allocate.
template<class Type,class Alloc=HJSTL_Alloc::HJSTL_Allocate_default>
class _HJSTL_vector{
_HJSTL_VECTOR_PUBLIC_://the follow typedefs is for traits.
	typedef Type   hjstl_value_type;
	typedef hjstl_value_type* hjstl_pointer;
	typedef const hjstl_value_type* hjstl_const_pointer;
	typedef hjstl_value_type* hjstl_iterator;
	typedef const hjstl_value_type* hjstl_const_iterator;
	typedef hjstl_value_type& hjstl_reference;
	typedef const hjstl_value_type& hjstl_const_reference;
	typedef size_t   hjstl_size_type;
	typedef ptrdiff_t hjstl_difference_type;


	//the vector will use the follow allocate to alloc
	typedef HJSTL_Alloc::HJSTL_Allocate_default vector_alloc;

	//the range of vector.
	hjstl_iterator start;
	hjstl_iterator finish;
	hjstl_iterator end_of_storage;

_HJSTL_VECTOR_PROTECTED_:
	//insert aux.
	void insert_aux(hjstl_iterator position, const Type& value);
	//allocate and fill
	hjstl_iterator allocate_and_fill(hjstl_size_type size, const Type& value)
	{
		//use second level allocate to alloc memory.
		hjstl_iterator result = vector_alloc::hjstl_allocate(size);
		try{
			hjstl_uninitialized_fill_n(result, size, value);
			return result;
		}
		catch(...){//if error,deallocate
			vector_alloc::hjstl_deallocate(result, size);
		}
	}
	//allocate and copy
	hjstl_iterator allocate_and_copy(hjstl_size_type size, 
		hjstl_const_iterator first, hjstl_const_iterator last)
	{
		hjstl_iterator result = vector_alloc::hjstl_allocate(size);
		try{
			hjstl_uninitialized_copy(first, last, result);
			return result;
		}
		catch (...){
			vector_alloc::hjstl_deallocate(result, size);
		}
	}

	//range initialze
	template<class ForwardIterator>
	void range_initialze(ForwardIterator first, ForwardIterator last, hjstl_forward_iterator_tag)
	{
		hjstl_size_type size = 0;
		hjstl_distance(first, last, size);
		start = allocate_and_copy(size, first, last);
		finish = start + size;
		end_of_storage = finish;
	}
_HJSTL_VECTOR_PUBLIC_:
	//deallocate.
	void deallocate(){
		if (start){
			vector_alloc::hjstl_deallocate(start, end_of_storage - start);
		}
	}

	//initialize the vector
	void fill_initialze(hjstl_size_type size, const Type& value)
	{
		start = allocate_and_fill(size, value);
		finish = start + size;
		end_of_storage = finish;//this is the limit we can reach now.
	}

	//////about iterztor operation//////
	hjstl_iterator begin(){ return start; }
	//hjstl_const_iterator begin(){ return start; }

	hjstl_iterator end(){ return finish; }
	//hjstl_const_iterator end(){ return finish; }

	//get the elements
	hjstl_reference front(){ return *begin(); }
	//hjstl_const_reference front() const{ return *begin(); }

	hjstl_reference  back(){ return *(end() - 1); }
	//hjstl_const_reference back() const{ return *(end() - 1); }


	//get the size.
	hjstl_size_type size(){ return hjstl_size_type(end() -begin()); }
	//the max size
	hjstl_size_type max_size(){ return hjstl_size_type(-1) / sizeof(Type); }
	//capcity of this vector
	hjstl_size_type capcity(){ return hjstl_size_type(end_of_storage - begin()); }
	//whether this vector is empty
	bool empty(){ return begin() == end(); }

	//overload implements
	hjstl_reference operator[](hjstl_size_type index){
		return *(begin() + index);
	}

	hjstl_const_reference operator[](hjstl_size_type index) const{
		return *(begin() + index);
	}

	///////the constructor///////////////
	_HJSTL_vector() {
		start = 0;
		finish = 0;
		end_of_storage = 0;
	}

	_HJSTL_vector(hjstl_size_type size, const Type&value){
		fill_initialze(size, value);
	}

	_HJSTL_vector(int n, const Type& value){
		fill_initialze(size, value);
	}

	_HJSTL_vector(hjstl_size_type size){
		fill_initialze(size, Type());
	}

	_HJSTL_vector(const _HJSTL_vector<Type, Alloc>& vec){
		start = allocate_and_fill(vec.end() - vec.begin(), vec.begin(), vec.end());
		finish = start + (vec.end() - vec.begin());
		end_of_storage = finish;
	}
	/////////////////////////////////////

	//operator =
	_HJSTL_vector<Type, Alloc>& operator =(const _HJSTL_vector<Type, Alloc>&vec);

	//reserve the vector
	void reserve(hjstl_size_type size)
	{
		if (capcity < size){//if the capcity is not so enough,just alloc
			const hjstl_size_type old_size = size();
			//new storage allocate.
			hjstl_iterator storage=allocate_and_copy(size,start,finish);
			//deallocate the src memory,and update the storage.
			deallocate();
			start = storage;
			finish = storage + size;
			end_of_storage = start + size;
		}
		//else,do nothing.
	}

	//some operators.
_HJSTL_VECTOR_PUBLIC_:
	//push back an element into this vector.
	void push_back(const Type& value){
		if (finish != end_of_storage){//whether left memory?
			//if left memory,just do it.
			construct(finish, value);
			++finish;
		}
		else{//no memory,need to re-alloc
			insert_aux(end(), value);
		}
	}

	//you want to swap two vector..
	void swap(_HJSTL_vector<Type, Alloc>& vec){
		std::swap(start, vec.start);
		std::swap(finish, vec.finish);
		std::swap(end_of_storage, vec.end_of_storage);
	}

	//you want to insert an element to position,the value is 'value'
	hjstl_iterator insert(hjstl_iterator position, const Type& value)
	{
		if (finish != end_of_storage&&position == end()){//you want to push_back.
			construct(finish, value);
			++finish;
		}
		else{//you need to insert the mid..
			insert_aux(position, value);
		}
		//return the iterator
		return (begin() + hjstl_size_type(position - begin()));
	}

	//other insert,but no initialze
	hjstl_iterator insert(hjstl_iterator position)
	{
		return insert(position, T());
	}

	//you also can insert like this
	void insert(hjstl_iterator position, hjstl_size_type size, const Type& v);

	//partial.
	void insert(hjstl_iterator position, int n, const Type& value){
		insert(position, n, value);
	}

	//pop back.
	void pop_back(){
		//easy to do this
		--finish;
		destroy(finish);
	}
	//you want to earse an object in vector
	//no use but return the position you give me.
	hjstl_iterator earse(hjstl_iterator position){
		if (position + 1 != end()){//you delete element actually.
			copy(position + 1, finish, position);
		}
		--finish;
		destroy(finish);
		return position;
	}

	//you also can delete an range.
	hjstl_iterator earse(hjstl_iterator first, hjstl_iterator last){
		//the follow will remove the range[first..last]
		//the copy function will copy the [last...finish] to [first..]
		//and return the result.
		hjstl_iterator result = copy(last, finish, first);

		//you need to deallocate the obj
		destroy(result, finish);
		//update the storage
		finish = finish - (last - first);
		return first;
	}

	//you want to resize the vector..
	void resize(hjstl_size_type new_size, const Type& value)
	{
		//if the new size < old size,earse some elements.
		if (new_size < size()){
			earse(begin() + new_size, end());
		}
		//else,the new size >= old size,insert 
		else{
			insert(end(), new_size - size(), value);
		}
	}

	//another resize but not initialze
	void resize(hjstl_size_type size){
		resize(size, Type());
	}

	//clear the vector
	void clear(){
		earse(begin(), end());
	}
};//end of vector

//the operator ==
template<class Type,class Alloc>
inline bool operator ==(const _HJSTL_vector<Type, Alloc>& x, const _HJSTL_vector<Type, Alloc>& y)
{
	return x.size() == y.size() &&
		equal(x.begin(), x.end(), y.begin());
}

//operator <
template<class Type,class Alloc>
inline bool operator <(const _HJSTL_vector<Type, Alloc>& x, const _HJSTL_vector<Type, Alloc>& y)
{
	return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

//swap
template<class Type,class Alloc>
inline void swap(const _HJSTL_vector<Type, Alloc>& x, const _HJSTL_vector<Type, Alloc>& y){
	x.swap(y);
}

//implement.
template<class Type,class Alloc>
_HJSTL_vector<Type, Alloc>& _HJSTL_vector<Type, Alloc>::operator=(const _HJSTL_vector<Type, Alloc>& x)
{
	//if the capcity is not enough.we need to alloc.
	if (x.size() > capcity){
		hjstl_iterator result = allocate_and_copy(x.end() - x.begin(), x.begin(), x.end());
		//destory old mem
		destroy(start, finish);
		deallocate();
		//reset the storage
		start = result;
		end_of_storage = start + (x.end() - x.begin());
	}
	//else if the capcity is enough
	else if (size() >= x.size()){
		hjstl_iterator result = copy(x.begin(), x.end(), begin());
		//destory the left 
		destroy(result, finish);
	}
	else{//can append.
		//copy first
		copy(x.begin(), x.begin() + size(), start);
		//copy the left
		hjstl_uninitialized_copy(x.begin() + size(), x.end(), finish);
	}
	//reset the finish
	finish = start + x.size();
	return *this;
}

//aux_insert
template<class Type,class Alloc>
void _HJSTL_vector<Type, Alloc>::insert_aux(hjstl_iterator position, const Type& value)
{
	//still left memory can use
	if (finish != end_of_storage){
		construct(finish, *(finish - 1));
		++finish;
		Type copy_v = value;
		//copy from back to front.
		//copy_backward(start,end,dststart)
		//[start..end]-> start....end
		//you should know the update of finish.
		//before construct,the structure is like this:
		//  ...[x][x][x][x].[finish]......[end_of_starage]
		//the finish is no data,finish-1 is the last data position.
		//after construct the structure change to this:
		//  ...[x][x][x][x].[x][finish]...[end_of_storage]
		//so,the last data's position is finish-2.
		//so,you can understand now.

		copy_backward(position, finish - 2, finish - 1);

		//let the position's value as copy_v
		*position = copy_v;
	}
	else{//no memory.
		const hjstl_size_type old_size = size();
		//2*old_size is needed.
		const hjstl_size_type len = old_size != 0 ? 2 * old_size : 1;
		//use the second allocate to alloc the new memory from memory pool.
		hjstl_iterator new_start =(Type*)vector_alloc::hjstl_allocate(len);

		hjstl_iterator new_finish = new_start;
		//what we want to do is like this.
		try{
			new_finish = hjstl_uninitialized_copy(start, position, new_start);
			construct(new_finish, value);
			++new_finish;
			new_finish = hjstl_uninitialized_copy(position, finish, new_finish);
		}
		catch (...){
			//if error.destroy the memory.
			destroy(new_start, new_finish);
			vector_alloc::hjstl_deallocate(new_start, len);
		}
		//destory the old mem
		destroy(begin(), end());
		deallocate();
		//reset the start and finish and storage
		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + len;
	}
}


//from position,insert size elements,and the start value is v
template<class Type,class Alloc>
void _HJSTL_vector<Type, Alloc>::insert(hjstl_iterator position, hjstl_size_type size, const Type& v)
{
	//if size==0,no use.
	if (0 != size){
		//the memory is so enough.just insert these elements
		if (hjstl_size_type(end_of_storage - finish) >= size){
			Type copy_v = v;
			const hjstl_size_type elements_after = finish - position;
			hjstl_iterator old_finish = finish;
			//the elements after position's num > the new elements
			if (elements_after > size){
				hjstl_uninitialized_copy(finish - size, finish, finish);
				finish += size;

				copy_backward(position, old_finish - size, old_finish);

				//fill the new elements
				fill(position, position + size, copy_v);
			}
			else{//the elements after position's num < the new elements
				hjstl_uninitialized_fill_n(finish, size - elements_after, copy_v);
				finish += (size - elements_after);
				hjstl_uninitialized_copy(position, old_finish, finish);
				finish += (elements_after);
				fill(position, old_finish, copy_v);
			}
		}//end of memory enough
		else{//the left memory is not enough to alloc
			//then,we need to re-alloc the new memory,the new alloc length is the 2*oldsize
			const hjstl_size_type old_size = old_size();
			const hjstl_size_type len = old_size+max(old_size,n);

			//alloc new vector space
			hjstl_iterator   new_start = vector_alloc::hjstl_allocate(len);
			hjstl_iterator   new_finish = new_start;
			//copy old data to new space,then insert new elements
			new_finish = hjstl_uninitialized_copy(start, position, new_start);
			new_finish = hjstl_uninitialized_fill_n(new_finish, n, v);
			new_finish = hjstl_uninitialized_copy(position, finish, new_finish);
			//free the old memory
			destroy(start, finish);
			deallocate();
			//reset the start and finsih
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start + len; //this is the memory we can use.
		}
	}
}

#endif  //end of _HJ_STL_VECTOR_H_

