
#ifndef MTRN3500_TRAP_PRISM_H
#define MTRN3500_TRAP_PRISM_H

#include "Shape.hpp"

class TrapezoidalPrism: public Shape{

public:  
  TrapezoidalPrism();
  TrapezoidalPrism(double x_, double y_, double z_);
  TrapezoidalPrism(double x_, double y_, double z_, double rotation_);
  void draw();

  double get_bottom_x_length();
  double get_top_x_length();
  double get_y_length();
  double get_z_length();
  double get_offset();

  void set_bottom_x_length(double new_bottom_x_length);
  void set_top_x_length(double new_top_x_length);
  void set_y_length(double new_y_length);
  void set_z_length(double new_z_length);
  void set_offset(double new_offset);
  
  ~TrapezoidalPrism();
protected:
  double bottom_x_length,top_x_length, y_length, z_length; 
  double offset; 
};


#endif
