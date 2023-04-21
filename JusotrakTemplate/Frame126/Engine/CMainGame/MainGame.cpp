#include "stdafx.h"
#include "MainGame.h"

#include "Engine//CObject//CPlayer//Player.h"
#include "Engine//CObject//CMonster//Monster.h"

#include "Engine//Manager//CKeyMgr//CKeyMgr.h"
#include "Engine//Manager//CTimeMgr//CTimeMgr.h"
#include "Engine//Manager//CEventMgr//CEventMgr.h"
#include "Engine//Manager//CSceneMgr//CSceneMgr.h"
#include "Engine//Manager//CCollisionMgr//CCollisionMgr.h"

CMainGame::CMainGame()
	: m_pPlayer(nullptr)
	, m_pMonster(nullptr)
	, m_memDC(0)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(HWND _hwnd)
{
	m_hwnd = _hwnd;
	m_DC = GetDC(m_hwnd);

	HBITMAP hNewBitMap = CreateCompatibleBitmap(m_DC, WINCX, WINCY);
	m_memDC = CreateCompatibleDC(m_DC);
	DeleteObject(SelectObject(m_memDC, hNewBitMap));

	CTimeMgr::Get_Instance()->Initialize();
	CKeyMgr::Get_Instance()->Initialize();
	CSceneMgr::Get_Instance()->Initialize();
}

void CMainGame::Update(void)
{
	CTimeMgr::Get_Instance()->Update();
	CKeyMgr::Get_Instance()->Update();

	CSceneMgr::Get_Instance()->Update();
	CCollisionMgr::Get_Instance()->Update();
	CCollisionMgr::Get_Instance()->Update_Late();

	CEventMgr::Get_Instance()->Update();
}

void CMainGame::Render(void)
{
	Rectangle(m_memDC, 0, 0, WINCX, WINCY);
	CSceneMgr::Get_Instance()->Render(m_memDC);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, m_memDC, 0, 0, SRCCOPY);
}

void CMainGame::Release(void)
{
	Safe_Delete<CObject*>(m_pMonster);
	Safe_Delete<CObject*>(m_pPlayer);
	ReleaseDC(m_hwnd, m_DC);

	CTimeMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CCollisionMgr::Get_Instance()->Destroy_Instance();
	CEventMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();

}
