//////////////////////////////////////////////////////////////////
// tst_namesorter.cpp
//////////////////////////////////////////////////////////////////
#include <QtTest>
#include <QTemporaryDir>
#include <QFile>
#include <QTextStream>
#include "../src/namesorter.h"

//////////////////////////////////////////////////////////////////
// TestNameSorter Class
//////////////////////////////////////////////////////////////////
class TestNameSorter : public QObject
{
    Q_OBJECT

private slots:

    //////////////////////////////////////////////////////////////
    // Test sorting by last name.
    //////////////////////////////////////////////////////////////
    void testLastNameSorting()
    {
        QStringList input = {
            "John Smith",
            "Mary Anderson",
            "David Brown"
        };

        QStringList expected = {
            "Mary Anderson",
            "David Brown",
            "John Smith"
        };

        QStringList result;
        QString error;

        QVERIFY(NameSorter::sortNames(input, result, error));
        QCOMPARE(result, expected);
    }

    //////////////////////////////////////////////////////////////
    // Test sorting by first given name when last names match.
    //////////////////////////////////////////////////////////////
    void testFirstGivenNameSorting()
    {
        QStringList input = {
            "John Smith",
            "Albert Smith",
            "David Smith"
        };

        QStringList expected = {
            "Albert Smith",
            "David Smith",
            "John Smith"
        };

        QStringList result;
        QString error;

        QVERIFY(NameSorter::sortNames(input, result, error));
        QCOMPARE(result, expected);
    }

    //////////////////////////////////////////////////////////////
    // Test sorting by second given name.
    //////////////////////////////////////////////////////////////
    void testSecondGivenNameSorting()
    {
        QStringList input = {
            "John Michael Smith",
            "John Albert Smith",
            "John David Smith"
        };

        QStringList expected = {
            "John Albert Smith",
            "John David Smith",
            "John Michael Smith"
        };

        QStringList result;
        QString error;

        QVERIFY(NameSorter::sortNames(input, result, error));
        QCOMPARE(result, expected);
    }

    //////////////////////////////////////////////////////////////
    // Test sorting by third given name.
    //////////////////////////////////////////////////////////////
    void testThirdGivenNameSorting()
    {
        QStringList input = {
            "John Michael William Smith",
            "John Michael Albert Smith",
            "John Michael David Smith"
        };

        QStringList expected = {
            "John Michael Albert Smith",
            "John Michael David Smith",
            "John Michael William Smith"
        };

        QStringList result;
        QString error;

        QVERIFY(NameSorter::sortNames(input, result, error));
        QCOMPARE(result, expected);
    }

    //////////////////////////////////////////////////////////////
    // Test names with different numbers of given names.
    //////////////////////////////////////////////////////////////
    void testDifferentNumberOfGivenNames()
    {
        QStringList input = {
            "John Michael Albert Smith",
            "John Smith",
            "John Albert Smith"
        };

        QStringList expected = {
            "John Smith",
            "John Albert Smith",
            "John Michael Albert Smith"
        };

        QStringList result;
        QString error;

        QVERIFY(NameSorter::sortNames(input, result, error));
        QCOMPARE(result, expected);
    }

    //////////////////////////////////////////////////////////////
    // Test case-insensitive sorting.
    //////////////////////////////////////////////////////////////
    void testCaseInsensitiveSorting()
    {
        QStringList input = {
            "John smith",
            "Mary Anderson",
            "David SMITH"
        };

        QStringList expected = {
            "Mary Anderson",
            "David SMITH",
            "John smith"
        };

        QStringList result;
        QString error;

        QVERIFY(NameSorter::sortNames(input, result, error));
        QCOMPARE(result, expected);
    }

