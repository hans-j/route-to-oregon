#include "QMainWnd.h"



QMainWnd::QMainWnd(QWidget *parent)
	: QMainWindow(parent), m_createMenu(this)
{
	ui.setupUi(this);

	setWindowTitle("Route to Garmin");

	m_createMenu.createFromFile(":/QMainWnd/Resources/mainmenu.xml");

	//m_createMenu.createFromFile("D:\\qtProjekte\\GPX\\GPX\\Resources\\mainmenu.xml");
	
	
	connect(&m_createMenu, SIGNAL(signalAction(const QAction * , const QString & )), 
		    this, SLOT(slotAction(const QAction * , const QString & )));
}

void QMainWnd::load_gpx_file(QString strFilename)
{
	ui.widget->load_gpx(strFilename);
	QString s = ui.widget->getGpx()->m_strName;
	ui.lineEditName->setText(s);
	double dLaenge = ui.widget->getGpx()->m_dTrackLaenge;
	ui.lineEditLaenge->setText(QString("%1 km").arg(dLaenge, 0, 'f', 1,' '));
}

void QMainWnd::slotAction(const QAction * pAction, const QString & strId)
{
	int iId = strId.toInt();
	
	switch (iId)
	{
		case 101: { ui.widget->load_gpx();
					QString s = ui.widget->getGpx()->m_strName;
					ui.lineEditName->setText(s);
					double dLaenge = ui.widget->getGpx()->m_dTrackLaenge;
					ui.lineEditLaenge->setText(QString("%1 km").arg(dLaenge, 0, 'f', 1,' '));
				 } break;

		case 102: { ui.widget->getGpx()->m_strName = ui.lineEditName->text();
					ui.widget->save_gpx_to_pc();
				  } break;

		case 103:{ ui.widget->getGpx()->m_strName = ui.lineEditName->text();
				   ui.widget->save_gpx_to_garmin();
				  }break;

		case 201:
			ui.widget->route_erstellen();
			break;

		case 202:
			ui.widget->route_loesche();

		case 203:
			ui.widget->track_umkehren();
			break;

	}
	
	
}

	
	


	



