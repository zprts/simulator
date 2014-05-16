#include "simulation.h"


void Simulation::load(QString filePath) throw(Exception)
{
	city_.load("Path there is probably not a good solution..");
	obj_.push_back(std::shared_ptr<Object>(new Human(7, 1, 1, 1.0d, ObjectInitDir::North)));
	obj_[0].get()->addPathItem(PIDir::Forward);
	obj_[0].get()->addPathItem(PIDir::Left, PIR::Rs);
	obj_[0].get()->addPathItem(PIDir::Forward);

	obj_.push_back(std::shared_ptr<Object>(new SmallCar(0, 1, 1, 1.0d, ObjectInitDir::North)));
	obj_[1].get()->addPathItem(PIDir::Forward);
	obj_[1].get()->addPathItem(PIDir::Left, PIR::Rl);
	obj_[1].get()->addPathItem(PIDir::Forward);

	obj_.push_back(std::shared_ptr<Object>(new LargeCar(5, 3, 2, 1.0d, ObjectInitDir::East)));
	obj_[2].get()->addPathItem(PIDir::Forward);
	obj_[2].get()->addPathItem(PIDir::Right, PIR::Rs);
	obj_[2].get()->addPathItem(PIDir::Forward);
}

void Simulation::drawAll()
{
	city_.draw();
	for (std::shared_ptr<Object> o : obj_) {
		glPushMatrix();
			o.get()->drawAt(time_);
		glPopMatrix();
	}
}
