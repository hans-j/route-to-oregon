#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QMainWnd.h"
#include <QSignalMapper.h>

#include "QCreateMenu.h"
#include "gpx.h"

class QMainWnd : public QMainWindow
{
	Q_OBJECT

public:
	QMainWnd(QWidget *parent = Q_NULLPTR);

	void load_gpx_file(QString strFilename);

private slots:
	void slotAction(const QAction * pAction, const QString & strId); 
	

private:
	Ui::QMainWndClass ui;

	QSignalMapper m_actionMapper;

	QCreateMenu m_createMenu;
};
