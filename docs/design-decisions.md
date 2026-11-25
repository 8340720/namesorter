
# NameSorter – Design Decisions

## 1. Introduction

This document records the key technical and architectural decisions made during the design and development of NameSorter.

The purpose is to provide transparency into the reasoning behind technology choices, implementation approaches, and architectural trade-offs.

Documenting these decisions helps:

- Explain why particular technologies and approaches were selected.
- Make architectural decisions easier to understand and maintain.
- Provide context for future enhancements.
- Support informed technical discussions.
- Establish a consistent engineering direction.

Decisions documented here reflect the current implementation unless explicitly identified as proposed or under evaluation.

---

## 2. Decision Summary

| ID | Decision | Status |
|---|---|---|
| ADR-001 | Use C++17 as the implementation language | Accepted |
| ADR-002 | Use Qt 6 as the application framework | Accepted |
| ADR-003 | Use qmake as the build system | Accepted |
| ADR-004 | Use stable sorting for name ordering | Accepted |
| ADR-005 | Use static methods for core NameSorter operations | Accepted |
| ADR-006 | Use Qt Test for unit testing | Accepted |

---

## 3. ADR-001: Selection of C++17

### Context

NameSorter requires an implementation language that provides good performance, portability, maintainability, and access to mature development tools.

The application also benefits from modern language features that improve code readability and reduce implementation complexity.

### Decision

C++ was selected as the application development language with Qt libraries for targeting the same code deployment on multiple platforms.

### Alternatives Considered

No alternatives were considered 

### Rationale

C++ provides:

- Strong static typing.
- Modern language features.
- Standard library algorithms and containers.
- Efficient resource management.
- Broad compiler support.
- Compatibility with Qt 6.

It also provides a good balance between performance, maintainability, and portability.

### Consequences

Positive:

- Modern C++ development practices can be applied.
- The application benefits from standard library functionality.
- The codebase remains suitable for future enhancements.

Considerations:

- Developers need familiarity with modern C++.
- Compiler compatibility must be considered when selecting build environments.

---

## 4. ADR-002: Selection of Qt 6

### Context

The application requires functionality for file handling, string processing, application initialization, and unit testing.

A framework that provides these capabilities while supporting multiple operating systems was desirable.

### Decision

Qt 6 was selected as the application framework.

### Alternatives Considered

- Standard C++ Library only.
- Boost libraries.
- Other cross-platform application frameworks.

### Rationale

Qt provides a mature collection of libraries for:

- File operations.
- String manipulation.
- Application infrastructure.
- Cross-platform development.
- Unit testing through Qt Test.

Using Qt Core avoids introducing unnecessary dependencies for common application functionality.

### Consequences

Positive:

- Consistent APIs across supported operating systems.
- Access to established Qt development tools.
- Integrated unit testing capabilities.

Considerations:

- Qt must be available in the build environment.
- Qt version compatibility needs to be maintained.

---

## 5. ADR-003: Selection of qmake

### Context

The project needs a build configuration that defines source files, headers, compiler settings, dependencies, and build targets.

### Decision

qmake was selected as the current build configuration system.

### Alternatives Considered

- CMake could be considered for Windows deployment.

### Rationale

qmake integrates with Qt and provides a straightforward way to configure Qt-based C++ applications.

It supports the current project's relatively simple build requirements.

### Consequences

Positive:

- Straightforward Qt project configuration.
- Familiar integration with Qt development tools.
- Separate configurations can be maintained for the application and its tests.

Considerations:

- CMake has broader adoption in many modern C++ projects.

A migration should be based on concrete project needs rather than modernization for its own sake.

---

## 6. ADR-004: Use of Stable Sorting

### Context

NameSorter must sort names according to multiple comparison criteria.

Some names may have equivalent sorting keys. In these cases, preserving the original input order provides predictable behavior.

### Decision

The application uses std::stable_sort() with a custom comparison function.

### Alternatives Considered

- std::sort().
- Manual sorting implementation.
- Sorting based on a single concatenated string.

### Rationale

std::stable_sort() preserves the relative order of elements that compare as equivalent.

This is useful when sorting names with identical comparison keys.

The custom comparison function allows the application to apply its own name-specific sorting rules.

### Sorting Priority

The comparison order is:

