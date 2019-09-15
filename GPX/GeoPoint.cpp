
#include "GeoPoint.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef  ABSTAND_BREITENGRAD
#define  ABSTAND_BREITENGRAD 111.3
#endif


CGeoPoint::CGeoPoint(double dLat, double dLng, double dEle /*= 0*/)
{
	m_dLat = dLat;
	m_dLng = dLng;
	m_dEle = dEle;
}

QVector2D CGeoPoint::simpleToXYkm()
{
	double dB = ABSTAND_BREITENGRAD * (m_dLat);
	double dL = ABSTAND_BREITENGRAD * (m_dLng)* cos(m_dLat *  M_PI / 180.0);
	return QVector2D(dL, dB);
}


CGeoPoint CGeoPoint::simpleToLatLng(QVector2D v)
{
	double dLat = v.y() / ABSTAND_BREITENGRAD;
	double dLon = v.x() / (ABSTAND_BREITENGRAD *  cos(dLat *  M_PI / 180.0));
	return CGeoPoint(dLat, dLon);
}

double CGeoPoint::distanceTo(const CGeoPoint & n)
{
	return distanceTo(n.m_dLat, n.m_dLng);
}

double CGeoPoint::distanceTo(double dLat, double dLng)
{
	double dB = ABSTAND_BREITENGRAD * (m_dLat - dLat);
	double dL = ABSTAND_BREITENGRAD * (m_dLng - dLng) * cos(m_dLat *  M_PI / 180.0);
	return sqrt(dB *dB + dL * dL);
}
