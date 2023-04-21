#pragma once
#include "..//Player.h"

class CAim;
class CGauge;

class CPlayer_JYS :
    public CPlayer
{

public:
    CPlayer_JYS();
    ~CPlayer_JYS();

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
private:
	void		Key_Input(void);
	D3DXVECTOR3 m_vVertex[4]{};
	D3DXVECTOR3 m_vVel{};
	D3DXVECTOR3 m_vAcc{};
	CAim*		m_tAim = nullptr;
	float		m_fFirePower = 0.f;
	float		m_fPowerPerSec = 500.f;
	bool		m_bCharging = false;
	bool		m_bFlying = false;
	CGauge*		m_pGauge = nullptr;
	float		m_fLookRadian = 0.f;
};

