#pragma once
#include "TPoint.h"

// 100,0        200, 0  // point
//
// 0,200      200,200 // size

// 100,0   -> 100
//  /
// 100 

class TRegion 
{
public:
	enum { POINT_POINT, POINT_SIZE };
	int   m_iValue;
private:	
	Point   m_Center;
	int		m_iLeft;
	int		m_iTop;
	int		m_iRight; // m_iWidth
	int		m_iBottom;// m_iHeight
public:
	// 인라인화 된 함수
	int    GetLeft() const { return m_iLeft; }
	int    GetTop() const  { return m_iTop; }
	void	SetRect( int iL, int iT, int iR, int iB);
	void	SetRect(Point& p1, Point& p2);
	void	SetRect(	const Point& p1,
						const Point& p2) ;
	void	SetRect(	const Point* const p1, 
						const Point* const p2);
	void	Move(int iX, int iY);
	void	Resize(int iWidth, int iHeight);
	void	GetCenterPoint(int& iX, int & iY) const;
	Point	GetCenterPoint() const;
	bool	IntersectRegion(const TRegion& r1, 
							const TRegion& r2);
	void	UnionRegion(const TRegion& r1,	const TRegion& r2);
	// 멤버 변수를 수정 할 수 없다.
	int	    GetWidth() const;
	int		GetHeight()const;

	void	Show();
public:
	TRegion();
	~TRegion();
};

