#include "..\\..\\..\\stdafx.h"
#include "Player.h"
#include "..//..//Manager//CKeyMgr//CKeyMgr.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };

	m_fSpeed = 5.f;
}

void CPlayer::Update(void)
{
	//m_tInfo.vPos += m_tInfo.vDir;
	D3DXVECTOR3 vec = { 0.0, 0.0, 0.0 };


	if(KEY_STATE::HOLD == CKeyMgr::Get_Instance()->Get_Key_State(KEY::LEFT))
	{
		D3DXVECTOR3 vec = { -1, 0.0, 0.0 };
		m_tInfo.vPos += vec * m_fSpeed;
	}

	if (KEY_STATE::HOLD == CKeyMgr::Get_Instance()->Get_Key_State(KEY::RIGHT))
	{
		D3DXVECTOR3 vec = { 1, 0.0, 0.0 };
		m_tInfo.vPos += vec * m_fSpeed;
	}

	if (KEY_STATE::HOLD == CKeyMgr::Get_Instance()->Get_Key_State(KEY::UP))
	{
		D3DXVECTOR3 vec = { 0.0, -1, 0.0 };
		m_tInfo.vPos += vec * m_fSpeed;
	}

	if (KEY_STATE::HOLD == CKeyMgr::Get_Instance()->Get_Key_State(KEY::DOWN))
	{
		D3DXVECTOR3 vec = { 0.0, 1, 0.0 };
		m_tInfo.vPos += vec * m_fSpeed;
	}
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, 
		int(m_tInfo.vPos.x - 50.f),
		int(m_tInfo.vPos.y - 50.f),
		int(m_tInfo.vPos.x + 50.f),
		int(m_tInfo.vPos.y + 50.f));
}

void CPlayer::Release(void)
{
	
}

void CPlayer::OnCollisionBegin(CCollider* _pOther)
{
}

void CPlayer::OnCollision(CCollider* _pOther)
{
}

void CPlayer::OnCollisionEnd(CCollider* _pOther)
{
}

void CPlayer::Key_Input(void)
{
	/*if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
	}*/
	
	// GetKeyState()
}
