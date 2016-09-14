#ifndef MTRN3500_MY_VEHICLE_H
#define MTRN3500_MY_VEHICLE_H

#include "Vehicle.hpp"
#include "Shape.hpp"
#include "Cylinder.hpp"
#include "RectangularPrism.hpp"

class MyVehicle: public Vehicle {

public:
  MyVehicle();
  ~MyVehicle();

  void draw();

private:
  
};

#endif
