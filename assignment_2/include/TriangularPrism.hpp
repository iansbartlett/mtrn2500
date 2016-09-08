
#ifndef MTRN3500_TRI_PRISM_H
#define MTRN3500_TRI_PRISM_H

#include "Shape.hpp"

class TriangularPrism: public Shape{

public:  
  TriangularPrism();
  TriangularPrism(double x_, double y_, double z_);
  TriangularPrism(double x_, double y_, double z_, double rotation_);
  void draw();

  double get_angle();
  double get_side();
  double get_x_length();
  double get_z_length();

  void set_x_length(double new_x_length);
  void set_angle(double new_angle);
  void set_side(double new_side);
  void set_z_length(double new_z_length);
  
  ~TriangularPrism();
protected:
  double angle,side,x_length, z_length; 
  
};


#endif
