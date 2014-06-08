#ifndef OBJECT_H
#define OBJECT_H

#include "tile.h"
#include "tools.h"
#include "path.h"

//enum class ObjectInitDir {North = 0, South = 2, East = 3, West = 1};
/*!
 * \brief Obiekt dynamiczny dodawany do symulacji.
 */
class Object
{
public:
    Object(double initX, double initY, double speed) :
        initX_(initX), initY_(initY), speed_(speed/4) {
	}
	/**
	 * @brief Object::drawAt Całkowicie wirtualna metoda, która w obiekcie właściwej kalsy rysuje dany obiekt w OpenGL.
	 * Obiekt rysowany jest w miejscu i pod kątem jaki miałby po wykonywaniu ruchu przez czas time.
	 * @param time Parametr opisujący czas symulacji w jakim obiekt ma byc narysowany.
	 */
	virtual void drawAt(double time) = 0;

	void	clearPath() {
		p_.totalLength_ = 0.0d;
		p_.wps_.clear();
	}
	/*!
	 * \brief Object::addPathItem
	 * Dodaje wskazaną ściezkę poruszania się obiektu. Na podstawie różnicy między aktualnym
	 * i nastepnym położeniem oraz na podstawie aktalnego kąta obiektu oblicza wymagany kąt skrętu obiektu
	 * \param x składowa x wektora różnicy pomiędzy aktualnym i nastepnym położeniem
	 * \param y składowa y wektora różnicy pomiędzy aktualnym i nastepnym położeniem
	 */
    void addPathItem(double x, double y);

protected:
    /*!
     * \brief p_ ścieżka po której porusza się obiekt
     */
    Path	p_;
    /*!
     * \brief initX_ początkowa pozycja x
     */
    double		initX_;
    /*!
     * \brief initY_ początkowa pozycja y
     */
    double		initY_;
    /*!
     * \brief speed prędkość
     */
    double	speed_;
    /*!
     * \brief currentAngle aktualny kąt obiektu
     */
    double currentAngle = 0;
};
/**
 * @brief Klasa obiektu opisującego pieszego w symulacji
 */
class Human : public Object {
public:
    Human(double initX, double initY, double speed) : Object(initX, initY, speed) {

	}
	virtual void drawAt(double time);
private:
};

/**
 * @brief Klasa obiektu opisującego mały samochód w symulacji
 */
class SmallCar : public Object {
public:
    SmallCar(double initX, double initY, double speed) : Object(initX, initY, speed) {

    }

	virtual void drawAt(double time);
private:
};

/**
 * @brief Klasa obiektu opisującego duży samochód w symulacji
 */
class LargeCar : public Object {
public:
    LargeCar(double initX, double initY, double speed) : Object(initX, initY, speed) {

	}
	virtual void drawAt(double time);
private:
};

#endif // OBJECT_H
