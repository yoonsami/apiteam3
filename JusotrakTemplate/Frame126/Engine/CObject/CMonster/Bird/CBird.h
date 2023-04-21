#pragma once
#include "..//Monster.h"

class CBird :
    public CMonster
{
public:
	CBird();
	virtual ~CBird();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void OnCollisionBegin(CCollider* _pOther) override;
	virtual void OnCollision(CCollider* _pOther) override;
	virtual void OnCollisionEnd(CCollider* _pOther) override;

private:
	void		 Cal_WorldMat();
	D3DXVECTOR3		m_vVertex[9]{};
	float			m_fDir = 1.f;
};

