#pragma once
#include "TBase.h"
class TTimer : public TBase
{
public:
	bool     Init(); // �ʱ�ȭ
	bool     Frame();// ���
	bool     Render();// ��ο�
	bool     Release();// ����, �Ҹ�
public:
	TTimer();
	virtual ~TTimer();
};

