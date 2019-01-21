// Welt.h: Schnittstelle für die Klasse CWelt.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WELT_H__928B87ED_C500_46D3_83D0_14572613D40C__INCLUDED_)
#define AFX_WELT_H__928B87ED_C500_46D3_83D0_14572613D40C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Agent.h"
#include "AgentList.h"

class Environment  
{
private:
	double m_SizeX,
		m_SizeY,
		m_SizeZ;
		

public:
	Environment();
	Environment(double,double,double);
	virtual ~Environment();
	
	void Update();
	
	double GetDimX();
	double GetDimY();
	double GetDimZ();
	void SetDim(double,double,double);

	void AddKoerper(double x, double y, double Energy);

	Agent* GetKoerper(int Nr);
	AgentList agentList;
	int GetCount();

	int laufZeit;
};

#endif // !defined(AFX_WELT_H__928B87ED_C500_46D3_83D0_14572613D40C__INCLUDED_)
