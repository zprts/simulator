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

void Tile::initPos(int x, int y, int pos, double d)
{
	glTranslated(x * 1.0d, y * 1.0d, 0.0);
	switch (pos) {
	case 0: {
			glTranslated(0.5d, -0.5d+d, 0.0);
			break;
		}
	case 1: {
			glTranslated(0.5d-d, -0.5d, 0.0);
			break;
		}
	case 2: {
			glTranslated(-0.5d+d, -0.5d, 0.0);
			break;
		}
	case 3: {
			glTranslated(-0.5d, -0.5d+d, 0.0);
			break;
		}
	case 4: {
			glTranslated(-0.5d, 0.5d-d, 0.0);
			break;
		}
	case 5: {
			glTranslated(-0.5d+d, 0.5d, 0.0);
			break;
		}
	case 6: {
			glTranslated(0.5d-d, 0.5d, 0.0);
			break;
		}
	case 7: {
			glTranslated(0.5d, 0.5d-d, 0.0);
			break;
		}
	default:
		break;
	}
}
