#include "tools.h"
std::auto_ptr<GLUquadric> OpenGLTools::quadric_(gluNewQuadric());

GLuint OpenGLTools::loadTexture(QString path) throw (Exception) {
	QImage t, b;
	GLuint r;
	if (!b.load(path)) {
		throw Exception("Texture loading error: " + path);
	}
	t = QGLWidget::convertToGLFormat(b);
	glGenTextures(1, &r);
	glBindTexture(GL_TEXTURE_2D, r);
	glTexImage2D( GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits() );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	return r;
}

void OpenGLTools::drawPlane()
{
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f(-0.5, -0.5,  0.0);
		glTexCoord2f(1.0, 0.0); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f( 0.5, -0.5,  0.0);
		glTexCoord2f(1.0, 1.0); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f( 0.5,  0.5,  0.0);
		glTexCoord2f(0.0, 1.0); glNormal3f(0.0f, 0.0f, 1.0f); glVertex3f(-0.5,  0.5,  0.0);
		glEnd();
}

void OpenGLTools::drawCube()
{
	glBegin(GL_QUADS);        // Draw The Cube Using quads
	glVertex3f( 0.5f, 0.5f, 0.5f);    // Top Right Of The Quad (Front)
	glVertex3f(-0.5f, 0.5f, 0.5f);    // Top Left Of The Quad (Front)
	glVertex3f(-0.5f,-0.5f, 0.5f);    // Bottom Left Of The Quad (Front)
	glVertex3f( 0.5f,-0.5f, 0.5f);    // Bottom Right Of The Quad (Front)

	glColor3f(0.8f, 0.8f, 0.8f);

		//glColor3f(0.2f, 0.2f,0.2f);    // Color Blue
		glVertex3f( 0.5f, 0.5f,-0.5f);    // Top Right Of The Quad (Top)
		glVertex3f(-0.5f, 0.5f,-0.5f);    // Top Left Of The Quad (Top)
		glVertex3f(-0.5f, 0.5f, 0.5f);    // Bottom Left Of The Quad (Top)
		glVertex3f( 0.5f, 0.5f, 0.5f);    // Bottom Right Of The Quad (Top)
		   // Color Orange
		glVertex3f( 0.5f,-0.5f, 0.5f);    // Top Right Of The Quad (Bottom)
		glVertex3f(-0.5f,-0.5f, 0.5f);    // Top Left Of The Quad (Bottom)
		glVertex3f(-0.5f,-0.5f,-0.5f);    // Bottom Left Of The Quad (Bottom)
		glVertex3f( 0.5f,-0.5f,-0.5f);    // Bottom Right Of The Quad (Bottom)
		//glColor3f(0.5f,0.0f,0.0f);    // Color Red

		//glColor3f(0.5f,0.5f,0.0f);    // Color Yellow
		glVertex3f( 0.5f,-0.5f,-0.5f);    // Top Right Of The Quad (Back)
		glVertex3f(-0.5f,-0.5f,-0.5f);    // Top Left Of The Quad (Back)
		glVertex3f(-0.5f, 0.5f,-0.5f);    // Bottom Left Of The Quad (Back)
		glVertex3f( 0.5f, 0.5f,-0.5f);    // Bottom Right Of The Quad (Back)
		//glColor3f(0.0f,0.0f,0.5f);    // Color Blue
		glVertex3f(-0.5f, 0.5f, 0.5f);    // Top Right Of The Quad (Left)
		glVertex3f(-0.5f, 0.5f,-0.5f);    // Top Left Of The Quad (Left)
		glVertex3f(-0.5f,-0.5f,-0.5f);    // Bottom Left Of The Quad (Left)
		glVertex3f(-0.5f,-0.5f, 0.5f);    // Bottom Right Of The Quad (Left)
		//glColor3f(0.5f,0.0f,0.5f);    // Color Violet
		glVertex3f( 0.5f, 0.5f,-0.5f);    // Top Right Of The Quad (Right)
		glVertex3f( 0.5f, 0.5f, 0.5f);    // Top Left Of The Quad (Right)
		glVertex3f( 0.5f,-0.5f, 0.5f);    // Bottom Left Of The Quad (Right)
		glVertex3f( 0.5f,-0.5f,-0.5f);    // Bottom Right Of The Quad (Right)
	  glEnd();            // End Drawing The Cube - See more at: http://www.codemiles.com/c-opengl-examples/draw-3d-cube-using-opengl-t9018.html#sthash.FCoGkGtp.dpuf
}

void OpenGLTools::drawHuman()
{
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.12);
		glColor3f(0.8, 0.0, 0.0);
		glScalef(0.3, 0.3, 1.0);
		gluSphere(quadric_.get(), 0.1, 10, 10);
		glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();
}

void OpenGLTools::drawSmallCar()
{
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.05);
		glColor3f(0.2, 0.2, 0.95);
		glScalef(0.3, 0.15, 0.1);
		drawCube();
		glColor3f(1.0, 1.0, 1.0);
		glPopMatrix();
}

void OpenGLTools::drawLargeCar()
{
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.1);
		glColor3f(0.95, 0.2, 0.2);
		glScalef(0.35, 0.18, 0.15);
		drawCube();
		glColor3f(1.0, 1.0, 1.0);
		glPopMatrix();
}

