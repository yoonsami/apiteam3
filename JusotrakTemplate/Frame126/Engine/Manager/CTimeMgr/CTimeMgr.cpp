#include "..//..//..//stdafx.h"
#include "CTimeMgr.h"
#include "..//..//CMainGame//MainGame.h"

CTimeMgr* CTimeMgr::m_pInstance = nullptr;


CTimeMgr::CTimeMgr()
	: m_llCurCount{0}
	, m_llPrevCount{0}
	, m_llFreq{0}
	, m_uiFPS(0)
	, m_dDeltaTime(0)
	, m_dAccTime(0)
{

}

CTimeMgr::~CTimeMgr()
{

}


void CTimeMgr::Initialize()
{
	QueryPerformanceFrequency(&m_llFreq);
	QueryPerformanceCounter(&m_llCurCount);
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_dDeltaTime = (m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFreq.QuadPart;

	m_dAccTime += m_dDeltaTime;
	++m_uiFPS;
	

	if (m_dDeltaTime > 1. / 60.)
	{
		m_dDeltaTime = 1. / 60.;
	}

#ifdef _DEBUG
	if (m_dAccTime >= 1.f)
	{
		m_dAccTime = 0.0f;
		WCHAR InfoText[256];
		swprintf_s(InfoText, L"DeltaTime = %f and FPS = %u", m_dDeltaTime, m_uiFPS);
		SetWindowText(g_hWnd, InfoText);
	}
#endif

	m_llPrevCount = m_llCurCount;
}