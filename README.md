# NameSorter

A simple Qt 6 C++ command-line application that sorts
a list of people's names alphabetically.

## Requirements

- Qt 6
- qmake
- C++17 compatible compiler
- make (or an appropriate platform build tool like cmake)

## Input format

The input file contains one person's name per line.

Each name must contain:
- One first name
- Zero, one, or two middle names
- One last name

Each name therefore contains between 2 and 4 words.

Example:

    John Michael Smith
    Mary Anderson
    David William James Brown
    Anne Wilson

Blank lines are ignored.

Invalid names cause the application to report an error.

## Sorting rules

Names are sorted using the following order:

1. Last name
2. First given name
3. Second given name
4. Third given name

All comparisons are case-insensitive.

If all shared given names match, the name with fewer
given names sorts first.

Names that compare equally retain their original order.

## Build the application

From the project root:

    qmake namesorter.pro
    make

## Run the application

The input filename must be provided as a command-line argument.

    ./namesorter names-list.txt

The application:

- Reads and validates the input file.
- Sorts the names.
- Prints the sorted names to the screen.
- Creates or overwrites sorted-names-list.txt.

The output file is created in the current working directory.

## Build unit tests

From the tests directory:

    qmake tst_namesorter.pro
    make

## Run unit tests

From the tests directory:

    ./namesortertests

For more detailed test output:

    ./namesortertests -v2

## Error handling

The application reports errors if:

- The input file cannot be opened.
- A name does not contain between 2 and 4 words.
- The input file cannot be read.
- The output file cannot be created or written.
