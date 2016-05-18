#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <tchar.h>
using namespace std;

#define SAFE_ZERO( p) { p = 0;}
#define SAFE_NEW( p, type ) { if(!p) { p = new type; } }
#define SAFE_DEL( p ) { if(p) { delete p; p = NULL;} }
#define SAFE_NEW_ARRAY( p, type, size ) { if(!p) { p = new type[size];} }
#define SAFE_DEL_ARRAY( p ) { if(p) { delete [] p; p = NULL;} }

//��ü
class Point
{
	/////////////////// ��� ���� /////////////
//�������� ������
private:// Ŭ���� �ܺη� ������Ѵ�.
	int		m_iX;
	int		m_iY;
	char*	m_pszData;
public:
	static int g_iCount;
	//////////////  ��� �Լ� ///////////////
public:
	static int  GetCount();
	// iX, iY �� 0~100 ������ �����Ѵ�.
	// ������ ���� ���� ��� 0���� ���õȴ�.
	// ��������
	const bool	SetPosition(int iX, int iY);
	// �б� ����
	const int		GetX() { return m_iX; }
	const int		GetY() { return m_iY; }
	void	SetString(char* pData);
	const char*   GetString() { return m_pszData; }
	void	Show();
	void	Delete();
	/////////////// ������ / ������ //////////
public:
	//// �⺻ ������
	Point();
	// �Լ������ε�
	Point(int x, int y);
	Point(int x, int y, char* pData);
	// ���� ������
	Point( const Point& data) ;
	//// ������
	~Point();
};
//public: static int Point::g_iCount" 
//(?g_iCount@Point@@2HA)��(��) 
//Sample.obj�� �̹� ���ǵǾ� �ֽ��ϴ�.
//int Point::GetCount()
//{
//	return Point::g_iCount;
//};

//ublic: static int __cdecl Point::GetCount
//(void)" (?GetCount@Point@@SAHXZ) 
//�ܺ� ��ȣ(���� ��ġ: _main �Լ�)���� Ȯ������ ���߽��ϴ�.