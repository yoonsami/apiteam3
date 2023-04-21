#include "..//..//..//stdafx.h"
#include "CSceneExperiment.h"

#include "..//..//CObject//CPlayer//Player.h"
#include "..//..//CObject//CMonster//Monster.h"

CSceneExperiment::CSceneExperiment()
{
}

CSceneExperiment::~CSceneExperiment()
{
}


void CSceneExperiment::Enter()
{
	CObject* pPlayer = new CPlayer;
	pPlayer->Initialize();
	m_vecObj[(UINT)GROUP_TYPE::PLAYER].push_back(pPlayer);

	CObject* pMonster = new CMonster;
	pMonster->Initialize();
	m_vecObj[(UINT)GROUP_TYPE::MONSTER].push_back(pMonster);


	dynamic_cast<CMonster*>(pMonster)->Set_Player(pPlayer);

}

void CSceneExperiment::Exit()
{

}

void CSceneExperiment::Update()
{
	CScene::Update();
}

void CSceneExperiment::Render(HDC _hdc)
{
	CScene::Render(_hdc);
}
