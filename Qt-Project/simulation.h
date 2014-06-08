#ifndef SIMULATION_H
#define SIMULATION_H

#include "city.h"
#include "object.h"
#include <QTimer>

class Camera;

class Simulation
{
	friend class Camera;
public:
	static Simulation *getInstance() {
		static Simulation sim;
		return &sim;
	}
    void load();
	void setSimulationTime(double time) {
		time_ = time;
	}
    void drawAll();

    void addObject(QString type, double speed, double x, double y);
    void addPath(int idObject, double x, double y);

    double incr_time();
private:
	Simulation() {}
	explicit Simulation(Simulation &) {}
	double		time_ = 0.0;
    double      max_time;
	City		city_;
    QVector<std::shared_ptr<Object>>	obj_;
};

#endif // SIMULATION_H
