#pragma once

#include "qmenu.h"
#include "qmenubar.h"
#include <QSignalMapper.h>
#include <QtWidgets/QMainWindow>
#include "xml.h"

class QCreateMenu : public QObject
{
	Q_OBJECT

public:
	QString m_strErrortext;
	QCreateMenu(QMainWindow * parent);

	bool createFromFile(QString strFilename);

signals:
	void signalAction(const QAction * pAction, const QString & strId);

private slots:
	void slotActionMapper(QObject * p);

private:
	QString m_strDir;
	QSignalMapper m_actionMapper;

	QMainWindow * m_pParent;

	bool addMenu(QDomElement  & xElmt, QMenuBar * pMenubar);
	bool addMenu(QDomElement  & xElmt, QMenu * pMenu);
	bool addAction(QDomElement  & xElmt, QMenu * pMenu);
};