
// ChildFrm.cpp: Implementierung der Klasse CChildFrame
//

#include "stdafx.h"
#include "FirstAgentWorldMFC.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// CChildFrame-Erstellung/Zerst�rung

CChildFrame::CChildFrame()
{
	// TODO: Hier Code f�r die Memberinitialisierung einf�gen
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ndern Sie die Fensterklasse oder die Stile hier, indem Sie CREATESTRUCT �ndern
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame-Diagnose

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame-Meldungshandler
