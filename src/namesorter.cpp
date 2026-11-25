//////////////////////////////////////////////////////////////////
// namesorter.cpp
//////////////////////////////////////////////////////////////////
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QVector>
#include <algorithm>
#include "namesorter.h"

#define MIN_NAMES_LEN		2
#define MAX_NAMES_LEN		4
#define REG_EXP_NAMES_PARSER	"\\s+"
#define DELIM			' '

//////////////////////////////////////////////////////////////////
// NameSorter::NameSorter()	- Constructor
//////////////////////////////////////////////////////////////////
NameSorter::NameSorter(QObject *parent)
    : QObject(parent)
{
}
//////////////////////////////////////////////////////////////////
// NameSorter::parseName()
//
// Parses and validates a person's full name.
// A valid name contains 2 to 4 words:
// one to three given names followed by a last name.
//////////////////////////////////////////////////////////////////
bool NameSorter::parseName(const QString &name, Person &person)
{
    QStringList parts = name.trimmed().split(
        QRegularExpression(REG_EXP_NAMES_PARSER),
        Qt::SkipEmptyParts);

    if (parts.size() < MIN_NAMES_LEN || parts.size() > MAX_NAMES_LEN)
        return false;

    person.fullName = parts.join(DELIM);
    person.lastName = parts.last();

    parts.removeLast();
    person.givenNames = parts;

    return true;
}

//////////////////////////////////////////////////////////////////
// Compares two people alphabetically.
// Primary key: last name.
// Secondary keys: first, second, and third given names.
// Comparisons are case-insensitive.
// If shared given names match, the person with fewer
// given names sorts first.
//////////////////////////////////////////////////////////////////
bool NameSorter::comparePerson(const Person &a,
                               const Person &b)
{
    int result = QString::compare(a.lastName,
				  b.lastName,
				  Qt::CaseInsensitive);

    if (result != 0)
        return result < 0;

    int count = qMin(a.givenNames.size(),
                     b.givenNames.size());

    for (int i = 0; i < count; ++i)
    {
        result = QString::compare(a.givenNames[i],
				  b.givenNames[i],
				  Qt::CaseInsensitive);

        if (result != 0)
            return result < 0;
    }

    return (a.givenNames.size() < b.givenNames.size());
}

//////////////////////////////////////////////////////////////////
// NameSorter::sortNames()
//
// Validates and sorts an in-memory list of names.
// Uses stable_sort to preserve the original order of
// names that compare equally.
//////////////////////////////////////////////////////////////////
bool NameSorter::sortNames(const QStringList &names,
                           QStringList &sortedNames,
                           QString &errorMessage)
{
    sortedNames.clear();
    errorMessage.clear();

    QVector<Person> people;

    for (const QString &name : names)
    {
        if (name.trimmed().isEmpty())
            continue;

        Person person;

        if (!parseName(name, person))
        {
            errorMessage = tr("Invalid name (expected %1 to %2 words): %3")
			    .arg(MIN_NAMES_LEN)
			    .arg(MAX_NAMES_LEN)
			    .arg(name);

            return false;
        }

        people.append(person);
    }

    std::stable_sort(
        people.begin(),
        people.end(),
        comparePerson);

    for (const Person &person : people)
        sortedNames.append(person.fullName);

    return true;
}

//////////////////////////////////////////////////////////////////
// NameSorter::sortFile()
//
// Reads names from an input file and sorts them.
// Each non-empty line must contain a valid full name.
//////////////////////////////////////////////////////////////////
bool NameSorter::sortFile(const QString &inputFile,
                          QStringList &sortedNames,
                          QString &errorMessage)
{
    sortedNames.clear();
    errorMessage.clear();

    QFile file(inputFile);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        errorMessage = tr("Cannot open input file: %1").arg(inputFile);
        return false;
    }

    QTextStream in(&file);
    QStringList names;

    while (!in.atEnd())
        names.append(in.readLine());

    if (in.status() != QTextStream::Ok)
    {
        errorMessage = tr("Error reading input file: %1").arg(inputFile);
        return false;
    }

    file.close();

    return sortNames(names, sortedNames, errorMessage);
}

//////////////////////////////////////////////////////////////////
// NameSorter::writeFile()
//
// Writes sorted names to an output file.
// Existing file contents are overwritten.
//////////////////////////////////////////////////////////////////
bool NameSorter::writeFile(const QString &outputFile,
                           const QStringList &names,
                           QString &errorMessage)
{
    errorMessage.clear();

    QFile file(outputFile);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        errorMessage = tr("Cannot open output file: %1").arg(outputFile);
        return false;
    }

    QTextStream out(&file);

    for (const QString &name : names)
        out << name << '\n';

    out.flush();

    if (file.error() != QFileDevice::NoError)
    {
        errorMessage = tr("Error writing output file: %1").arg(outputFile);
        return false;
    }

    file.close();

    return true;
}

