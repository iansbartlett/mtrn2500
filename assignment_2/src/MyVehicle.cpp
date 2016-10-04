#include "MyVehicle.hpp"
#include "Wheel.hpp"
#include "RectangularPrism.hpp"
#include "TriangularPrism.hpp"
#include "Shape.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

MyVehicle::MyVehicle() : Vehicle() {
  glPushMatrix(); 
  glRotated(-90,0,1,0);
  //Create basic structures
  //Assessment code goes here
  addShape(new RectangularPrism(0, 0.57,0));
  dynamic_cast<RectangularPrism*>(shapes[0])->set_x_length(1.28);
  dynamic_cast<RectangularPrism*>(shapes[0])->set_y_length(0.09);
  dynamic_cast<RectangularPrism*>(shapes[0])->set_z_length(3.84);
  shapes[0]->setColor(1.0,0.82,0.51);
  
  addShape(new RectangularPrism(0, (0.57+0.09), ((-3.84/2)+0.14+(1.18/2))));
  dynamic_cast<RectangularPrism*>(shapes[1])->set_x_length(1.18);
  dynamic_cast<RectangularPrism*>(shapes[1])->set_y_length(0.65);
  dynamic_cast<RectangularPrism*>(shapes[1])->set_z_length(1.01);
  shapes[1]->setColor(1.0,0.1,0.0);

  addShape(new Cylinder(((1.28/2)+0.16), 0, -1.34));
  dynamic_cast<Cylinder*>(shapes[2])->set_isRolling(true);
  dynamic_cast<Cylinder*>(shapes[2])->set_radius(0.78/2);
  dynamic_cast<Cylinder*>(shapes[2])->set_y_length(0.22);
  dynamic_cast<Cylinder*>(shapes[2])->setRotation(90);
  shapes[2]->setColor(0.0,0.0,0.0);

  addShape(new Cylinder(-((1.28/2)+0.16), 0, -1.34));
  dynamic_cast<Cylinder*>(shapes[3])->set_isRolling(true);
  dynamic_cast<Cylinder*>(shapes[3])->set_radius(0.78/2);
  dynamic_cast<Cylinder*>(shapes[3])->set_y_length(0.22);
  dynamic_cast<Cylinder*>(shapes[3])->setRotation(90);
  shapes[3]->setColor(0.0,0.0,0.0);

  addShape(new Cylinder(((1.28/2)+0.16+0.23), (0.78-0.35)/2, -1.34));
  dynamic_cast<Cylinder*>(shapes[4])->set_isRolling(true);
  dynamic_cast<Cylinder*>(shapes[4])->set_radius(0.35/2);
  dynamic_cast<Cylinder*>(shapes[4])->set_y_length(0.06);
  dynamic_cast<Cylinder*>(shapes[4])->setRotation(90);
  shapes[4]->setColor(1.0,1.0,0.0);

  addShape(new Cylinder(-((1.28/2)+0.16+0.23), (0.78-0.35)/2, -1.34));
  dynamic_cast<Cylinder*>(shapes[5])->set_isRolling(true);
  dynamic_cast<Cylinder*>(shapes[5])->set_radius(0.35/2);
  dynamic_cast<Cylinder*>(shapes[5])->set_y_length(0.06);
  dynamic_cast<Cylinder*>(shapes[5])->setRotation(90);
  shapes[5]->setColor(1.0,1.0,0.0);

  addShape(new TriangularPrism(0, 0.57, -(3.84/2-0.17)));
  dynamic_cast<TriangularPrism*>(shapes[6])->setRotation(90);
  dynamic_cast<TriangularPrism*>(shapes[6])->set_angle(-atan(0.57/0.17));

  ///////////////////////
  /*
  addShape(new Cylinder(1.1, 0.4, 1.05));
  addShape(new Cylinder(1.1, 0.4, -1.05));
  addShape(new Cylinder(-1.1, 0.4, 1.05));
  addShape(new Cylinder(-1.1, 0.4, -1.05));
  addShape(new RectangularPrism(0, 0.8, 0));
  dynamic_cast<Cylinder*>(shapes[1])->setRotation(0);
  dynamic_cast<Cylinder*>(shapes[0])->set_isSteering(true);
  dynamic_cast<Cylinder*>(shapes[1])->set_isSteering(true);
  dynamic_cast<Cylinder*>(shapes[0])->set_isRolling(true);
  dynamic_cast<Cylinder*>(shapes[1])->set_isRolling(true);
  dynamic_cast<Cylinder*>(shapes[2])->set_isRolling(true);
  dynamic_cast<Cylinder*>(shapes[3])->set_isRolling(true);
  dynamic_cast<Cylinder*>(shapes[3])->setRotation(180);
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

  */
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

MyVehicle::MyVehicle(bool defaultVehicle) : Vehicle() {
  wheel_angle = 0;
};

void MyVehicle::draw(){

  glPushMatrix();
  positionInGL();

    //for(int i = 0; i < 4; i++){
    //dynamic_cast<Wheel*>(shapes[i])->set_wheel_rotation(-wheel_angle);
    //}
  //shapes[0]->setRotation(-getSteering());
  //shapes[1]->setRotation(-getSteering()+180);
  for(int i = 0; i < shapes.size(); i++){
    if(dynamic_cast<Cylinder*>(shapes[i])){
     dynamic_cast<Cylinder*>(shapes[i])->set_wheel_rotation(-speed/dynamic_cast<Cylinder*>(shapes[i])->get_radius()+dynamic_cast<Cylinder*>(shapes[i])->get_wheel_rotation());
     dynamic_cast<Cylinder*>(shapes[i])->set_steering_angle((double)getSteering());
     }
      shapes[i]->draw();
  }

  glPopMatrix();

  
};

void MyVehicle::clearShapes(){
  shapes.clear();
}

std::vector<Shape *> MyVehicle::returnShapes(){
  return shapes;
}

MyVehicle::~MyVehicle(){

};
