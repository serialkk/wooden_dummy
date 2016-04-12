#include "TRegion.h"

void main()
{
	int * a = new int;
	*a = 0;
	/*const int * const b = a;
	*b = 10;
	int * c = new int;
	b = c;*/

	int x = 10;
	int y = 19;
	const int & d = x;
	const int & j = x;
	j = 100;
	j = y;
	cout << j; 



	TPoint x1(0,0);
	TPoint x2(100, 100);
	

	const TPoint& x4 = x1;
	const TPoint* x5 = &x1;

	const TPoint& x6 = x1.GetRef();
	const TPoint* x7 = x1.Get();

	//TPoint x3 = x1.GetRef();	
	//TPoint& x4 = x1.GetRef();
	//TPoint* x3 = x1.Get();

	//int iX = x6.GetX();
	////int iY = x6.GetY(); // 오류! 비 상수 함수 호출

	//iX = x7->GetX();
	//// iY = x7->GetY(); // 오류! 비 상수 함수 호출
	//iX = x3.GetX();
	//const int iY = x3.GetY();

	//std::cout << x1.x << std::endl;
	////이항 '++': 'TPoint'이(가) 이 연산자를 정의하지 
	////않거나 미리 정의된 연산자에 허용되는 형식으로의 
	////변환을 정의하지 않습니다.
	//++x1;
	//std::cout << x1.x << std::endl;		
	//x1++;
	//std::cout << x1.x << std::endl;
	//x3 = x1 + x2;
	//std::cout << x3.x << std::endl;
	//x3 = x1 + 10;
	//std::cout << x3.x << std::endl;
	//x3 = 10 + x1;
	//std::cout << x3.x << std::endl;
	//x3 += x2;
	//if (x3 == x2)
	//{
	//	std::cout << "같다" << std::endl;
	//}
	//else{
	//	std::cout << "다르다" << std::endl;
	//}
	//TPoint x5(10, 10);
	//std::cout << x5[0] << x5[1] << std::endl;

	//std::cin >> x5;
	//std::cout << x5;

	//const TPoint& p4 = x1;
	//x3 = p4 + 10;
	//


	//TRegion   rectA, rectB, rectC, rectD;
	//rectA.SetRect(10, 10, 100, 100);
	//rectA.Show();
	//rectB.SetRect(50, 50, 120, 120);
	//rectB.Show();

	//bool bFlag = rectA ^ rectB;


	//TPoint a;
	//a.Set(&rectA);
	//a.m_pRegion->GetLeft();

	////rectA.Resize(40, 40);
	////rectA.Show();
	//rectB.SetRect(50, 50, 120, 120);
	//rectB.Show();

	//rectC.UnionRegion(rectA, rectB);
	//rectC.Show();

	//if (rectD.IntersectRegion(rectA, rectB))
	//{
	//	rectD.Show();
	//}

	//TRegion   rectE, rectF;
	//TPoint p1, p2;
	//p1.SetPosition(10, 10);
	//p2.SetPosition(100, 100);
	//rectE.SetRect(p1, p2);
	//rectE.Show();

	//const TPoint& p6 = p1;
	//rectF.SetRect(p6, p2);

	//rectF.SetRect(&p1, &p2);
	//rectF.Show();
}