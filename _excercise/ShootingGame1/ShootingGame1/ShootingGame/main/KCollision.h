#pragma once
#include "KStd.h"
struct KSphere
{
	POINT ptCenter;
	float fRadius;
};
class KCollision
{
public:
	friend bool     RectInPt(RECT& rt, POINT& pt);
	friend bool     RectInPt(KRect& rt, POINT& pt);
	friend bool     RectInRect(RECT& rtDesk,
		RECT& rtSrc);
	friend bool	 SphereInSphere(KSphere& s1,
		KSphere& s2);
	friend bool	 SphereInSphere(RECT& s1,
		RECT& s2);
	friend bool     RectInRect(KRect& s1, KRect& s2);
public:
	KCollision();
	virtual ~KCollision();
};

