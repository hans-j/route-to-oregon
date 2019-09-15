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

#ifndef SLIPPYMAP_H
#define SLIPPYMAP_H

#include <QNetworkAccessManager>
#include <QPixmap>
#include <QUrl>
#include "GeoPoint.h"

class QNetworkReply;
class QPainter;


class QTile
{
	public:

	QTile()
	{
		m_iZoom = 0;
	}

	QTile(int iZoom, int iX, int iY) { m_iZoom = iZoom;  m_tp = QPoint( iX,iY); };

	int m_iZoom;
	QPoint m_tp;
	
	QPixmap m_pixmap;

	QString getKey() { return QString("%1/%2/%3").arg(m_iZoom).arg(m_tp.x()).arg( m_tp.y() ); };

	static QString getKey(int iZoom, int iX, int iY)
	{
		return  QString("%1/%2/%3").arg(iZoom).arg(iX).arg(iY); 
	}

	static QString getKey(int iZoom, QPoint pt)
	{
		return  QString("%1/%2/%3").arg(iZoom).arg(pt.x() ).arg(pt.y() );
	}
};

class SlippyMap: public QObject
{
    Q_OBJECT

public:

    SlippyMap(QWidget *parent );
    void invalidate();
    void render(QPainter *p, const QRect &rect);
    void pan(const QPoint &delta);

    int m_iWidth;
    int m_iHeight;
    int m_iZoom;
    // qreal m_dLatitude;    // Center 
	// qreal m_dLongitude;	  // Center 
	
	CGeoPoint m_geoCenter;

	QPointF toScreenPos(CGeoPoint geoPos);

signals:
    void updated(const QRect &rect);

private slots:
    void handleNetworkData(QNetworkReply *reply);
    void download();
	QPointF tileForCoordinate(CGeoPoint geoPos, int zoom);
	CGeoPoint GeoPosFromTile(qreal tx, qreal ty, int zoom);

protected:
    QRect tileRect(const QPoint &tp);

	

private:
	int m_iMissingTiles;
    QPoint m_offset;
    QRect  m_tilesRect;
    QPixmap m_emptyTile;
    QMap<QString, QTile>  m_tilePixmaps;
    QNetworkAccessManager m_manager;
    QUrl m_url;
};

#endif