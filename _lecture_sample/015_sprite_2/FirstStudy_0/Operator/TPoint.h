#pragma once
#include "TStd.h"

class TRegion;
struct Point2
{
	union {		
		struct{
			int		x;
			int		y;
		};
		int		v[2];
	};
};
//객체
class TPoint : public Point2
{
public:
	const TPoint* Get() const { return this; }
	const TPoint& GetRef() const { return *this; }
public:
	// 연산자 재정의 함수 선언
	TPoint operator ++(void) ; // ++p1
	TPoint operator ++(int); // p1++
	TPoint operator +( const TPoint& pt) const; //c= a + pt
	TPoint operator +(int iValue) const ;
	friend TPoint operator +(int iValue, const TPoint& p);
	TPoint& operator=(const TPoint& pt);
	TPoint& operator+=(const TPoint& pt);	
	bool operator ==(const TPoint& pt);
	int&  operator [] (int iIndex);
	void* operator new (size_t size)
	{
		return malloc(size);
	}
	void operator delete(void* p)
	{
		free(p);
	}
	friend ostream& operator << ( ostream &os, const TPoint& p);
	friend istream& operator >> ( istream &is, TPoint& p);
public:
	static int g_iCount;
	TRegion * m_pRegion;
	void    Set(TRegion* a);
	//////////////  멤버 함수 ///////////////
public:
	void        Compute(const  TRegion& a);
	int			GetX() const { return x; }
	int			GetY() const  { return y; }
	static int  GetCount();
	// iX, iY 은 0~100 범위로 제한한다.
	// 범위를 벗어 났을 경우 0으로 세팅된다.
	// 쓰기전용
	const bool	SetPosition(int iX, int iY);
	void		SetPosition(TPoint p1)
	{
		x = p1.x;
		y = p1.y;
	}
	void	Show();
	void	Delete();
	/////////////// 생성자 / 해제자 //////////
public:
	//// 기본 생성자
	TPoint();
	// 함수오버로딩
	TPoint(int x, int y);
	// 복사 생성자
	TPoint(const TPoint& data);
	//// 해제자
	~TPoint();
};