#ifndef TILE_H
#define TILE_H

#include <QCoreApplication>
#include <QGLWidget>
#include "tools.h"

enum class TileType {Empty = 0, Straight = 1, Turn = 2};

class Tile
{
public:
	Tile(TileType tt = TileType::Empty, uchar dir = 0) : tType_(tt), dir_(dir) {
	}
	void draw();
	static void initTextures();
    static void	initPos(int x, int y, int pos, double d);
	TileType	tType_;
	uchar		dir_;
private:
	static GLuint tex_[5];
};



#endif // TILE_H
