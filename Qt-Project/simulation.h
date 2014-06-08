#ifndef SIMULATION_H
#define SIMULATION_H

#include "city.h"
#include "object.h"
#include <QTimer>

class Camera;

/**
 * @brief Singleton opisujący symulację
 */
class Simulation
{
	friend class Camera;
public:
	/**
	 * @brief getInstance Funkcja zwraca instancję obiektu klasy Simulation
	 * @return Wskaźnik do obiektu
	 */
	static Simulation *getInstance() {
		static Simulation sim;
		return &sim;
	}
	/**
	 * @brief load Funkcja ładuje symulację
	 */
    void load();
	/**
	 * @brief setSimulationTime Funkcja ustawia aktualny czas symulacji
	 * @param time Czas symulacji
	 */
	void setSimulationTime(double time) {
		time_ = time;
	}
	/**
	 * @brief drawAll Funkcja rysuje symulację
	 */
    void drawAll();
	/*!
	 * \brief Simulation::addObject
	 * Dodaje obiekt do symulacji.
	 * \param type typ obiektu
	 * \param speed prędkość obiektu
	 * \param x współrzędna x
	 * \param y współrzędna y
	 */
    void addObject(QString type, double speed, double x, double y);
	/*!
	 * \brief Simulation::addPath
	 * Dodaje ścieżkę ruchu obiektu.
	 * \param idObject id obiektu
	 * \param x współrzędna x następnego punktu
	 * \param y współrzędna y następnego punktu
	 */
    void addPath(int idObject, double x, double y);
	/*!
	 * \brief Simulation::incr_time
	 * Zwiększa czas symulacji.
	 * \return aktualny czas symulacji
	 */
    double incr_time();
private:
	Simulation() {}
	explicit Simulation(Simulation &) {}
	double		time_ = 0.0; //!< czas symulacji
	City		city_;	//!< Miasto, z którym płączona jest symulacja
	/**
	 * @brief Wektor obiektów opisywanych przez symulację
	 * @see Human SmallCar LargeCar
	 */
	QVector<std::shared_ptr<Object>>	obj_;
};

#endif // SIMULATION_H
