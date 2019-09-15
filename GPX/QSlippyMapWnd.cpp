#include "QSlippyMapWnd.h"
#include "slippymap.h"
#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include "Settings.h"

QSlippyMapWnd::QSlippyMapWnd(QWidget *parent)
	: QWidget(parent)
{

	m_slippyMap = new SlippyMap(this);
	m_bPressed = false;
	ui.setupUi(this);

	setCenter( CGeoPoint(53.5, 7.5) );

	connect(m_slippyMap, SIGNAL(updated(QRect)), SLOT(updateMap(QRect)));
	
}

QSlippyMapWnd::~QSlippyMapWnd()
{
	
}

void QSlippyMapWnd::setCenter(CGeoPoint geoPos)
{
	m_slippyMap->m_geoCenter = geoPos;
	m_slippyMap->invalidate();
}

void QSlippyMapWnd::resizeEvent(QResizeEvent *)
{
	m_slippyMap->m_iWidth = width();
	m_slippyMap->m_iHeight = height();
	m_slippyMap->invalidate();
}

void QSlippyMapWnd::updateMap(const QRect &r)
{
	update(r);
}

void QSlippyMapWnd::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() != Qt::LeftButton)
		return;
	m_bPressed = true;
	pressPos = dragPos = event->pos();
	
}

void QSlippyMapWnd::mouseMoveEvent(QMouseEvent *event)
{
	if (!event->buttons())
		return;
		
	QPoint delta = event->pos() - pressPos;
	pressPos = event->pos();
	m_slippyMap->pan(delta);
	update();
	
}

void QSlippyMapWnd::mouseReleaseEvent(QMouseEvent *)
{
	m_bPressed = false;
	update();
}

void QSlippyMapWnd::wheelEvent(QWheelEvent *event)
{
	if (m_slippyMap->m_iZoom >= 10 && event->delta() < 0)
	{
		m_slippyMap->m_iZoom--;
		m_slippyMap->invalidate();
	}

	if (m_slippyMap->m_iZoom < 18 && event->delta() > 0)
	{
		m_slippyMap->m_iZoom++;
		m_slippyMap->invalidate();
	}

}

void QSlippyMapWnd::paintEvent(QPaintEvent *event)
{
	QPainter p;
	p.begin(this);
	m_slippyMap->render(&p, event->rect());
	
	p.setPen(Qt::black);
	p.drawText(rect(), Qt::AlignBottom | Qt::TextWordWrap,
		"Map data CCBYSA 2009 OpenStreetMap.org contributors");
	p.end();

	

	p.begin(this);
	QPen Pen1(Qt::black);
	Pen1.setWidthF( 3.0 );
	p.setPen( Pen1);


	bool b = false;
	CGeoPoint pos1;
	for each(CGeoPoint pos2 in m_Gpx.m_track)
	{
		if (b)
		{ 
			p.drawLine(m_slippyMap->toScreenPos(pos1), m_slippyMap->toScreenPos(pos2));
			p.drawEllipse(m_slippyMap->toScreenPos(pos1), 2, 2);
		}
	
		pos1 = pos2;
		b = true;
	}

	QPen PenRed(Qt::red);    PenRed.setWidthF(3.0);
	QPen PenGreen(Qt::green); PenRed.setWidthF(3.0);
	p.setPen(PenRed);
	int i = 1;
	for each(CGeoPoint pos in m_Gpx.m_route)
	{
		QPointF pt = m_slippyMap->toScreenPos(pos);
		p.drawEllipse( pt , 4, 4);
		QString s = QString("%1/%2").arg(i).arg(m_Gpx.m_route.size());
		p.drawText(pt + QPointF(10, -10), s);
		i++;
	}
	
	if (m_Gpx.m_track.size() >= 2 && m_Gpx.m_route.size() == 0)
	{
		CGeoPoint pos = m_Gpx.m_track[0];
		QPointF pt = m_slippyMap->toScreenPos(pos);
		p.drawText( pt + QPointF(10, -10), "A");

		p.setPen(PenGreen);
		pos = m_Gpx.m_track.last();
		pt = m_slippyMap->toScreenPos(pos);
		p.drawText(pt + QPointF(10, -10), "B");
	}
	
	p.end();

}


bool QSlippyMapWnd::load_gpx(QString strFilename)
{
	bool b = m_Gpx.load(strFilename);

	if (m_Gpx.m_route.size() == 0 && m_Gpx.m_route.size()) return false;
	
	if (m_Gpx.m_route.size() == 0 && m_Gpx.m_track.size() > 3)
	{
		int iRc = xml::YesNoMsgBox(QString().fromStdWString(L"Route erstellen ?                "), "GPX");
		if (iRc == QMessageBox::Yes)
		{
			m_Gpx.CreateRoute();
		}
	}

	CGeoPoint pos = m_Gpx.getCenter();
	m_slippyMap->m_iZoom = 12;
	this->setCenter(pos);
	update();
	return b;
}

void QSlippyMapWnd::route_erstellen()
{
	m_Gpx.CreateRoute();
	update();
}

void QSlippyMapWnd::route_loesche()
{
	m_Gpx.m_route.resize(0);
	update();
}

void QSlippyMapWnd::track_umkehren()
{
	m_Gpx.Reverse();
	update();
}

bool QSlippyMapWnd::load_gpx()
{
	QString s("C:\\");
	QStringList	l = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
	if (l.size() > 0)
		s = l[0];
	QString strFileName = QFileDialog::getOpenFileName(this, tr("Open GPX"), s, tr("GPX-Files (*.gpx)"));
	bool b =  load_gpx(strFileName );

	return b;
}


void QSlippyMapWnd::save_gpx_to_pc()
{
	save_gpx(SETTINGS_SAVE_DOCUMENT);
}

void QSlippyMapWnd::save_gpx_to_garmin()
{
	if (m_Gpx.m_route.size() == 0)
	{
		int iRc = xml::YesNoMsgBox(QString().fromStdWString(L"GPX enhält keine Route. Trotzdem speichern ?"), "GPX");
		if (iRc != QMessageBox::Yes)
		{
			return;
		}
	}

	save_gpx(SETTINGS_SAVE_GARMIN);
}

void QSlippyMapWnd::save_gpx(QString strSettingKey)
	{

	QString strDir = Settings.value(strSettingKey, "c:\\").toString();
	QString strFilename1 = strDir + "\\" + m_Gpx.m_strName + ".gpx";
	QString strFilename2 = QFileDialog::getSaveFileName(this, "GPX-Track", strFilename1, "GPX (*.gpx)");
	if (strFilename2.isEmpty()) return;

	{
		QFileInfo f2(strFilename2);
		QString s = f2.dir().absolutePath();
		Settings.setValue(strSettingKey, s);
	}

	m_Gpx.save(strFilename2);
}
