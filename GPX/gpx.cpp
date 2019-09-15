#include "gpx.h"
#include "xml.h"



#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef uint32_t index_t;
typedef uint32_t distance_t;


QGpx::QGpx()
{
	m_dTrackLaenge = 0.0;
}

void QGpx::Reverse()
{
	if (m_track.size() > 0)
	{
		QVector<CGeoPoint> tmp;
		for (int i = m_track.size()-1; i >= 0; i--) // 09.07.2019  Indexfehler -1
		{
			tmp.append(m_track[i]);
		}
		m_track = tmp;
	}

	if (m_route.size() > 0)
	{
		QVector<CGeoPoint> tmp;
		for (int i = m_route.size()-1; i >= 0; i--)           // 09.07.2019  Indexfehler -1
		{
			tmp.append(m_route[i]);
		}
		m_route = tmp;
	}
}
	


void QGpx::StartHere(double dLat, double dLon)
{
	double dAbstand = 10e10;
	int idx = -1;

	for( int i=0;i< m_track.size();i++ )
	{ 
		double d = m_track[i].distanceTo(dLat, dLon);
		if( d< dAbstand )
		{
			dAbstand = d;
			idx = i;
		}
	}

	QVector<CGeoPoint> tmp;
	for (int i = idx; i< m_track.size(); i++)
	{
		tmp.append(m_track[i] );
	}
	for (int i = 0; i < idx; i++)
	{
		tmp.append(m_track[i]);
	}
	m_track = tmp;

	if (m_route.size() > 0)
	{
		CreateRoute();
	}
}


CGeoPoint QGpx::getCenter()
{
	CGeoPoint min, max;

	getMinMax(min, max);

	return CGeoPoint(min.m_dLat + (max.m_dLat - min.m_dLat) / 2.0,
		             min.m_dLng + (max.m_dLng - min.m_dLng) / 2.0);

}

void QGpx::getMinMax(CGeoPoint & min, CGeoPoint & max )
{
	

	bool b = false;
	for each(CGeoPoint p in m_track )
	{
		if (b)
		{
			if (p.m_dLat < min.m_dLat) min.m_dLat = p.m_dLat;
			if (p.m_dLng < min.m_dLng) min.m_dLng = p.m_dLng;

			if (p.m_dLat > max.m_dLat) max.m_dLat = p.m_dLat;
			if (p.m_dLng > max.m_dLng) max.m_dLng = p.m_dLng;
		}
		else
		{
			min = max = p;
		}

		b = true;
	}

	for each(CGeoPoint p in m_route)
	{
		if (b)
		{
			if (p.m_dLat < min.m_dLat) min.m_dLat = p.m_dLat;
			if (p.m_dLng < min.m_dLng) min.m_dLng = p.m_dLng;

			if (p.m_dLat > max.m_dLat) max.m_dLat = p.m_dLat;
			if (p.m_dLng > max.m_dLng) max.m_dLng = p.m_dLng;
		}
		else
		{
			min = max = p;
		}

		b = true;
	}

}

void QGpx::CreateRoute()
{
	m_dMaxError = 0.150;                    // 150m
	m_dVerschiebenRichtungTrackEnde = 0.050; // 50m
	m_dMinAbstand = 0.150; //in km

	m_route.resize(0);

	int iBegin = 0;
	int iEnd = m_track.size() - 1; // Wenn Abstand Start-Ende < 100m, dann Endpunkt verschieben

	while (iEnd > 1)
	{
		double d = m_track[iBegin].distanceTo(m_track[iEnd]);
		if (d > 0.1) break; // 100m
		iEnd--;
	}

	if (iEnd < 2) return;

	
	while (1)
	{
		m_route.resize(0);
		m_route.append(m_track[0]);
		MaxDiff(iBegin, iEnd);
		m_route.append(m_track[m_track.size() - 1]);
		if (m_route.size() < 50) break;
		m_route.resize(0);
		m_dMaxError *= 1.1;
	}

	

	
	QString s; 
	s = QString("Track erstellt. \n%1 Zielpunkte \nmax Fehlerabstand %2 m").arg(m_route.size()).arg((int)(m_dMaxError * 1000));
	xml::InfoMsgBox(s, "");
}


