#include "..//..//..//stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };	

	m_fSpeed = 2.f;
}

void CMonster::Update(void)
{
	m_tInfo.vDir = m_pTarget->Get_Info().vPos - m_tInfo.vPos;
	
	m_tInfo.NormalizedToDirVec();

	D3DXVECTOR3 dx_vecUp = { 1.0, 0.0, 0.0 };

	float fRad = acosf(D3DXVec3Dot(&m_tInfo.vDir, &dx_vecUp));

	float fRadian = acosf(m_tInfo.vDir.x);

	if (m_tInfo.vDir.y < 0)
	{
		//fRadian = -fRadian;
		fRad = -fRad;
	}

	D3DXVECTOR3 vecDir(cosf(fRad), sinf(fRad), 0);
	//D3DXVECTOR3 vecDir(0, 0, 0);


	m_tInfo.vPos += 5 * vecDir;
}

void CMonster::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_tInfo.vPos.x - 50.f),
		int(m_tInfo.vPos.y - 50.f),
		int(m_tInfo.vPos.x + 50.f),
		int(m_tInfo.vPos.y + 50.f));
}

void CMonster::Release(void)
{
}

void CMonster::OnCollisionBegin(CCollider* _pOther)
{
}

void CMonster::OnCollision(CCollider* _pOther)
{
}

void CMonster::OnCollisionEnd(CCollider* _pOther)
{
}
