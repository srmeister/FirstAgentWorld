
// FirstAgentWorldMFCDoc.h: Schnittstelle der Klasse CFirstAgentWorldMFCDoc
//


#pragma once


class CFirstAgentWorldMFCDoc : public CDocument
{
protected: // Nur aus Serialisierung erstellen
	CFirstAgentWorldMFCDoc();
	DECLARE_DYNCREATE(CFirstAgentWorldMFCDoc)

// Attribute
public:

// Vorg�nge
public:

// �berschreibungen
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementierung
public:
	virtual ~CFirstAgentWorldMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Funktionen f�r die Meldungstabellen
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Hilfsfunktion, die Suchinhalt f�r Suchhandler festlegt
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
