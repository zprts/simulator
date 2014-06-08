#include "city.h"

void City::draw()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	for (auto line : map_) {
		glPushMatrix();
			for (Tile t : line) {
				t.draw();
				glTranslatef(1.0f, 0.0f, 0.0f);
			}
		glPopMatrix();
		glTranslatef(0.0f, 1.0f, 0.0f);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void City::load()
{
	map_.clear();
	map_.resize(4);
	map_[0] = {Tile(TileType::Turn, 1), Tile(TileType::Turn, 2), Tile(TileType::Empty), Tile(TileType::Empty)};
	map_[1] = {Tile(TileType::Straight, 1), Tile(TileType::Turn), Tile(TileType::Straight), Tile(TileType::Turn, 2)};
	map_[2] = {Tile(TileType::Turn), Tile(TileType::Turn, 2), Tile(TileType::Empty), Tile(TileType::Straight, 1)};
	map_[3] = {Tile(TileType::Empty), Tile(TileType::Turn), Tile(TileType::Straight), Tile(TileType::Turn, 3)};
	//map_[1] = {Tile(TileType::Empty), Tile(TileType::Turn)};
}
