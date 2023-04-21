#pragma once

#define			WINCX		800
#define			WINCY		600
#define			GRAVITY		100.f
#define			PI			3.141592f
#define			PURE		= 0
#define			fDT				CTimeMgr::Get_Instance()->Get_fDeltaTime()
#define			KEY_CHECK(key,state) (CKeyMgr::Get_Instance()->Get_Key_State(key) == state)

#define			KEY_HOLD(key) KEY_CHECK(key,KEY_STATE::HOLD)
#define			KEY_TAP(key) KEY_CHECK(key,KEY_STATE::TAP)
#define			KEY_AWAY(key) KEY_CHECK(key,KEY_STATE::AWAY)

extern		HWND	g_hWnd;