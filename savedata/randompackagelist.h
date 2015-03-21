#ifndef RANDOMPACKAGELIST_H
#define RANDOMPACKAGELIST_H

#include <QList>
#include <QtGlobal>
#include <QDateTime>

struct Package
{
    int timestamp;
    QString name;
    char *buffer;           // Puntero a un buffer en memoria
    int bufferSize;         // Número de bytes reservados en el buffer anterior
};

QList<Package> randomPackageList()
{
    QList<Package> packages;

    Package package1 = {8, "teno", new char[200], 200};
    Package package2 = {102, "igueste", new char[56], 56};
    Package package3 = {1024, "ifonche", new char[1086], 1086};
    Package package4 = {1120, "taguluche", new char[860], 860};
    Package package5 = {1121, "orotava", new char[350], 350};

    qsrand(QDateTime::currentDateTime().toTime_t());
    int rand = qrand() / (RAND_MAX + 1.0) * 5;
    if (rand < 2)
         packages << package1 << package2;

    if (rand < 3)
        packages << package3;

    if (rand < 4)
        packages << package4;

    if (rand < 5)
        packages << package5;

    return packages;
}

#endif // RANDOMPACKAGELIST_H
