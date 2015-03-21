#include <QCoreApplication>
#include <QDebug>
#include <QFile>

#include "randompackagelist.h"

#define FILENAME    "/home/alumno/Escritorio/data.bin"


QDataStream &operator <<(QDataStream &out, Package &package) {

    out << (int)package.timestamp
        << (QString)package.name
        << (char *)package.buffer
        << (int)package.bufferSize;

    return out;
}


QDataStream &operator <<(QDataStream &out, QList<Package> &packageList) {

    out << (int)packageList.size();

    foreach (Package package, packageList)
        out << package;

    return out;
}


void writeToFile(QFile &file, QList<Package> &packages)
{
    qDebug() << packages[0].timestamp;
    qDebug() << packages[0].name;
    qDebug() << QString().sprintf("%8p", packages[0].buffer);
    qDebug() << packages[0].bufferSize;

    // TU CÓDIGO AQUÍ...
    if (file.open(QIODevice::WriteOnly)){

        QByteArray datos;
        QDataStream out(&datos, QIODevice::WriteOnly);
        out << packages;

        file.write(datos);
        file.close();
    }

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file(FILENAME);
    QList<Package> packages = randomPackageList();
    writeToFile(file, packages);

    return a.exec();
}
