#pragma once

#include "..//CScene.h"

class CSceneExperiment
	: public CScene
{

public:
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

public:
	CSceneExperiment();
	~CSceneExperiment();
};

