
// FirstAgentWorldMFCView.cpp: Implementierung der Klasse CFirstAgentWorldMFCView
//

#include "stdafx.h"
// SHARED_HANDLERS können in einem ATL-Projekt definiert werden, in dem Vorschau-, Miniaturansichts- 
// und Suchfilterhandler implementiert werden, und die Freigabe von Dokumentcode für das Projekt wird ermöglicht.
#ifndef SHARED_HANDLERS
#include "FirstAgentWorldMFC.h"
#endif

#include "FirstAgentWorldMFCDoc.h"
#include "FirstAgentWorldMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFirstAgentWorldMFCView

IMPLEMENT_DYNCREATE(CFirstAgentWorldMFCView, CView)

BEGIN_MESSAGE_MAP(CFirstAgentWorldMFCView, CView)
	// Standarddruckbefehle
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFirstAgentWorldMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CFirstAgentWorldMFCView-Erstellung/Zerstörung

CFirstAgentWorldMFCView::CFirstAgentWorldMFCView()
{
	// TODO: Hier Code zur Konstruktion einfügen

}

CFirstAgentWorldMFCView::~CFirstAgentWorldMFCView()
{
}

BOOL CFirstAgentWorldMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Ändern Sie hier die Fensterklasse oder die Darstellung, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

// CFirstAgentWorldMFCView-Zeichnung

void CFirstAgentWorldMFCView::OnDraw(CDC* /*pDC*/)
{
	CFirstAgentWorldMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: Code zum Zeichnen der nativen Daten hinzufügen
}


// CFirstAgentWorldMFCView drucken


void CFirstAgentWorldMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFirstAgentWorldMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CFirstAgentWorldMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CFirstAgentWorldMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: Bereinigung nach dem Drucken einfügen
}

void CFirstAgentWorldMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFirstAgentWorldMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFirstAgentWorldMFCView-Diagnose

#ifdef _DEBUG
void CFirstAgentWorldMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CFirstAgentWorldMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFirstAgentWorldMFCDoc* CFirstAgentWorldMFCView::GetDocument() const // Nichtdebugversion ist inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFirstAgentWorldMFCDoc)));
	return (CFirstAgentWorldMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CFirstAgentWorldMFCView-Meldungshandler
