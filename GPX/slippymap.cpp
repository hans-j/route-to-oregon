/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

// 10.09.2019
// Diese Code ist den Qt-Beispielen entnommen


#include <math.h>

#include <QtWidgets>
#include <QtNetwork>
#include "slippymap.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


// tile size in pixels
const int tdim = 256;

QPointF SlippyMap::tileForCoordinate(CGeoPoint geoPos, int zoom)
{
	qreal lat = geoPos.m_dLat;
	qreal lng = geoPos.m_dLng;
    qreal zn = static_cast<qreal>(1 << zoom);
    qreal tx = (lng + 180.0) / 360.0;
    qreal ty = (1.0 - log(tan(lat * M_PI / 180.0) +
                          1.0 / cos(lat * M_PI / 180.0)) / M_PI) / 2.0;
    return QPointF(tx * zn, ty * zn);
}



CGeoPoint SlippyMap::GeoPosFromTile(qreal tx, qreal ty, int zoom)
{
	qreal zn = static_cast<qreal>(1 << zoom);
	qreal  lng = tx / zn * 360.0 - 180.0;
	qreal n = M_PI - 2 * M_PI * ty / zn;
	qreal  lat = 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));

	return CGeoPoint(lat, lng);
}

SlippyMap::SlippyMap(QWidget *parent)
    : QObject(parent), m_iWidth(800), m_iHeight(600), m_iZoom(13), m_iMissingTiles(0),m_geoCenter(53.5, 7.5 )
   
{
    m_emptyTile = QPixmap(tdim, tdim);
    m_emptyTile.fill(Qt::lightGray);

    QNetworkDiskCache *cache = new QNetworkDiskCache;
    cache->setCacheDirectory(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    m_manager.setCache(cache);
    connect(&m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));
}

void SlippyMap::invalidate()
{
    if (m_iWidth <= 0 || m_iHeight <= 0)
        return;

    // QPointF ct = tileForCoordinate(m_dLatitude, m_dLongitude, m_iZoom);
	QPointF ct = tileForCoordinate(m_geoCenter, m_iZoom);
    qreal tx = ct.x();
    qreal ty = ct.y();

    // top-left corner of the center tile
    int xp = m_iWidth / 2 - (tx - floor(tx)) * tdim;
    int yp = m_iHeight / 2 - (ty - floor(ty)) * tdim;

    // first tile vertical and horizontal
    int xa = (xp + tdim - 1) / tdim;
    int ya = (yp + tdim - 1) / tdim;
    int xs = static_cast<int>(tx) - xa;
    int ys = static_cast<int>(ty) - ya;

    // offset for top-left tile
    m_offset = QPoint(xp - xa * tdim, yp - ya * tdim);

    // last tile vertical and horizontal
    int xe = static_cast<int>(tx) + (m_iWidth - xp - 1) / tdim;
    int ye = static_cast<int>(ty) + (m_iHeight - yp - 1) / tdim;

    // build a rect
    m_tilesRect = QRect(xs, ys, xe - xs + 1, ye - ys + 1);

    if (m_url.isEmpty())
        download();

    emit updated(QRect(0, 0, m_iWidth, m_iHeight));
}

void SlippyMap::render(QPainter *p, const QRect &rect)
{
	m_iMissingTiles = 0;
	for (int x = 0; x <= m_tilesRect.width(); ++x)
	{
		for (int y = 0; y <= m_tilesRect.height(); ++y)
		{
			QPoint tp(x + m_tilesRect.left(), y + m_tilesRect.top());
			QString strKey = QTile::getKey(m_iZoom, tp);
			QRect box = tileRect(tp);
			if (rect.intersects(box))
			{
				if (m_tilePixmaps.contains(strKey))
				{
					p->drawPixmap(box, m_tilePixmaps.value(strKey).m_pixmap);
				}
				else
				{
					p->drawPixmap(box, m_emptyTile);
					m_iMissingTiles++;
				}
			}
		}
	}
}

void SlippyMap::pan(const QPoint &delta)
{
    QPointF dx = QPointF(delta) / qreal(tdim);
    //QPointF center = tileForCoordinate(m_dLatitude, m_dLongitude, m_iZoom) - dx;
	QPointF center = tileForCoordinate(m_geoCenter, m_iZoom) - dx;
	
	m_geoCenter = GeoPosFromTile(center.x(),center.y(), m_iZoom);
   /* m_dLatitude  = latitudeFromTile(center.y(),   m_iZoom);
    m_dLongitude = longitudeFromTile(center.x(), m_iZoom);*/
    invalidate();
}

