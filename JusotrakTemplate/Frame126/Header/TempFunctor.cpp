#include "stdafx.h"
#include "Include.h"
#include "TempFunctor.h"
#include "Engine/Manager/CEventMgr/CEventMgr.h"


void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEventMsg evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.wParam = (DWORD_PTR)_pObj;
	evn.lParam = (DWORD_PTR)_eGroup;

	CEventMgr::Get_Instance()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEventMsg evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.wParam = (DWORD_PTR)_pObj;
	evn.lParam = (DWORD_PTR)_eGroup;
	CEventMgr::Get_Instance()->AddEvent(evn);
}