void QGpx::MaxDiff(int i1, int i2)
{
	
	QVector3D v1 = m_track[i1].simpleToXYkm();
	QVector3D v2 = m_track[i2].simpleToXYkm();
	QVector3D vR = v2 - v1;
	vR.normalize();

	double dMax = 0;
	int idx = -1;
	for (int i = i1; i < i2; i++)
	{
		QVector3D v0 = m_track[i].simpleToXYkm();
		double dAbstabd = (v1 - v0).length();
		double d = v0.distanceToLine(v1, vR);
		if (d > m_dMaxError && d > dMax && dAbstabd > m_dMinAbstand)
		{
			idx = i;
			dMax = d;
		}
	}

	if (idx > 0)
	{
		MaxDiff(i1, idx);

		if (idx < m_track.size() - 1) // 07.09.2019 um 30m zum Trackende verschieben
		{
			QVector2D v1 = m_track[idx].simpleToXYkm();
			QVector2D v2 = m_track[idx+1].simpleToXYkm();
			QVector2D vR = v2 - v1;
			double dLen = vR.length();
			double dVerschiebenRichtungTrackEnde = m_dVerschiebenRichtungTrackEnde;
			while(dVerschiebenRichtungTrackEnde > dLen && idx < m_track.size() - 1)
			{ 
					dVerschiebenRichtungTrackEnde -= dLen;
					idx++;
					v1 = m_track[idx].simpleToXYkm();
					v2 = m_track[idx + 1].simpleToXYkm();
					vR = v2 - v1;
					dLen = vR.length();
			}
				
			{
				vR.normalize();
				QVector2D v3 = v1 + ( vR * dVerschiebenRichtungTrackEnde);
				m_route.append(CGeoPoint::simpleToLatLng(v3));
			}
		}
		else
		{
			m_route.append(m_track[idx]);
		}
		MaxDiff(idx, i2);
	}
}

bool QGpx::load(QString strDateiname)
{
	m_track.resize(0);
	m_route.resize(0);
	m_strDateiname = strDateiname;

	QDomDocument xdoc;
	if (xml::load(xdoc, m_strDateiname, &m_strError))
	{
		QDomElement  root = xml::getRoot(xdoc);
		QString      strRoot = xml::getTagName(root);
		m_dTrackLaenge = 0.0;
		m_bReadTrack = false;
		m_bReadRoute = false;
		m_track.resize(0);
		read(root);
		m_dTrackLaenge = trackLaenge();
		return true;
	}
	return false;
}

bool QGpx::save()
{
	return save( m_strDateiname );
}

