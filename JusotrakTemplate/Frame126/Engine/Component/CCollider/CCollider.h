#pragma once

class CObject;

class CCollider
{
private:
	int				m_iID;
	CObject*		m_pOwner;
	static int		g_iNextID;

	wstring			m_szName;
	D3DXVECTOR3		m_vOffset;
	D3DXVECTOR3		m_vFinalPos;
	D3DXVECTOR3		m_vScale;

public:
	void			SetOwner(CObject* _pOwner) { m_pOwner = _pOwner; }
	void			SetName(wstring _szName) { m_szName = _szName; }
	void			SetOffset(D3DXVECTOR3 _vOffset) { m_vOffset = _vOffset; }
	void			SetScale(D3DXVECTOR3 _vScale) { m_vScale = _vScale; }

	wstring			GetName() { return m_szName; }
	CObject*		GetOwner() { return m_pOwner; }
	int				GetID() { return m_iID; }
	D3DXVECTOR3		GetScale() { return m_vScale; }
	D3DXVECTOR3		GetFinalPos() { return m_vFinalPos; }


public:
	void Update_Final();
	void OnCollisionBegin(CCollider* _pOther);
	void OnCollision(CCollider* _pOther);
	void OnCollisionEnd(CCollider* _pOther);
	void Render(HDC _hdc);
	RECT Get_Rect();

public:
	CCollider();
	~CCollider();
};

