#pragma once
#include "..//..//..//CObject.h"
class CPlayer_JYS;

class CAim :
    public CObject
{
    friend class CPlayer_JYS;
	friend class CEventMgr;
public:
    CAim();
    virtual ~CAim();

private:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void OnCollisionBegin(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionEnd(CCollider* _pOther) override;
	void		 Cal_WorldMat();
	void		 Fire_Bullet(float FirePower);

private:
	CPlayer_JYS* m_pOwner = nullptr;

	D3DXVECTOR3 m_vVertex[4]{};
	float m_fDirTheta = 0.f;
};

