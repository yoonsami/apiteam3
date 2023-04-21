#include "stdafx.h"
#include "CScene_JYS.h"
#include "../../CObject/CPlayer/CPlayer_JYS/Player_JYS.h"
#include "../../CObject/CMonster/Bird/CBird.h"
#include "../../Manager/CCollisionMgr/CCollisionMgr.h"
#include "../../Manager/CTimeMgr/CTimeMgr.h"

void CScene_JYS::Enter()
{
	CObject* pPlayer = new CPlayer_JYS;
	pPlayer->Initialize();
	m_vecObj[(UINT)GROUP_TYPE::PLAYER].push_back(pPlayer);

	CObject* bird = new CBird;
	bird->Initialize();
	bird->Set_Pos({ 0.f,0.f,0.f });
	m_vecObj[(UINT)GROUP_TYPE::MONSTER].push_back(bird);

	CCollisionMgr::Get_Instance()->Check_Group(GROUP_TYPE::MONSTER, GROUP_TYPE::PLAYER_BULLET);
	CCollisionMgr::Get_Instance()->Check_Group(GROUP_TYPE::MONSTER, GROUP_TYPE::PLAYER);
	m_vCorner[0] = { 0.f,0.f,0.f };
	m_vCorner[1] = { 0.f,WINCY,0.f };
	m_vCorner[2] = { WINCX,WINCY,0.f };
	m_vCorner[3] = { WINCX,0.f,0.f };


}

void CScene_JYS::Exit()
{

}

void CScene_JYS::Update()
{
	CScene::Update();
	if (m_vecObj[(UINT)GROUP_TYPE::MONSTER].size() == 0)
	{
		CObject* bird = new CBird;
		bird->Initialize();
		bird->Set_Pos({ 0.f,0.f,0.f });
		CreateObject(bird, GROUP_TYPE::MONSTER);
	}
	if (m_vecObj[(UINT)GROUP_TYPE::PLAYER].size() == 0)
	{
		CObject* pPlayer = new CPlayer_JYS;
		pPlayer->Initialize();
		CreateObject(pPlayer, GROUP_TYPE::PLAYER);
	}

	if (m_bFlying)
	{
		m_fCameraTheta -= PI * fDT;
		m_fLookAt += m_fDir * 500.f * fDT;
	}

	D3DXMATRIX CameraRotateZ, CameraDiff, tmp1, tmp2;
	D3DXVECTOR3 vCameraDiff = (CScene_JYS::m_fLookAt - D3DXVECTOR3{ WINCX,WINCY,0.f }) * -1.f;
	D3DXMatrixTranslation(&tmp1, -WINCX * 0.5f, -WINCY * 0.5f, 0.f);
	//D3DXMatrixTranslation(&tmp2, WINCX * 0.5f, WINCY * 0.5f, 0.f);
	D3DXMatrixRotationZ(&CameraRotateZ, CScene_JYS::m_fCameraTheta);
	D3DXMatrixTranslation(&CameraDiff, vCameraDiff.x, vCameraDiff.y, vCameraDiff.z);


	m_matCamera = tmp1 * CameraRotateZ *  CameraDiff;

	//if(g_iScore > 10)
		//Scene_Change()
}

void CScene_JYS::Render(HDC _hdc)
{

	D3DXVECTOR3 WorldVertex[4]{};

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&WorldVertex[i], &m_vCorner[i], &m_matCamera);
	}

	MoveToEx(_hdc, int(WorldVertex[3].x), int(WorldVertex[3].y), nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(_hdc, int(WorldVertex[i].x), int(WorldVertex[i].y));
	}

	CScene::Render(_hdc);

	TextOut(_hdc, 50, 50, to_wstring(g_iScore).c_str(), int(to_wstring(g_iScore).length()));

}

CScene_JYS::CScene_JYS()
{
}

CScene_JYS::~CScene_JYS()
{
}

UINT CScene_JYS::g_iScore = 0;

D3DXVECTOR3 CScene_JYS::m_fLookAt = { WINCX * 0.5f, WINCY * 0.5f,0.f };

float CScene_JYS::m_fCameraTheta =0.f;

D3DXMATRIX CScene_JYS::m_matCamera = *D3DXMatrixIdentity(&m_matCamera);

bool CScene_JYS::m_bFlying = false;

D3DXVECTOR3 CScene_JYS::m_fDir{};
