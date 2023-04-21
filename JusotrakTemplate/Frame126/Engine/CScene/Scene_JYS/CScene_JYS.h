#pragma once
#include "..//CScene.h"

class CScene_JYS :
    public CScene
{
public:
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

public:
	CScene_JYS();
	~CScene_JYS();
public:
	static UINT g_iScore;

	static D3DXVECTOR3 m_fLookAt;
	static float	   m_fCameraTheta;
	static D3DXMATRIX  m_matCamera;
	D3DXVECTOR3	m_vCorner[4]{};
	static bool			m_bFlying;
	static D3DXVECTOR3 m_fDir;
};

