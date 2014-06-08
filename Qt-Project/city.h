#ifndef CITY_H
#define CITY_H

#include "tile.h"
#include <QVector>

class City
{
public:
	void draw();
    void load();

public:
	QVector<QVector<Tile>> map_;
};

#endif // CITY_H
