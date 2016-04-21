#include "KCollision.h"
bool     RectInRect(KRect& s1,
	KRect& s2)
{
	POINT cS1, cS2;
	cS1.x = (s1.w + s1.x) / 2;
	cS1.y = (s1.y + s1.h) / 2;
	cS2.x = (s2.w + s2.x) / 2;
	cS2.y = (s2.y + s2.h) / 2;

	POINT  Radius, RadiusS1, RadiusS2;
	Radius.x = abs(cS1.x - cS2.x);
	Radius.y = abs(cS1.y - cS2.y);

	RadiusS1.x = (s1.w - s1.x) / 2;
	RadiusS1.y = (s1.h - s1.y) / 2;
	RadiusS2.x = (s2.w - s2.x) / 2;
	RadiusS2.y = (s2.h - s2.y) / 2;

	if (Radius.x <= (RadiusS1.x + RadiusS2.x) &&
		Radius.y <= (RadiusS1.y + RadiusS2.y))
	{
		return true;
	}
	return false;
}
bool     RectInPt(KRect& rt, POINT& pt)
{
	if (rt.x <= pt.x && rt.w >= pt.x)
	{
		if (rt.y <= pt.y && rt.h >= pt.y)
		{
			return true;
		}
	}
	return false;
};
bool     RectInPt(RECT& rt, POINT& pt)
{
	if (rt.left <= pt.x && rt.right >= pt.x)
	{
		if (rt.top <= pt.y && rt.bottom >= pt.y)
		{
			return true;
		}
	}
	return false;
};
bool     RectInRect(RECT& rtDesk,
	RECT& rtSrc)
{
	// ����
	POINT  cDesk, cSrc, Radius, DeskRadius, SrcRadius;
	cDesk.x = (rtDesk.left + rtDesk.right) / 2;
	cDesk.y = (rtDesk.top + rtDesk.bottom) / 2;
	cSrc.x = (rtSrc.left + rtSrc.right) / 2;
	cSrc.y = (rtSrc.top + rtSrc.bottom) / 2;
	Radius.x = abs(cDesk.x - cSrc.x);
	Radius.y = abs(cDesk.y - cSrc.y);
	DeskRadius.x = (rtDesk.right - rtDesk.left) / 2;
	DeskRadius.y = (rtDesk.bottom - rtDesk.top) / 2;
	SrcRadius.x = (rtSrc.right - rtSrc.left) / 2;
	SrcRadius.y = (rtSrc.bottom - rtSrc.top) / 2;
	if (Radius.x <= (DeskRadius.x + SrcRadius.x) &&
		Radius.y <= (DeskRadius.y + SrcRadius.y))
	{
		return true;
	}
	return false;
};
bool	 SphereInSphere(KSphere& s1,
	KSphere& s2)
{
	float fDistanceRadius = s1.fRadius + s2.fRadius;
	float fX = abs(s1.ptCenter.x - s2.ptCenter.x);
	float fY = abs(s1.ptCenter.y - s2.ptCenter.y);
	float fDistanceCenter = 
		sqrt( (fX*fX) + (fY*fY) );
	if (fDistanceCenter  <= fDistanceRadius)
	{
		return true;
	}
	return false;
};
bool	 SphereInSphere(RECT& s1,
	RECT& s2)
{
	POINT cS1, cS2;
	cS1.x = (s1.right + s1.left) / 2;
	cS1.y = (s1.top + s1.bottom) / 2;
	cS2.x = (s2.right + s2.left) / 2;
	cS2.y = (s2.top + s2.bottom) / 2;

	float  fS1, fS2;
	float  fX = s1.right - s1.left;
	float  fY = s1.bottom - s1.top;
	fS1 = (fX > fY) ? fX : fY;
	fX = s2.right - s2.left;
	fY = s2.bottom - s2.top;
	fS2 = (fX > fY) ? fX : fY;

	float fDistanceRadius = fS1/2 + fS2/2;
	fX = abs(cS1.x - cS2.x);
	fY = abs(cS1.y - cS2.y);
	float fDistanceCenter =
		sqrt((fX*fX) + (fY*fY));
	if (fDistanceCenter <= fDistanceRadius)
	{
		return true;
	}
	return false;
};
KCollision::KCollision()
{
}


KCollision::~KCollision()
{
}
