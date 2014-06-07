#include "simulation.h"

void Simulation::load(QString filePath) throw(Exception)
{
	city_.load("Path there is probably not a good solution..");
	obj_.push_back(std::shared_ptr<Object>(new Human(8, 0, 0, 0.5d, ObjectInitDir::North)));

	//obj_[0].get()->addPathItem(PIDir::Forward);
	//obj_[0].get()->addPathItem(PIDir::Left, PIR::Rs);
	//obj_[0].get()->addPathItem(PIDir::Forward);

	obj_.push_back(std::shared_ptr<Object>(new SmallCar(0, 1, 1, 1.0d, ObjectInitDir::North)));
	//obj_[1].get()->addPathItem(PIDir::Forward);
	//obj_[1].get()->addPathItem(PIDir::Left, PIR::Rl);
	//obj_[1].get()->addPathItem(PIDir::Forward);

	obj_.push_back(std::shared_ptr<Object>(new LargeCar(5, 3, 2, 1.0d, ObjectInitDir::East)));
	//obj_[2].get()->addPathItem(PIDir::Forward);
	//obj_[2].get()->addPathItem(PIDir::Right, PIR::Rs);
   // obj_[2].get()->addPathItem(PIDir::Forward);
}

void Simulation::drawAll()
{
	city_.draw();
	for (std::shared_ptr<Object> o : obj_) {
		glPushMatrix();
			//OpenGLTools::drawSmallCar();
			o.get()->drawAt(time_);
		glPopMatrix();
	}
}

void Simulation::addObject(QString type, double x, double y)
{
    if (type == "Human")
       obj_.push_back(std::shared_ptr<Object>(new Human(8, x, y, 0.5d, ObjectInitDir::North)));
    else if (type == "Small Car")
       obj_.push_back(std::shared_ptr<Object>(new SmallCar(8, x, y, 0.5d, ObjectInitDir::North)));
    else if (type == "Large Car")
       obj_.push_back(std::shared_ptr<Object>(new LargeCar(8, x, y, 0.5d, ObjectInitDir::North)));
}

void Simulation::addPath(int idObject, double x, double y)
{
    obj_[idObject].get()->addPathIt(x, y);
}

double Simulation::incr_time()
{
    time_ = time_ + 0.01;
    return time_;
}
