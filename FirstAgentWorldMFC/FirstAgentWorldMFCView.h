
// FirstAgentWorldMFCView.h: Schnittstelle der Klasse CFirstAgentWorldMFCView
//

#pragma once


class CFirstAgentWorldMFCView : public CView
{
protected: // Nur aus Serialisierung erstellen
	CFirstAgentWorldMFCView();
	DECLARE_DYNCREATE(CFirstAgentWorldMFCView)

// Attribute
public:
	CFirstAgentWorldMFCDoc* GetDocument() const;

// Vorgänge
public:

// Überschreibungen
public:
	virtual void OnDraw(CDC* pDC);  // Überschrieben, um diese Ansicht darzustellen
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementierung
public:
	virtual ~CFirstAgentWorldMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Funktionen für die Meldungstabellen
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Debugversion in FirstAgentWorldMFCView.cpp
inline CFirstAgentWorldMFCDoc* CFirstAgentWorldMFCView::GetDocument() const
   { return reinterpret_cast<CFirstAgentWorldMFCDoc*>(m_pDocument); }
#endif

