#pragma once
#include "..//..//..//CObject.h"
class CGauge :
    public CObject
{
	friend class CPlayer_JYS;
	friend class CAim;
public:
    CGauge();
    virtual ~CGauge();

private:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void OnCollisionBegin(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionEnd(CCollider* _pOther) override;
	void		 Cal_WorldMat();
	void		 Accelarate();
	void		 Set_Vel() { m_vVel = m_tInfo.vDir * m_fGauge; }

	CPlayer_JYS* m_pOwner = nullptr;
	D3DXVECTOR3 m_vVertex[4]{};
	D3DXVECTOR3 m_vGaugePoint[2]{};
	D3DXVECTOR3	m_vVel{};
	float		m_fGauge = 0.f;
	bool		m_bFired = false;
};

