#include "MyVehicle.hpp"
#include "Cylinder.hpp"
#include "RectangularPrism.hpp"
#include "Shape.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

MyVehicle::MyVehicle() : Vehicle() {
  glPushMatrix(); 
  //Create basic structures
  addShape(new Cylinder(1.1, 0.4, 1.05));
  addShape(new Cylinder(1.1, 0.4, -1.05));
  addShape(new Cylinder(-1.1, 0.4, 1.05));
  addShape(new Cylinder(-1.1, 0.4, -1.05));
  addShape(new RectangularPrism(0, 0.4, 0));
  dynamic_cast<Cylinder*>(shapes[0])->set_radius(0.4);
  dynamic_cast<Cylinder*>(shapes[0])->set_y_length(0.1);
  dynamic_cast<Cylinder*>(shapes[1])->set_radius(0.4);
  dynamic_cast<Cylinder*>(shapes[1])->set_y_length(0.1);
  dynamic_cast<Cylinder*>(shapes[2])->set_radius(0.8);
  dynamic_cast<Cylinder*>(shapes[2])->set_y_length(0.1);
  dynamic_cast<Cylinder*>(shapes[3])->set_radius(0.8);
  dynamic_cast<Cylinder*>(shapes[3])->set_y_length(0.1);
  //Set chassis sizes
  dynamic_cast<RectangularPrism*>(shapes[4])->set_x_length(3.0);
  dynamic_cast<RectangularPrism*>(shapes[4])->set_y_length(1.0);
  dynamic_cast<RectangularPrism*>(shapes[4])->set_z_length(2.0);

  shapes[0]->setColor(0,0,1);
  shapes[1]->setColor(0,0,1);
  shapes[2]->setColor(0,0,1);
  shapes[3]->setColor(0,0,1);
  
  
  glPopMatrix();
 
};
/*
MyVehicle::MyVehicle(double x_, double y_, double z_){
 
  glPushMatrix(); 
  glTranslated(x,y,z);
  //Create basic structures
  f_wheel_1 = new Cylinder(1.1, 0.4, 1.05);
  f_wheel_2 = new Cylinder(1.1, 0.4, -1.05);
  r_wheel_1 = new Cylinder(-1.1, 0.8, 1.05);
  r_wheel_2 = new Cylinder(-1.1, 0.8, -1.05);
  chassis = new RectangularPrism(0, 0, 0.4);
  //Create wheel sizes
  f_wheel_1->set_radius(0.4);
  f_wheel_1->set_y_length(0.1);
  f_wheel_2->set_radius(0.4);
  f_wheel_2->set_y_length(0.1);
  r_wheel_1->set_radius(0.8);
  r_wheel_1->set_y_length(0.1);
  r_wheel_2->set_radius(0.8);
  r_wheel_2->set_y_length(0.1);
  //Set chassis sizes
  chassis->set_x_length(3.0);
  chassis->set_y_length(1.0);
  chassis->set_z_length(2.0);
  glPopMatrix();
  
};

MyVehicle::MyVehicle(double x_, double y_, double z_, double rotation_){
  
  glPushMatrix(); 
  glTranslated(x,y,z);
  glRotated(rotation,0,1,0);
  //Create basic structures
  f_wheel_1 = new Cylinder(1.1, 0.4, 1.05);
  f_wheel_2 = new Cylinder(1.1, 0.4, -1.05);
  r_wheel_1 = new Cylinder(-1.1, 0.8, 1.05);
  r_wheel_2 = new Cylinder(-1.1, 0.8, -1.05);
  chassis = new RectangularPrism(0, 0, 0.4);
  //Create wheel sizes
  f_wheel_1->set_radius(0.4);
  f_wheel_1->set_y_length(0.1);
  f_wheel_2->set_radius(0.4);
  f_wheel_2->set_y_length(0.1);
  r_wheel_1->set_radius(0.8);
  r_wheel_1->set_y_length(0.1);
  r_wheel_2->set_radius(0.8);
  r_wheel_2->set_y_length(0.1);
  //Set chassis sizes
  chassis->set_x_length(3.0);
  chassis->set_y_length(1.0);
  chassis->set_z_length(2.0);
  glPopMatrix();
  
};
*/
void MyVehicle::draw(){

  glPushMatrix();
  positionInGL();

  for(int i = 0; i < shapes.size(); i++){
         shapes[i]->draw();
  }

  glPopMatrix();

  
};

MyVehicle::~MyVehicle(){

};
