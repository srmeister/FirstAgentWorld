// Koerper.cpp: Implementierung der Klasse CKoerper.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Koerper.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CKoerper::CKoerper(double dX, double dY, double dZ, double Mass, double Charge, double Spin, UINT uiID)
{
	m_pNext  = NULL;

	m_PktPos.SetPkt(dX, dY, dZ);

	m_dMasse = Mass;
	m_Charge = Charge;
	m_Spin = Spin;
	m_NormFest=0;
	m_RootLink=0;

	m_uiID = uiID;
}

int CKoerper::GetLinksCount()
{
	int iZaehler = 0;
	LinkList *cond;
	cond= m_RootLink;

	while(cond != NULL)
	{
		cond=cond->next;
		++iZaehler;
	}
	return iZaehler;
}

bool CKoerper::AddLink(CKoerper *pVerbindung)
{
	LinkList *cond;
	cond= m_RootLink;
	bool LinkOK=false;

	if (m_RootLink && PruefLink(pVerbindung))
	{
		while(cond->next != NULL)
		{
			cond=cond->next;
		}
		cond->next = new (LinkList);
		cond->next->Link = pVerbindung;
		cond->next->Alpha = 0;
		cond->next->fest = 50;
		cond->next->dist = 50;
		cond->next->next = NULL;
		LinkOK=true;
	} else if(PruefLink(pVerbindung))
	{
		m_RootLink = new(LinkList);
		m_RootLink->Link = pVerbindung;
		m_RootLink->dist = 50;
		m_RootLink->fest = 50;
		m_RootLink->next = NULL;
		LinkOK=true;
	}
	return LinkOK;
}

bool CKoerper::DelLink(CKoerper *pVerbindung)
{
	LinkList *cond,*del;
	cond= m_RootLink;

	bool ergebniss=false;

	if(cond && !PruefLink(pVerbindung))
	{
		if(cond->Link != pVerbindung)
		{
			while(cond->next && cond->next->Link != pVerbindung)
			{
				cond=cond->next;
			}
			if(cond->next && cond->next->Link == pVerbindung)
			{
				del = cond->next;
				cond->next = cond->next->next;
				delete del;
				ergebniss=true;
			}
		} else if(m_RootLink->Link == pVerbindung)
		{
			del=m_RootLink;
			m_RootLink=m_RootLink->next;
			delete del;
			ergebniss=true;
		}
	}
	return ergebniss;
}


bool CKoerper::PruefLink(CKoerper *pVerbindung) 
// Prüfung ob ein Link schon vorhanden ist
{
	bool LinkOK = true;
	LinkList *cond = m_RootLink;
	
	while (cond)
	{
		if(cond->Link == pVerbindung)
		{
			LinkOK = false; // Link ist schon vorhanden
		}
		cond = cond->next;
	}

	if(pVerbindung == this)
		LinkOK=false;
	return LinkOK;
}

CKoerper *CKoerper::GetLink(int iNr)
{
	if(iNr >= GetLinksCount())
	{
		return NULL;
	}else
	{
		int i=0;
		LinkList *cond = m_RootLink;
		
		while (cond && (i!=iNr))
		{
			cond=cond->next;
			i++;
		}
		return cond->Link;
	}
}

double CKoerper::GetAlpha(int iNr)
{
	if(iNr >= GetLinksCount())
	{
		return NULL;
	}else
	{
		int i=0;
		LinkList *cond = m_RootLink;
		
		while (cond && (i!=iNr))
		{
			cond=cond->next;
			i++;
		}
		return cond->Alpha;
	}
}

void CKoerper::SetAlpha(int iNr, double Alpha)
{
	if(iNr < GetLinksCount())
	{
		int i=0;
		LinkList *cond = m_RootLink;
		
		while (cond && (i!=iNr))
		{
			cond=cond->next;
			i++;
		}
		cond->Alpha = Alpha;
	}
}

void CKoerper::SetNormDist(int iNr, double Dist)  // "normale" entfernung
{
	if(iNr < GetLinksCount())
	{
		int i=0;
		LinkList *cond = m_RootLink;
		
		while (cond && (i!=iNr))
		{
			cond=cond->next;
			i++;
		}
		cond->dist = Dist;
		i=0;
		while(cond->Link->GetLink(i) != this)
		{
			i++;
		}
		if(cond->Link->GetNormDist(i) != Dist)
		{
			cond->Link->SetNormDist(i,Dist);
		}
	}
}

double CKoerper::GetDistLink(int iNr)  // AKTUELLE entfernung!
{
	if(iNr >= GetLinksCount())
	{
		return -1.0;
	}else
	{
		int i=0;
		LinkList *cond = m_RootLink;
		
		while (cond && (i!=iNr))
		{
			cond=cond->next;
			i++;
		}
		return m_PktPos.GetAbstand(cond->Link->m_PktPos);
	}
}

double CKoerper::GetNormDist(int iNr)  // "normale" entfernung!
{
	if(iNr >= GetLinksCount())
	{
		return -1.0;
	}else
	{
		int i=0;
		LinkList *cond = m_RootLink;
		
		while (cond && (i!=iNr))
		{
			cond=cond->next;
			i++;
		}
		return cond->dist;
	}
}

