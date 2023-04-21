#include "..//..//stdafx.h"
#include "CObject.h"
#include "..//Component//CCollider//CCollider.h"

CObject::CObject()
	: m_fSpeed(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
}


CObject::~CObject()
{
	if (m_pCollider)
		Safe_Delete(m_pCollider);
}

void CObject::Create_Collider()
{
	m_pCollider = new CCollider;
	m_pCollider->SetOwner(this);
}