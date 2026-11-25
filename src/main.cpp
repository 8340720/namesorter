///////////////////////////////////////////////////////////////////////////////
// main.cpp: reads input file and outputs to sorted-names-list.txt file 
///////////////////////////////////////////////////////////////////////////////
#include <QCoreApplication>
#include <QTextStream>
#include "namesorter.h"

#ifdef Q_OS_WIN32
#include <windows.h>
#endif

#define USAGE(fp) \
fprintf(fp, "\nUsage: namesorter <input-file> \n\n");

#define OUTPUT_FILE "sorted-names-list.txt"

///////////////////////////////////////////////////////////////////////////////
// Main application function
// Calls NameSorter for sorting with input file
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QTextStream out(stdout);
    QTextStream err(stderr);

    // Validate command-line arguments.
    if (app.arguments().size() != 2)
    {
        USAGE(stderr);
	return 1;
    }

    // Get input filename from command line.
    const QString inputFile = app.arguments().at(1);

    // Output file is created in the current working directory.
    const QString outputFile = OUTPUT_FILE;

    QStringList sortedNames;
    QString errorMessage;

    // Read and sort names from input file.
    if (!NameSorter::sortFile(
            inputFile, sortedNames, errorMessage))
    {
        err << "Error: " << errorMessage << Qt::endl;
        return 1;
    }

    // Print sorted names to screen.
    out << "Sorted names:" << Qt::endl;
    out << "-------------" << Qt::endl;

    for (const QString &name : sortedNames)
        out << name << Qt::endl;

    // Write sorted names to output file.
    if (!NameSorter::writeFile(
            outputFile, sortedNames, errorMessage))
    {
        err << "Error: " << errorMessage << Qt::endl;
        return 1;
    }

    out << Qt::endl;
    out << "Successfully sorted "
        << sortedNames.size() << " names." << Qt::endl;

    out << "Results saved to: "
        << outputFile << Qt::endl;

    return 0;
}

