
#include "QCreateMenu.h"

QCreateMenu::QCreateMenu(QMainWindow * parent):QObject( parent ), m_pParent(parent)
{
	connect(&m_actionMapper, SIGNAL(mapped(QObject *)), this, SLOT(slotActionMapper(QObject *)));
}


void QCreateMenu::slotActionMapper(QObject * p)
{
	int iStop = 0;
	QString strId  = p->property("id").toString();
	QString strTyp = p->property("typ").toString();

	if (strTyp == "QAction")
	{
		QAction * pAction = (QAction*)p;
		emit  signalAction(pAction, strId);
	}
}

bool QCreateMenu::createFromFile(QString strFilename)
{
	QDomDocument  XDoc;
	
	if (!m_strDir.isEmpty())
	{
		strFilename = m_strDir + "\\" + strFilename;
	}

	bool b = xml::load(XDoc, strFilename, &m_strErrortext);
	if (!b)
	{
		xml::InfoMsgBox(m_strErrortext, "XML-Error");
		return false;
	}

	QDomElement  root = XDoc.documentElement();
	addMenu(root, m_pParent->menuBar());

	return true;
}

bool QCreateMenu::addMenu(QDomElement  & xElmt, QMenuBar * pMenubar)
{
	QDomNodeList nodelist = xElmt.childNodes();
	for (int i1 = 0; i1 < nodelist.size(); i1++)
	{
		QDomElement n1 = nodelist.at(i1).toElement();
		QString strTag = n1.tagName();
		QString strName = xml::getAttr(n1, "name");
		QString strId = xml::getAttr(n1, "id");

		if (strTag == "menu")
		{
			QMenu *pMenu = pMenubar->addMenu(strName);
			addMenu(n1, pMenu);
			addAction(n1, pMenu);
		}

	}
	return true;
}


	bool QCreateMenu::addMenu(QDomElement  & xElmt, QMenu * pMenu)
	{
		QDomNodeList nodelist = xElmt.childNodes();
		for (int i1 = 0; i1 < nodelist.size(); i1++)
		{
			QDomElement n1 = nodelist.at(i1).toElement();
			QString strTag = n1.tagName();
			QString strName = xml::getAttr(n1, "name");
			QString strId = xml::getAttr(n1, "id");

			if (strTag == "menu")
			{
				QMenu *pMenu = pMenu->addMenu(strName);
				addMenu(n1, pMenu);
				addAction(n1, pMenu);
			}
		}
		return true;
	}

	bool QCreateMenu::addAction(QDomElement  & xElmt, QMenu * pMenu)
	{
		QDomNodeList nodelist = xElmt.childNodes();
		for (int i1 = 0; i1 < nodelist.size(); i1++)
		{
			QDomElement n1 = nodelist.at(i1).toElement();
			QString strTag = n1.tagName();
			QString strName = xml::getAttr(n1, "name");
			QString strId = xml::getAttr(n1, "id");

			if (strTag == "action")
			{
				QAction *pAction  = new QAction(strName, m_pParent);
				pAction->setProperty("id", strId);
				pAction->setProperty("typ", "QAction");
				pMenu->addAction(pAction);
				connect(pAction, SIGNAL(triggered()), &m_actionMapper, SLOT(map()));
				m_actionMapper.setMapping(pAction, pAction);
			}
		}
		return true;
	}



//void QCreateMenu::create(QDomElement  & xElmt, QWidget * pWidget, QLayout * pLayout)
//{
//
//}