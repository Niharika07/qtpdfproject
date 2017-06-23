#ifndef XMLWRITER_H
#define XMLWRITER_H
#include <QDomDocument>
#include <QDomElement>
#include <QApplication>
#include <QtCore>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <QTextStream>
#include <QList>
#include <QMap>
#include <QFile>
//#include "xmlreader.h"
void getfilepath(QString file);
class xmlwriter
{
public:
    xmlwriter();
    void writexml(QStringList filename,QString tarpdf);
    void getfilepath(QString file,QString tarpdf);

};

#endif // XMLWRITER_H
