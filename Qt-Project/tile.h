#ifndef TILE_H
#define TILE_H

#include <QCoreApplication>
#include <QGLWidget>
#include "tools.h"


enum class TileType {Empty = 0, Straight = 1, Turn = 2};

/**
 * @brief Klasa opisująca kafelek - element miasta
 */
class Tile
{
public:
	Tile(TileType tt = TileType::Empty, uchar dir = 0) : tType_(tt), dir_(dir) {
	}
	/**
	 * @brief Funkcja rysuje kafelek
	 */
	void draw();
	/**
	 * @brief Funkcja ładuje do kontekstu OpenGL tekstury wszystkich kafelków
	 */
	static void initTextures();

	TileType	tType_; //!< Typ kafelka
	uchar		dir_;	//!< Kierunek
private:
	static GLuint tex_[5]; //!< Identyfikatory tekstur w OpenGL
};



#endif // TILE_H
