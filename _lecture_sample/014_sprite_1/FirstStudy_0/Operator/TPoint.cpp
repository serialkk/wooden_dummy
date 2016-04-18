#include "TPoint.h"

int TPoint::g_iCount = 0;

ostream& operator << (ostream &os, const TPoint& p)
{
	os << "x=" << p.x << "," << "y=" << p.y << endl;
	return os;
};
istream& operator >> (istream &is, TPoint& p)
{
	is >> p.x;
	is >> p.y;
	return is;
};
int&  TPoint::operator [] (int iIndex)
{
	return v[iIndex];
}
TPoint  TPoint::operator ++(void) // ++p1
{
	++x;
	++y;
	return *this;
}
TPoint  TPoint::operator ++(int) // p1++
{
	TPoint temp = *this;
	x++;
	y++;
	return temp;
}
TPoint   TPoint::operator +(const TPoint& pt) const
{
	TPoint temp;
	temp.x = x + pt.x;
	temp.y = y + pt.y;
	return temp;
}
TPoint TPoint::operator +(int iValue) const 
{
	TPoint temp;
	temp.x = x + iValue;
	temp.y = y + iValue;
	return temp;
}
TPoint operator +(int iValue, const TPoint& p)
{
	return TPoint(p.x+iValue, p.y+iValue);
}
TPoint& TPoint::operator=(const TPoint& pt)
{
	x = pt.x;
	y = pt.y;
	return *this;
}
TPoint& TPoint::operator+=(const TPoint& pt)
{
	x += pt.x;
	y += pt.y;
	return *this;
}
bool TPoint::operator ==(const TPoint& pt)
{
	return (x==pt.x && y == pt.y);
}
void    TPoint::Set(TRegion* a)
{
	m_pRegion = a;
}
void    TPoint::Compute(const  TRegion& a)
{
};
int  TPoint::GetCount()
{

	return TPoint::g_iCount;
};

void TPoint::Delete()
{
};
const bool TPoint::SetPosition(int iX, int iY)
{
	if (iX < 0 || iX > 100)
	{
		std::cout << "\n X=0~ 100 범위로 입력하시오!!" << std::endl;
		return false;
	}
	if (iY < 0 || iY > 100)
	{
		std::cout << "\n Y=0~ 100 범위로 입력하시오!!" << endl;
		return false;
	}
	x = iX;
	this->y = iY;
	return true;
}
void TPoint::Show()
{
	printf("\n%d,%d", x, y);
}
//public: static int TPoint::g_iCount" (?g_iCount@TPoint@@2HA) 외부 기호를 확인할 수 없습니다
TPoint::TPoint()
{
	g_iCount++;
	x = 5; y = 50;
	cout << "생성자 호출" << endl;
}
TPoint::TPoint(int iX, int iY)
{
	g_iCount++;
	x = iX; y = iY;
	cout << "생성자 호출" << endl;
}
TPoint::TPoint(const TPoint& data)
{
	g_iCount++;
	x = data.x;
	y = data.y;
	cout << "복사 생성자 호출" << endl;
}
TPoint::~TPoint()
{
	Delete();
	cout << "해제자 호출" << endl;
}