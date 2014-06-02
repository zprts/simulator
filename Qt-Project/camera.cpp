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

cv::Mat QImage2Mat(QImage const& inImage)
{
    cv::Mat mat( inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );
    return mat.clone();
    //ma blizej nieokreslony problem z przekonwertowaniem
    //mimo const_cast to poprawny i dzialajacy sposob przekonwertowania QImage::Format_RGB32 na cv::Mat
}

void Camera::genObservation(Simulation *sim)
{
    if (sim)
    using namespace cv;
    QImage qimgOriginal = this->genImage(sim);
    Mat imgOriginal = this->QImage2Mat(qimgOriginal);

}
