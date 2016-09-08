
#ifndef MTRN3500_CYL_PRISM_H
#define MTRN3500_CYL_PRISM_H

#include "Shape.hpp"

class CylindricalPrism: public Shape{

public:  
  CylindricalPrism();
  CylindricalPrism(double x_, double y_, double z_);
  CylindricalPrism(double x_, double y_, double z_, double rotation_);
  void draw();

  double get_radius();
  double get_y_length();

  void set_radius(double new_radius);
  void set_y_length(double new_y_length);
  
  ~CylindricalPrism();
protected:
  double  radius, y_length; 
  int slices;  
};


#endif
