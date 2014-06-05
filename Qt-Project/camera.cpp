#include "camera.h"

void Camera::lookAt()
{
	QVector3D v = pos_ + step_;
	gluLookAt(pos_.x(), pos_.y(), pos_.z(), v.x(), v.y(), v.z(), 0.0, 0.0, 1.0);
}

void Camera::rotate(QPoint p)
{
	angleXY_ += p.rx() * 0.002f;
	angleZ_	 += p.ry() * 0.002f;
	if (angleZ_ < -M_PI_2*0.99f)
		angleZ_ = -M_PI_2*0.99f;
	if (angleZ_ > M_PI_2*0.99f)
		angleZ_ = M_PI_2*0.99f;
	if (angleXY_ < 0.0f)
		angleXY_ += 2*M_PI;
	if (angleXY_ > 2*M_PI)
		angleXY_ -= 2*M_PI;

	step_[0] = qCos(angleZ_)*qCos(angleXY_);
	step_[1] = qCos(angleZ_)*qSin(angleXY_);
	step_[2] = qSin(angleZ_);
}

void Camera::moveXY(QPoint p)
{
	QVector3D v = step_;
	v.setZ(0.0);
	v.normalize();
	pos_ += v*(p.ry()*0.003f);
	v[0] = step_[1];
	v[1] = -step_[0];
	v.normalize();
	pos_ -= v*(p.rx()*0.003f);
}

void Camera::distance(QPoint p)
{
	//pos_ -= step_ * p.ry()*0.005f;
	pos_[2] += p.ry()*0.005f;
}

void Camera::genView(Simulation *sim)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	lookAt();
	if (sim)
		sim->drawAll();
}

QImage Camera::genImage(Simulation *sim)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	lookAt();
	if (sim)
		sim->drawAll();

	float tab[4]{};
	glGetFloatv(GL_VIEWPORT, tab);
	QImage img(tab[2], tab[3], QImage::Format_RGB32);
	glReadPixels(0, 0, tab[2], tab[3], GL_BGRA, GL_UNSIGNED_BYTE, img.bits());
	return img;
}

void Camera::genObservation(Simulation *sim)
{
    QImage qImg = this->genImage(sim);

    int colors[3];
    int red_pxl_number = 0;

    QRgb* line;
    for(int y = 0; y < qImg.height() ; y++)
    {
        line = (QRgb *)qImg.scanLine(y);
        for(int x = 0; x < qImg.width(); x++)
        {
            colors[0] += qRed(line[x]);
            colors[1] += qGreen(line[x]);
            colors[2] += qBlue(line[x]);

            if (qRed(line[x]) > 200
                && (qRed(line[x])/qGreen(line[x]) > 8)
                && (qRed(line[x])/qBlue(line[x]) > 8))
                red_pxl_number++;
            //8 - stosunek dla którego mozna stwierdzic
            //ze kolor jest 'czerwony'  dobralem recznie
        }
    }
    int qImg_size = qImg.height() * qImg.width();

    double colors_percent[3];
    for(int k = 0; k < 3; k++)
        colors_percent[k] = 100*(colors[k]/255)/qImg_size;
    //procent zapelnienia poszczegolnych przestrzeni barw

    double red_pxl_percent = red_pxl_number/qImg_size;
    //procent czerwonego na obrazie

}
