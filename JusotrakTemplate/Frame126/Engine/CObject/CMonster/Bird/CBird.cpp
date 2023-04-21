#include "stdafx.h"
#include "CBird.h"
#include "Engine/Manager/CTimeMgr/CTimeMgr.h"
#include "Engine/Component/CCollider/CCollider.h"
#include "Engine/CScene/Scene_JYS/CScene_JYS.h"


CBird::CBird()
{
}

CBird::~CBird()
{
}

void CBird::Initialize(void)
{

	m_vScale = { 50.f, 20.f,0.f };
	m_tInfo.vDir = { 1.f,0.f,0.f };
	m_vVertex[0] = { -m_vScale.x * 0.5f, 0.f,0.f };
	m_vVertex[1] = { -m_vScale.x * 0.25f, -m_vScale.y * 0.5f, 0.f };
	m_vVertex[2] = { 0.f,0.f,0.f };
	m_vVertex[3] = { m_vScale.x * 0.25f, -m_vScale.y * 0.5f, 0.f };
	m_vVertex[4] = { m_vScale.x * 0.5f, 0.f,0.f };
	m_vVertex[5] = { m_vScale.x * 0.25f, -m_vScale.y * 0.25f, 0.f };
	m_vVertex[6] = { 0.f,0.f,0.f };
	m_vVertex[7] = { -m_vScale.x * 0.25f, -m_vScale.y * 0.25f, 0.f };
	m_vVertex[8] = { -m_vScale.x * 0.5f, 0.f,0.f };
	m_fSpeed = 200.f;
	Create_Collider();
	m_pCollider->SetScale(m_vScale);
}

void CBird::Update(void)
{
	float randValue =(float(rand()% 90) -45.f);

	if (m_tInfo.vPos.y < 100.f)
	{
		if (randValue < 0)
		{
			
			randValue *= -1.f;
		}
	}
	else if (m_tInfo.vPos.y > 200.f)
	{
		if (randValue > 0)
			randValue *= -1.f;
	}

	if (m_tInfo.GetRadianDirVec() > PI * 0.25f && randValue >  0)
	{
		randValue *= 0.f;
	}
	if (m_tInfo.GetRadianDirVec() < -PI * 0.25f && randValue < 0)
	{
		randValue *= 0.f;
	}

	if (m_tInfo.vPos.x < 0 && m_fDir == -1.f)
		m_fDir = 1.f;
	else if (m_tInfo.vPos.x > WINCX && m_fDir == 1.f)
		m_fDir = -1.f;

	D3DXMATRIX MatRotZ;
	D3DXMatrixRotationZ(&MatRotZ, D3DXToRadian(randValue * fDT));
	
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &MatRotZ);
	
	
	D3DXVECTOR3 tmpdir = D3DXVECTOR3{ m_tInfo.vDir.x * m_fDir, m_tInfo.vDir.y, m_tInfo.vDir.z };
	m_tInfo.vPos += tmpdir * m_fSpeed * fDT;
	Cal_WorldMat();
	m_pCollider->Update_Final();
}

void CBird::Render(HDC hDC)
{

	m_tInfo.matWorld = m_tInfo.matWorld * CScene_JYS::m_matCamera;

	D3DXVECTOR3 WorldVertex[9]{};

	for (int i = 0; i < 9; ++i)
	{
		D3DXVec3TransformCoord(&WorldVertex[i], &m_vVertex[i], &m_tInfo.matWorld);
	}

	MoveToEx(hDC, int(WorldVertex[8].x), int(WorldVertex[8].y), nullptr);

	for (int i = 0; i < 9; ++i)
	{
		LineTo(hDC, int(WorldVertex[i].x), int(WorldVertex[i].y));
	}
}

void CBird::Release(void)
{
}

void CBird::OnCollisionBegin(CCollider* _pOther)
{
	DeleteObject(this, GROUP_TYPE::MONSTER);
	CScene_JYS::g_iScore++;
}

void CBird::OnCollision(CCollider* _pOther)
{
}

void CBird::OnCollisionEnd(CCollider* _pOther)
{
}

void CBird::Cal_WorldMat()
{
	D3DXMATRIX MatRotZ;
	D3DXMatrixRotationZ(&MatRotZ, m_tInfo.GetRadianDirVec());
	// 이동 pos만큼
	D3DXMATRIX MatTrans;
	D3DXMatrixTranslation(&MatTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = MatRotZ * MatTrans;
}
