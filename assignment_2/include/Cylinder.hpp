
#ifndef MTRN3500_CYL_H
#define MTRN3500_CYL_H

#include "Shape.hpp"

class Cylinder: public Shape{

public:  
  Cylinder();
  Cylinder(double x_, double y_, double z_);
  Cylinder(double x_, double y_, double z_, double rotation_);
  void draw();

  double get_radius();
  double get_y_length();

  void set_radius(double new_radius);
  void set_y_length(double new_y_length);

  double get_wheel_rotation();
  void set_wheel_rotation(double new_wheel_rotation);
  
  bool get_isRolling();
  bool get_isSteering();

  void set_isRolling(bool);
  void set_isSteering(bool);
  ~Cylinder();
protected:
  double  radius, y_length; 
  int slices;  
  bool isRolling;
  bool isSteering;
  double wheel_rotation; 
};


#endif
