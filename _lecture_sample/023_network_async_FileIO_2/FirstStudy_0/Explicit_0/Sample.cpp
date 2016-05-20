#include <iostream>
#include <cstdarg> // va_list
using namespace std;
static void OutString(char* str, ... )
{
	va_list ap;
	va_start(ap, str);
		vfprintf(stderr, str, ap);
	va_end(ap);
}
int g_Array[10];
void OutString(int num, ...)
{
	va_list ap;
	va_start(ap, num);
	for (int i = 0; i < num; i++)
	{
		g_Array[i] =va_arg(ap, int);
		cout << g_Array[i];
	}
	va_end(ap);
}
class TClass
{
private:
	int  m_iValue;
public:
	int Get() { return m_iValue; }
	TClass( int iValue) : m_iValue( iValue)
	{}
	TClass( TClass& copy) : m_iValue( copy.m_iValue)
	{}
	~TClass() {};
};
class TClassExplicit
{
private:
	int  m_iValue;
public:
	int Get() { return m_iValue; }
	explicit TClassExplicit(int iValue) : m_iValue(iValue)
	{}
	TClassExplicit(TClassExplicit& copy) : m_iValue(copy.m_iValue)
	{}
	~TClassExplicit() {};
};
class TClassMutable
{
private:
	mutable int  m_iValue;
public:
	int Get() const 
	{ 
		m_iValue = 9;
		return m_iValue; 
	}
	TClassMutable(int iValue) : m_iValue(iValue)
	{}
	TClassMutable(TClassMutable& copy) : m_iValue(copy.m_iValue)
	{}
	~TClassMutable() {};
};
void main()
{
	int i = 10;
	OutString("%d %d %d %f", 1,2,3, 4.0f);
	OutString("%d", 1);
	OutString("%f %d", 3.14f, i);

	OutString(3, 1, 2, 3);

	TClass tA(3);
	TClass tB = 3; // 묵시적
	TClass tC = tA;
	cout << tA.Get();
	cout << tB.Get();
	cout << tC.Get();

	TClassExplicit tD(3.0f);
	//TClassExplicit tE = 3; // 묵시적 형변환 방지
	TClassExplicit tF = tD;
	cout << tD.Get();
	//cout << tE.Get();
	cout << tF.Get();

	TClassMutable tG(3.0f);
	TClassMutable tH = 3; // 묵시적 형변환 방지
	TClassMutable tI = tG;
	cout << tG.Get();
	cout << tH.Get();
	cout << tI.Get();

}