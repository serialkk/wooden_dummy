#include <iostream>
using namespace std;
struct A {
	virtual void test()
	{
		cout << "A class" << endl;
	}
};
struct B : A
{
	virtual void test()
	{
		cout << "B class" << endl;
	}
	virtual void test2()
	{
		cout << "B class test2" << endl;
	}
};
struct C : B
{
	virtual void test()
	{
		cout << "C class" << endl;
	}
	void test2()
	{
		cout << "C class test2" << endl;
	}
};
void Global(A& a)
{
	try {
		C& c = dynamic_cast<C&>(a);
	}
	catch (std::bad_cast)
	{
		cout << "Bad Cast" << endl;
	}
}

void main()
{
	A* a = new C;
	A* ab = new B;
	ab->test();
	// 포인터 혹은 참조
	B* ba = dynamic_cast<B*>(a);
	if (ba) ba->test2();

	C* bc = dynamic_cast<C*>(ab);
	if (bc) bc->test2();

	C c;
	Global(c);

	B b;
	Global(b);


}