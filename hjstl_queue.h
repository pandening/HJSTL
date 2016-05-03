#ifndef _HJSTL_QUEUE_H_
#define _HJSTL_QUEUE_H_
/*
* Author:hujian
* Time:2016/4/30
* discription:this file is about queue structure.
* NOTICE:using deque as the low-level structure of queue.
* you can use list replace deque to do the same work.
*
*/

#define _HJSTL_QUEUE_PUBLIC   public
#define _HJSTL_QUEUE_PRIVZTE  private
#define _HJSTL_QUEUE_PROTECTED  protected

#include "hjstl_deque.h"

template<class Type,class Sequence=_HJSTL_deque<Type>>
class _HJSTL_queue{
	
_HJSTL_QUEUE_PUBLIC:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;
	typedef typename Sequence::const_reference const_reference;

_HJSTL_QUEUE_PROTECTED:
	//this is a deque,but i will use it create a queue
	Sequence c;

_HJSTL_QUEUE_PUBLIC:
	//useful interface
	bool empty() const { return c.empty(); }
	size_type size() const { return c.size(); }
	reference front() { return c.front(); }
	const_reference front() const { return c.front(); }
	reference back() { return c.back(); }
	const_reference back() const { return c.back(); }

	void push(const value_type& v) { c.push_back(v); }
	void pop() { c.pop_front(); }
};//end of hjstl queue

#endif  //end of _HJSTL_QUEUE_H_