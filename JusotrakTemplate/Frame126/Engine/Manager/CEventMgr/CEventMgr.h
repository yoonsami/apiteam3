#pragma once
class CObject;

struct tEventMsg {
	EVENT_TYPE eEven;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
	//DWORD_PTR은 빌드 타겟(32bits, or 64bits)에 따라
	//ULONG으로 할지, UINT로 할지 결정됨.
};

class CEventMgr
{
private:
	static CEventMgr*	m_pInstance;
	deque<tEventMsg>	m_deqEvent;
	vector<CObject*>	m_vecDeadObj;

public:
	static CEventMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CEventMgr;
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
	void Execute(const tEventMsg&);

public:
	void Update();
	void AddEvent(const tEventMsg&);

private:
	CEventMgr();
	~CEventMgr();

};
