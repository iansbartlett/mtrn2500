#ifndef MTRN3500_MY_VEHICLE_H
#define MTRN3500_MY_VEHICLE_H

#include "Vehicle.hpp"
#include "Shape.hpp"
#include "Cylinder.hpp"
#include "RectangularPrism.hpp"

class MyVehicle: public Vehicle {

public:
  MyVehicle();
  //MyVehicle(double x_, double y_, double z_);
  //MyVehicle(double x_, double y_, double z_, double rotation_);
  ~MyVehicle();

  void draw();

private:
  
};

#endif
