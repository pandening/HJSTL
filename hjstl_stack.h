#ifndef _HJSTL_STACK_H_
#define _HJSTL_STACK_H_
/*
* Author:hujian
* Time:2016/4/30
* discription:this file is about stack structure.
* NOTICE:using deque as the low-level structure of stack.
* you can use list replace deque to do the same work.
* 
*/

#define _HJSTL_STACK_PUBLIC   public
#define _HJSTL_STACK_PRIVZTE  private
#define _HJSTL_STACK_PROTECTED  protected

#include "hjstl_deque.h"


template<class Type,class Sequence=_HJSTL_deque<Type>/*use deque to create stack*/>
class _HJSTL_stack{
	friend bool operator==(const _HJSTL_stack&, const _HJSTL_stack&);
	friend bool operator<(const _HJSTL_stack&, const _HJSTL_stack&);

_HJSTL_STACK_PUBLIC:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;
	typedef typename Sequence::const_reference const_reference;

_HJSTL_STACK_PROTECTED:
	//we can say,this is the stack instance.
	Sequence c;
_HJSTL_STACK_PUBLIC:
	//useful function
	bool empty(){ return c.empty(); }
	size_type size()const { return c.size(); }
	reference top(){ return c.back(); }
	const_reference top() const { return c.back(); }
	void push(const value_type&v){ c.push_back(v); }
	void pop(){ c.pop_back(); }
};//end of hjstl stack

//implement the friend function
template<class Type,class Sequence>
bool operator==(const _HJSTL_stack<Type, Sequence>&x, const _HJSTL_stack<Type, Sequence>& y)
{
	return x.c == y.c;
}

//implement the friend function
template<class Type, class Sequence>
bool operator<(const _HJSTL_stack<Type, Sequence>&x, const _HJSTL_stack<Type, Sequence>& y)
{
	return x.c<y.c;
}

#endif //end of  hjstl stack