bool QGpx::save(QString strDateiname)
{
	m_strDateiname = strDateiname;
	QDomDocument doc;

	doc.appendChild(doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\""));

	QDomElement root = doc.createElement("gpx");
	doc.appendChild(root);

	xml::setAttr(root,  "version", L"1.1");
	xml::setAttr(root,  "xmlns:gpxx", L"http://www.garmin.com/xmlschemas/GpxExtensions/v3");
	xml::setAttr(root,  "xmlns:gpxtpx", L"http://www.garmin.com/xmlschemas/TrackPointExtension/v1");
	xml::setAttr(root,  "xmlns", L"http://www.topografix.com/GPX/1/1");
	
	if (m_route.size() )                           
	{
		QDomElement rte = doc.createElement("rte");
		root.appendChild(rte);
		 
		if (m_strName.length() > 0)
		{
			QDomElement name_rte = doc.createElement("name");
			rte.appendChild(name_rte);
			name_rte.appendChild(doc.createTextNode(m_strName));
		}

		for (int i = 0; i < m_route.size(); i++)
		{
			QDomElement rtept = doc.createElement("rtept");
			rtept.setAttribute("lon", QString("%1").arg(m_route[i].m_dLng));
			rtept.setAttribute("lat", QString("%1").arg(m_route[i].m_dLat));
			rte.appendChild(rtept);
			QDomElement rtept_name = doc.createElement("name");
			rtept.appendChild(rtept_name);
			QString strName = QString("%1/%2").arg(i + 1).arg(m_route.size() );
			rtept_name.appendChild(doc.createTextNode(strName));
		}
	}

	if (m_track.size() > 0)
	{
		QDomElement trk = doc.createElement("trk");
		root.appendChild(trk);

		QDomElement trkseg = doc.createElement("trkseg");
		trk.appendChild(trkseg);

		QDomElement name_trk = doc.createElement("name");
		trk.appendChild(name_trk);

		name_trk.appendChild(doc.createTextNode(m_strName));

		for (int i = 0; i < m_track.size(); i++)
		{
			QDomElement trkpt = doc.createElement("trkpt");
			trkpt.setAttribute("lon", QString("%1").arg(m_track[i].m_dLng));
			trkpt.setAttribute("lat", QString("%1").arg(m_track[i].m_dLat));
			trkseg.appendChild(trkpt);

			QDomElement trkpt_ele = doc.createElement("ele");
			trkpt.appendChild(trkpt_ele);
			trkpt_ele.appendChild(doc.createTextNode(QString("%1").arg( m_track[i].m_dEle) ) );
		}
	}
	
	return xml::save(doc, m_strDateiname);
}


void QGpx::read(QDomElement & x)
{
	QDomNodeList nodelist = x.childNodes();

	for (int i1 = 0; i1 < nodelist.size(); i1++)
	{
		QDomElement n1 = nodelist.at(i1).toElement();
		QString s1 = n1.tagName();

		if (s1 == "ele")
		{
			QString s = n1.text();
			double dEle = n1.text().toDouble();
			m_track[m_track.size() - 1].m_dEle = dEle;
		}else
		if (s1 =="trkpt")
		{
			double dLat, dLon;
			xml::attr(n1, xml::eGet, "lat", dLat);
			xml::attr(n1, xml::eGet, "lon", dLon);
			CGeoPoint v( dLat, dLon);
			m_track.append(v);
			read(n1);
		}else
		if (s1 == "name")
		{
			m_strName = n1.text();
		}else
		if (s1 == "trk")
		{
			m_bReadTrack = true;
			read(n1);
			m_bReadTrack = false;
		}else
		if (s1 == "trkseg")
		{
			read(n1);
		}else
		if (s1 == "rte")
		{
			m_bReadRoute = true;
			read(n1);
			m_bReadRoute = true;
		}else
		if (s1 == "rtept")
		{
			double dLat, dLon;
			xml::attr(n1, xml::eGet, "lat", dLat);
			xml::attr(n1, xml::eGet, "lon", dLon);
			CGeoPoint v(dLat, dLon);
			m_route.append(v);
			read(n1);
		}
	}
}

//double  QGpx::abstand(double dLat1, double dLng1, double dLat2, double dLng2)
//{
//	double dB = ABSTAND_BREITENGRAD * (dLat1 - dLat2);
//	double dL = ABSTAND_BREITENGRAD * (dLng1 - dLng2) * cos(dLat1 *  M_PI / 180.0);
//	return sqrt(dB *dB + dL * dL);
//}

double QGpx::trackLaenge()
{
	if (m_track.size() < 2)
	{
		return 0;
	}

	double d = 0;
	CGeoPoint v0 = m_track[0];
	for (int i = 1; i < m_track.size(); i++)
	{
		CGeoPoint v1 = m_track[i];
		d += v0.distanceTo(v1);
		v0 = v1;
	}
	return d;
}








