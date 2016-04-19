#include <windows.h>
#include <tchar.h>
#include "KMain.h"
#include "tinyxml2.h"

#include <list>
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

list<KImageRect> g_rtImage;

void tinyxml2Parse(const XMLAttribute* firstAttr, unsigned int indent)
{
	XMLAttribute* attr;
	KImageRect temp;

	for (attr = (XMLAttribute*)firstAttr; attr != 0; attr = (XMLAttribute*)attr->Next()) {

		if (strcmp(attr->Name(), "name") == 0) {
			strcpy_s(temp.m_szName, attr->Value());
		}
		else if (strcmp(attr->Name(), "x") == 0) {
			temp.m_iX = atoi(attr->Value());
		}
		else if (strcmp(attr->Name(), "y") == 0) {
			temp.m_iY = atoi(attr->Value());
		}
		else if (strcmp(attr->Name(), "width") == 0) {
			temp.m_iWidth = atoi(attr->Value());
		}
		else if (strcmp(attr->Name(), "height") == 0) {
			temp.m_iHeight = atoi(attr->Value());

			g_rtImage.push_back(temp);

			memset(&temp, 0, sizeof(temp));
		}
		else { continue; }


	}
}



void tinyxml2Parse(const XMLNode* parent, unsigned int indent = 0)
{
	if (!parent) return;

	XMLNode* child;

	XMLDeclaration* decl;
	XMLElement* elem;
	XMLComment* comm;
	XMLAttribute* attr;
	XMLText* text;

	for (child = (XMLNode*)parent->FirstChild(); child != 0; child = (XMLNode*)child->NextSibling()) {
		
		decl = child->ToDeclaration();
		elem = child->ToElement();
		comm = child->ToComment();
									   
		if (elem) {
			attr = (XMLAttribute*)elem->FirstAttribute();
			if (attr) tinyxml2Parse(attr, indent + 1);
		}
		tinyxml2Parse(child, indent + 1);
	}
}

void tinyxml2Parse(const char* filename)
{
	TINYXMLDocument doc;
	if (XML_NO_ERROR == doc.LoadFile(filename)) {
		//printf("\n<Document> %s:\n", filename);
		tinyxml2Parse(&doc);
	}
	else {
		//printf("Failed to open: %s\n", filename);
	}
}




void     KMain::MsgEvent(MSG msg)
{
	m_Input.MsgEvent(msg);
};
bool KMain::Init()
{
	m_Timer.Init();
	m_Input.Init();

	tinyxml2Parse("data/sheet.xml");

	g_rtImage.max_size();

	return true;
}
bool KMain::Frame()
{
	m_Timer.Frame();
	m_Input.Frame();

	if (m_Input.KeyCheck('W') == KEY_PUSH)
	{
		MessageBox(m_hWnd, L"W KEY_UP", L"KeyState", MB_OK);
	}
	if (m_Input.KeyCheck('S') == KEY_PUSH)
	{
		MessageBox(m_hWnd, L"S click", L"KeyState", MB_OK);
	}
	if (m_Input.KeyCheck('A') == KEY_PUSH)
	{
		MessageBox(m_hWnd, L"A click", L"KeyState", MB_OK);
	}
	if (m_Input.KeyCheck('D') == KEY_PUSH)
	{
		MessageBox(m_hWnd, L"D click", L"KeyState", MB_OK);
	}
	return true;
}
bool KMain::Render()
{
	m_Timer.Render();
	m_Input.Render();
	HDC hdc = GetDC(this->m_hWnd);
	//SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, 0, 0, m_Timer.m_csBuffer,
		_tcslen(m_Timer.m_csBuffer));
	TextOut(hdc, 0, 25, m_Input.m_csBuffer,
		_tcslen(m_Input.m_csBuffer));
	ReleaseDC(m_hWnd, hdc);
	return true;
}
bool KMain::Release()
{
	m_Timer.Release();
	m_Input.Release();
	return true;
}

int WINAPI wWinMain(
	HINSTANCE hInstatnce,
	HINSTANCE hPrevInstatnce,
	LPWSTR   lpCmdLine,
	int      nCmdShow)
{
	KMain win;
	//win.SetRect(1024, 768);
	if (win.SetWindow(hInstatnce) == true)
	{
		win.Run();
	}
	return 0;
}


KMain::KMain() {}
KMain::~KMain() {}