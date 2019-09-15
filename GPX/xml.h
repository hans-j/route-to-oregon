#ifndef _XML_H_
#define _XML_H_

#include "QDomDocument"
#include "QStringList.h"
#include "QMessageBox.h"
#include "QFile.h"
#include "QVector3D"


namespace xml
{
	enum enumXML { eNull = 0, eGet = 1, eSet = 2 };

	void InfoMsgBox(QString strText, QString strTitel = "Info");
	bool FileExits(QString strDateiname);
	int YesNoMsgBox(QString strText, QString strTitel);

	QDomElement find(QDomDocument & doc, const QString strPfad);

	void addEncodingUtf8(QDomDocument & doc);

	bool save(QDomDocument & doc, QString strDateiname);
	bool load(QDomDocument & doc, QString strDateiname, QString * pErrortext);

	QDomElement getRoot(QDomDocument & doc);
	QString  getTagName(QDomElement & xElmt);
	
	int attr(QDomElement & n, enumXML eXML, QString strKey, double & dValue, int iNachkomma = 2);
	int attr(QDomElement & n, enumXML eXML, QString strKey, QVector3D & vValue, int iNachkomma = 2);
	int attr(QDomElement & n, enumXML eXML, QString strKey, int & iValue);
	int attr(QDomElement & n, enumXML eXML, QString strKey, uint64_t & uiValue);
	int attr(QDomElement & n, enumXML eXML, QString strKey, QString & strValue);
	int attr(QDomElement & n, enumXML eXML, QString strKey, bool & bValue);

	QString getAttr(QDomElement & n, QString strKey);
	int setAttr(QDomElement & n, QString strKey, const wchar_t * wChar);
};


#endif