#include "hjstl_alloc.h"
#include "hjstl_iterator.h"
#include "hjstl_construct.h"
#include "hjstl_type_traits.h"
#include "hjstl_uninitialized.h"
#include "hjstl_vector.h"
#include "hjstl_list.h"
#include "hjstl_deque.h"
#include "hjstl_stack.h"
#include "hjstl_queue.h"

using namespace std;

int main()
{
	__HJSTL_deque_iterator<int, int&, int*, 1024> p;
	//cout<<p.buffer_size();
	_HJSTL_deque<int> hujian;
	hujian.push_back(12);
	hujian.push_back(21);
	hujian.push_front(23);

	_HJSTL_deque<int>::iterator hit;
	for (hit = hujian.begin(); hit != hujian.end(); hit++){
		cout << *hit << " ";
	}
	cout << endl;
	
	cout << "the size of this deque is:" << hujian.size() << endl;
	cout << "the max size of this deue is:"<<hujian.max_size() << endl;

	hujian.pop_back();
	for (hit = hujian.begin(); hit != hujian.end(); hit++){
		cout << *hit << " ";
	}
	cout << endl;
	hujian.pop_front();
	for (hit = hujian.begin(); hit != hujian.end(); hit++){
		cout << *hit << " ";
	}
	cout << endl;
	hujian.clear();
	for (hit = hujian.begin(); hit != hujian.end(); hit++){
		cout << *hit << " ";
	}
	cout << endl;
	_HJSTL_stack<int> pppppp;
	pppppp.push(12);
	for (int i = 0; i < 100; i++){
		pppppp.push(i);
	}

	for (int i = 0; i < 101; i++){
		pppppp.pop();
	}

	if (!pppppp.empty()){
		cout << "ppppppp is not empty." << endl;
	}
	if (!pppppp.empty())
	 cout <<"stack's top=>"<<pppppp.top()<< endl;

	_HJSTL_queue<int> hj;
	hj.push(123);
	hj.push(32);

	cout << "hj.size=" << hj.size() << endl;





	return 0;
}