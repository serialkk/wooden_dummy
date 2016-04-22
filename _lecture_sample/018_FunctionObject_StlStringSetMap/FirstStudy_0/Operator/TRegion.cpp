#include "TRegion.h"
void	TRegion::UnionRegion(const TRegion& r1,
	const TRegion& r2)
{
	iLeft = (r1.iLeft < r2.iLeft) ? r1.iLeft : r2.iLeft;
	iRight = (r1.iRight > r2.iRight) ? r1.iRight : r2.iRight;

	iTop = (r1.iTop < r2.iTop) ? r1.iTop : r2.iTop;
	iBottom = (r1.iBottom > r2.iBottom) ? r1.iBottom : r2.iBottom;
}
bool   operator ^ (const TRegion& r1,
	const TRegion& r2)
{
	int iLeft = (r1.iLeft > r2.iLeft) ? r1.iLeft : r2.iLeft;
	int iRight = (r1.iRight < r2.iRight) ? r1.iRight : r2.iRight;

	int iTop = (r1.iTop > r2.iTop) ? r1.iTop : r2.iTop;
	int iBottom = (r1.iBottom < r2.iBottom) ? r1.iBottom : r2.iBottom;

	if (iLeft >= iRight || iTop >= iBottom)
	{
		iLeft = iRight = iTop = iBottom = 0;
		return false;
	}
	return true;
}
bool	TRegion::IntersectRegion(
	const TRegion& r1,
	const TRegion& r2)
{
	iLeft = (r1.iLeft > r2.iLeft) ? r1.iLeft : r2.iLeft;
	iRight = (r1.iRight < r2.iRight) ? r1.iRight : r2.iRight;

	iTop = (r1.iTop > r2.iTop) ? r1.iTop : r2.iTop;
	iBottom = (r1.iBottom < r2.iBottom) ? r1.iBottom : r2.iBottom;

	if (iLeft >= iRight || iTop >= iBottom)
	{
		iLeft = iRight = iTop = iBottom = 0;
		return false;
	}
	return true;
}

void	TRegion::Show()
{
	std::cout << " left:" << iLeft
		<< " top:" << iTop
		<< " right:" << iRight
		<< " bottom:" << iBottom << std::endl;
}
void	TRegion::GetCenterPoint(int& iX, int & iY) const
{
	iX = (iRight + iLeft) / 2;
	iY = (iBottom + iTop) / 2;
}
TPoint	TRegion::GetCenterPoint() const
{
	int iX = (iRight + iLeft) / 2;
	int iY = (iBottom + iTop) / 2;
	return TPoint(iX, iY);
}
void	TRegion::Resize(int iWidth, int iHeight)
{
	int iCenterX;
	int iCenterY;
	GetCenterPoint(iCenterX, iCenterY);
	//int iRadiusX = (iRight - iLeft) / 2;
	//int iRadiusY = (iBottom - iTop) / 2;
	// c(0, 0) w=40
	//  -20, -20 -> 20, 20
	//  -20, -20 -> -20 +  40 = 20
	iLeft = iCenterX - iWidth / 2;
	iTop = iCenterY - iHeight / 2;
	iRight = iLeft + iWidth;//iCenterX + iWidth / 2;  
	iBottom = iTop + iHeight;// iCenterY + iHeight / 2;
}
void    TRegion::Move(int iX, int iY)
{
	iLeft += iX;
	iRight += iX;
	iTop += iY;
	iBottom += iY;
}
void	 TRegion::SetRect(int iL, int iT, int iR, int iB)
{
	iLeft = iL;
	iRight = iR;
	iTop = iT;
	iBottom = iB;
	m_Center.SetPosition(GetCenterPoint());
};
void	TRegion::SetRect(TPoint& p1,
	TPoint& p2)
{
	iLeft = p1.GetX();
	iRight = p2.GetY();
	iTop = p1.GetY();
	iBottom = p2.GetY();
	m_Center.SetPosition(GetCenterPoint());
};
void	TRegion::SetRect(const TPoint& p1,
	const TPoint& p2)
{
	iLeft = p1.GetX();
	iRight = p2.GetY();
	iTop = p1.GetY();
	iBottom = p2.GetY();

	//int iX;// = (iRight + iLeft) / 2;
	//int iY;// = (iBottom + iTop) / 2;
	//GetCenterPoint(iX, iY);
	m_Center.SetPosition(GetCenterPoint());
};
// ������
// const char* p = 0; // ���� ������, ��� ������
// char* const p = 0; // ��� ������, ���� ������
// const char *cosnt p = 0;// ��� ������, ��� ������
// const �Լ������� const �Լ��� ȣ�Ⱑ���ϴ�.
// �Լ� �����ε� ����, ������ ���еȴ�.
// void a() cosnt {} // �Լ������� �� ���� �Ұ���.
void	TRegion::SetRect(const TPoint* const p1,
	const TPoint* const p2)
{
	iLeft = p1->GetX();
	iRight = p2->GetY();
	iTop = p1->GetY();
	iBottom = p2->GetY();

	//int iX;// = (iRight + iLeft) / 2;
	//int iY;// = (iBottom + iTop) / 2;
	//GetCenterPoint(iX, iY);
	m_Center.SetPosition(GetCenterPoint());
};
int	    TRegion::GetWidth() const
{
	// point
	int iWidth = iRight - iLeft;
	return iWidth;
}
int		TRegion::GetHeight() const
{
	// point
	int iHeight = iBottom - iTop;
	return iHeight;
}

TRegion::TRegion()
{
}


TRegion::~TRegion()
{
}
