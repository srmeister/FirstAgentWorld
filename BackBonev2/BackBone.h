// BackBone.h : Haupt-Header-Datei für die Anwendung BACKBONE
//

#if !defined(AFX_BACKBONE_H__B36414F4_5AEE_4DCD_A45B_9DAD26BC68A8__INCLUDED_)
#define AFX_BACKBONE_H__B36414F4_5AEE_4DCD_A45B_9DAD26BC68A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CBackBoneApp:
// Siehe BackBone.cpp für die Implementierung dieser Klasse
//

class CBackBoneApp : public CWinApp
{
public:
	CBackBoneApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CBackBoneApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CBackBoneApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_BACKBONE_H__B36414F4_5AEE_4DCD_A45B_9DAD26BC68A8__INCLUDED_)
