#pragma once

class CCollider;

class CObject abstract
{
public:
	CObject();
	virtual ~CObject();

public:
	const INFO&		Get_Info(void) const { return m_tInfo; }

public:
	virtual void		Initialize(void)PURE;
	virtual void		Update(void)PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release(void)PURE;
	virtual void		OnCollisionBegin(CCollider* _pOther) = 0;
	virtual void		OnCollision(CCollider* _pOther) = 0;
	virtual void		OnCollisionEnd(CCollider* _pOther) = 0;
	// Á¤À±¼º Ãß°¡
	const D3DXVECTOR3&	Get_Scale() const { return m_vScale; }
	void				Set_Pos(const D3DXVECTOR3& pos) { m_tInfo.vPos = pos; }
	D3DXVECTOR3&		Get_Pos() { return m_tInfo.vPos; }
	void				Set_Dir(const D3DXVECTOR3& dir) { m_tInfo.vDir = dir; }
	
	void				Set_Speed(const float& speed) { m_fSpeed = speed; }

public:
	void		Create_Collider();
	CCollider*	Get_Collider() { return m_pCollider; }
	void		Set_Dead(bool _bDead) { m_bDead = _bDead; }
	bool		Is_Dead() { return m_bDead; }

protected:
	INFO			m_tInfo;
	CCollider*		m_pCollider = nullptr;
	float			m_fSpeed;
	bool			m_bDead;

	// Á¤À±¼º Ãß°¡
	D3DXVECTOR3		m_vScale{};
	D3DXVECTOR3		m_vVertex[4]{};
};

