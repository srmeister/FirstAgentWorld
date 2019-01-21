// BackBoneDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "BackBone.h"
#include "BackBoneDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackBoneDlg Dialogfeld

CBackBoneDlg::CBackBoneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBackBoneDlg::IDD, pParent), 
	m_Viewport(&m_Welt)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_RunTime = 0;
}

void CBackBoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBackBoneDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CBackBoneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Symbol f�r dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Gro�es Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zus�tzliche Initialisierung einf�gen
	
	// Welt init

	m_Welt.SetDim(400,300,200);

	m_Welt.AddKoerper(100, 150, 100);
	m_Welt.AddKoerper(120, 200, 100);

	m_RunTime = 0;
	
	SetTimer(0,100,0);

	UpdateData(false);

	return TRUE;  // Geben Sie TRUE zur�ck, au�er ein Steuerelement soll den Fokus erhalten
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfl�che "Minimieren" hinzuf�gen, ben�tigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. F�r MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch f�r Sie erledigt.

void CBackBoneDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Ger�tekontext f�r Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, w�hrend der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CBackBoneDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBackBoneDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 0:
		m_Welt.Update();
		break;
	default:
		break;
	}
	
	m_RunTime += 0.1f;
		
	CString Anz;
	
	Anz.Format("%d",m_Welt.GetCount());
	SetDlgItemText(IDC_EDIT_ANZAHL,Anz);
	
	
	Anz.Format("%02i :%02i",(int)(m_RunTime/60),(int)m_RunTime%60);
	SetDlgItemText(IDC_EDIT_ZEIT,Anz);

	CClientDC A(this);
	m_Viewport.Darstellen(&A);
	CDialog::OnTimer(nIDEvent);
}
