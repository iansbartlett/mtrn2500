
#include "Wheel.hpp"
#include "RectangularPrism.hpp"
#include "Cylinder.hpp"

/*
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined(WIN32)
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
*/
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//#endif

#include <math.h>

#define DEFAULT_SLICES 64

Wheel::Wheel(): Shape(){
  addShape(new Cylinder());
  addShape(new RectangularPrism(0.05, 0.0, 0.5));
  dynamic_cast<Cylinder*>(shapes[0])->set_radius(0.4);
  dynamic_cast<Cylinder*>(shapes[0])->set_y_length(0.1);
  dynamic_cast<RectangularPrism*>(shapes[1])->set_x_length(0.1);
  dynamic_cast<RectangularPrism*>(shapes[1])->set_y_length(0.4);
  dynamic_cast<RectangularPrism*>(shapes[1])->set_z_length(0.2);
  wheel_rotation = 0;
};

Wheel::Wheel(double x_, double y_, double z_): Shape(x_, y_, z_){
  addShape(new Cylinder());
  addShape(new RectangularPrism(0.0, 0.1, 0.1));
  dynamic_cast<Cylinder*>(shapes[0])->set_radius(0.4);
  dynamic_cast<Cylinder*>(shapes[0])->set_y_length(0.1);
  dynamic_cast<RectangularPrism*>(shapes[1])->set_x_length(0.1);
  dynamic_cast<RectangularPrism*>(shapes[1])->set_y_length(0.6);
  dynamic_cast<RectangularPrism*>(shapes[1])->set_z_length(0.2);
  shapes[0]->setColor(1.0,0,0);
  shapes[1]->setColor(0,0,1.0);
  wheel_rotation = 0;
};

Wheel::Wheel(double x_, double y_, double z_, double rotation_):
  Shape(x_, y_, z_, rotation_){
  addShape(new Cylinder());
  addShape(new RectangularPrism(0.05, 0.0, 0.1));
  dynamic_cast<Cylinder*>(shapes[0])->set_radius(0.4);
  dynamic_cast<Cylinder*>(shapes[0])->set_y_length(0.1);
  dynamic_cast<RectangularPrism*>(shapes[1])->set_x_length(0.1);
  dynamic_cast<RectangularPrism*>(shapes[1])->set_y_length(0.4);
  dynamic_cast<RectangularPrism*>(shapes[1])->set_z_length(0.2);

  shapes[0]->setColor(1.0,0,0);
  shapes[1]->setColor(0,0,1.0);
  wheel_rotation = 0;
};
void Wheel::draw(){
  
  glPushMatrix();
  glTranslated(x,y+0.4,z);
  glRotated(rotation,0,1,0);
  glRotated(-wheel_rotation,0,0,1);
  glTranslated(0,-0.4,0);
  
  for(int i = 0; i < shapes.size(); i++){
      shapes[i]->draw();
  }
  glPopMatrix();
  
};

double Wheel::get_wheel_rotation(){
  return wheel_rotation; 
};

void Wheel::set_wheel_rotation(double new_wheel_rotation){
  wheel_rotation = new_wheel_rotation;
};

Wheel::~Wheel(){

};

void Wheel::addShape(Shape * shape) 
{
	shapes.push_back(shape);
}
