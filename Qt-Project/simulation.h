#ifndef SIMULATION_H
#define SIMULATION_H

#include "city.h"
#include "object.h"

class Camera;

class Simulation
{
	friend class Camera;
public:
	static Simulation *getInstance() {
		static Simulation sim;
		return &sim;
	}
	void load(QString filePath) throw(Exception);
	void setSimulationTime(double time) {
		time_ = time;
	}
	void drawAll();
private:
	Simulation() {}
	explicit Simulation(Simulation &) {}
	double		time_ = 0.0;
	City		city_;
	QVector<std::shared_ptr<Object>>	obj_;
};

#endif // SIMULATION_H
