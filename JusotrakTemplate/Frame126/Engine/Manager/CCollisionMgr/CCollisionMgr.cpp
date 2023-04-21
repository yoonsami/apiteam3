#include "..//..//..//stdafx.h"
#include "CCollisionMgr.h"
#include "..//..//Component//CCollider//CCollider.h"
#include "..//..//Manager//CSceneMgr//CSceneMgr.h"
#include "..//..//CScene//CScene.h"
#include "..//..//CObject//CObject.h"

CCollisionMgr* CCollisionMgr::m_pInstance = nullptr;

CCollisionMgr::CCollisionMgr()
	: m_arrCollisionCheck{0}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::Initialize()
{
}

void CCollisionMgr::Update()
{
	for (int iRow = 0; iRow < (int)(GROUP_TYPE::END); ++iRow)
	{
		for (int iCol = iRow; iCol < (int)(GROUP_TYPE::END); ++iCol)
		{
			if (m_arrCollisionCheck[iRow] & (1 << iCol))
			{
				Collision_Group_Update((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::Update_Late()
{
	for (int iRow = 0; iRow < (int)(GROUP_TYPE::END); ++iRow)
	{
		for (int iCol = iRow; iCol < (int)(GROUP_TYPE::END); ++iCol)
		{
			if (m_arrCollisionCheck[iRow] & (1 << iCol))
			{
				Collision_Group_Update((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}



void CCollisionMgr::Check_Group(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	int iRow = min( (int)_eLeft, (int)_eRight );
	int iCol = max( (int)_eLeft, (int)_eRight );

	if (m_arrCollisionCheck[iRow] & (1 << iCol))
	{
		// 이미 충돌 그룹으로 지정해놓은 경우, 해제.
		m_arrCollisionCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCollisionCheck[iRow] |= (1 << iCol);
	}
}

void CCollisionMgr::Collision_Group_Update(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	/*
	반드시 이 함수는 인수가 _eLeft <= _eRight 이어야 함!
	*/
	CScene* pCurScene = CSceneMgr::Get_Instance()->Get_Cur_Scene();
	vector<CObject*> vecLeftGroup = pCurScene->Get_Group_Object(_eLeft);
	vector<CObject*> vecRightGroup = pCurScene->Get_Group_Object(_eRight);

	CCollider* pLeftCollider = nullptr;
	CCollider* pRightCollider = nullptr;

	for (size_t i = 0; i < vecLeftGroup.size(); ++i)
	{
		pLeftCollider = vecLeftGroup[i]->Get_Collider();
		if (nullptr == pLeftCollider) continue;

		for (size_t j = 0; j < vecRightGroup.size(); ++j)
		{
			pRightCollider = vecRightGroup[j]->Get_Collider();
			if (nullptr == pRightCollider) continue;

			if (pLeftCollider->GetID() == pRightCollider->GetID()) continue;

			COLLIDER_ID ID = {};
			ID.LeftID = pLeftCollider->GetID();
			ID.RightID = pRightCollider->GetID();

			auto iter = m_mapColInfo.find(ID.ID);

			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert({ ID.ID, false });
				iter = m_mapColInfo.find(ID.ID);
			}

			if (IsCollisionByRectangle(pLeftCollider, pRightCollider))
			{
				if (iter->second)
				{
					pLeftCollider->OnCollision(pRightCollider);
					pRightCollider->OnCollision(pLeftCollider);
				}
				else
				{
					pLeftCollider->OnCollisionBegin(pRightCollider);
					pRightCollider->OnCollisionBegin(pLeftCollider);
					iter->second = true;
				}
			}
			else
			{
				if (iter->second)
				{
					pLeftCollider->OnCollisionEnd(pRightCollider);
					pRightCollider->OnCollisionEnd(pLeftCollider);
					iter->second = false;
				}
			}


		}
	}
}

void CCollisionMgr::Reset_Collision_Group()
{
	memset(m_arrCollisionCheck, 0, sizeof(int) * (UINT)(GROUP_TYPE::END));
}

bool CCollisionMgr::IsCollisionByRectangle(CCollider* _ptLeftCol, CCollider* _ptRightCol)
{
	RECT rtLeft = _ptLeftCol->Get_Rect();
	RECT rtRight = _ptRightCol->Get_Rect();
	RECT rt;

	if (IntersectRect(&rt, &rtLeft, &rtRight)) return true;
	else return false;
}