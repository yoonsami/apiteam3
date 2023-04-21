#pragma once
class CTimeMgr
{
private:
	static CTimeMgr*	m_pInstance;
	LARGE_INTEGER		m_llCurCount;
	LARGE_INTEGER		m_llPrevCount;
	LARGE_INTEGER		m_llFreq;
	UINT				m_uiFPS;
	double				m_dDeltaTime;
	double				m_dAccTime;

public:
	double	Get_DeltaTime() { return m_dDeltaTime; }
	float	Get_fDeltaTime() { return (float)m_dDeltaTime; }
	UINT	Get_FPS() { return m_uiFPS; }

public:
	void Initialize();
	void Update();
	
public:
	static CTimeMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CTimeMgr;
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
	CTimeMgr();
	~CTimeMgr();
};

