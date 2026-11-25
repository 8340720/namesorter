
# NameSorter – Software Architecture

## 1. Overview

NameSorter is a Qt 6-based C++17 command-line application designed to read, validate, alphabetically sort, and write lists of people's names.

The application follows a simple modular architecture that separates command-line orchestration from the core name-processing functionality.

The architecture emphasizes:

- Separation of responsibilities.
- Reusable business logic.
- Input validation.
- Deterministic sorting behavior.
- Testability.
- Cross-platform compatibility.

## 2. Technology Stack

| Technology | Purpose |
|---|---|
| C++17 | Application implementation |
| Qt 6 | Application framework |
| Qt Core | File handling, strings, and application infrastructure |
| Qt Test | Unit testing |
| qmake | Build configuration |
| Standard C++ Library | Sorting algorithms |

## 3. Architectural Components

### 3.1 Application Entry Point – main.cpp

The main application entry point is responsible for coordinating application execution.

Responsibilities:

- Initialize the Qt Core application.
- Validate command-line arguments.
- Identify the input file.
- Invoke the NameSorter functionality.
- Display sorted results.
- Write results to the output file.
- Report errors and return appropriate exit codes.

The entry point does not implement the sorting algorithm itself.

### 3.2 Core Processing Component – NameSorter

The NameSorter class contains the core name-processing functionality.

It exposes three primary static operations.

#### sortFile()

- Opens and reads the input file.
- Collects names into memory.
- Checks file-reading errors.
- Delegates validation and sorting to sortNames().

#### sortNames()

- Validates individual names.
- Parses names into their constituent components.
- Sorts names according to the defined comparison rules.
- Preserves original ordering when names compare equally.

#### writeFile()

- Writes the sorted names to the specified output file.
- Overwrites existing file contents.
- Reports file-opening and writing errors.

### 3.3 Name Parsing

The private parseName() method converts a full name into an internal Person representation.

The Person structure contains:

- fullName
- givenNames
- lastName

Names must contain between two and four words, representing one to three given names followed by a last name.

Whitespace is trimmed and consecutive whitespace characters are normalized.

### 3.4 Sorting Strategy

The application uses std::stable_sort() with a custom comparison function.

The comparison priority is:

1. Last name.
2. First given name.
3. Second given name.
4. Third given name.

Comparisons are case-insensitive.

When all compared components are equivalent, the original input order is preserved.

## 4. Data Flow

The application follows this processing sequence:

1. Receive the input filename.
2. Open and read the input file.
3. Parse and validate the names.
4. Sort the names.
5. Display the sorted results.
6. Write the results to sorted-names-list.txt.
7. Report completion or an error.

## 5. Error Handling

The application reports errors associated with:

- Invalid command-line arguments.
- Input file access failures.
- Invalid name formats.
- Input file reading failures.
- Output file access failures.
- Output file writing failures.

Errors are communicated through an error message returned by the NameSorter operations.

The command-line application displays the error and exits with a non-zero status.

## 6. Testability

The core NameSorter functionality is implemented using static methods that accept input values and return results through explicit parameters.

This allows the core processing functionality to be tested independently of the command-line interface.

The project uses Qt Test and temporary directories for file-operation tests.

## 7. Architectural Considerations

The current architecture is intentionally straightforward and appropriate for the application's scope.

Potential future improvements include:

- More granular separation of parsing, sorting, and file operations.
- Improved diagnostic information.
- Additional automated quality checks.
- Expanded test coverage.
- Evaluation of unnecessary QObject dependencies.

These improvements should be driven by actual requirements rather than introducing unnecessary complexity.

## 8. Design Philosophy

The primary architectural objective is to keep the application understandable, maintainable, and testable while avoiding unnecessary abstractions.

The design favors clear responsibilities, explicit error handling, and reusable core functionality.

