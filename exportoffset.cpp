#include "exportoffset.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

// constructor
exportOffset::exportOffset(int argc, char *argv[])
{
	jepa(argc, argv);
}


/*

heh kind of procedural style function / method ;)

*/
void exportOffset::jepa(int argc, char *argv[])
{
	// check if we have enough parameters
	if (argc < 4)
	{
		qDebug() << "Not enough parameters! :(";
		exit(1);
	}

	// input visitor 3 object export file, text
	QFile file(argv[1]);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "Unable to open " << file.fileName();
		exit(1);
	}
	QTextStream in(&file);

	qDebug() << "Opened input file: " << file.fileName();

	// output visitor 3 export file, text
	QFile file2(argv[2]);
	if (!file2.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "Unable to open " << file2.fileName();
		exit(1);
	}
	QTextStream out(&file2);

	qDebug() << "Opened output file: " << file2.fileName();

	float offsetx, offsety, numberx, numbery;

	// make numbers out of the offset parameters
	offsetx = atof(argv[3]);
	offsety = atof(argv[4]);

	qDebug() << "Offset X: " << offsetx << " Offset Y: " << offsety;

	QString line;
	QStringList list;

	// read and process until we are at the end of the input file
	while (!in.atEnd())
	{
		line = in.readLine();
		line = line.toLower();
		list = line.split(";");

		numberx = list[1].toFloat();
		numbery = list[2].toFloat();
		//qDebug() << "list[1]" << list[1] << "numberx:" << numberx << "numbery" << numbery;

		numberx = numberx + offsetx;
		numbery = numbery + offsety;
		//qDebug() << "list[1]" << list[1] << "numberx:" << numberx << "numbery" << numbery << "NEW!";

		// write into output visitor 3 export file
		out << list[0] << ";" << numberx << ";" << numbery << ";" << list[3] << ";" << list[4] <<";\n";
	}

	file.close();
	file2.close();

	qDebug() << "All done, bye.";
}
