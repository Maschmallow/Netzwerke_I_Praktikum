#ifndef PARSEJSON_H
#define PARSEJSON_H

#include <QString>

#include <document.h>
#include <writer.h>
#include <stringbuffer.h>
#include <iostream>

class QWidget;

class ParseJson
{
public:
    ParseJson(QWidget *parent);

    bool parse(QString &jsontxt);
    int getDistance() const { return m_distance; }
    int getDuration() const { return m_duration; }
private:
    QWidget *m_pParent;
    // distance in meters
    int m_distance;
    // duration in seconds
    int m_duration;
};

#endif // PARSEJSON_H
