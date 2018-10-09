
// FirstAgentWorldMFC.h: Hauptheaderdatei für die FirstAgentWorldMFC-Anwendung
//
#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"       // Hauptsymbole


// CFirstAgentWorldMFCApp:
// Siehe FirstAgentWorldMFC.cpp für die Implementierung dieser Klasse
//

class CFirstAgentWorldMFCApp : public CWinAppEx
{
public:
	CFirstAgentWorldMFCApp();


// Überschreibungen
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementierung
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFirstAgentWorldMFCApp theApp;
