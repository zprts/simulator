#include "tile.h"
#include <QtCore/qmath.h>

GLuint Tile::tex_[5]{};

void Tile::draw()
{
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, tex_[static_cast<int>(tType_)]);
	glPushMatrix();
		glRotatef(90.0 * dir_, 0.0, 0.0, 1.0);
		OpenGLTools::drawPlane();
	glPopMatrix();
}

void Tile::initTextures() {
	QString path = QCoreApplication::applicationDirPath();
	QString names[] = {"empty.jpg", "straight.jpg", "turn.jpg"};
	GLuint *tex = tex_;
	for (QString name : names) {
		if (*tex == 0)
			*(tex++) = OpenGLTools::loadTexture(path + "/tex/tiles/" + name);
	}
	//todo
}
