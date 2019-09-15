#pragma once

#include "qobject.h"
#include "qstring.h"
#include "xml.h"
#include "qvector2d.h"
#include "qvector.h"
#include <stdint.h>

#include "GeoPoint.h"


class QGpx : public QObject
{
	Q_OBJECT

	public:

	QString m_strError;
	QString m_strDateiname;
	QString m_strName;
	double  m_dTrackLaenge;

	QGpx(); 

	bool load(QString strDateiname);
	
	bool save();
	bool save(QString strDateiname);

	QVector<CGeoPoint> m_track;
	QVector<CGeoPoint> m_route;

	void CreateRoute();
	void Reverse();
	void StartHere(double dLat, double dLon);

	CGeoPoint getCenter();
	void getMinMax(CGeoPoint & min, CGeoPoint & max);
	double trackLaenge();
	
private:

	void read(QDomElement & x);
	// double abstand(double dLat1, double dLng1, double dLat2, double dLng2);
	

	void MaxDiff(int i1, int i2);
	
	bool m_bReadTrack;
	bool m_bReadRoute;
	double m_dMaxError;
	double m_dVerschiebenRichtungTrackEnde;
	double m_dMinAbstand;
};
