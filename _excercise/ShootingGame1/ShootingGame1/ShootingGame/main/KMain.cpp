#include "KMain.h"
#include "KSys.h"
#include "KBitmapMgr.h"
#include "KCollision.h"
#include "KTinyXML2Parse.h"

extern vector<KImageRect> g_vectorImage;

bool	 KMain::Init()
{

	//sheet.xml�� �̹��� ��ǥ ���� �Ľ���.[start]
	tinyxml2Parse("data/sheet.xml");
	g_vectorImage.max_size();
	//sheet.xml�� �̹��� ��ǥ ���� �Ľ���.[end]

	m_pSound.Init();
	int iIndex  = m_pSound.Load("../../data/OnlyLove.mp3");
	m_pSound.Play(iIndex, true);

	iIndex = m_pSound.Load("../../data/Gun1.wav");
	iIndex = m_pSound.Load("../../data/Gun2.wav");	

	m_BackGround.SetPos(0, 0, 0.0f);
	m_BackGround.SetRect(0, 0, 256, 256);
	m_Hero.SetPos(350, 250, 100.0f);
	
	//m_Hero.SetRect(90, 1, 42, 60);


	for (int i = 0; i < (int)g_vectorImage.size(); i++) 
	{
		if (strcmp(g_vectorImage[i].m_szName, "playerShip1_red.png") == 0) {
			m_Hero.SetRect(g_vectorImage[i].m_iX, g_vectorImage[i].m_iY, g_vectorImage[i].m_iWidth, g_vectorImage[i].m_iHeight);
			break;
		}
	}



	m_BackGround.Load(m_hScreenDC,
		m_hOffScreenDC, L"data/purple.bmp");
	m_Hero.Load(m_hScreenDC,
		m_hOffScreenDC, L"data/SpaceShooterRedux.bmp");

	for (int iObj = 0; iObj < MAX_OBJECT; iObj++)
	{
		m_Object[iObj].SetPos(
			rand() % m_rtClient.right/2,
			rand() % m_rtClient.bottom/2, 
			50.0f + rand() % 100);
		//m_Object[iObj].SetRect(46, 62, 68, 79);
		
		for (int i = 0; i < (int)g_vectorImage.size(); i++)
		{
			if (strcmp(g_vectorImage[i].m_szName, "enemyGreen1.png") == 0) {
				m_Object[iObj].SetRect(g_vectorImage[i].m_iX, g_vectorImage[i].m_iY, g_vectorImage[i].m_iWidth, g_vectorImage[i].m_iHeight);
				break;
			}
		}

		m_Object[iObj].Load(m_hScreenDC,
			m_hOffScreenDC, L"data/SpaceShooterRedux.bmp");

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
		//m_Hero.Up();
		
		m_BackGround.Move(0, g_fSecondPerFrame * 100.0f);
		for (int iObj = 0; iObj < MAX_OBJECT; iObj++){ m_Object[iObj].Move(0,g_fSecondPerFrame * 100.0f); }
	}
	if (m_Input.KeyCheck('S') == KEY_HOLD)
	{
		//m_Hero.Down();
		m_BackGround.Move(0, g_fSecondPerFrame * -100.0f);
		for (int iObj = 0; iObj < MAX_OBJECT; iObj++) { m_Object[iObj].Move(0, g_fSecondPerFrame * -100.0f); }
	}
	if (m_Input.KeyCheck('A') == KEY_HOLD)
	{
		//m_Hero.Left();
		m_BackGround.Move(g_fSecondPerFrame * 100.0f, 0);
		for (int iObj = 0; iObj < MAX_OBJECT; iObj++) { m_Object[iObj].Move(g_fSecondPerFrame * 100.0f,0 ); }
	}
	if (m_Input.KeyCheck('D') == KEY_HOLD)
	{
		//m_Hero.Right();
		m_BackGround.Move(g_fSecondPerFrame * -100.0f, 0);
		for (int iObj = 0; iObj < MAX_OBJECT; iObj++) { m_Object[iObj].Move(g_fSecondPerFrame * -100.0f, 0); }

	}
	m_Hero.Frame();

	for (int iObj = 0; iObj < MAX_OBJECT; iObj++)
	{
		m_Object[iObj].Frame();
	}
	for (int iObj = 0; iObj < MAX_OBJECT; iObj++)
	{
		if (m_Input.m_dwMouseState[0]
			&& m_Object[iObj].m_bUsed ==true)
		{
			
			if (RectInPt(m_Object[iObj].m_rtCollide,
				m_Input.m_MovePt))
			{
				m_Object[iObj].m_bUsed = false;
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