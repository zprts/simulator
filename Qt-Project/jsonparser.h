#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "simulation.h"
#include <QStandardItemModel>
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardItemModel>
#include <QJsonArray>

/*!
 * \brief The JsonParser class
 * Moduł do obsługi plików w formacie json.
 */
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
    /*!
     * \brief fileName ścieżka do bieżacego pliku json
     */
    QString fileName;
    /*!
     * \brief objects tablica obiektów dodawanych do scenariusza
     */
    QJsonArray objects;
};

#endif // JSONPARSER_H
