
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTree-Fenster

class CViewTree : public CTreeCtrl
{
// Konstruktion
public:
	CViewTree();

// �berschreibungen
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// Implementierung
public:
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
};
