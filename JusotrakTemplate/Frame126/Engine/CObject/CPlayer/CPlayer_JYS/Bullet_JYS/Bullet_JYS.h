#pragma once
#include "..//..//..//CObject.h"
class CBullet_JYS :
    public CObject
{
public:
    CBullet_JYS();
    ~CBullet_JYS();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void OnCollisionBegin(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionEnd(CCollider* _pOther) override;
	void		 Cal_WorldMat();
	void		 Accelarate();
	void		Set_Vel() { m_vVel = m_tInfo.vDir * m_fSpeed; }

private:
	D3DXVECTOR3 m_vVertex[5]{};

	D3DXVECTOR3 m_vVel;

};

