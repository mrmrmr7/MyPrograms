#ifndef SETTINGS_H
#define SETTINGS_H

#define PROPERTY(type, name, defaultValue)\
private:\
    type name = defaultValue;\
    Q_PROPERTY(type name READ get##name WRITE set##name NOTIFY name##Changed)\
public:\
    type get##name() { return name; }\
    void set##name(type value) { name = value; emit name##Changed(value); }\

#include <QObject>
#include <QVariant>
#include <QDebug>

class Settings: public QObject
{
    Q_OBJECT

    PROPERTY(unsigned, width, 1024)
    PROPERTY(unsigned, height, 768)

    PROPERTY(QString, labelAxisX, "%f")
    PROPERTY(QString, labelAxisY, "%f")
    PROPERTY(QString, labelAxisZ, "%f")

    PROPERTY(float, minX, 0.f)
    PROPERTY(float, minY, -210)
    PROPERTY(float, minZ, 0.f)

    PROPERTY(float, maxX, 2.f)
    PROPERTY(float, maxY, 100)
    PROPERTY(float, maxZ, 3.f)

    PROPERTY(unsigned, gridX, 5)
    PROPERTY(unsigned, gridY, 5)
    PROPERTY(unsigned, gridZ, 5)

    PROPERTY(unsigned, cache, 500)
    PROPERTY(unsigned, columns, 41)
    PROPERTY(unsigned, rows, 61)

public:
    Settings(QObject *parent = 0) : QObject(parent) {}

signals:
    void widthChanged(unsigned value);
    void heightChanged(unsigned value);

    void labelAxisXChanged(QString value);
    void labelAxisYChanged(QString value);
    void labelAxisZChanged(QString value);

    void minXChanged(float value);
    void minYChanged(float value);
    void minZChanged(float value);

    void maxXChanged(float value);
    void maxYChanged(float value);
    void maxZChanged(float value);

    void gridXChanged(unsigned value);
    void gridYChanged(unsigned value);
    void gridZChanged(unsigned value);

    void cacheChanged(unsigned value);
    void columnsChanged(unsigned value);
    void rowsChanged(unsigned value);
};

#endif
