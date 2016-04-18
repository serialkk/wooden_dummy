#include "TRegion.h"

void main()
{
	TRegion   rectA, rectB, rectC, rectD;
	rectA.SetRect(10, 10, 100, 100);
	rectA.Show();

	Point a;
	a.Set(&rectA);
	a.m_pRegion->GetLeft();

	//rectA.Resize(40, 40);
	//rectA.Show();
	rectB.SetRect(50, 50, 120, 120);
	rectB.Show();

	rectC.UnionRegion(rectA, rectB);
	rectC.Show();

	if (rectD.IntersectRegion(rectA, rectB))
	{
		rectD.Show();
	}

	TRegion   rectE,rectF;
	Point p1, p2;
	p1.SetPosition(10, 10);
	p2.SetPosition(100, 100);
	rectE.SetRect(p1, p2);
	rectE.Show();

	const Point& p6 = p1;
	rectF.SetRect(p6, p2);

	rectF.SetRect(&p1, &p2);
	rectF.Show();
}