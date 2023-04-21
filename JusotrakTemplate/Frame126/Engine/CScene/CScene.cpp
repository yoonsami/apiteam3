#include "..//..//stdafx.h"
#include "CScene.h"
#include "..//CObject//CObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	for (size_t i = 0; i < (size_t)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < (size_t)m_vecObj[i].size(); ++j)
		{
			delete m_vecObj[i][j];
			m_vecObj[i][j] = nullptr;
		}
		m_vecObj[i].clear();
	}
}

void CScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (auto pObj : m_vecObj[i])
		{
			if(!pObj->Is_Dead())
				pObj->Update();
		}
	}
}

void CScene::Render(HDC _hdc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (auto pObj : m_vecObj[i])
		{
			if (!pObj->Is_Dead())
				pObj->Render(_hdc);
		}
	}
}

void CScene::Delete_Group_Object(GROUP_TYPE _eType, CObject* _obj)
{
	auto iter = m_vecObj[(UINT)_eType].begin();
	auto end = m_vecObj[(UINT)_eType].end();

	while (end != iter)
	{
		if (_obj == *iter) break;

		++iter;
	}
	if (end != iter) m_vecObj[(UINT)_eType].erase(iter);
}