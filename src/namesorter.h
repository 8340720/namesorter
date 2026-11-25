#ifndef NAMESORTER_H
#define NAMESORTER_H

/////////////////////////////////////////////////////////////
// NameSorter Class
// Sorts the names from a text file based by last name which
//
// sortFile():
//	 Reads, validates and sorts names from an input file.
//       Returns false if the input cannot be read or contains
//       an invalid name.
// sortNames():
//       Sorts an in-memory list of names by last name,
//       followed by given names.
// writeFile():
//       Sorts an in-memory list of names by last name,
//       followed by given names.
//
/////////////////////////////////////////////////////////////

#include <QObject>
#include <QString>
#include <QStringList>

class NameSorter : public QObject
{
    Q_OBJECT

public:
    explicit NameSorter(QObject *parent = nullptr);
    static bool sortFile(const QString &inputFile,
                         QStringList &sortedNames,
                         QString &errorMessage);

    static bool sortNames(const QStringList &names,
                          QStringList &sortedNames,
                          QString &errorMessage);

    static bool writeFile(const QString &outputFile,
                          const QStringList &names,
                          QString &errorMessage);

private:
    struct Person
    {
        QString fullName;
        QStringList givenNames;
        QString lastName;
    };

    static bool parseName(const QString &name,
                          Person &person);

    // Compares last names first then given names
    static bool comparePerson(const Person &a,
                              const Person &b);
};

#endif // NAMESORTER_H
