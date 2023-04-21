#pragma once

class CCollider;

union COLLIDER_ID {
	struct {
		UINT LeftID;
		UINT RightID;
	};
	ULONGLONG ID;
};


class CCollisionMgr
{
private:
	int						m_arrCollisionCheck[(UINT)GROUP_TYPE::END];
	static CCollisionMgr*	m_pInstance;
	map<ULONGLONG, bool>	m_mapColInfo;

public:
	static CCollisionMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CCollisionMgr;
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
	void Initialize();
	void Update();
	void Update_Late();
	void Check_Group(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollisionByRectangle(CCollider* _ptLeftCol, CCollider* _ptRightCol);
	void Collision_Group_Update(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset_Collision_Group();

private:
	CCollisionMgr();
	~CCollisionMgr();
};

