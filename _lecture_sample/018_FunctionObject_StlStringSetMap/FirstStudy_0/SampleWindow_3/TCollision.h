#pragma once
#include "TStd.h"
struct TSphere
{
	POINT ptCenter;
	float fRadius;
};
class TCollision
{
public:
	friend bool     RectInPt(RECT& rt, POINT& pt);
	friend bool     RectInPt(TRect& rt, POINT& pt);
	friend bool     RectInRect(RECT& rtDesk,
		RECT& rtSrc);
	friend bool	 SphereInSphere(TSphere& s1,
		TSphere& s2);
	friend bool	 SphereInSphere(RECT& s1,
		RECT& s2);
	friend bool     RectInRect(TRect& s1, TRect& s2);
public:
	TCollision();
	virtual ~TCollision();
};

