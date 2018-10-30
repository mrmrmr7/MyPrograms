QT += qml quick datavisualization

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
datasource.cpp \
    datawork.cpp \
    membrana.cpp
HEADERS += datasource.h \
    settings.h \
    membrana.h

RESOURCES += qmloscilloscope.qrc

OTHER_FILES += doc/src/* \
doc/images/* \
qml/qmloscilloscope/*
