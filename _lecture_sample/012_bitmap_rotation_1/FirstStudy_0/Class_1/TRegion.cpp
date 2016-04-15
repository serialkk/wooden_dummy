#include "TRegion.h"
void	TRegion::UnionRegion(const TRegion& r1,
	const TRegion& r2)
{
	m_iLeft = (r1.m_iLeft < r2.m_iLeft) ? r1.m_iLeft : r2.m_iLeft;
	m_iRight = (r1.m_iRight > r2.m_iRight) ? r1.m_iRight : r2.m_iRight;

	m_iTop = (r1.m_iTop < r2.m_iTop) ? r1.m_iTop : r2.m_iTop;
	m_iBottom = (r1.m_iBottom > r2.m_iBottom) ? r1.m_iBottom : r2.m_iBottom;
}
bool	TRegion::IntersectRegion(
	const TRegion& r1,
	const TRegion& r2)
{
	m_iLeft = (r1.m_iLeft > r2.m_iLeft) ? r1.m_iLeft : r2.m_iLeft;
	m_iRight = (r1.m_iRight < r2.m_iRight) ? r1.m_iRight : r2.m_iRight;

	m_iTop = (r1.m_iTop > r2.m_iTop) ? r1.m_iTop : r2.m_iTop;
	m_iBottom = (r1.m_iBottom < r2.m_iBottom) ? r1.m_iBottom : r2.m_iBottom;

	if (m_iLeft >= m_iRight || m_iTop >= m_iBottom)
	{
		m_iLeft = m_iRight = m_iTop = m_iBottom = 0;
		return false;
	}
	return true;
}

void	TRegion::Show()
{
	std::cout	<< " left:" << m_iLeft 
				<< " top:" 	<< m_iTop 
				<< " right:" << m_iRight 
				<< " bottom:" << m_iBottom << std::endl;
}
void	TRegion::GetCenterPoint(int& iX, int & iY) const
{
	iX = (m_iRight + m_iLeft) / 2;
	iY = (m_iBottom + m_iTop) / 2;
}
Point	TRegion::GetCenterPoint() const
{
	int iX = (m_iRight + m_iLeft) / 2;
	int iY = (m_iBottom + m_iTop) / 2;
	return Point(iX, iY);
}
void	TRegion::Resize(int iWidth, int iHeight)
{	
	int iCenterX;
	int iCenterY;
	GetCenterPoint(iCenterX, iCenterY);
	//int iRadiusX = (m_iRight - m_iLeft) / 2;
	//int iRadiusY = (m_iBottom - m_iTop) / 2;
	// c(0, 0) w=40
	//  -20, -20 -> 20, 20
	//  -20, -20 -> -20 +  40 = 20
	m_iLeft = iCenterX - iWidth/2;
	m_iTop = iCenterY - iHeight / 2;
	m_iRight = m_iLeft + iWidth;//iCenterX + iWidth / 2;  
	m_iBottom = m_iTop + iHeight;// iCenterY + iHeight / 2;
}
void    TRegion::Move(int iX, int iY)
{
	m_iLeft += iX;
	m_iRight += iX;
	m_iTop += iY;
	m_iBottom += iY;
}
void	 TRegion::SetRect(int iL, int iT, int iR, int iB)
{
	m_iLeft = iL;
	m_iRight = iR;
	m_iTop = iT;
	m_iBottom = iB;
	m_Center.SetPosition(GetCenterPoint());
};
void	TRegion::SetRect(   Point& p1,
							Point& p2)
{
	m_iLeft = p1.GetX();
	m_iRight = p2.GetY();
	m_iTop = p1.GetY();
	m_iBottom = p2.GetY();
	m_Center.SetPosition(GetCenterPoint());
};
void	TRegion::SetRect(const Point& p1,
						 const Point& p2)
{
	m_iLeft = p1.GetX();
	m_iRight = p2.GetY();
	m_iTop = p1.GetY();
	m_iBottom = p2.GetY();

	//int iX;// = (m_iRight + m_iLeft) / 2;
	//int iY;// = (m_iBottom + m_iTop) / 2;
	//GetCenterPoint(iX, iY);
	m_Center.SetPosition(GetCenterPoint());
};
// 포인터
// const char* p = 0; // 비상수 포인터, 상수 데이터
// char* const p = 0; // 상수 포인터, 비상수 데이터
// const char *cosnt p = 0;// 상수 포이터, 상수 데이터
// const 함수에서는 const 함수만 호출가능하다.
// 함수 오버로딩 참조, 포인터 구분된다.
// void a() cosnt {} // 함수내에서 값 변경 불가능.
void	TRegion::SetRect(	const Point* const p1, 
							const Point* const p2)
{
	m_iLeft = p1->GetX();
	m_iRight = p2->GetY();
	m_iTop = p1->GetY();
	m_iBottom = p2->GetY();

	//int iX;// = (m_iRight + m_iLeft) / 2;
	//int iY;// = (m_iBottom + m_iTop) / 2;
	//GetCenterPoint(iX, iY);
	m_Center.SetPosition(GetCenterPoint());
};
int	    TRegion::GetWidth() const
{
	// point
	int iWidth = m_iRight - m_iLeft;
	return iWidth;
}
int		TRegion::GetHeight() const
{
	// point
	int iHeight = m_iBottom - m_iTop;
	return iHeight;
}

TRegion::TRegion()
{
}


TRegion::~TRegion()
{
}
