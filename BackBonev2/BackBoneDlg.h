// BackBoneDlg.h : Header-Datei
//

#if !defined(AFX_BACKBONEDLG_H__7E00C4CD_70AF_47CF_9503_B5012D447FD1__INCLUDED_)
#define AFX_BACKBONEDLG_H__7E00C4CD_70AF_47CF_9503_B5012D447FD1__INCLUDED_

#include "Environment.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Viewport.h"

/////////////////////////////////////////////////////////////////////////////
// CBackBoneDlg Dialogfeld

class CBackBoneDlg : public CDialog
{
// Konstruktion
public:
	double m_RunTime;
	Environment m_Welt;
	Viewport m_Viewport;
	CBackBoneDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CBackBoneDlg)
	enum { IDD = IDD_BACKBONE_DIALOG };
//	CSpinButtonCtrl	m_NodeSel;
//	UINT	m_Anzahl;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CBackBoneDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);

public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_BACKBONEDLG_H__7E00C4CD_70AF_47CF_9503_B5012D447FD1__INCLUDED_)
