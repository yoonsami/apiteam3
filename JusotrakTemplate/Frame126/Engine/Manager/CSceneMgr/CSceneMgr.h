#pragma once

enum class SCENE_TYPE
{
	STAGE_01,
	STAGE_02,
	STAGE_03,
	STAGE_04,
	END,
};

class CScene;

class CSceneMgr
{
private:
	static CSceneMgr*	m_pInstance;
	CScene*				m_pCurScene;
	CScene*				m_arrScene[(UINT)SCENE_TYPE::END];

public:
	CScene* Get_Cur_Scene() { return m_pCurScene; }
	void	Set_Cur_Scene(CScene* _pScene) { m_pCurScene = _pScene; }
	void	Change_Scene(SCENE_TYPE _eType);

public:
	void	Initialize();
	void	Update();
	void	Render(HDC);

public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
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

private:
	CSceneMgr();
	~CSceneMgr();
};

