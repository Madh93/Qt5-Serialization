#include <QCoreApplication>
#include <QList>
#include <QDebug>
#include <QFile>

#define FILENAME    "/home/alumno/Escritorio/data.bin"

struct Package
{
    int timestamp;
    QString name;
    char *buffer;           // Puntero a un buffer en memoria
    int bufferSize;         // Número de bytes reservados en el buffer anterior
};


QDataStream &operator >>(QDataStream &in, Package &package) {

    in >> package.timestamp
        >> package.name
        >> package.buffer
        >> package.bufferSize;

    return in;
}


QDataStream &operator >>(QDataStream &in, QList<Package> &packageList) {

    int size = 0;
    in >> size;

    for (int i=0; i<size; i++) {
        Package package;
        in >> package;
        packageList.push_back(package);
    }

    return in;
}


QList<Package> readFromFile(QFile &file)
{
    QList<Package> packages;

    if (file.open(QIODevice::ReadOnly)){

        QByteArray datos = file.readAll();
        QDataStream in(datos);
        in >> packages;

        file.close();
    }

    return packages;
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file(FILENAME);
    QList<Package> packages = readFromFile(file);

    qDebug() << packages[0].timestamp;
    qDebug() << packages[0].name;
    qDebug() << QString().sprintf("%8p", packages[0].buffer);
    qDebug() << packages[0].bufferSize;

    // ...

    foreach (Package package, packages)
        qDebug() << package.timestamp << "\t"
                 << package.name << "\t"
                 << QString().sprintf("%8p", package.buffer) << "\t"
                 << package.bufferSize << "\t";

    return a.exec();
}
