TARGET = namesorter

mac {
  QMAKE_APPLE_DEVICE_ARCHS = x86_64 arm64
}

unix {
  QMAKE_CFLAGS   += -Wno-unused-variable
  QMAKE_CXXFLAGS += -Wno-unused-variable
  QMAKE_CFLAGS   += -Wno-deprecated-declarations
  QMAKE_CXXFLAGS += -Wno-deprecated-declarations
}

unix:!mac {
  QMAKE_CC = $$(CC)
  QMAKE_CXX = $$(CXX)
  QMAKE_LINK = $$(CXX)
}

win32 {
  CONFIG  += console
  DEFINES += _CRT_SECURE_NO_WARNINGS
  DEFINES += _CRT_NONSTDC_NO_DEPRECATE
  CONFIG  -= debug_and_release debug_and_release_target
  INCLUDEPATH += ../../include/win32_h
}

mac {
  CONFIG -= app_bundle
}

#QT += core
#QT -= gui

INCLUDEPATH += src

HEADERS += src/namesorter.h

SOURCES +=  src/main.cpp \
	    src/namesorter.cpp


