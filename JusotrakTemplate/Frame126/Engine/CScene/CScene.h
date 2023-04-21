#pragma once

class CObject;

class CScene
{
protected:
	vector<CObject*> m_vecObj[(UINT)GROUP_TYPE::END];

public:
	vector<CObject*>& Get_Group_Object(GROUP_TYPE _eType) { return m_vecObj[(UINT)_eType]; }
	void Add_Object(GROUP_TYPE _eType, CObject* _obj) { m_vecObj[(UINT)_eType].push_back(_obj); }
	void Delete_Group_Object(GROUP_TYPE _eType, CObject* _obj);

public:
	virtual void Update();
	virtual void Render(HDC);

public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	CScene();
	virtual ~CScene();

};

