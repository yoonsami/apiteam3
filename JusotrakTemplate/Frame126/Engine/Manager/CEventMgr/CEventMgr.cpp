#include "..//..//..//stdafx.h"
#include "CEventMgr.h"
#include "..//CSceneMgr//CSceneMgr.h"
#include "..//..//CScene//CScene.h"
#include "..//..//CObject//CObject.h"

CEventMgr* CEventMgr::m_pInstance = nullptr;

CEventMgr::CEventMgr()
{
	m_vecDeadObj.reserve(1000);
}

CEventMgr::~CEventMgr()
{
}


void CEventMgr::Update()
{
	// =========================
	// Dead 상태 오브젝트들 지우기
	// =========================
	for (int i = 0; i < m_vecDeadObj.size(); ++i)
	{
 		delete m_vecDeadObj[i];
	}
	m_vecDeadObj.clear();

	// ============
	// Event 핸들링
	// ============
	while (!m_deqEvent.empty())
	{
		tEventMsg& msg = m_deqEvent.front();
		m_deqEvent.pop_front();
		Execute(msg);
	}
}

void CEventMgr::Execute(const tEventMsg& _msg)
{

	switch (_msg.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		CScene* pCurScene = CSceneMgr::Get_Instance()->Get_Cur_Scene();

		GROUP_TYPE eType = (GROUP_TYPE)_msg.lParam;
		CObject* pObj = (CObject*)_msg.wParam;

		pCurScene->Add_Object(eType, pObj);
	}
	break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		CScene* pCurScene = CSceneMgr::Get_Instance()->Get_Cur_Scene();

		GROUP_TYPE eType = (GROUP_TYPE)_msg.lParam;
		CObject* pObj = (CObject*)_msg.wParam;

		pObj->Set_Dead(true);
		pCurScene->Delete_Group_Object(eType, pObj);
		m_vecDeadObj.push_back(pObj);
	}
	break;

	case EVENT_TYPE::SCENE_CHANGE:
	{
		CScene* pCurScene = nullptr;
		SCENE_TYPE eType = (SCENE_TYPE)_msg.lParam;
		CSceneMgr::Get_Instance()->Change_Scene(eType);
	}
	break;
	}
}


void CEventMgr::AddEvent(const tEventMsg& _msg)
{
	m_deqEvent.push_back(_msg);
}
