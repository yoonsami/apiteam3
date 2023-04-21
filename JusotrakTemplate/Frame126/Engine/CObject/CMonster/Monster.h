#pragma once

#include "..//CObject.h"

class CMonster 
	: public CObject
{
public:
	CMonster();
	~CMonster();

public:
	void		Set_Player(CObject* pPlayer) { m_pTarget = pPlayer;  }

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
	CObject*		m_pTarget = nullptr;

};

