#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QtCore/qmath.h>
#include "city.h"
#include "simulation.h"
#include <vector>


class Camera
{
public:
	Camera(QString name = "cam") : name_(name) {
		step_[0] = qCos(angleZ_)*qCos(angleXY_);
		step_[1] = qCos(angleZ_)*qSin(angleXY_);
		step_[2] = qSin(angleZ_);
	}
	/**
	 * @brief Klasa pomocnicza do opisu tła mapy z obrazem
	 */
	class MapBg : public std::vector<std::vector<int>> {
	public:
		void init(QImage *img) {
			init(img->width(), img->height());
		}
		void init(int w, int h) {
			clear();
			resize(w, vector<int>(h, 0));
		}
	};
	/**
	 * @brief Struktura opisująca obserwację
	 */
	struct Observation {
		std::vector<QPoint> people, smallCars, largeCars;
	};
	/**
	 * @brief Funkcja wykonuje ustawienie kamery w odpowiednim kierunku w kontekście OpenGL
	 */
	void		lookAt();

	/**
	 * @brief Wykonuje rotację kamery zadaną przez przesunięcie myszki.
	 * @param p Przesunięcie kursora określające obrót.
	 */
	void		rotate(QPoint p);
	/**
	 * @brief Wykonuje przesunięcie kamery w płaszczyźnie XY.
	 * @param p Względna zmiana położenia kursora na ekranie.
	 */
	void		moveXY(QPoint p);
	/**
	 * @brief Ustawia dystans od płaszczyzny miasta - wysokość kamery
	 * @param p Względna zmiana położenia kursora na ekranie.
	 */
	void		distance(QPoint p);

	/**
	 * @brief Funkcja generuje widok OpenGL zgodnie z symulacją podaną w parametrze.
	 * @param sim Parametr opisujący symulację.
	 */
	void		genView(Simulation *sim);
	/**
	 * @brief Funkcja generuje bitmapę z widokiem z kamery.
	 * @param sim Obiekt aktualnej symulacji
	 * @return Bitmapa z widokiem z kamery
	 */
	QImage		genImage(Simulation *sim);
	/**
	 * @brief Funkcja zwraca obserwacje widziane przez kamerę: Camera::Observation
	 * @param sim Aktualna symulacja
	 * @return Obiekt klasy Observation zawierający opis widzianych obiektów
	 */
	Observation genObservation(Simulation *sim);

	/**
	 * @brief Funkcja zwraca nazwę kamery.
	 * @return Nazwa kamery
	 */
	QString		getName() {
		return name_;
	}
	/**
	 * @brief Funkcja ustawia nazwę kamery.
	 * @param name Nazwa kamery
	 */
	void		setName(QString name) {
		name_ = name;
	}
private:
	QVector3D	pos_ = {0.0, 0.0, 1.1}; //!< Pozycja kamery
	QVector3D	step_; //!< Wektor określający kierunek patrzenia
	qreal		angleXY_ = 0.0; //!< Kąt na płaszczyźnie XY liczony standardowo (od osi X).
	qreal		angleZ_ = -M_PI_2*0.3f; //!< Kąt do osi Z
	QString		name_;	//!< Nazwa kamery

public:
	/**
	 * @brief Funkcja wykorzystywana w algorytmie generowania obserwacji
	 * @param x Pozycja X z której startujemy algorytm wypełnienia
	 * @param y Pozycja Y z której startujemy algorytm wypełnienia
	 * @param img Obraz, który analizujemy
	 * @param mapBg Mapa tła analizowanego obrazu
	 * @param area_number Numer dla obiektu, który może zostac znaleziony
	 * @param color Kolor szukanego obiektu
	 * @param [out] pxl_number Ilość pikseli, z których składa się obiekt
	 */
	static void fillColorMap(int x, int y,
					  QImage *img,
					  MapBg &mapBg,
					  int area_number,
					  QRgb color,
					  int &pxl_number);

	/**
	 * @brief Funkcja znajduje pozycję obiektów o danym kolorze
	 * @param img Obraz, który przeszukujemy
	 * @param color Kolor, którego szukmy
	 * @return Wektor pozycji znalezionych obiektów (pozycja na bitmapie).
	 */
	static std::vector<QPoint> findCentres(QImage *img, QRgb color);
};

#endif // CAMERA_H
