
# NameSorter – Build Environment Setup

## 1. Overview

This document describes how to prepare a Rocky Linux 8.X development environment for building NameSorter and its associated dependencies.

The environment uses the following toolchain:

| Component | Version |
|---|---|
| Operating System | Rocky Linux 8.10 |
| GCC | 11.5.0 |
| GNU Binutils | 2.43.1 |
| Qt | 6.8.6 |
| CMake | Distribution package |
| C++ Standard | C++17 |

The instructions cover:

1. Operating system preparation.
2. Required development packages.
3. GCC installation.
4. GNU Binutils installation.
5. Qt installation.
6. Environment configuration.

---

## 2. Operating System Preparation

Start by updating the operating system packages.

```bash
sudo dnf update -y
```

### 2.1 Required Development Packages

Install the development libraries required by the build environment.

Some packages are available through the `devel` and `powertools` repositories.

#### Core development libraries

```bash
sudo dnf install -y libicu-devel
sudo dnf install -y readline-devel
sudo dnf install -y cmake
sudo dnf install -y mpfr-devel
```

#### Packages from the devel repository

```bash
sudo dnf --enablerepo=devel install -y libnsl
sudo dnf --enablerepo=devel install -y libaio-devel

sudo dnf --enablerepo=devel install -y libxcb-devel
sudo dnf --enablerepo=devel install -y libxkbcommon-x11-devel
sudo dnf --enablerepo=devel install -y libxshmfence-devel

sudo dnf --enablerepo=devel install -y xcb-util-wm-devel
sudo dnf --enablerepo=devel install -y xcb-util-keysyms-devel

sudo dnf --enablerepo=devel install -y libdrm-devel
sudo dnf --enablerepo=devel install -y libXcomposite-devel
sudo dnf --enablerepo=devel install -y libXcursor-devel
sudo dnf --enablerepo=devel install -y libXi-devel
sudo dnf --enablerepo=devel install -y libXtst-devel

sudo dnf --enablerepo=devel install -y isl-devel
sudo dnf --enablerepo=devel install -y libmpc-devel
sudo dnf --enablerepo=devel install -y glib2-devel
```

#### Packages from the PowerTools repository

```bash
sudo dnf --enablerepo=powertools install -y texinfo-tex
sudo dnf --enablerepo=powertools install -y nss-devel
sudo dnf --enablerepo=powertools install -y dbus-devel

sudo dnf --enablerepo=powertools install -y libstdc++-static
sudo dnf --enablerepo=powertools install -y libinput-devel
sudo dnf --enablerepo=powertools install -y mtdev-devel
sudo dnf --enablerepo=powertools install -y libxkbfile-devel

sudo dnf --enablerepo=powertools install -y xcb-util-devel
```

### 2.2 EPEL Repository

Some required packages are provided through the Extra Packages for Enterprise Linux (EPEL) repository.

Download the appropriate EPEL 8 release RPM from:

http://dl.fedoraproject.org/pub/epel/8/Everything/x86_64/

Install the downloaded RPM:

```bash
sudo rpm -Uvh epel-release*.rpm
```

Install the XCB cursor development packages:

```bash
sudo dnf install -y xcb-util-cursor
sudo dnf install -y xcb-util-cursor-devel
```

### 2.3 Additional Repository and Dependencies

Install the additional repository:

```bash
sudo dnf install -y \
  http://repo.okay.com.mx/centos/8/x86_64/release/okay-release-1-1.noarch.rpm
```

Install the Perl IPC module:

```bash
sudo dnf install -y perl-IPC-Cmd
```

### 2.4 libnsl Symbolic Link

The build environment requires the `libnsl.so` library link.

Navigate to `/usr/lib64`:

```bash
cd /usr/lib64
```

Create the symbolic link:

```bash
sudo ln -s libnsl-2.28.so libnsl.so
```

---

## 3. GCC Installation

### 3.1 Download GCC

Download and extract GCC version 11.5.x from the official GNU website:

https://ftp.gnu.org/gnu/gcc/gcc-11.5.0/

Extract the source archive and navigate to the GCC source directory.

### 3.2 Configure GCC

Create a separate build directory:

```bash
mkdir build
cd build
```

Configure GCC:

```bash
../configure \
  --enable-languages=c,c++ \
  --disable-multilib
```

### 3.3 Build and Install

Compile GCC:

```bash
make
```

Install GCC:

```bash
sudo make install
```

### 3.4 Verify Installation

Verify the installed compiler:

```bash
gcc --version
g++ --version
```

The expected compiler version is GCC 11.5.0.

---

## 4. GNU Binutils Installation

### 4.1 Download Binutils

Download GNU Binutils version 2.43.1 from:

https://ftp.gnu.org/gnu/binutils/

Extract the source archive and navigate to the extracted source directory.

### 4.2 Configure, Build and Install

Configure the build:

```bash
./configure
```

Compile:

```bash
make
```

Install:

```bash
sudo make install
```

### 4.3 Verify Installation

Verify the installed Binutils components:

```bash
as --version
ld --version
```

The expected Binutils version is 2.43.x.

---

## 5. Qt Installation

### 5.1 Download Qt

Download Qt 6.8.6 source code.

Extract the archive under:

```text
/opt/development/
```

The resulting source directory should be:

```text
/opt/development/qt6.8.6/
```

### 5.2 Configure Qt

Navigate to the Qt build directory:

```bash
cd /opt/development/qt6.8.6/build
```

Run the Qt configuration script:

```bash
../qt6_linux.conf
```

The configuration script contains the build configuration used for the Linux environment.

### 5.3 Build Qt

Compile Qt using CMake:

```bash
cmake --build . --parallel
```

### 5.4 Install Qt

Install the compiled Qt libraries and tools:

```bash
sudo cmake --install .
```

The expected Qt installation directory is:

```text
/usr/local/Qt/6.8.6
```

---

## 6. Environment Configuration

After installing GCC and Qt, configure the environment variables required by the build process.

### 6.1 Environment Variables

The following environment variables identify the compiler and Qt installation:

```bash
export QTDIR=/usr/local/Qt/6.8.6

export CC=/usr/local/bin/gcc

export CXX=/usr/local/bin/g++

export LD_LIBRARY_PATH=/usr/local/lib64:$LD_LIBRARY_PATH
```

Reload the configuration:

```bash
source ~/.bashrc
```

### 6.2 Verify Environment Configuration

Verify the compiler:

```bash
$CC --version
$CXX --version
```

Verify the Qt installation:

```bash
qmake --version
```

Check the configured Qt directory:

```bash
echo $QTDIR
```

---

## 7. Build Environment Verification

Before building NameSorter, verify that the required development tools are available.

| Component | Verification Command |
|---|---|
| G++ | `g++ --version` |
| GCC | `gcc --version` |
| CMake | `cmake --version` |
| Qt | `qmake --version` |
| Binutils | `ld --version` |

Confirm that the compiler and Qt installations are accessible from the current shell.

---

## 8. Building NameSorter

Once the development environment is configured, proceed with building NameSorter.

Clone the repository:

```bash
git clone https://github.com/8340720/namesorter.git
```

Navigate to the project directory:

```bash
cd namesorter
```

Follow the project's build configuration and instructions in the main README.

---

## 9. Environment Summary

The completed development environment consists of:

- Rocky Linux 8.10.
- GCC 11.5.0.
- GNU Binutils 2.43.1.
- Qt 6.8.6.
- CMake.
- Required Qt and X11 development dependencies.

This environment provides the compiler, framework, and development libraries needed for building and maintaining the NameSorter application.

