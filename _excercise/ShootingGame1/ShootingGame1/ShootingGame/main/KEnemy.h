#pragma once
#include "KObject.h"
class KEnemy : public KObject
{
public:
	bool	Frame();
	void	Move(float fMoveX, float fMoveY);
public:
	KEnemy();
	virtual ~KEnemy();
};

