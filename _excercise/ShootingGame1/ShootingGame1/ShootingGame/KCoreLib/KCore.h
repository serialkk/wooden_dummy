#pragma once
#include "KWindow.h"
class KCore : public KWindow
{
public:
	virtual bool Init(); //�ʱ�ȭ
	virtual bool Frame();//���
	virtual bool Render();//��ο�
	virtual bool Release();//����, �Ҹ�
public:
	bool Run();
	bool GameRun();
	bool GameInit();
	bool GameFrame();
	bool GameRender();
	bool GameRelease();
public:
	KCore();
	virtual ~KCore();
};

