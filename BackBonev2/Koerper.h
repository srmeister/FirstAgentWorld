// Koerper.h: Schnittstelle für die Klasse CKoerper.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KOERPER_H__4FF114BD_C1BD_4CE8_8C73_C88FDCCFF7F2__INCLUDED_)
#define AFX_KOERPER_H__4FF114BD_C1BD_4CE8_8C73_C88FDCCFF7F2__INCLUDED_

#include "Punkt.h"

struct LinkList
{
	CKoerper *Link;
	// Link Eigenschaften
	double Alpha;	//Std.Winkel
	double dist;	//Std.Entfernung
	double fest;	//Festigkeit
	LinkList *next;
};

class CKoerper
{
	friend class CWelt;
private:
	// Verkettete Liste
	CKoerper *m_pNext;
	LinkList *m_RootLink;

	//Eigenschaften
	double m_dMasse;
	double m_Charge;
	double m_Spin;
//	double m_MinRad,
//		m_MaxRad;		// unused
	
	//Geschwindigkeits- und Richtungsvektoren (Betrag == V)
	CPunkt m_PktFRichtung;
	CPunkt m_PktPos;
	CPunkt m_PktNorm;

	bool m_NormFest;

	//Identifikation
	UINT m_uiID;
public:

	// Konstruktor, Destruktor
	CKoerper(double dX, double dY, double dZ, double Mass, double Charge, double Spin, UINT uiID);

	inline ~CKoerper() {if(m_pNext != NULL) delete m_pNext;}
	
	// Eigenschaften
	inline double GetMass() {return m_dMasse;}
	inline void SetMass(double dMasse){ m_dMasse = dMasse; }
	inline double GetCharge() {return m_Charge;}
	inline void SetCharge(double Charge){ m_Charge = Charge; }

	inline UINT GetID() {return m_uiID;}

	// Koordinaten
	inline void SetPos(double dX, double dY, double dZ) {m_PktPos.SetPkt(dX, dY, dZ);}
	inline void SetPos(CPunkt PktPos) {m_PktPos.SetPkt(PktPos.GetX(), PktPos.GetY(), PktPos.GetZ());}
	inline double GetPosX() {return m_PktPos.GetX();}
	inline double GetPosY() {return m_PktPos.GetY();}
	inline double GetPosZ() {return m_PktPos.GetZ();}
	
	// Vektoren
	inline CPunkt GetRichtung() {return m_PktFRichtung;}

	// Kraft
	inline void SetF(double dFX, double dFY, double dFZ) {m_PktFRichtung.SetPkt(dFX, dFY, dFZ);}
	inline void SetF(CPunkt PktFRichtung) {m_PktFRichtung.SetPkt(PktFRichtung.GetX(), PktFRichtung.GetY(), PktFRichtung.GetZ());}
	inline void AddFX(double DeltaFX) {m_PktFRichtung.AddX(DeltaFX);}
	inline void AddFY(double DeltaFY) {m_PktFRichtung.AddY(DeltaFY);}
	inline void AddFZ(double DeltaFZ) {m_PktFRichtung.AddZ(DeltaFZ);}
	inline double GetFX() {return m_PktFRichtung.GetX();}
	inline double GetFY() {return m_PktFRichtung.GetY();}
	inline double GetFZ() {return m_PktFRichtung.GetZ();}

	// Geschwindigkeit:
	inline double GetVX() {return m_PktFRichtung.GetX()/m_dMasse;}
	inline double GetVY() {return m_PktFRichtung.GetY()/m_dMasse;}
	inline double GetVZ() {return m_PktFRichtung.GetZ()/m_dMasse;}
	inline double GetGeschw() {return m_PktFRichtung.GetRelativLaenge()/m_dMasse;}
	inline void SetV(double dVX, double dVY, double dVZ) {m_PktFRichtung.SetPkt(GetFX()+dVX*m_dMasse, GetFY()+dVY*m_dMasse, GetFZ()+dVZ*m_dMasse);}
	inline void SetGeschw(double dG){
		m_PktFRichtung.m_dX *= dG;
		m_PktFRichtung.m_dY *= dG;
		m_PktFRichtung.m_dZ *= dG;
	}

	// Normale
	double GetNX();
	double GetNY();
	double GetNZ();

	double GetNormLaenge() { UpdateNorm();return m_PktNorm.GetRelativLaenge();}
	void UpdateNorm();

	bool GetNormFest() {return m_NormFest;}
	void SetNormFest(bool NF)
	{
		m_NormFest=NF;
	}
	void SetPktNorm(float NX, float NY, float NZ)
	{
		m_PktNorm.m_dX = NX;
		m_PktNorm.m_dY = NY;
		m_PktNorm.m_dZ = NZ;
	}

//##### Links ##########
	// Allgemein
	int GetLinksCount();
	bool AddLink(CKoerper *pVerbindung);
	bool DelLink(CKoerper *pVerbindung);
	bool PruefLink(CKoerper *pVerbindung);
	CKoerper *GetLink(int iNr);
	// Link eigenschaften
	double GetAlpha(int iNr);			// Winkel zur Normalen
	void SetAlpha(int iNr, double Alpha);
	void SetNormDist(int iNr, double Dist);  // Entfernung
	double GetNormDist(int iNr);
	double GetDistLink(int iNr);
	void Expand();	// Festigkeit
	void Radial();	// Radialkraft zur Normale
	void SetFest(int, double);
	double GetFest(int);
	
};

#endif // !defined(AFX_KOERPER_H__4FF114BD_C1BD_4CE8_8C73_C88FDCCFF7F2__INCLUDED_)
