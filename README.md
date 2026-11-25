
# NameSorter

A simple Qt 6 C++ command-line application that sorts a list of people's names alphabetically.

## Downloads (Precompiled Binaries)

Precompiled versions of NameSorter are available for macOS and Linux.

Visit the [GitHub Releases](https://github.com/8340720/namesorter/releases) page to download the appropriate version for your operating system.

### macOS

**Release:** NameSorter 1.0.0 for macOS

Available downloads:

- `namesorter-macos.zip`
- `namesortertest-macos.zip`

Download and extract the appropriate ZIP file.

### Linux (x86_64)

**Release:** NameSorter 1.0.0 for Linux

Available downloads:

- `namesorter-linux-x86_64.tar.gz` - Linux application package.
- `namesorter-linux-x86_64.tar.gz.sha256` - SHA-256 checksum for verifying the download.
- `namesortertest-linux-x86_64.tar.gz` - Linux application package.
- `namesortertest-linux-x86_64.tar.gz.sha256` - SHA-256 checksum for verifying the download.

#### Installation

Download and extract the archive:

```bash
tar -xzf namesorter-linux-x86_64.tar.gz
cd namesorter-linux-x86_64
```

Run NameSorter, specifying the input filename:

```bash
./run-namesorter names-list.txt
```

The Linux distribution includes the required Qt and C++ runtime libraries. A separate Qt installation is not required.

**Platform:** Linux x86_64. Built in a Rocky Linux 8 environment. Compatibility with other Linux distributions may vary.

#### Verify the Download (Optional)

To verify the downloaded archive using the supplied SHA-256 checksum:

```bash
sha256sum -c namesorter-linux-x86_64.tar.gz.sha256
```

## Requirements (Building from Source)

- Qt 6
- qmake
- C++17 compatible compiler
- make (or an appropriate platform build tool like CMake)

## Input Format

The input file contains one person's name per line.

Each name must contain:

- One first name
- Zero, one, or two middle names
- One last name

Each name therefore contains between 2 and 4 words.

Example:

```text
John Michael Smith
Mary Anderson
David William James Brown
Anne Wilson
```

Blank lines are ignored.

Invalid names cause the application to report an error.

## Sorting Rules

Names are sorted using the following order:

1. Last name
2. First given name
3. Second given name
4. Third given name

All comparisons are case-insensitive.

If all shared given names match, the name with fewer given names sorts first.

Names that compare equally retain their original order.

## Build the Application

From the project root:

```bash
qmake namesorter.pro
make
```

## Run the Application

The input filename must be provided as a command-line argument.

```bash
./namesorter names-list.txt
```

The application:

- Reads and validates the input file.
- Sorts the names.
- Prints the sorted names to the screen.
- Creates or overwrites `sorted-names-list.txt`.

The output file is created in the current working directory.

## Build Unit Tests

From the tests directory:

```bash
qmake tst_namesorter.pro
make
```

## Run Unit Tests

From the tests directory:

```bash
./namesortertests
```

For more detailed test output:

```bash
./namesortertests -v2
```

## Error Handling

The application reports errors if:

- The input file cannot be opened.
- A name does not contain between 2 and 4 words.
- The input file cannot be read.
- The output file cannot be created or written.

## License

No license requirements.
