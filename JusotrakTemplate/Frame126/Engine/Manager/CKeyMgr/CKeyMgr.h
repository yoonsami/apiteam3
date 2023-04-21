#pragma once

enum class KEY_STATE
{
	NONE,	//������ �ʾҰ�, �������� ������ ���� ����
	TAP,	//�� ���� ����
	HOLD,	//������ �ִ�
	AWAY,	//�� �� ����
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G,
	Z, X, C, V, B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST,
};

struct tKeyInfo {
	KEY_STATE	eState;
	bool		bPrevTap;

	tKeyInfo() { eState = KEY_STATE::NONE; bPrevTap = false; }
};

class CKeyMgr
{
	

private:
	static CKeyMgr*		m_pInstance;
	tKeyInfo			m_arrKey[(int)KEY::LAST];
	D3DXVECTOR3			m_vCurMousePos;

public:
	static CKeyMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CKeyMgr;
		}

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void			Initialize();
	void			Update();

public:
	KEY_STATE		Get_Key_State(KEY);
	D3DXVECTOR3		Get_Mouse_Pos();

private:
	CKeyMgr();
	~CKeyMgr();
};
