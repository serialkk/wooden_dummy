#include "TPoint.h"

int Point::g_iCount = 0;
void    Point::Set(TRegion* a)
{
	m_pRegion = a;		
}
void    Point::Compute( const  TRegion& a)
{	
};
int  Point::GetCount()
{
	
	return Point::g_iCount;
};

void Point::Delete()
{
	SAFE_DEL_ARRAY(m_pszData);/*
							  if (m_pszData != NULL)
							  {
							  delete m_pszData;
							  m_pszData = NULL;
							  }*/
};
void Point::SetString(char* pData)
{
	int iSize = strlen(pData);
	if (m_pszData == NULL)
	{
		SAFE_NEW_ARRAY(m_pszData, char, iSize + 1);
		//this->m_pszData = new char[iSize + 1];
	}
	strcpy(m_pszData, pData);
}
const bool Point::SetPosition(int iX, int iY)
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
	m_iX = iX;
	this->m_iY = iY;
	return true;
}
void Point::Show()
{
	printf("\n%d,%d", m_iX, m_iY);
}
//public: static int Point::g_iCount" (?g_iCount@Point@@2HA) 외부 기호를 확인할 수 없습니다
Point::Point()
{
	SAFE_ZERO(m_pszData);
	g_iCount++;
	m_iX = 5; m_iY = 50;
	cout << "생성자 호출" << endl;
}
Point::Point(int x, int y)
{
	SAFE_ZERO(m_pszData);
	g_iCount++;
	m_iX = x; m_iY = y;
	cout << "생성자 호출" << endl;
}
Point::Point(int x, int y, char* pData)
{
	SAFE_ZERO(m_pszData);
	g_iCount++;
	m_iX = x; m_iY = y;
	SetString(pData);
	cout << "생성자 호출" << endl;
};
//error C2662: '
//bool Point::SetPosition(int,int)': 
//'this' 포인터를 'const Point'에서 
//'Point &'(으)로 변환할 수 없습니다.
Point::Point(const Point& data)
{
	SAFE_ZERO(m_pszData);
	g_iCount++;
	m_iX = data.m_iX;
	m_iY = data.m_iY;
	//this->m_pszData = data.GetString();
	SetString(data.m_pszData);
	cout << "복사 생성자 호출" << endl;
}
Point::~Point()
{
	Delete();
	cout << "해제자 호출" << endl;
}