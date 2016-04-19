//#define _CRT_SECURE_NO_WARNINGS
#include "Sample.h"
#include "TSys.h"
#include <iostream>
#include "TSpriteMgr.h"

bool Sample::Init()
{
	LoadSprite(L"Sprite.txt");

	int iIndex = I_Sprite.Load(L"TypeA",
		L"../../data/bitmap1.bmp",
		L"../../data/bitmap2.bmp");	
	TSprite* pSprite = I_Sprite.Find(iIndex);
	pSprite->SetRectArray(m_SpriteList[0], 2.0f);
	
	iIndex = I_Sprite.Load(L"TypeB",
		L"../../data/bitmap1.bmp",
		L"../../data/bitmap2.bmp");
	pSprite = I_Sprite.Find(iIndex);
	pSprite->SetRectArray(m_SpriteList[1], 1.0f);

	iIndex = I_Sprite.Load(L"TypeC",
		L"../../data/bitmap1.bmp",
		L"../../data/bitmap2.bmp");
	pSprite = I_Sprite.Find(iIndex);
	pSprite->SetRectArray(m_SpriteList[2], 1.0f);

	m_Hero.Load(L"../../data/bitmap1.bmp",
				L"../../data/bitmap2.bmp");
	m_Effect.SetSprite(0);
	return true;
}
//void Sample::SetSprite(int iIndex, float fLifeTime)
//{
//	m_iSpriteID = iIndex;
//	m_fLifeTime = fLifeTime;
//	int iFrame = m_SpriteList[m_iSpriteID].size();
//	m_fSecPerRender = m_fLifeTime / iFrame;
//	m_Bitmap.m_Position.x = 400;
//	m_Bitmap.m_Position.y = 300;
//	m_iFrame = 0;
//	m_fTimer = 0.0f;	
//}
bool Sample::Frame()
{
	/*if (m_Input.KeyCheck('0') == KEY_PUSH)
	{
		SetSprite(0);
	}
	if (m_Input.KeyCheck('1') == KEY_PUSH)
	{
		SetSprite(1);
	}
	if (m_Input.KeyCheck('2') == KEY_PUSH)
	{
		SetSprite(2);
	}*/
	
	//m_Bitmap.m_rtDraw = m_SpriteList[m_iSpriteID][m_iFrame];
	return true;
}
bool Sample::Render()
{
	for (int iEffect = 0; iEffect < m_EffectList.size(); iEffect++)
	{
		m_EffectList[iEffect]->Frame();
		m_EffectList[iEffect]->Render();
	}
	return true;
}
bool Sample::LoadSprite(TCHAR* pFileName)
{
	TCHAR pBuffer[256] = { 0 };
	TCHAR pTemp[256] = { 0 };

	FILE* fp;
	_wfopen_s(&fp, pFileName, _T("rt"));
	if (fp == NULL) return false;

	int iNumSprite = 0;
	_fgetts(pBuffer, _countof(pBuffer), fp);
	_stscanf_s(pBuffer, _T("%s%d"),
		pTemp, _countof(pTemp), &iNumSprite);	
	
	m_SpriteList.resize(iNumSprite);	
	// *m_SpriteList[3]

	int iNumFrame = 0;
	for (int iSprite = 0; iSprite < iNumSprite; iSprite++)
	{
		_fgetts(pBuffer, _countof(pBuffer), fp);
		_stscanf_s(pBuffer, _T("%s%d"),
			pTemp, _countof(pTemp), &iNumFrame);

		int iNumber;
		m_SpriteList[iSprite].resize(iNumFrame);
		// m_SpriteList[0][iNumFrame]
		// m_SpriteList[1][?]
		// m_SpriteList[2][?]
		for(int iFrame= 0; iFrame < iNumFrame; iFrame++)
		{
			RECT rt;
			_fgetts(pBuffer, _countof(pBuffer), fp);
			_stscanf_s(pBuffer, _T("%d %d%d%d%d"),
				&iNumber, 
				&rt.left, &rt.top, &rt.right, &rt.bottom);
			// 메모리가 부족하면 재할당을 통해서 저장한다.
			//m_SpriteList.push_back(rt);
			m_SpriteList[iSprite][iFrame] = rt;
		}
	}
	fclose(fp);
	return true;
}

Sample::Sample()
{

}


Sample::~Sample()
{
}
int WINAPI wWinMain(
	HINSTANCE hInstatnce,
	HINSTANCE hPrevInstatnce,
	LPWSTR   lpCmdLine,
	int      nCmdShow)
{
	Sample win;
	//win.SetRect(1024, 768);
	if (win.SetWindow(hInstatnce) == true)
	{
		win.Run();
	}
	return 0;
}