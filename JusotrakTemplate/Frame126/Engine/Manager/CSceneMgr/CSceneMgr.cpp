#include "..//..//..//stdafx.h"
#include "CSceneMgr.h"
#include "..//..//CScene//CScene.h"

#include "..//..//CScene//Scene_Experiment//CSceneExperiment.h"
#include "../../CScene/Scene_JYS/CScene_JYS.h"


CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pCurScene(nullptr)
	, m_arrScene{ nullptr }
{
}

CSceneMgr::~CSceneMgr()
{
	for (size_t i = 0; i < (size_t)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
			m_arrScene[i] = nullptr;
		}
	}
}


void CSceneMgr::Change_Scene(SCENE_TYPE _eType)
{
	if (nullptr != m_pCurScene)
	{
		m_pCurScene->Exit();
	}

	m_pCurScene = m_arrScene[(size_t)_eType];
	m_pCurScene->Enter();

}

void CSceneMgr::Initialize()
{
	//m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	//m_pCurScene->Enter();

	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CSceneExperiment;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_JYS;


	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::STAGE_02];
	m_pCurScene->Enter();
}

void CSceneMgr::Update()
{
	m_pCurScene->Update();
}

void CSceneMgr::Render(HDC _hdc)
{
	m_pCurScene->Render(_hdc);
}

