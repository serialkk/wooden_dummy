#include "TPoint.h"

// Point data = p4
void PRINT_REF(Point& pData)
{
	//pData.SetPosition(100, 100);
	cout << pData.GetX() << " " << pData.GetY() <<
		" " << pData.GetString() << endl;
}
void PRINT_POINT(Point* pData)
{
	//pData->SetPosition(100, 100);
	cout << pData->GetX() << " " << pData->GetY() <<
		" " << pData->GetString() << endl;
}
void PRINT(Point pData)
{
	pData.SetPosition(100, 100);
	cout << pData.GetX() << " " << pData.GetY() <<
		" " << pData.GetString() << endl;
}
void main()
{
	{
		//인스턴스(메모리 실체)
		Point* p1 = 0;
		SAFE_NEW(p1, Point);
		//p1.SetPosition(10, 10);
		cout << p1->GetX() << p1->GetY();
		p1->SetString("KGCA");
		p1->Show();
		SAFE_DEL(p1);		
	}
	//인스턴스(메모리 실체)
	Point p2(20, 20);
	//p1.SetPosition(10, 10);
	cout << p2.GetX() << p2.GetY();
	p2.SetString("KGCA");
	p2.Show();

	Point p3(30, 30, "GAME");	
	cout << p3.GetX() << p3.GetY() << p3.GetString();
	p3.Show();

	// m_iX, m_iY, char* m_pszData = new
	Point p4 = p3;
	cout << p4.GetX() << p4.GetY() << p4.GetString();

	PRINT_REF(p4);
	PRINT_POINT(&p4);
	PRINT(p4);
	cout << '\n' << Point::g_iCount << "프로그램 종료";
	cout << '\n' << p4.GetCount() << "프로그램 종료";
}