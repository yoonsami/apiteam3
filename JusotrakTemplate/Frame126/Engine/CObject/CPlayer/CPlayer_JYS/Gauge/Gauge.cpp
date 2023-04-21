#include "stdafx.h"
#include "Gauge.h"
#include "Engine/Manager/CTimeMgr/CTimeMgr.h"
#include "Engine/Component/CCollider/CCollider.h"
#include "Engine/CScene/Scene_JYS/CScene_JYS.h"

CGauge::CGauge()
{
}

CGauge::~CGauge()
{
}

void CGauge::Initialize(void)
{
	m_vScale = { 70.f,20.f,0.f };
	m_vVertex[0] = { 0, -m_vScale.y * 0.5f, 0.f };
	m_vVertex[1] = { m_vScale.x, -m_vScale.y * 0.5f, 0.f };
	m_vVertex[2] = { m_vScale.x, m_vScale.y * 0.5f, 0.f };
	m_vVertex[3] = { 0, m_vScale.y * 0.5f, 0.f };
	Create_Collider();
	m_pCollider->SetScale({ 10.f,10.f,0.f });
	
}

void CGauge::Update(void)
{
	

	if(!m_bFired)
	{
		m_vGaugePoint[0] = { m_vScale.x * (m_fGauge - 500.f) / 1000.f, -m_vScale.y * 0.5f, 0.f };
		m_vGaugePoint[1] = { m_vScale.x * (m_fGauge - 500.f) / 1000.f, m_vScale.y * 0.5f, 0.f };
	}
	else
	{
		Accelarate();
		if (m_tInfo.vPos.x > WINCX || m_tInfo.vPos.x < 0 || m_tInfo.vPos.y > WINCY)
			DeleteObject(this, GROUP_TYPE::PLAYER_BULLET);
	}

	Cal_WorldMat();
	m_pCollider->Update_Final();
}

void CGauge::Render(HDC hDC)
{

	m_tInfo.matWorld = m_tInfo.matWorld * CScene_JYS::m_matCamera;
	D3DXVECTOR3 WorldVertex[4]{};

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&WorldVertex[i], &m_vVertex[i], &m_tInfo.matWorld);
	}

	MoveToEx(hDC, int(WorldVertex[3].x), int(WorldVertex[3].y), nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, int(WorldVertex[i].x), int(WorldVertex[i].y));
	}

	D3DXVECTOR3 WorldGaugePoint[2]{};

	for (int i = 0; i < 2; ++i)
	{
		D3DXVec3TransformCoord(&WorldGaugePoint[i], &m_vGaugePoint[i], &m_tInfo.matWorld);
	}

	MoveToEx(hDC, int(WorldGaugePoint[0].x), int(WorldGaugePoint[0].y), nullptr);

	LineTo(hDC, int(WorldGaugePoint[1].x), int(WorldGaugePoint[1].y));

}

void CGauge::Release(void)
{
}

void CGauge::OnCollisionBegin(CCollider* _pOther)
{
	DeleteObject(this, GROUP_TYPE::PLAYER_BULLET);
}

void CGauge::OnCollision(CCollider* _pOther)
{
}

void CGauge::OnCollisionEnd(CCollider* _pOther)
{
}

void CGauge::Cal_WorldMat()
{
	D3DXMATRIX MatRotZ;
	D3DXMatrixRotationZ(&MatRotZ, m_tInfo.GetRadianDirVec());

	// 이동 pos만큼
	D3DXMATRIX MatTrans;

	D3DXMatrixTranslation(&MatTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = MatRotZ * MatTrans;
}

void CGauge::Accelarate()
{
	D3DXVECTOR3 gravity{ 0.f,600.f,0.f };

	m_vVel += gravity * fDT;

	m_tInfo.vDir = m_vVel;

	m_tInfo.vDir = m_tInfo.GetNormalizedDirVec();

	m_tInfo.vPos += m_vVel * fDT;
}
