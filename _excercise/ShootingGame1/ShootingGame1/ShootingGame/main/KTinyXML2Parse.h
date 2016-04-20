#pragma once
#include "tinyxml2.h"

#include <vector>
#include <memory.h>

using namespace tinyxml2;
using namespace std;

class KImageRect {
public:
	char m_szName[256];
	int m_iX;
	int m_iY;
	int m_iWidth;
	int m_iHeight;
public:
	KImageRect() {};
	~KImageRect() {};
};



class KTinyXML2Parse
{
public:
	friend void tinyxml2Parse(const XMLAttribute* firstAttr, unsigned int indent);
	friend void tinyxml2Parse(const XMLNode* parent, unsigned int indent = 0);
	friend void tinyxml2Parse(const char* filename);

public:
	KTinyXML2Parse();
	virtual ~KTinyXML2Parse();
};

