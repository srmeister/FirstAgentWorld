// Welt.cpp: Implementierung der Klasse CWelt.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Welt.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CWelt::CWelt()
{
	m_FRad			= true;
	m_FExp			= true;
	m_G				= 0; // 9.81;
	m_Vmax			= 3.0;
	laufZeit		= 0;
	m_pKrpConductor = NULL;
	m_pKrpRoot      = NULL;

	m_X=100;
	m_Y=100;
	m_Z=100;
}
CWelt::CWelt(double X, double Y, double Z)
{
	CWelt();

	m_X=X;
	m_Y=Y;
	m_Z=Z;
}

CWelt::~CWelt()
{

}


void CWelt::AddKoerper(double x, double y, double Mass, double Charge, double Spin)
{
	if (!m_pKrpRoot)
	{
		m_pKrpRoot = new CKoerper(x, y, 0, Mass, Charge, Spin, GetCount());
		m_pKrpConductor = m_pKrpRoot;
	}
	else
	{
		m_pKrpConductor->m_pNext = new CKoerper(x, y, 0, Mass, Charge, Spin, GetCount());
		m_pKrpConductor = m_pKrpConductor->m_pNext;
	}
}

CKoerper* CWelt::GetKoerper(int Nr)
{
	int i=1;
	m_pKrpCondTmp=m_pKrpRoot;
	while (i!=Nr && m_pKrpCondTmp)
	{
		m_pKrpCondTmp=m_pKrpCondTmp->m_pNext;
		i++;
	}
	return m_pKrpCondTmp;
}

void CWelt::Update()
{
	m_pKrpCondTmp=m_pKrpRoot;
	laufZeit++;
	do
	{
		Kraft();
		m_pKrpCondTmp->SetPos(m_pKrpCondTmp->GetPosX()+m_pKrpCondTmp->GetVX(), m_pKrpCondTmp->GetPosY()+m_pKrpCondTmp->GetVY(), 0);
		m_pKrpCondTmp = m_pKrpCondTmp->m_pNext;
	} while (m_pKrpCondTmp);
}

void CWelt::Kraft()
{
	// Maximalgeschwindigkeit
	if(m_pKrpCondTmp->GetGeschw()>m_Vmax)
	{
		m_pKrpCondTmp->SetF((m_pKrpCondTmp->GetFX()/m_pKrpCondTmp->GetGeschw())*m_Vmax,(m_pKrpCondTmp->GetFY()/m_pKrpCondTmp->GetGeschw())*m_Vmax,(m_pKrpCondTmp->GetFZ()/m_pKrpCondTmp->GetGeschw())*m_Vmax);
	}
	// allgemeine verlangsamung
	//m_pKrpCondTmp->SetF(m_pKrpCondTmp->GetFX()*0.99,m_pKrpCondTmp->GetFY()*0.99,m_pKrpCondTmp->GetFZ()*0.99);
	
	// Schwerkraft
	/*if (m_pKrpCondTmp->GetPosY()>0 )
	{
		m_pKrpCondTmp->SetF(m_pKrpCondTmp->GetFX(),m_pKrpCondTmp->GetFY()-((m_pKrpCondTmp->GetMass()*m_G)/m_Hz),0);
	}*/

	// Links
	if (m_pKrpCondTmp->GetLinksCount() && m_FExp)
	{
		m_pKrpCondTmp->Expand();
	}
	
	if (m_FRad)		/*m_pKrpCondTmp->GetNormFest() && m_pKrpCondTmp->GetLinksCount() &&*/ 
	{
		m_pKrpCondTmp->Radial();

	}
}

int CWelt::GetCount()
{
	int i=1;
	m_pKrpCondTmp = m_pKrpRoot;
	if(m_pKrpCondTmp != NULL)
	{
		while (m_pKrpCondTmp->m_pNext != NULL)
		{
			m_pKrpCondTmp = m_pKrpCondTmp->m_pNext;
			i++;
		}
		return i;
	} 
	else
	{
		return 0;
	}
}

bool CWelt::AddLink(int QuellID, int ZielID)
{
	GetKoerper(QuellID)->AddLink(GetKoerper(ZielID));
	return GetKoerper(ZielID)->AddLink(GetKoerper(QuellID));	
}

bool CWelt::DelLink(int QuellID, int ZielID)
{
	bool e=false;
	if(GetKoerper(QuellID)->DelLink(GetKoerper(ZielID)))
		if(GetKoerper(ZielID)->DelLink(GetKoerper(QuellID)))
			e=true;
	return e;	
}

void CWelt::SetFRad(bool FRad)
{
	m_FRad = FRad;
}
bool CWelt::GetFRad()
{
	return m_FRad;
}
void CWelt::SetFExp(bool FExp)
{
	m_FExp = FExp;
}
bool CWelt::GetFExp()
{
	return m_FExp;
}

double CWelt::GetDimX()
{
	return m_X;
}

double CWelt::GetDimY()
{
	return m_Y;
}

double CWelt::GetDimZ()
{
	return m_Z;
}

void CWelt::SetDim(double X,double Y,double Z)
{
	m_X=X;
	m_Y=Y;
	m_Z=Z;
}

void CWelt::LLReset()
{
	m_pKrpCondTmp = m_pKrpRoot;
}
CKoerper *CWelt::LLGetNext()
{
	CKoerper *retVal = m_pKrpCondTmp;
	if (m_pKrpCondTmp)
	{
		m_pKrpCondTmp = m_pKrpCondTmp->m_pNext;
	}
	else
	{
		m_pKrpCondTmp = NULL;

	}
	return retVal;
}