#pragma once
#include "KNetwork.h"
class KAsyncSelect : public KNetwork
{

public:
	bool		Connect(char* ip, int iPort);
	void		MsgEvent(MSG msg);
public:
	KAsyncSelect();
	virtual ~KAsyncSelect();
};

