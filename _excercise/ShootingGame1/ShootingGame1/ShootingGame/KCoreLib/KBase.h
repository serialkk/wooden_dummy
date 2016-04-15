#pragma once
#include "KStd.h"
class KBase
{
public:
	virtual bool     Init() = 0; // �ʱ�ȭ
	virtual bool     Frame() = 0;// ���
	virtual bool     Render() = 0;// ��ο�
	virtual bool     Release() = 0;// ����, �Ҹ�
public:
	KBase();
	virtual ~KBase();
};

