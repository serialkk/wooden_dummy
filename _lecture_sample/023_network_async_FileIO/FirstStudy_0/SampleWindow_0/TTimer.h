#pragma once
#include "TBase.h"
class TTimer : public TBase
{
public:
	bool     Init(); // 초기화
	bool     Frame();// 계산
	bool     Render();// 드로우
	bool     Release();// 삭제, 소멸
public:
	TTimer();
	virtual ~TTimer();
};

