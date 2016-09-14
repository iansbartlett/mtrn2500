#include "MyVehicle.hpp"
#include "Wheel.hpp"
#include "RectangularPrism.hpp"
#include "Shape.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

MyVehicle::MyVehicle() : Vehicle() {
  glPushMatrix(); 
  //Create basic structures
  addShape(new Wheel(1.1, 0.4, 1.05));
  addShape(new Wheel(1.1, 0.4, -1.05));
  addShape(new Wheel(-1.1, 0.4, 1.05));
  addShape(new Wheel(-1.1, 0.4, -1.05));
  addShape(new RectangularPrism(0, 0.8, 0));
  dynamic_cast<Wheel*>(shapes[1])->setRotation(90);
  dynamic_cast<Wheel*>(shapes[3])->setRotation(180);
  /*
  dynamic_cast<Cylinder*>(shapes[0])->set_radius(0.4);
  dynamic_cast<Cylinder*>(shapes[0])->set_y_length(0.1);
  dynamic_cast<Cylinder*>(shapes[1])->set_radius(0.4);
  dynamic_cast<Cylinder*>(shapes[1])->set_y_length(0.1);
  dynamic_cast<Cylinder*>(shapes[2])->set_radius(0.8);
  dynamic_cast<Cylinder*>(shapes[2])->set_y_length(0.1);
  dynamic_cast<Cylinder*>(shapes[3])->set_radius(0.8);
  dynamic_cast<Cylinder*>(shapes[3])->set_y_length(0.1);
  */
  //Set chassis sizes
  dynamic_cast<RectangularPrism*>(shapes[4])->set_x_length(3.0);
  dynamic_cast<RectangularPrism*>(shapes[4])->set_y_length(1.0);
  dynamic_cast<RectangularPrism*>(shapes[4])->set_z_length(2.0);

  shapes[0]->setColor(0,0,1);
  shapes[1]->setColor(0,0,1);
  shapes[2]->setColor(0,0,1);
  shapes[3]->setColor(0,0,1);

  wheel_angle = 0;
  
  glPopMatrix();
 
};

/*
MyVehicle::MyVehicle(vehicleShapes) : Vehicle() {
  
  glPushMatrix(); 

  for(int i = 0; i < vehicleShapes.size(); i++){
    //Add generic vehicle code
  }

  glPopMatrix();
 
};
*/

void MyVehicle::draw(){

  double wheel_angular_v; 

  glPushMatrix();
  positionInGL();

  for(int i = 0; i < 4; i++){
       dynamic_cast<Wheel*>(shapes[i])->set_wheel_rotation(-wheel_angle);
    }
  shapes[0]->setRotation(-getSteering());
  shapes[1]->setRotation(-getSteering()+180);
  for(int i = 0; i < shapes.size(); i++){
      shapes[i]->draw();
  }

  glPopMatrix();

  
};

MyVehicle::~MyVehicle(){

};
