// Punkt.h: Schnittstelle für die Klasse CPunkt.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUNKT_H__A93CDE6F_5698_4598_B613_F2FC53859C49__INCLUDED_)
#define AFX_PUNKT_H__A93CDE6F_5698_4598_B613_F2FC53859C49__INCLUDED_

class CPunkt  
{
	friend class CKoerper;
private:
	double m_dX;
	double m_dY;
	double m_dZ;
public:
	CPunkt();
	CPunkt(double dX, double dY, double dZ);

	double GetAbstand(const CPunkt &ZielPkt);

	double GetDelta(double dKoord1, double dKoord2){
		if(dKoord1 > dKoord2)
			return (dKoord1 - dKoord2);
		if(dKoord2 > dKoord1)
			return (dKoord2 - dKoord1);
		else
			return (0.0);
	}
	
	void SetPkt(double dX, double dY, double dZ) {m_dX = dX; m_dY = dY; m_dZ = dZ;}
	void SetX(double dX) {m_dX = dX;};
	void SetY(double dY) {m_dY = dY;};
	void SetZ(double dZ) {m_dZ = dZ;};

	void AddX(double dX) {m_dX += dX;};
	void AddY(double dY) {m_dY += dY;};
	void AddZ(double dZ) {m_dZ += dZ;};

	double GetX() {return m_dX;};
	double GetY() {return m_dY;};
	double GetZ() {return m_dZ;};

	double GetRelativLaenge();

	void PrintPkt(HWND hWnd);

	virtual ~CPunkt() {};
};

#endif // !defined(AFX_PUNKT_H__A93CDE6F_5698_4598_B613_F2FC53859C49__INCLUDED_)
