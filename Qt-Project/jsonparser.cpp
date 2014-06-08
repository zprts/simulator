#include "jsonparser.h"
#include "simulation.h"

void JsonParser::readJson(QString fileName)
{
   QString val;
   QFile file;
   file.setFileName(fileName);
   file.open(QIODevice::ReadOnly | QIODevice::Text);
   val = file.readAll();
   file.close();

   QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
   QJsonObject sett2 = d.object();

   QJsonArray objects = sett2.value(QString("Objects")).toArray();

   for (int i = 0; i < objects.size(); i++) {
      QJsonObject obj = objects[i].toObject();
      QString type = obj.value("TypeObject").toString();
      double speed = obj.value("Speed").toDouble();

      QJsonArray points = obj.value(QString("Points")).toArray();

      QJsonObject point = points[0].toObject();
      double CoX = point.value(QString("CoordX")).toDouble();
      double CoY = point.value(QString("CoordY")).toDouble();

      Simulation::getInstance()->addObject(type, speed, CoX, CoY);

      double CoXOld = CoX;
      double CoYOld = CoY;

      for (int j = 1; j < points.size(); j++) {
          point = points[j].toObject();
          CoX = point.value(QString("CoordX")).toDouble();
          CoY = point.value(QString("CoordY")).toDouble();
          Simulation::getInstance()->addPath(i, CoX - CoXOld, CoY - CoYOld);
          //obj_[i].get()->addPathIt(CoX - CoXOld, CoY - CoYOld);
          CoXOld = CoX;
          CoYOld = CoY;
      }
   }
}

void JsonParser::addObject(QString type, double speed, QStandardItemModel *model)
{
    QJsonValue type_ = type;
    QJsonObject object;
    object.insert("TypeObject", type_);

    object.insert("Speed", speed);

    QJsonArray array;
    QJsonObject point;
    QJsonValue value;

    for (int i = 0; i <model->rowCount(); i++) {
        value = model->takeItem(i,0)->data(Qt::DisplayRole).toDouble();
        point.insert("CoordX", value);
        value = model->takeItem(i,1)->data(Qt::DisplayRole).toDouble();
        point.insert("CoordY", value);
        array.insert(i,point);
    }
    value = array;
    object.insert("Points", value);
    objects.push_back(object);

    QJsonDocument d;
    QJsonObject obj;
    obj.insert("Objects", static_cast<QJsonValue>(objects));
    d.setObject(obj);
    d.toJson();


    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    file.write(d.toJson());
    file.close();
}

void JsonParser::setFile(QString name)
{
    fileName = name;
}
