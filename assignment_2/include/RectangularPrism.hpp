
#ifndef MTRN3500_RECT_PRISM_H
#define MTRN3500_RECT_PRISM_H

#include "Shape.hpp"

class RectangularPrism: public Shape{

public:  
  RectangularPrism();
  RectangularPrism(double x_, double y_, double z_);
  RectangularPrism(double x_, double y_, double z_, double rotation_);
  void draw();

  double get_x_length();
  double get_y_length();
  double get_z_length();

  void set_x_length(double new_x_length);
  void set_y_length(double new_y_length);
  void set_z_length(double new_z_length);
  
  ~RectangularPrism();
protected:
     double x_length, y_length, z_length; 
  
};


#endif
