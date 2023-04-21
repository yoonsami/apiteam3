#include "stdafx.h"
#include "Aim.h"
#include "..//Player_JYS.h"
#include "../Bullet_JYS/Bullet_JYS.h"
#include "Engine/CScene/Scene_JYS/CScene_JYS.h"

CAim::CAim()
{
}

CAim::~CAim()
{
}

void CAim::Initialize(void)
{
	m_tInfo.vPos = { m_pOwner->Get_Scale().x*0.3f, -m_pOwner->Get_Scale().y * 0.5f,0.f };
	m_vScale = { 70.f,10.f,0.f };
	m_vVertex[0] = { 0, -m_vScale.y * 0.5f, 0.f };
	m_vVertex[1] = { m_vScale.x, -m_vScale.y * 0.5f, 0.f };
	m_vVertex[2] = { m_vScale.x, m_vScale.y * 0.5f, 0.f };
	m_vVertex[3] = { 0, m_vScale.y * 0.5f, 0.f };
}

void CAim::Update(void)
{

}

void CAim::Render(HDC hDC)
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
}

void CAim::Release(void)
{
}

void CAim::OnCollisionBegin(CCollider* _pOther)
{
}

void CAim::OnCollision(CCollider* _pOther)
{
}

void CAim::OnCollisionEnd(CCollider* _pOther)
{
}

void CAim::Cal_WorldMat()
{
	//vDir 계산
	m_tInfo.vDir = { cosf(m_fDirTheta),sinf(m_fDirTheta),0.f };
	// 회전
	D3DXMATRIX MatRotZ;
	D3DXMatrixRotationZ(&MatRotZ, m_fDirTheta);

	// 이동 pos만큼
	D3DXMATRIX MatTrans;

	D3DXMatrixTranslation(&MatTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = MatRotZ * MatTrans * m_pOwner->Get_Info().matWorld;
}

void CAim::Fire_Bullet(float FirePower)
{
	CObject* tmpBullet = new CBullet_JYS;
	tmpBullet->Initialize();

	D3DXVECTOR3 tmpPos = D3DXVECTOR3{m_vVertex[1] + m_vVertex[2]} * 0.5f;
	D3DXVec3TransformCoord(&tmpPos, &tmpPos, &m_tInfo.matWorld);
	tmpBullet->Set_Pos(tmpPos);

	D3DXVECTOR3 tmpDir = { 1.f,0.f,0.f };
	D3DXVec3TransformNormal(&tmpDir, &tmpDir, &m_tInfo.matWorld);
	tmpBullet->Set_Dir(tmpDir);

	tmpBullet->Set_Speed(FirePower);
	static_cast<CBullet_JYS*>(tmpBullet)->Set_Vel();
	CreateObject(tmpBullet, GROUP_TYPE::PLAYER_BULLET);
}
