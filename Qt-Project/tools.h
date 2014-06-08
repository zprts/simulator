#ifndef TOOLS_H
#define TOOLS_H

#include <QGLWidget>
#include <QImage>
#include <QException>
#include <GL/glu.h>
#include <memory>

/**
 * @brief Rozszerzona kalsa QException zawierająca tekstowy opis wyjątku.
 */
class Exception : public QException {
public:
	Exception(QString desc) {
		desc_ = desc;
	}
	/**
	 * @brief Metoda zwracająca opis wyjątku.
	 * @return Obiekt QString z opisem wyjątku.
	 */
	QString getDesc() {
		return desc_;
	}
private:
	QString desc_; //!< Zmienna zawierająca opis wyjątku
};

/**
 * @brief Klasa zawierająca zestaw statycznych metod do obsługi podstawowych operacji związnych z grafiką w OpenGL.
 */
class OpenGLTools
{
public:
	//OpenGLTools();
	/**
	 * @brief Funkcja ładująca teksturę do kontekstu OpenGL.
	 * @param path Ścieżka do pliku z teksturą.
	 * @throw Exception
	 * @return Identyfikator tekstury w kontekście OpenGL.
	 */
	static GLuint	loadTexture(QString path) throw (Exception);
	/**
	 * @brief Metoda rysująca kwadrat w płaszczyźnie XY
	 */
	static void		drawPlane();
	/**
	 * @brief Metoda rysująca sześcian o jednostkowym boku.
	 */
	static void		drawCube();
	/**
	 * @brief Metoda rysująca postać człowieka (pieszego).
	 */
	static void		drawHuman();
	/**
	 * @brief Metoda rysująca obiekt małego samochodu.
	 */
	static void		drawSmallCar();
	/**
	 * @brief Metoda rysująca obiekt dużego samochodu.
	 */
	static void		drawLargeCar();
};



#endif // TOOLS_H
