#pragma once


class CObject;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(HWND _hwnd);	
	void		Update(void);		
	void		Render(void);		
	void		Release(void);		

private:
	HDC				m_DC = nullptr;
	HDC				m_memDC;
	HWND			m_hwnd = nullptr;
	CObject*		m_pPlayer;
	CObject*		m_pMonster;
};