    //////////////////////////////////////////////////////////////
    // Test invalid names.
    //////////////////////////////////////////////////////////////
    void testInvalidNames()
    {
        QStringList input = {
            "John Smith",
            "Mary",
            "David Michael James Robert Brown"
        };

        QStringList result;
        QString error;

        QVERIFY(!NameSorter::sortNames(input, result, error));
        QVERIFY(!error.isEmpty());
    }

    //////////////////////////////////////////////////////////////
    // Test empty lines.
    //////////////////////////////////////////////////////////////
    void testEmptyLines()
    {
        QStringList input = {
            "John Smith",
            "",
            "   ",
            "Mary Anderson"
        };

        QStringList expected = {
            "Mary Anderson",
            "John Smith"
        };

        QStringList result;
        QString error;

        QVERIFY(NameSorter::sortNames(input, result, error));
        QCOMPARE(result, expected);
    }

    //////////////////////////////////////////////////////////////
    // Test duplicate names.
    //////////////////////////////////////////////////////////////
    void testDuplicateNames()
    {
        QStringList input = {
            "John Smith",
            "John Albert Smith",
            "John Smith"
        };

        QStringList expected = {
            "John Smith",
            "John Smith",
            "John Albert Smith"
        };

        QStringList result;
        QString error;

        QVERIFY(NameSorter::sortNames(input, result, error));
        QCOMPARE(result, expected);
    }

    //////////////////////////////////////////////////////////////
    // Test that equal names retain their original order.
    //////////////////////////////////////////////////////////////
    void testStableSorting()
    {
        QStringList input = {
            "John Smith",
            "John Smith",
            "John Smith"
        };

        QStringList result;
        QString error;

        QVERIFY(NameSorter::sortNames(input, result, error));
        QCOMPARE(result, input);
    }

    //////////////////////////////////////////////////////////////
    // Test reading and writing files.
    //////////////////////////////////////////////////////////////
    void testFileOperations()
    {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());

        QString inputFile = dir.filePath("input.txt");
        QString outputFile = dir.filePath("output.txt");

        {
            QFile file(inputFile);
            QVERIFY(file.open(QIODevice::WriteOnly |
                              QIODevice::Text));

            QTextStream out(&file);
            out << "John Smith\n";
            out << "Mary Anderson\n";
            out << "David Brown\n";
        }

        QStringList result;
        QString error;

        QVERIFY(NameSorter::sortFile(
            inputFile, result, error));

        QVERIFY(NameSorter::writeFile(
            outputFile, result, error));

        QFile file(outputFile);
        QVERIFY(file.open(QIODevice::ReadOnly |
                          QIODevice::Text));

        QStringList output;
        QTextStream in(&file);

        while (!in.atEnd())
            output.append(in.readLine());

        QStringList expected = {
            "Mary Anderson",
            "David Brown",
            "John Smith"
        };

        QCOMPARE(output, expected);
    }

    //////////////////////////////////////////////////////////////
    // Test rejection of an invalid input file.
    //////////////////////////////////////////////////////////////
    void testInvalidInputFile()
    {
        QTemporaryDir dir;
        QVERIFY(dir.isValid());

        QString inputFile = dir.filePath("invalid.txt");

        {
            QFile file(inputFile);
            QVERIFY(file.open(QIODevice::WriteOnly |
                              QIODevice::Text));

            QTextStream out(&file);
            out << "John Smith\n";
            out << "Mary\n";
        }

        QStringList result;
        QString error;

        QVERIFY(!NameSorter::sortFile(
            inputFile, result, error));

        QVERIFY(!error.isEmpty());
    }

    //////////////////////////////////////////////////////////////
    // Test handling of a nonexistent input file.
    //////////////////////////////////////////////////////////////
    void testMissingInputFile()
    {
        QStringList result;
        QString error;

        QVERIFY(!NameSorter::sortFile(
            "/nonexistent/names.txt", result, error));

        QVERIFY(!error.isEmpty());
    }
};

QTEST_GUILESS_MAIN(TestNameSorter)

#include "tst_namesorter.moc"

