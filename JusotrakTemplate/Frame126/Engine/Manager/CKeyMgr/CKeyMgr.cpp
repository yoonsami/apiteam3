#include "..//..//..//stdafx.h"
#include "CKeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

int g_arrVK[(int)KEY::LAST + 1] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q','W','E','R','T','Y','U','I','O','P',
	'A','S','D','F','G',
	'Z','X','C','V','B',
	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,
	VK_LBUTTON,
	VK_RBUTTON
};

CKeyMgr::CKeyMgr()
	: m_vCurMousePos{0, 0, 0}
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::Initialize()
{
	for (size_t i = 0; i < (size_t)KEY::LAST; ++i)
	{
		m_arrKey[i].eState = KEY_STATE::NONE;
		m_arrKey[i].bPrevTap = false;
	}
}

void CKeyMgr::Update()
{
	HWND hWnd = GetFocus();

	// �����찡 ��Ŀ�� ���� ����
	if (nullptr != hWnd)
	{
		for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_arrKey[i].bPrevTap)
					m_arrKey[i].eState = KEY_STATE::HOLD;
				else
					m_arrKey[i].eState = KEY_STATE::TAP;

				m_arrKey[i].bPrevTap = true;
			}
			else
			{
				if (m_arrKey[i].bPrevTap)
					m_arrKey[i].eState = KEY_STATE::AWAY;
				else
					m_arrKey[i].eState = KEY_STATE::NONE;

				m_arrKey[i].bPrevTap = false;
			}
		}
	}
	else
	{
		for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{
			if (m_arrKey[i].eState == KEY_STATE::TAP || m_arrKey[i].eState == KEY_STATE::HOLD)
				m_arrKey[i].eState = KEY_STATE::AWAY;
			else if (m_arrKey[i].eState == KEY_STATE::AWAY)
				m_arrKey[i].eState = KEY_STATE::NONE;
			m_arrKey[i].bPrevTap = false;
		}
	}


	//Mouse ��ġ ���
	POINT ptPos = {};
	GetCursorPos(&ptPos);
	//��ü ������, �� ���÷��� ��ü ���ؿ��� ��ǥ�� ��ȯ����.

	ScreenToClient(g_hWnd, &ptPos);
	//��ü ���÷��̿��� ���� ������ â��
	//�������� ���� ��ǥ

	m_vCurMousePos = { (float)ptPos.x, (float)ptPos.y , 0};

}

KEY_STATE CKeyMgr::Get_Key_State(KEY _eKey)
{
	return m_arrKey[(size_t)_eKey].eState;
}

D3DXVECTOR3 CKeyMgr::Get_Mouse_Pos()
{

	return m_vCurMousePos;
}
