#include "..//..//..//stdafx.h"
#include "CCollider.h"
#include "../../CObject/CObject.h"

int CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
	, m_szName(L"")
{
}

CCollider::~CCollider()
{
}


void CCollider::Update_Final()
{
	D3DXVECTOR3 vPos = m_pOwner->Get_Pos();
	m_vFinalPos = vPos + m_vOffset;
}

void CCollider::OnCollisionBegin(CCollider* _pOther)
{
	m_pOwner->OnCollisionBegin(_pOther);
}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnd(CCollider* _pOther)
{
	m_pOwner->OnCollisionEnd(_pOther);
}

void CCollider::Render(HDC _hdc)
{
	Rectangle(_hdc, (int)(m_vFinalPos.x - m_vScale.x / 2.f),
		(int)(m_vFinalPos.y - m_vScale.y / 2.f),
		(int)(m_vFinalPos.x + m_vScale.x / 2.f),
		(int)(m_vFinalPos.y + m_vScale.y / 2.f));


}

RECT CCollider::Get_Rect()
{
	return {
		(int)(m_vFinalPos.x - m_vScale.x / 2.f),
		(int)(m_vFinalPos.y - m_vScale.y / 2.f),
		(int)(m_vFinalPos.x + m_vScale.x / 2.f),
		(int)(m_vFinalPos.y + m_vScale.y / 2.f)
	};
}