#include "parsejson.h"
#include "error/en.h"

#include <QDebug>
#include <QMessageBox>
#include <QFile>

using namespace rapidjson;

ParseJson::ParseJson(QWidget *parent) : m_pParent(parent), m_distance(0), m_duration(0)
{}

bool ParseJson::parse(QString &jsontxt)
{
    // 1. Parse a JSON string into DOM.
    Document document;
    int test = jsontxt.length();
    QString rep = jsontxt.mid(jsontxt.indexOf("{"),jsontxt.size());

    rep = rep.mid(0, rep.lastIndexOf("}")+1);
    rep.replace("\n","");
    rep.replace("\r","");
    QByteArray ba = rep.toLatin1();
    const char *cstr = ba.data();
    qDebug() << cstr << "\n";

    QFile file("result.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << rep;
    file.close();
    ParseResult ok = document.Parse(cstr);


    if (!ok) {
        QString parseError = GetParseError_En(document.GetParseError());
        QString error =
                "Beim Parsen von JSON ist ein Fehler aufgetreten.\n\nError:\n"
                + parseError;

        QMessageBox::critical(m_pParent, "Fehler beim Parsen.", error);
        return false;
    }

    // 2. Check Status.
    Value& stat = document["status"];
    QString status = stat.GetString();
    qDebug() << status;

    if (status == "NOT_FOUND") {
        QMessageBox::information(m_pParent, "NOT_FOUND", "Keine Gültige Route gefunden.");
        return false;
    }
    else if (status == "OK")
    {
        //Q_ASSERT(s.IsArray());
        //for (SizeType i = 0; i < s.Size(); i++)
            //qDebug() << "a[" << i << " = " << s.GetString() << "\n";
        const Value& routes = document["routes"];
        Q_ASSERT(routes.IsArray());
        // Get always first route
        const Value& legs = routes[0]["legs"];
        Q_ASSERT(legs.IsArray());
        for (SizeType i = 0; i < legs.Size(); i++)
        {
            const Value& b = legs[i];
            const Value& distance = b["distance"];
            m_distance += distance["value"].GetInt();
            const Value& duration = b["duration"];
            m_duration += duration["value"].GetInt();
        }

        return true;
    }
    else
    {
        QMessageBox::information(m_pParent, "Fehler", "Unbekannter Fehler beim Suchen der Route.");
        return false;
    }
}