void CKoerper::SetFest(int iNr, double Fest)
{
	if(iNr < GetLinksCount())
	{
		int i=0;
		LinkList *cond = m_RootLink;
		
		while (cond && (i!=iNr))
		{
			cond=cond->next;
			i++;
		}
		cond->fest = Fest;
		i=0;
		while(cond->Link->GetLink(i) != this)
		{
			i++;
		}
		if(cond->Link->GetFest(i) != Fest)
		{
			cond->Link->SetFest(i,Fest);
		}
	}
}


double CKoerper::GetFest(int iNr)  // "normale" entfernung!
{
	if(iNr >= GetLinksCount())
	{
		return -1.0;
	}else
	{
		int i=0;
		LinkList *cond = m_RootLink;
		
		while (cond && (i!=iNr))
		{
			cond=cond->next;
			i++;
		}
		return cond->fest;
	}
}

void CKoerper::Expand()
{

	LinkList *cond;
	cond = m_RootLink;
	int i=0;

	while(cond)
	{
		double x,y,z,over=0.001;
				
		x = cond->Link->GetPosX() - GetPosX();
		y = cond->Link->GetPosY() - GetPosY();
		z = cond->Link->GetPosZ() - GetPosZ();

		over=(GetDistLink(i) - cond->dist)/(m_dMasse*10)*0.001;
		//if(over <= -0.001 || over >= 0.001)	// sollte später auch ohne bedingung gehen
		SetF(GetFX()+(x*over),GetFY()+(y*over),GetFZ()+(z*over));

		cond = cond->next;
		i++;
	}
}

void CKoerper::Radial()
{
	double DX,DY,DZ; // DZ unused
	double fX,fY,fZ=0, L;
	double RadForce=10;

	for(int i=0;i<GetLinksCount();i++)
	{
		DX = (GetPosX() - GetLink(i)->GetPosX() );
		DY = (GetPosY() - GetLink(i)->GetPosY() );
		DZ = (GetPosZ() - GetLink(i)->GetPosZ() );

		SetAlpha(i,RadForce*(3.1415 - acos((GetNX()*DX + GetNY()*DY)
			/ (sqrt(GetNX()*GetNX() +GetNY()*GetNY()	)
					* sqrt( DX*DX + DY*DY)))));
				
		fX =(DY*(GetNX()*DY - GetNY()*DX ) - DZ*(GetNZ()*DX - GetNX()*DZ));
		fY =(DZ*(GetNY()*DZ - GetNZ()*DY ) - DX*(GetNX()*DY - GetNY()*DX));
		//fZ =(DX*(GetNZ()*DX - GetNX()*DZ ) - DY*(GetNY()*DZ - GetNZ()*DY)) 
		
			
		L=sqrt((fX*fX)+(fY*fY)+(fZ*fZ));

		if(m_NormFest)
		{
			GetLink(i)->AddFX((fX/L/m_dMasse)*GetAlpha(i));
			GetLink(i)->AddFY((fY/L/m_dMasse)*GetAlpha(i));
			//GetLink(i)->AddFZ(fZ/L));
			//AddFX(-fX/L);
			//AddFY(-fY/L);
			//AddVZ(-fZ/L);
		}
		if(!m_NormFest && i>0)
		{
			GetLink(i)->AddFX((-fX/L/m_dMasse)*GetAlpha(i));
			GetLink(i)->AddFY((-fY/L/m_dMasse)*GetAlpha(i));
			//GetLink(i)->AddFZ(fZ/L));
			//AddFX((fX/L/m_dMasse)*GetAlpha(i));
			//AddFY((fY/L/m_dMasse)*GetAlpha(i));
			//AddVZ(-fZ/L);
		}
	}

}

void CKoerper::UpdateNorm()
{
	if (!m_NormFest && GetLinksCount()>0)
	{
		m_PktNorm.m_dX = (GetLink(0)->GetPosX() - m_PktPos.m_dX)/GetDistLink(0);
		m_PktNorm.m_dY = (GetLink(0)->GetPosY() - m_PktPos.m_dY)/GetDistLink(0);
		m_PktNorm.m_dZ = (GetLink(0)->GetPosZ() - m_PktPos.m_dZ)/GetDistLink(0);
	}
}

double CKoerper::GetNX() 
{
	double X=0;

	if(!m_NormFest && GetLinksCount()>0)
	{
		X = (GetLink(0)->GetPosX() - m_PktPos.m_dX)/GetDistLink(0);
	} else if(m_NormFest)
	{
		X=m_PktNorm.GetX();
	}

	return X;
}
double CKoerper::GetNY() 
{
	double Y=0;

	if(!m_NormFest && GetLinksCount()>0)
	{
		Y = (GetLink(0)->GetPosY() - m_PktPos.m_dY)/GetDistLink(0);
	} else if(m_NormFest)
	{
		Y=m_PktNorm.GetY();
	}

	return Y;
}
double CKoerper::GetNZ() 
{
	double Z=0;

	if(!m_NormFest && GetLinksCount()>0)
	{
		Z = (GetLink(0)->GetPosZ() - m_PktPos.m_dZ)/GetDistLink(0);
	} else if(m_NormFest)
	{
		Z=m_PktNorm.GetZ();
	}

	return Z;
}
