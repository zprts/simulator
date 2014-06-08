#ifndef PATH_H
#define PATH_H

#include <QGLWidget>
#include "tools.h"
#include <cmath>

class Object;

/**
 * @brief Klasa opisująca elementy ścieżki, po której porusza się obiekt.
 */
class WayPoint {	//I really hope that eps of d_ and a_ won't be critical...
public:
	WayPoint(double d = 0.0d, double a = 0.0d) : d_(d), a_(a) {
	}
	double	d_; //!< Długość odcinka jaką należy przejść w rmach danego elementu.
	double	a_; //!< Kąt obrotu przed wykonaniem translacji

	/**
	* @brief Funkcja wykonująca włąściwe przejście w przestrzeni OpenGL.
	* Wykonuje rotację i translację do miejsca, w którym powinien znajdować się obiekt
	* po przejściu dystansu \p dist.
	* Jeśli dystans w parametrze jest większy niż zapisany w obiekcie - translacja
	* odbywa się na odłegłość \p d_.
	* @param dist Odległość jaką należy przejść w ramach danego obiektu klasy WayPoint.
	* @return Pozostała odległość do przejścia. Jeśli \p dist < \p d_ zwracane jest 0.
	* W przeciwnym przypadku zwracana jest różnica \p d_ - \p dist.
	*/
	double	walk(const double &dist);
};

/**
 * @brief Klasa opisująca ścieżkę obiektu.
 */
class Path
{
	friend class Object;
public:
	Path();

	QVector<WayPoint> wps_; //!< Wektor zawierający elementy ścieżki

	/**
	 * @brief Funkcja ustawiająca układ współrzędnych OpenGL w miejscu, w którym obiekt znajdowałby się
	 * po przejściu dystansu \p dist. Jeśli dystans jest większy od całkowitej długości ścieżki - obiekt
	 * rozpoczyna przejście ścieżki od początku.
	 * @param dist Dystans do przejścia.
	 */
	void	walk(double dist);
private:
	double	totalLength_; //!< Całkowita długość ścieżki. Używana przez zaprzyjaźnioną klasę Object.
};

#endif // PATH_H
