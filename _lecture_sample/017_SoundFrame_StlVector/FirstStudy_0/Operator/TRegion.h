#pragma once
#include "TPoint.h"

// 100,0        200, 0  // point
//
// 0,200      200,200 // size

// 100,0   -> 100
//  /
// 100 
struct TRect
{
	int		iLeft;
	int		iTop;
	int		iRight; // m_iWidth
	int		iBottom;// m_iHeight
};
class TRegion : public TRect
{
public:
	enum { POINT_POINT, POINT_SIZE };
	int   m_iValue;
private:
	TPoint   m_Center;	
public:
	// 인라인화 된 함수
	int    GetLeft() const { return iLeft; }
	int    GetTop() const { return iTop; }
	void	SetRect(int iL, int iT, int iR, int iB);
	void	SetRect(TPoint& p1, TPoint& p2);
	void	SetRect(const TPoint& p1,
		const TPoint& p2);
	void	SetRect(const TPoint* const p1,
		const TPoint* const p2);
	void	Move(int iX, int iY);
	void	Resize(int iWidth, int iHeight);
	void	GetCenterPoint(int& iX, int & iY) const;
	TPoint	GetCenterPoint() const;
	bool	IntersectRegion(const TRegion& r1,
		const TRegion& r2);
	friend bool   operator ^ (const TRegion& r1,
						const TRegion& r2);

	void	UnionRegion(const TRegion& r1, const TRegion& r2);
	// 멤버 변수를 수정 할 수 없다.
	int	    GetWidth() const;
	int		GetHeight()const;
	void	Show();
public:
	TRegion();
	~TRegion();
};

