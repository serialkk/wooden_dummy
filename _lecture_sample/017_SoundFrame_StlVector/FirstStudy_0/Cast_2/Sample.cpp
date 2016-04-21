#include <iostream>
using namespace std;
void f()
{
	char ch;
	int i = 65;
	float f = 2.5f;
	double d;
	ch = static_cast<char>(i);
	d = static_cast<double>(f);
	i = static_cast<int>(ch);
}
class B
{
public:
	virtual ~B() {}
};
class D : public B
{

};
void f(B* b)
{
	D* d1 = dynamic_cast<D*>(b);
	// 안전하지 못하다.
	D* d2 = static_cast<D*>(b);
	//// 안전하다.
	//B* d3 = static_cast<B*>(d);
	if( d1 == NULL)
	{ 
		cout << "d1=NULL" << endl;
	}
	if (d2 == NULL)
	{
		cout << "d2=NULL" << endl;
	}

}
void main()
{
	B b;
	f(&b);
	f();
}