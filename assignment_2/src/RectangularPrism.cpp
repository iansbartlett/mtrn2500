
#include "RectangularPrism.hpp"
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

RectangularPrism::RectangularPrism(): Shape(){
  x_length = y_length = z_length = 1;
};

RectangularPrism::RectangularPrism(double x_, double y_, double z_): Shape(x_, y_, z_){
  x_length = y_length = z_length = 1;
};

RectangularPrism::RectangularPrism(double x_, double y_, double z_, double rotation_):
  Shape(x_, y_, z_, rotation_){
  x_length = y_length = z_length = 1;
};
void RectangularPrism::draw(){

  double groundOffset = y_length/2;
  
  glPushMatrix();
  glRotated(rotation,0,1,0);
  glTranslated(x,y+groundOffset,z);
  glScaled(x_length/2,y_length/2,z_length/2);

  glColor3f(red, green, blue);

  glBegin(GL_QUADS);

  //Front face 
  glVertex3f(1, 1, 1);
  glVertex3f(1, 1, -1);
  glVertex3f(-1, 1, -1);
  glVertex3f(-1, 1, 1);
  //Back face 
  glVertex3f(1, -1, 1);
  glVertex3f(1, -1, -1);
  glVertex3f(-1, -1, -1);
  glVertex3f(-1, -1, 1);
  //Top face 
  glVertex3f(1, 1, 1);
  glVertex3f(1, 1, -1);
  glVertex3f(1, -1, -1);
  glVertex3f(1, -1, 1);
  //Bottom face 
  glVertex3f(-1, 1, 1);
  glVertex3f(-1, 1, -1);
  glVertex3f(-1, -1, -1);
  glVertex3f(-1, -1, 1);
  //Left face 
  glVertex3f(1, 1, 1);
  glVertex3f(1, -1, 1);
  glVertex3f(-1, -1, 1);
  glVertex3f(-1, 1, 1);
  //Right face 
  glVertex3f(1, 1, -1);
  glVertex3f(1, -1, -1);
  glVertex3f(-1, -1, -1);
  glVertex3f(-1, 1, -1);

  glEnd();

  glPopMatrix();
  
};

double RectangularPrism::get_x_length(){
  return x_length; 
};
double RectangularPrism::get_y_length(){
  return y_length; 
};

double RectangularPrism::get_z_length(){
  return z_length; 
};

void RectangularPrism::set_x_length(double new_x_length){
  x_length = new_x_length;
};

void RectangularPrism::set_y_length(double new_y_length){
  y_length = new_y_length;
};

void RectangularPrism::set_z_length(double new_z_length){
  z_length = new_z_length;
};

RectangularPrism::~RectangularPrism(){

};