void SlippyMap::handleNetworkData(QNetworkReply *reply)
{
	QStringList l  = reply->request().attribute(QNetworkRequest::User).toStringList();
	QString strUrl = l[0];
	int iZoom      = l[1].toInt();
	int iX         = l[2].toInt();
	int iY = l[3].toInt();

	

    QImage img;
    //QPoint tp = reply->request().attribute(QNetworkRequest::User).toPoint();
    QUrl url = reply->url();
    if (!reply->error())
        if (!img.load(reply, 0))
            img = QImage();
    reply->deleteLater();

	QTile newTile(m_iZoom, iX, iY);
	newTile.m_pixmap = img.isNull() ? m_emptyTile : QPixmap::fromImage(img);
	QString strKey = newTile.getKey();

    m_tilePixmaps[strKey] = newTile;
 
	QWidget * p = (QWidget*) this->parent();
	

    emit updated(tileRect( newTile.m_tp) );


    download();
}



void SlippyMap::download()
{
    QPoint grab(0, 0);
	for (int x = 0; x <= m_tilesRect.width(); ++x)
	{
		for (int y = 0; y <= m_tilesRect.height(); ++y) 
		{
			
			QPoint tp = m_tilesRect.topLeft() + QPoint(x, y);
			QString strKey = QTile::getKey(m_iZoom, tp);
			if (!m_tilePixmaps.contains(strKey))
			{
				grab = tp;
				break;
			}
		}
	}
    
	if (grab == QPoint(0, 0)) 
	{
        m_url = QUrl();
        return;
    }


	//QString strKey = QTile::getKey(m_iZoom, grab );

	QStringList l;
	l << m_url.toString();
	l << QString("%1").arg(m_iZoom);
	l << QString("%1").arg(grab.x() );
	l << QString("%1").arg(grab.y() );


    QString path = "http://tile.openstreetmap.org/%1/%2/%3.png";
    m_url = QUrl(path.arg(m_iZoom).arg(grab.x()).arg(grab.y()));
    QNetworkRequest request;
    request.setUrl(m_url);
    request.setRawHeader("User-Agent", "The Qt Company (Qt) Graphics Dojo 1.0");

    request.setAttribute(QNetworkRequest::User, QVariant(l));
	
    m_manager.get(request);
}




QRect SlippyMap::tileRect(const QPoint &tp)
{
    QPoint t = tp - m_tilesRect.topLeft();
    int x = t.x() * tdim + m_offset.x();
    int y = t.y() * tdim + m_offset.y();
    return QRect(x, y, tdim, tdim);
}

QPointF SlippyMap::toScreenPos(CGeoPoint geoPos ) // double dLon, double dLat)
{
	/*double dLon = geoPos.m_dLng;
	double dLat = geoPos.m_dLat;*/

	QRect box = tileRect(m_tilesRect.topLeft()); // QPoint(iX1, iY1) );

	box.setWidth( m_tilesRect.width()   * tdim);
	box.setHeight(m_tilesRect.height() * tdim);

	CGeoPoint geoPos1 = GeoPosFromTile(m_tilesRect.left(), m_tilesRect.top(), m_iZoom);
	CGeoPoint geoPos2 = GeoPosFromTile(m_tilesRect.left() + m_tilesRect.width() , m_tilesRect.top() + m_tilesRect.height(), m_iZoom);

	//double dLon1 = longitudeFromTile(m_tilesRect.left(), m_iZoom);
	//double dLat1 = latitudeFromTile( m_tilesRect.top() , m_iZoom);
	//
	//double dLon2 = longitudeFromTile(m_tilesRect.left() + m_tilesRect.width(),  m_iZoom);
	//double dLat2 = latitudeFromTile( m_tilesRect.top()  + m_tilesRect.height(), m_iZoom);

	double fx = (geoPos.m_dLng - geoPos1.m_dLng) / (geoPos2.m_dLng - geoPos1.m_dLng);
	double fy = (geoPos.m_dLat - geoPos1.m_dLat) / (geoPos2.m_dLat - geoPos1.m_dLat);

	double dx = box.width()  * fx + box.left();
	double dy = box.height() * fy + box.top();

	return QPointF(dx, dy);

}