1. Last name.
2. First given name.
3. Second given name.
4. Third given name.

Name comparisons are case-insensitive.

### Consequences

Positive:

- Predictable sorting behavior.
- Preservation of input order for equivalent keys.
- Use of a well-established standard library algorithm.
- No need to implement a custom sorting algorithm.

Considerations:

- The comparison function must maintain a consistent strict weak ordering.
- Additional name formats may require revisiting the comparison rules.

---

## 7. ADR-005: Use of Static Methods in NameSorter

### Context

The core sorting functionality does not require maintaining application state between operations.

The NameSorter component performs operations on supplied input data and returns results through its method interfaces.

### Decision

The primary NameSorter operations are implemented as static methods.

### Alternatives Considered

- Instance-based service class.
- Singleton implementation.
- Separate objects for parsing, sorting, and file operations.

### Rationale

Static methods provide a straightforward interface for functionality that does not require object-specific state.

They also allow the core processing operations to be invoked without creating NameSorter instances.

### Consequences

Positive:

- Simple API.
- No unnecessary object construction.
- Straightforward invocation from the application entry point.
- Core functionality can be tested independently.

Considerations:

- Static methods can become restrictive if future requirements introduce configurable behavior or dependencies.
- A service-based design may be more appropriate if the application grows.

The current implementation favors simplicity over unnecessary abstraction.

---

## 8. ADR-006: Selection of Qt Test

### Context

The application requires automated testing to validate sorting behavior, input validation, and file operations.

A testing framework integrated with the existing Qt technology stack was preferred.

### Decision

Qt Test was selected as the unit testing framework.

### Alternatives Considered

- Bash scripts could be writtent to test
- QtQuick (Squish)

### Rationale

Qt Test provides an established testing framework that integrates naturally with Qt applications.

It supports:

- Test cases.
- Data-driven testing.
- Assertions.
- Test execution through Qt development tools.
- Temporary directory and file testing when combined with Qt Core.

### Consequences

Positive:

- Consistent testing environment.
- Integration with the existing Qt technology stack.
- Reduced need for additional testing dependencies.

Considerations:

- Tests should remain focused on observable behavior.
- Test infrastructure should not become unnecessarily coupled to application implementation details.

---

## 9. Future Design Considerations

Currently the scope of the project was limited thus no future design changes proposed.
However if any it will be in the following areas:

### 9.1 Build System Modernization

Evaluate migration from qmake to CMake.

Potential benefits:

- Broader adoption in modern C++ development.
- Improved integration with different development environments.
- More flexible build configuration.
- Better support for larger multi-component projects.

### 9.2 Separation of Responsibilities

Evaluate whether parsing, sorting, and file operations should be separated into dedicated components.

Potential benefits:

- More focused responsibilities.
- Improved test isolation.
- Greater flexibility for future functionality.

### 9.3 Improved Diagnostic Information

Evaluate a more structured error reporting strategy.

Potential benefits:

- Better troubleshooting.
- More descriptive error messages.
- Improved user experience.
- Easier automated testing of failure scenarios.

### 9.4 Continuous Integration

Introduce automated builds and tests through GitHub Actions.

Potential benefits:

- Earlier identification of regressions.
- Consistent build validation.
- Cross-platform verification.
- More reliable releases.

---

## 10. Decision Review and Governance

Due to the scope of the project this was solely decided for quick and rapid prototyping.
Under normal project settings the technical decisions should be revisited when:

- New requirements introduce architectural constraints.
- Existing approaches become difficult to maintain.
- Technology dependencies reach end-of-life.
- Performance or scalability requirements change.
- A better-supported alternative provides measurable benefits.

Any significant change should document:

1. The problem being addressed.
2. The alternatives considered.
3. The proposed solution.
4. The expected benefits.
5. The associated trade-offs.
6. The migration implications.

This approach ensures that architectural evolution remains intentional, transparent, and aligned with project requirements.

---

## 11. Conclusion

NameSorter follows a simple pragmatic engineering approach.

The selected technologies and implementation strategies prioritize simplicity, maintainability, portability, and testability.

The project avoids introducing unnecessary architectural complexity while preserving opportunities for future evolution.

Technical decisions are documented to provide context, support maintainability, and establish a clear foundation for continued development.

