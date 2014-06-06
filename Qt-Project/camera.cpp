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



int Camera::genObservation(Simulation *sim)
{

    /* //tak to powinno wyglądać
     * QColor bigCar;
     * bigCar.setBlue(0)
     * bigCar.setRed(255);
     * bigCar.setGreen(0);
     * QRgb bigCar_color = (QRgb)bigCar.rgb();
     */

    QColor red;
    red.setBlue(0);
    red.setRed(255);
    red.setGreen(0);
    QRgb red_pxl = (QRgb)red.rgb();

    QImage qImg = this->genImage(sim);

    if (!qImq) return 0;

    /* 18:00 nadal nie mogę kodu przetestować
     * nie wiem jeszcze jak przekazac wszystko na raz, jakąś multimapą
     * ale to raczej nie duży problem
     */
    std::vector<std::pair<int, int> > red_centres = findCentres(&qImg, red_pxl);

    return 1;
}

std::vector<std::pair<int, int> > Camera::findCentres(QImage *img, QRgb color)
/*
 * Przeszukanie obrazu w celu znalezienia plam o okreslonym w argumencie color kolorze
 * oraz zwrocenie tablicy pikseli srodkowych wszystkich plam,
 * obliczonych na podstawie sredniej arytmetycznej.
 */
{
    int color_map[IMG_WIDTH][IMG_HEIGHT];
    for(int y = 0; y < IMG_HEIGHT ; y++)
        for(int x = 0; x < IMG_WIDTH; x++)
            color_map[x][y] = 0;

    int color_areas_number = 0;
    std::vector<int> color_areas_pxl_number;

    for(int y = 0; y < IMG_HEIGHT ; y++)
    {
        for(int x = 0; x < IMG_WIDTH; x++)
        {
            if ((img->pixel(x,y) == color) && (color_map[x][y] == 0))
            {
                   color_areas_number++;
                   int temp = 0;

                   fillColorMap(x, y, img, color_map,
                                color_areas_number, color, &temp);
                   color_areas_pxl_number.push_back(temp);
            }
        }
    }

    std::vector<std::pair<int, int> >centres;

    for (int k = 1; k <= color_areas_number; k++)
    {
        int temp_x = 0, temp_y = 0;
        for(int y = 0; y < IMG_HEIGHT ; y++)
        {
            for(int x = 0; x < IMG_WIDTH; x++)
            {
                if (color_map[x][y] == k)
                {
                    temp_x += x;
                    temp_y += y;
                }
            }
        }
        temp_x = round((double)temp_x/color_areas_pxl_number[k-1]);
        temp_y = round((double)temp_y/color_areas_pxl_number[k-1]);
        centres.push_back(std::make_pair(temp_x, temp_y));
        return centres;
    }
}

void Camera::fillColorMap(  int x, int y,
                            QImage *img,
                            int color_map[IMG_WIDTH][IMG_HEIGHT],
                            int area_number,
                            QRgb color,
                            int *pxl_number)
/*
 * Realizacja algorytmu wypelniania przez spojnosc dla siatki czterospojnej
 * wraz ze sprawdzeniem koncow tablicy plam kolorów (color_map).
 *
 * area_number określa numer plamy
 * color to kolor szukanej plamy
 * pod pxl_number znajduje się liczba pikseli należących do szukanej plamy *
 */
{
   color_map[x][y] = area_number;
   *pxl_number++;

    if ((x-1 >= 0)
        && (color_map[x-1][y] != area_number)
        && (img->pixel(x-1, y) == color))
        fillColorMap(x-1, y, img, color_map, area_number, color, pxl_number);

    if ((x+1 < IMG_WIDTH)
        && (color_map[x+1][y] != area_number)
        && (img->pixel(x+1,y) == color))
        fillColorMap(x+1, y, img, color_map, area_number, color, pxl_number);

    if ((y-1 >= 0)
        && (color_map[x][y-1] != area_number)
        && (img->pixel(x,y-1) == color))
        fillColorMap(x, y-1, img, color_map, area_number, color, pxl_number);

    if ((y+1 < IMG_HEIGHT)
        && (color_map[x][y+1] != area_number)
        && (img->pixel(x,y+1) == color))
        fillColorMap(x, y+1, img, color_map, area_number, color, pxl_number);
}

//http://wazniak.mimuw.edu.pl/index.php?title=GKIW_Modu%C5%82_3_-_Podstawowe_operacje_rastrowe
