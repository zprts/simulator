#ifndef OBJECT_H
#define OBJECT_H

#include "tile.h"
#include "tools.h"
#include "path.h"

//enum class ObjectInitDir {North = 0, South = 2, East = 3, West = 1};
/*!
 * \brief The Object class Obiekt dynamiczny dodawany do symulacji.
 */
class Object
{
public:
    Object(double initX, double initY, double speed) :
        initX_(initX), initY_(initY), speed_(speed/4) {
	}
	virtual void drawAt(double time) = 0;

	void	clearPath() {
		p_.totalLength_ = 0.0d;
		p_.wps_.clear();
	}

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

class Human : public Object {
public:
    Human(double initX, double initY, double speed) : Object(initX, initY, speed) {

	}
	virtual void drawAt(double time);
private:
};

class SmallCar : public Object {
public:
    SmallCar(double initX, double initY, double speed) : Object(initX, initY, speed) {

    }

	virtual void drawAt(double time);
private:
};
class LargeCar : public Object {
public:
    LargeCar(double initX, double initY, double speed) : Object(initX, initY, speed) {

	}
	virtual void drawAt(double time);
private:
};

#endif // OBJECT_H
