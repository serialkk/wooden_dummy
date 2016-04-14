#include <iostream> 
#define _cplusplus
#ifndef _cplusplus
	struct Point
	{
		int x;
		int y;
	};
	void SetPosition(Point* pPoint, int iX,int iY)
	{
		pPoint->x = iX;
		pPoint->y = iY;
	}
	void Show(Point* pPoint)
	{
		printf("\n%d,%d", pPoint->x, pPoint->y);
	}
	void main()
	{
		Point p1;
		SetPosition(&p1, 10, 10);
		Show(&p1);
	}
#else
	struct Point
	{	
		int x;
		int y;
		void SetPosition(int iX, int iY);
		void Show();
	};
	void Point::SetPosition(int iX, int iY)
	{
		x = iX;
		this->y = iY;
	}
	void Point::Show()
	{
		printf("\n%d,%d", x, y);
	}
	void main()
	{
		Point p1;
		p1.SetPosition(10, 10);
		p1.Show();
	}
#endif