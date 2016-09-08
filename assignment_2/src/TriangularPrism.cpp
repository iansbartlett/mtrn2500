#include "TriangularPrism.hpp"
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

TriangularPrism::TriangularPrism(): Shape(){
  x_length = side = z_length = 1;
  angle = M_PI/3;
};

TriangularPrism::TriangularPrism(double x_, double y_, double z_): Shape(x_, y_, z_){
  x_length = side = z_length = 1;
  angle = M_PI/3;
};

TriangularPrism::TriangularPrism(double x_, double y_, double z_, double rotation_):
  Shape(x_, y_, z_, rotation_){
  x_length = side = z_length = 1;
  angle = M_PI/3;
};

void TriangularPrism::draw(){

  //TODO: Error handling for illegal angles
  
  double top_y = side*sin(angle);
  double top_x = side*cos(angle);

  glPushMatrix();
  glRotated(rotation,0,1,0);
  glTranslated(-x_length/2,0,-z_length/2);
  glColor3f(red, green, blue);
  glBegin(GL_TRIANGLES);

  //Front face 
  glVertex3f(0, 0, 0);
  glVertex3f(top_x, top_y, 0);
  glVertex3f(x_length, 0, 0);

  //Back face 
  glVertex3f(0, 0, z_length);
  glVertex3f(top_x, top_y, z_length);
  glVertex3f(x_length, 0, z_length);

  glEnd();

  glBegin(GL_QUADS);

  //Base 
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, z_length);
  glVertex3f(x_length, 0, z_length);
  glVertex3f(x_length, 0, 0);

  //Angle Side 
  glVertex3f(0, 0, 0);
  glVertex3f(top_x, top_y, 0);
  glVertex3f(top_x, top_y, z_length);
  glVertex3f(0, 0, z_length);

  //Opposite Side
  glVertex3f(x_length, 0, 0);
  glVertex3f(top_x, top_y, 0);
  glVertex3f(top_x, top_y, z_length);
  glVertex3f(x_length, 0, z_length);

  glEnd();

  glPopMatrix();
  
};

double TriangularPrism::get_x_length(){
  return x_length; 
};

double TriangularPrism::get_angle(){
  return angle; 
};

double TriangularPrism::get_side(){
  return side; 
};

double TriangularPrism::get_z_length(){
  return z_length; 
};

void TriangularPrism::set_angle(double new_angle){
  angle = new_angle;
};

void TriangularPrism::set_side(double new_side){
  side = new_side;
};

void TriangularPrism::set_x_length(double new_x_length){
  x_length = new_x_length;
};

void TriangularPrism::set_z_length(double new_z_length){
  z_length = new_z_length;
};

TriangularPrism::~TriangularPrism(){

};
