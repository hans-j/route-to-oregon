#include "QMainWnd.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QMainWnd w;
	w.show();


	QStringList args( a.arguments() );

	for (int i = 1; i < args.count(); i++)
	{
		QString s = args.at(i).toLower();
		if (s.contains(".gpx"))
		{
			w.load_gpx_file(s); 
			break;
		}

	}

	return a.exec();
}
