#include "stdafx.h"
#include "Bullet_JYS.h"
#include "..//..//..//..//Manager//CTimeMgr/CTimeMgr.h"
#include "Engine/Component/CCollider/CCollider.h"
#include "Engine/CScene/Scene_JYS/CScene_JYS.h"


CBullet_JYS::CBullet_JYS()
{
}

CBullet_JYS::~CBullet_JYS()
{
}

void CBullet_JYS::Initialize(void)
{
	m_vScale = { 30.f, 10.f ,0.f};
	m_vVertex[0] = { -Get_Scale().x * 0.5f, -Get_Scale().y * 0.5f, 0.f }; //LT
	m_vVertex[1] = { Get_Scale().x * 0.5f, -Get_Scale().y * 0.5f, 0.f }; // RT
	m_vVertex[2] = { Get_Scale().x , 0.f ,0.f };
	m_vVertex[3] = { Get_Scale().x * 0.5f, Get_Scale().y * 0.5f, 0.f }; // RB
	m_vVertex[4] = { -Get_Scale().x * 0.5f, Get_Scale().y * 0.5f, 0.f }; // LB
	m_fSpeed = 500.f;

	Create_Collider();
	m_pCollider->SetScale({ 10.f,10.f,0.f });
}

void CBullet_JYS::Update(void)
{
	Accelarate();
	Cal_WorldMat();
	if (m_tInfo.vPos.x > WINCX || m_tInfo.vPos.x < 0 || m_tInfo.vPos.y > WINCY)
		DeleteObject(this,GROUP_TYPE::PLAYER_BULLET);

	m_pCollider->Update_Final();
}

void CBullet_JYS::Render(HDC hDC)
{

	m_tInfo.matWorld = m_tInfo.matWorld * CScene_JYS::m_matCamera;

	D3DXVECTOR3 WorldVertex[5]{};

	for (int i = 0; i < 5; ++i)
		D3DXVec3TransformCoord(&WorldVertex[i], &m_vVertex[i], &m_tInfo.matWorld);

	MoveToEx(hDC, int(WorldVertex[4].x), int(WorldVertex[4].y), nullptr);

	for (int i = 0; i < 5; ++i)
		LineTo(hDC, int(WorldVertex[i].x), int(WorldVertex[i].y));
}

void CBullet_JYS::Release(void)
{
}

void CBullet_JYS::OnCollisionBegin(CCollider* _pOther)
{
	DeleteObject(this, GROUP_TYPE::PLAYER_BULLET);
}

void CBullet_JYS::OnCollision(CCollider* _pOther)
{
}

void CBullet_JYS::OnCollisionEnd(CCollider* _pOther)
{
}

void CBullet_JYS::Cal_WorldMat()
{
	D3DXMATRIX MatRotZ;
	D3DXMatrixRotationZ(&MatRotZ, m_tInfo.GetRadianDirVec());
	// 이동 pos만큼
	D3DXMATRIX MatTrans;
	D3DXMatrixTranslation(&MatTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = MatRotZ * MatTrans;
}

void CBullet_JYS::Accelarate()
{

	D3DXVECTOR3 gravity{0.f,600.f,0.f};

	m_vVel += gravity * fDT;

	m_tInfo.vDir = m_vVel;

	m_tInfo.vDir = m_tInfo.GetNormalizedDirVec();

	m_tInfo.vPos += m_vVel * fDT;
}
