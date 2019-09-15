#pragma once

#include "QPointF"
#include "QVector2D"
#include "QVector3D"




class CGeoPoint
{

public:

	double m_dLat;
	double m_dLng;
	double m_dEle;


	CGeoPoint() { init(); };
	CGeoPoint(double dLat, double dLng, double dEle = 0);
	CGeoPoint(const CGeoPoint & n) { set(n); };
	CGeoPoint operator=(const CGeoPoint & n) { set(n); return *this; };

	void init()
	{
		m_dLat = 0;
		m_dLng = 0;
		m_dEle = 0;
	}

	void set(const CGeoPoint & n)
	{
		m_dLat = n.m_dLat;
		m_dLng = n.m_dLng;
		m_dEle = n.m_dEle;
	}

	QVector2D simpleToXYkm();

	static CGeoPoint simpleToLatLng(QVector2D v);
	
	double distanceTo(const CGeoPoint & n);
	double distanceTo(double dLat, double dLng);
};
