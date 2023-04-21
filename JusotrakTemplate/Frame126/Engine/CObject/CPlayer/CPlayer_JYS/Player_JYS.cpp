#include "stdafx.h"
#include "Player_JYS.h"
#include "..//..//..//Manager//CKeyMgr/CKeyMgr.h"
#include "..//..//..//Manager//CTimeMgr/CTimeMgr.h"
#include "Aim/Aim.h"
#include "Gauge/Gauge.h"
#include "Engine/Component/CCollider/CCollider.h"
#include "Engine/CScene/Scene_JYS/CScene_JYS.h"


CPlayer_JYS::CPlayer_JYS()
{
}

CPlayer_JYS::~CPlayer_JYS()
{
	Release();
}

void CPlayer_JYS::Initialize(void)
{
	m_vScale = { 100.f,30.f,0.f };
	m_tInfo.vPos = { 0.f, WINCY - m_vScale.y * 0.5f,0.f };
	m_tInfo.vDir = { 1.f,0.f,0.f };
	m_tInfo.vLook = { 1.f,0.f,0.f };
	m_fSpeed = 200.f;
	m_vVertex[0] = { -m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vVertex[1] = { m_vScale.x * 0.5f, -m_vScale.y * 0.5f, 0.f };
	m_vVertex[2] = { m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };
	m_vVertex[3] = { -m_vScale.x * 0.5f, m_vScale.y * 0.5f, 0.f };

	Create_Collider();
	m_pCollider->SetScale({50.f, 30.f, 0.f});
	m_tAim = new CAim;
	(m_tAim)->m_pOwner = this;
	m_tAim->Initialize();
}

void CPlayer_JYS::Update(void)
{
	if(m_bFlying)
	{
		if (m_tInfo.vPos.x > WINCX || m_tInfo.vPos.x < 0 || m_tInfo.vPos.y > WINCY)
			DeleteObject(this, GROUP_TYPE::PLAYER);
	}

	if (!m_bFlying)
		Key_Input();
	else
		Accelarate();

	Cal_WorldMat();
	if (m_pGauge)
		m_pGauge->Update();
	if (m_pCollider)
		m_pCollider->Update_Final();
}

void CPlayer_JYS::Render(HDC hDC)
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

	m_tAim->Render(hDC);

	if (m_pGauge)
		m_pGauge->Render(hDC);
}

void CPlayer_JYS::Release(void)
{
	Safe_Delete(m_tAim);
}

void CPlayer_JYS::OnCollisionBegin(CCollider* _pOther)
{
}

void CPlayer_JYS::OnCollision(CCollider* _pOther)
{
}

void CPlayer_JYS::OnCollisionEnd(CCollider* _pOther)
{
}

void CPlayer_JYS::Cal_WorldMat()
{
	D3DXMATRIX MatRotZ;
	D3DXMatrixRotationZ(&MatRotZ, m_tInfo.GetRadianLookVec());

	// 이동 pos만큼
	D3DXMATRIX MatTrans;
	D3DXMatrixTranslation(&MatTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = MatRotZ * MatTrans;
	m_tAim->Cal_WorldMat();

}

void CPlayer_JYS::Accelarate()
{
	D3DXVECTOR3 gravity{ 0.f,600.f,0.f };

	m_vVel += gravity * fDT;

	m_tInfo.vDir = m_vVel;

	m_tInfo.vDir = m_tInfo.GetNormalizedDirVec();

	m_tInfo.vPos += m_vVel * fDT;
	
	m_fLookRadian -= 2 * PI * fDT;
	m_tInfo.vLook = { cosf(m_fLookRadian),sinf(m_fLookRadian),0.f };

}

void CPlayer_JYS::Key_Input(void)
{
	if (KEY_HOLD(KEY::A))
		m_tInfo.vPos -= m_tInfo.GetNormalizedDirVec() * m_fSpeed * fDT ;

	if (KEY_HOLD(KEY::D))
		m_tInfo.vPos += m_tInfo.GetNormalizedDirVec() * m_fSpeed * fDT;

	if (KEY_HOLD(KEY::W))
		m_tAim->m_fDirTheta -= PI * fDT;

	if (KEY_HOLD(KEY::S))
		m_tAim->m_fDirTheta += PI * fDT;

	if (KEY_TAP(KEY::SPACE))
	{
		m_pGauge = new CGauge;
		m_pGauge->Initialize();
	}

	else if (KEY_HOLD(KEY::SPACE))
	{
		m_bCharging = true;

		D3DXVECTOR3 tmpPos = D3DXVECTOR3{ 0.f,-40.f,0.f };
		D3DXVec3TransformCoord(&tmpPos, &tmpPos, &m_tAim->m_tInfo.matWorld);
		m_pGauge->Set_Pos(tmpPos);

		D3DXVECTOR3 tmpDir = { 1.f,0.f,0.f };
		D3DXVec3TransformNormal(&tmpDir, &tmpDir, &m_tAim->m_tInfo.matWorld);
		m_pGauge->Set_Dir(tmpDir);

		m_fFirePower += m_fPowerPerSec * fDT;
		m_pGauge->m_fGauge = clamp(m_fFirePower, 500.f, 1500.f);

	}

	else if (KEY_AWAY(KEY::SPACE))
	{
		if(KEY_HOLD(KEY::CTRL))
		{
			m_pGauge->m_bFired = true;
			m_pGauge->Set_Vel();
			CreateObject(m_pGauge, GROUP_TYPE::PLAYER_BULLET);
		}
		else if (KEY_HOLD(KEY::LSHIFT))
		{
			D3DXVECTOR3 tmpDir = { 1.f,0.f,0.f };
			D3DXVec3TransformNormal(&tmpDir, &tmpDir, &m_tAim->m_tInfo.matWorld);
			m_tInfo.vDir = tmpDir;
			m_bFlying = true;
			Safe_Delete(m_pGauge);
			m_vVel = m_tInfo.vDir * clamp(m_fFirePower, 500.f, 1500.f);
		}
		else if (KEY_HOLD(KEY::Z))
		{
			D3DXVECTOR3 tmpDir = { 1.f,0.f,0.f };
			D3DXVec3TransformNormal(&tmpDir, &tmpDir, &m_tAim->m_tInfo.matWorld);
			m_tInfo.vDir = tmpDir;
			CScene_JYS::m_fDir = tmpDir;
			CScene_JYS::m_bFlying = true;
			Safe_Delete(m_pGauge);
		}
		else
		{
			Safe_Delete(m_pGauge);
			m_tAim->Fire_Bullet(clamp(m_fFirePower,500.f, 1500.f));
		}

		m_fFirePower = 0.f;
		m_bCharging = false;
		m_pGauge = nullptr;
	}

}
