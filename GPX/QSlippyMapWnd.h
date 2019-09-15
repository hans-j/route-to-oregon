#pragma once

#include <QWidget>
#include "ui_QSlippyMapWnd.h"

#include "GeoPoint.h"
#include "gpx.h"

class SlippyMap;


class QSlippyMapWnd : public QWidget
{
	Q_OBJECT

public:
	QSlippyMapWnd(QWidget *parent = Q_NULLPTR);
	~QSlippyMapWnd();

	void setCenter( CGeoPoint geoPos );


	bool load_gpx(QString strFilename);
	bool load_gpx();

	void save_gpx_to_pc();
	void save_gpx_to_garmin();
	void save_gpx(QString strSettingKey );

	void route_erstellen();
	void route_loesche();
	void track_umkehren();

	QGpx * getGpx() { return &m_Gpx;  };

private slots:
	void updateMap(const QRect &r);

protected:
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *);
	void wheelEvent(QWheelEvent *event);
	//void keyPressEvent(QKeyEvent *event);

private:
	Ui::QSlippyMapWnd ui;

	QGpx  m_Gpx;

	SlippyMap *m_slippyMap;

	QPoint pressPos;
	QPoint dragPos;
	bool m_bPressed;
};
