#ifndef CITY_H
#define CITY_H

#include "tile.h"
#include <QVector>

/**
 * @brief Klasa opisująca obiekt miasta
 */
class City
{
public:
	/**
	 * @brief Funkcja rysująca misto
	 */
	void draw();
	/**
	 * @brief Funkcja ładująca miasto
	 */
    void load();

public:
	QVector<QVector<Tile>> map_; //!< Macierz elementów miasta
};

#endif // CITY_H
