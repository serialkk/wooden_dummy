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

class TRegion;
//객체
class Point
{
	/////////////////// 멤버 변수 /////////////
	//접근제어 연산자
private:// 클래스 외부로 비공개한다.
	int		m_iX;
	int		m_iY;
	char*	m_pszData;
public:
	static int g_iCount;
	TRegion * m_pRegion;
	void    Set(TRegion* a);
	//////////////  멤버 함수 ///////////////
public:
	void        Compute(const  TRegion& a);
	int			GetX() const  { return m_iX; }
	int			GetY() const  { return m_iY; }
	static int  GetCount();
	// iX, iY 은 0~100 범위로 제한한다.
	// 범위를 벗어 났을 경우 0으로 세팅된다.
	// 쓰기전용
	const bool	SetPosition(int iX, int iY);
	void		SetPosition(Point p1)
	{
		m_iX = p1.m_iX;
		m_iY = p1.m_iY;
	}
	// 읽기 전용
	const int		GetX() { return m_iX; }
	const int		GetY() { return m_iY; }
	void	SetString(char* pData);
	const char*   GetString() { return m_pszData; }
	void	Show();
	void	Delete();
	/////////////// 생성자 / 해제자 //////////
public:
	//// 기본 생성자
	Point();
	// 함수오버로딩
	Point(int x, int y);
	Point(int x, int y, char* pData);
	// 복사 생성자
	Point(const Point& data);
	//// 해제자
	~Point();
};
//public: static int Point::g_iCount" 
//(?g_iCount@Point@@2HA)이(가) 
//Sample.obj에 이미 정의되어 있습니다.
//int Point::GetCount()
//{
//	return Point::g_iCount;
//};

//ublic: static int __cdecl Point::GetCount
//(void)" (?GetCount@Point@@SAHXZ) 
//외부 기호(참조 위치: _main 함수)에서 확인하지 못했습니다.