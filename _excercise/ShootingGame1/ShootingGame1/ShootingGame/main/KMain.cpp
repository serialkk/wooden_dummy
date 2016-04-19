#include "KMain.h"
#include "KSys.h"
#include "KBitmapMgr.h"
#include "KCollision.h"

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

bool	 KMain::Init()
{

	tinyxml2Parse("data/sheet.xml");

	g_rtImage.max_size();

	m_pSound.Init();
	int iIndex  = m_pSound.Load("../../data/OnlyLove.mp3");
	m_pSound.Play(iIndex, true);

	iIndex = m_pSound.Load("../../data/Gun1.wav");
	iIndex = m_pSound.Load("../../data/Gun2.wav");	

	m_BackGround.SetPos(0, 0, 0.0f);
	m_BackGround.SetRect(0, 0, 800, 600);
	m_Hero.SetPos(100, 100, 100.0f);
	m_Hero.SetRect(90, 1, 42, 60);

	m_BackGround.Load(m_hScreenDC,
		m_hOffScreenDC, L"../../data/bk.bmp");
	m_Hero.Load(m_hScreenDC,
		m_hOffScreenDC, L"../../data/Bitmap1.bmp");

	for (int iObj = 0; iObj < MAX_OBJECT; iObj++)
	{
		m_Object[iObj].SetPos(
			rand() % m_rtClient.right/2,
			rand() % m_rtClient.bottom/2, 
			50.0f + rand() % 100);
		m_Object[iObj].SetRect(46, 62, 68, 79);
		m_Object[iObj].Load(m_hScreenDC,
			m_hOffScreenDC, L"../../data/Bitmap1.bmp");

	}
	return true;
};
bool	 KMain::Frame()
{
	if (m_Input.KeyCheck(VK_HOME) == KEY_PUSH)
	{
		m_pSound.Stop(0);
	}
	if (m_Input.KeyCheck(VK_END) == KEY_PUSH)
	{
		m_pSound.Paused(0);
	}
	if (m_Input.KeyCheck(VK_INSERT) == KEY_HOLD)
	{
		m_pSound.Volume(0, g_fSecondPerFrame , true);
	}
	if (m_Input.KeyCheck(VK_DELETE) == KEY_HOLD)
	{
		m_pSound.Volume(0, g_fSecondPerFrame, false);
	}

	if (m_Input.KeyCheck('W') == KEY_HOLD)
	{
		m_Hero.Up();
	}
	if (m_Input.KeyCheck('S') == KEY_HOLD)
	{
		m_Hero.Down();
	}
	if (m_Input.KeyCheck('A') == KEY_HOLD)
	{
		m_Hero.Left();
	}
	if (m_Input.KeyCheck('D') == KEY_HOLD)
	{
		m_Hero.Right();
	}
	m_Hero.Frame();

	for (int iObj = 0; iObj < MAX_OBJECT; iObj++)
	{
		m_Object[iObj].Frame();
	}
	for (int iObj = 0; iObj < MAX_OBJECT; iObj++)
	{
		if (m_Input.m_dwMouseState[0] == TRUE
			&& m_Object[iObj].m_bUsed ==true)
		{
			
			if (RectInPt( m_Object[iObj].m_rtCollide, 
				      m_Input.m_MovePt))
			{
				m_Object[iObj].m_bUsed = false;
				OutputDebugString(L"Frame\n");
			}
		}
	}
	for (int iObj = 0; iObj < MAX_OBJECT; iObj++)
	{
		if ( m_Object[iObj].m_bUsed == true)
		{
			if (RectInRect(m_Object[iObj].m_rtCollide,
				m_Hero.m_rtCollide))
			{
				//m_pSound.Play(1, true);
				m_Object[iObj].m_bUsed = false;
			}
		}
	}
	
	
	/*if (m_Input.KeyCheck(VK_SPACE) == KEY_HOLD)
	{
		m_Hero.SetSpeed(30.0f);
	}
	else
	{
		m_Hero.SetSpeed(-100.0f);
	}*/
	return true;
};
bool	 KMain::Render() {
	m_BackGround.Draw();
	for (int iObj = 0; iObj < MAX_OBJECT; iObj++)
	{
		m_Object[iObj].Render();
	}
	m_Hero.Render();
	return true;
};
bool	 KMain::Release()
{	
	KBitmapMgr::GetInstance().Release();
	m_BackGround.Release();
	m_Hero.Release();
	for (int iObj = 0; iObj < MAX_OBJECT; iObj++)
	{
		m_Object[iObj].Release();
	}
	return true;
};

KMain::KMain()
{
	m_iX = 0;
	m_iY = 0;
}


KMain::~KMain()
{
}
int WINAPI wWinMain(
	HINSTANCE hInstatnce,
	HINSTANCE hPrevInstatnce,
	LPWSTR   lpCmdLine,
	int      nCmdShow)
{
	KMain win;
	if (win.SetWindow(hInstatnce) == true)
	{
		win.Run();
	}
	return 0;
}