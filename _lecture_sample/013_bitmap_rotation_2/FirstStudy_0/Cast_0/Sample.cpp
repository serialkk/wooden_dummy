#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
int Hash(void * p)
{
	int iKey = reinterpret_cast<int>(p);
	return (iKey ^ (iKey >> 16));
}
class   TParent2
{
public:
	int m_iValue2;
	char*  m_pName;
	int Hash(void * p)
	{
		int iKey = reinterpret_cast<int>(p);
		return (iKey ^ (iKey >> 16));
	}
	void  SetName(char* pName)
	{
		strcpy(m_pName, pName);
		cout << m_pName << endl;
	}
	void  Set(const int iValue)
	{
	}
	void Print() const
	{
	}
	void Delete()
	{
		delete m_pName;
	}
	void SetNew() {
		m_pName = new char[20];
	}
	TParent2() {
		m_pName = new char[20];
	}
	~TParent2() {
		delete m_pName;
	}
};
class   TParent
{
public :
	int m_iValue;
	/*void  SetName(char* pName)
	{		
	}
	void  Set(const int iValue)
	{		
	}
	void Print() const
	{		
	}*/
	TParent() {}
	virtual  ~TParent() {}
};

class TClass : public TParent
{
private:
	int   m_iNumber;
	char*  m_pName;
public:	
	void  SetName( char* pName)
	{
		
		strcpy(m_pName, pName);
		cout << m_pName << endl;
	}
	void  Set(const int iValue)
	{
		m_iValue = iValue;
	}
	void  Print() const
	{	
		// const �Ӽ��� ����ó��
		const_cast<TClass*>(this)->m_iNumber = 100;
		//m_iNumber = 100;
		cout << m_iNumber << endl;
	}
	void Delete()
	{
		delete m_pName;
	}
	void SetNew() {
		m_pName = new char[20];
	}
	TClass() {
		m_pName = new char[20];
	}
	~TClass() {
		delete m_pName; 
	}
};

void main()
{
	int i = 100;
	int j = 200;
	float d = (float)i / j;
	// �⺻ ������ ���� ����ȯ
	float e = static_cast<float>(i) / j;

	TParent* f = new TParent();
	//TParent* c = (TParent*)f;
	TClass * g = new TClass();



	TParent * p = g;
	//TParent* c = (TParent*)f;
	TClass* c = dynamic_cast<TClass*>(p);
	//if (c != NULL)	{	}
	// �ƹ��� ���� ���� �� ��ȯ.
	// å�Ӿ���. ��Ÿ�ӿ��� ������ �߻��� �� �ִ�.
	//  ��Ÿ�ӿ��� �˻����� �ʴ´�.
	//TParent2* w = static_cast<TParent2*>(p);
	TParent2* w = reinterpret_cast<TParent2*>(p);
	w->SetNew();
	w->Set(100);
	w->Print();

	int iData = 100;
	w->Set(iData);
	const char  name[] = "kgca";
	//error C2664 : 'void TClass::SetName(char *)' 
	//: �μ� 1��(��) 'const char [5]'���� 
	//'char *'(��)�� ��ȯ�� �� �����ϴ�	
	w->SetName(const_cast<char*>(name));
	w->Delete();
}