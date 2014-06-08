#include "simulation.h"

void Simulation::load()
{
    city_.load();
    //obj_.push_back(std::shared_ptr<Object>(new Human(8, 0, 0, 0.5d, ObjectInitDir::North)));

	//obj_[0].get()->addPathItem(PIDir::Forward);
	//obj_[0].get()->addPathItem(PIDir::Left, PIR::Rs);
	//obj_[0].get()->addPathItem(PIDir::Forward);

    //obj_.push_back(std::shared_ptr<Object>(new SmallCar(0, 1, 1, 1.0d, ObjectInitDir::North)));
	//obj_[1].get()->addPathItem(PIDir::Forward);
	//obj_[1].get()->addPathItem(PIDir::Left, PIR::Rl);
	//obj_[1].get()->addPathItem(PIDir::Forward);

    //obj_.push_back(std::shared_ptr<Object>(new LargeCar(5, 3, 2, 1.0d, ObjectInitDir::East)));
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

void Simulation::addObject(QString type, double speed, double x, double y)
{
    if (type == "Human")
       obj_.push_back(std::shared_ptr<Object>(new Human(x, y, speed)));
    else if (type == "Small Car")
       obj_.push_back(std::shared_ptr<Object>(new SmallCar(x, y, speed)));
    else if (type == "Large Car")
       obj_.push_back(std::shared_ptr<Object>(new LargeCar(x, y, speed)));
}

void Simulation::addPath(int idObject, double x, double y)
{
    obj_[idObject].get()->addPathItem(x, y);
}

double Simulation::incr_time()
{
    time_ = time_ + 0.01;
    return time_;
}
