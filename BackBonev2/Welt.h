// Welt.h: Schnittstelle für die Klasse CWelt.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WELT_H__928B87ED_C500_46D3_83D0_14572613D40C__INCLUDED_)
#define AFX_WELT_H__928B87ED_C500_46D3_83D0_14572613D40C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Koerper.h"

class CWelt  
{
private:
	double m_G,
		m_Vmax;
	double m_X,
		m_Y,
		m_Z;

	bool	m_FRad,
		m_FExp;
	
	CKoerper *m_pKrpRoot;
	CKoerper *m_pKrpConductor;
	CKoerper *m_pKrpCondTmp;

public:
	CWelt();
	CWelt(double,double,double);
	virtual ~CWelt();

	void LLReset();
	CKoerper *LLGetNext();

	void Update();
	
	double GetDimX();
	double GetDimY();
	double GetDimZ();
	void SetDim(double,double,double);

	void Kraft();

	//Kräfte
	void SetFRad(bool);
	bool GetFRad();
	void SetFExp(bool);
	bool GetFExp();

	void AddKoerper(double x, double y, double Mass, double Charge, double Spin);
	bool AddLink(int QuellID, int ZielID);
	bool DelLink(int QuellID, int ZielID);

	CKoerper* GetKoerper(int Nr);
	int GetCount();

	int laufZeit;
};

#endif // !defined(AFX_WELT_H__928B87ED_C500_46D3_83D0_14572613D40C__INCLUDED_)
