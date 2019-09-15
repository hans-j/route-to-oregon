#include "xml.h"

namespace xml
{


	bool FileExits(QString strDateiname)
	{
		QFile F(strDateiname);
		return F.exists();
	}

	void InfoMsgBox(QString strText, QString strTitel )
	{
		QMessageBox msgBox;
		msgBox.setText(strTitel);
		msgBox.setInformativeText(strText);
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		/*int iRc = */msgBox.exec();
	}

	int YesNoMsgBox(QString strText, QString strTitel )
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle(strTitel);
		msgBox.setText(strText);
		msgBox.setStandardButtons(QMessageBox::Yes);
		msgBox.addButton(QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);
		int iRc = msgBox.exec();
		return iRc;
	}


	void addEncodingUtf8(QDomDocument & doc)
	{
		doc.appendChild(doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\""));
	}

	QDomElement getRoot(QDomDocument & doc)
	{
		return doc.documentElement();
	}

	QString  getTagName(QDomElement & xElmt)
	{
		return xElmt.tagName();
	}


	bool save(QDomDocument & doc, QString strDateiname)
	{
		QFile file(strDateiname);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			InfoMsgBox(QString("Error Failed to open file for writing. %1").arg(strDateiname), "Save XML");
			return false;
		}

		QByteArray ba = doc.toByteArray();
		int iAnz = file.write(ba);
		file.close();

		if (iAnz != ba.size())
		{
			InfoMsgBox(QString("Error wrting to file: %1 ").arg(strDateiname), "Save XML");
			return false;
		}
		return true;
	}


	bool load(QDomDocument & doc, QString strDateiname, QString * pErrortext)
	{
		QFile inFile(strDateiname);
		if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			if (pErrortext)
			{
				*pErrortext = QString("Error %1 Failed to open file for reading.").arg(strDateiname);
			}
			return false;
		}


		QString  errorMsg;
		int  errorLine = 0;
		int  errorColumn = 0;
		if (!doc.setContent(&inFile, false, &errorMsg, &errorLine, &errorColumn))
		{
			if (pErrortext)
			{
				*pErrortext = QString("Failed to parse XML-File %1 Error %2 Line %3 Colum %4").arg(strDateiname).arg(errorMsg).arg(errorLine).arg(errorColumn);
			}
			inFile.close();
			return false;
		}

		inFile.close();
		return true;
	}


	QDomElement   find(QDomDocument & doc, const QString strPfad)
	{
		QStringList  pfad = strPfad.split("\\");
		if (pfad.size() == 0) return QDomElement();

		QDomElement  root = doc.documentElement();
		QString s0 = root.tagName();

		int idx = 0;
		if (pfad[idx] != s0) return QDomElement();
		if (pfad.size() == 1) return root;


		QDomElement  next = root;
		idx++;
		while (idx < pfad.size())
		{
			QString s1 = pfad[idx];
			QDomNodeList nodelist = next.elementsByTagName(s1);
			if (nodelist.size() == 0)
			{
				return QDomElement();
			}
			next = nodelist.at(0).toElement();
			idx++;
			if (idx == pfad.size())
			{
				return next;
			}
		}

		return QDomElement();
	}

	int attr(QDomElement & n, enumXML eXML, QString strKey, QVector3D & vValue, int iNachkomma)
	{
		if (eXML == eGet)
		{
			QStringList l = n.attribute(strKey).split(";");
			if (l.size() > 0) vValue.setX(l[0].toDouble());
			if (l.size() > 1) vValue.setY(l[1].toDouble());
			if (l.size() > 2) vValue.setZ(l[2].toDouble());
			return l.size();
		};


		if (eXML == eSet)
		{
			n.setAttribute(strKey, QString("%1;%2;%3")
				.arg(vValue.x(), 0, 'f', iNachkomma)
				.arg(vValue.y(), 0, 'f', iNachkomma)
				.arg(vValue.z(), 0, 'f', iNachkomma));
			return 1;
		}
		return 1;
	}

	int attr(QDomElement & n, enumXML eXML, QString strKey, double & dValue, int iNachkomma)
	{
		if (eXML == eGet)
		{
			QString s = n.attribute(strKey);
			dValue = s.toDouble();
			return s.length();
		}

		if (eXML == eSet)
		{
			n.setAttribute(strKey, QString("%1").arg(dValue, 0, 'f', iNachkomma));
			return 1;
		}
		return 1;
	}


	int attr(QDomElement & n, enumXML eXML, QString strKey, bool & bValue)
	{
		if (eXML == eGet)
		{
			QString s = n.attribute(strKey);
			bValue = s.toInt() == 1;
			return s.length();
		}

		if (eXML == eSet)
		{

			n.setAttribute(strKey, bValue ? "1" : "0");
			return 1;
		}
		return 1;
	}

	int attr(QDomElement & n, enumXML eXML, QString strKey, uint64_t & uiValue)
	{
		if (eXML == eGet)
		{
			QString s = n.attribute(strKey);
			uiValue = s.toLongLong();
			return s.length();
		}

		if (eXML == eSet)
		{
			n.setAttribute(strKey, QString("%1").arg(uiValue));
			return 1;
		}
		return 1;
	}

	int attr(QDomElement & n, enumXML eXML, QString strKey, int & iValue)
	{
		if (eXML == eGet)
		{
			QString s = n.attribute(strKey);
			iValue = s.toInt();
			return s.length();
		}

		if (eXML == eSet)
		{
			n.setAttribute(strKey, QString("%1").arg(iValue));
			return 1;
		}
		return 1;
	}

	int attr(QDomElement & n, enumXML eXML, QString strKey, QString & strValue)
	{
		if (eXML == eGet)
		{
			strValue = n.attribute(strKey);
			return strValue.length();
		}

		if (eXML == eSet)
		{
			n.setAttribute(strKey, strValue);
			return 1;
		}
		return 1;
	}


	QString getAttr(QDomElement & n, QString strKey)
	{
		QString s;
		attr(n, eGet, strKey, s);
		return s;
	}

	int setAttr(QDomElement & n, QString strKey, const wchar_t * wChar)
	{
		n.setAttribute(strKey, QString().fromStdWString( wChar) );
		return 1;
	}
}