#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QStandardItemModel>
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardItemModel>
#include <QJsonArray>

class JsonParser
{
public:
    static JsonParser *getInstance() {
        static JsonParser par;
        return &par;
    }

    void readJson(QString fileName);
    void addObject(QString type, double speed, QStandardItemModel *model);
    void setFile(QString name);

private:
    JsonParser() {}
    explicit JsonParser(JsonParser &) {}

    QString fileName;
    QJsonArray objects;
};

#endif // JSONPARSER_H
