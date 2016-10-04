
#include "TrapezoidalPrism.hpp"
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

TrapezoidalPrism::TrapezoidalPrism(): Shape(){
  top_x_length = y_length = z_length = 1;
  bottom_x_length = 2;
  offset = 0.5;
};

TrapezoidalPrism::TrapezoidalPrism(double x_, double y_, double z_): Shape(x_, y_, z_){
  top_x_length = y_length = z_length = 1;
  bottom_x_length = 2;
  offset = 0.5;
};

TrapezoidalPrism::TrapezoidalPrism(double x_, double y_, double z_, double rotation_):
  Shape(x_, y_, z_, rotation_){
  top_x_length = y_length = z_length = 1;
  bottom_x_length = 2;
  offset = 0.5;
};
void TrapezoidalPrism::draw(){
  
  glPushMatrix();
  glRotated(rotation,0,1,0);
  glTranslated(x-bottom_x_length/2,y,z-z_length/2);
  glColor3f(red, green, blue);
  glBegin(GL_QUADS);

  //Front face 
  glVertex3f(0, 0, 0);
  glVertex3f(offset, y_length, 0);
  glVertex3f(top_x_length+offset, y_length, 0);
  glVertex3f(bottom_x_length, 0, 0);
  //Back face 
  glVertex3f(0, 0, z_length);
  glVertex3f(offset, y_length, z_length);
  glVertex3f(top_x_length+offset, y_length, z_length);
  glVertex3f(bottom_x_length, 0, z_length);
  //Top face 
  glVertex3f(offset, y_length, 0);
  glVertex3f(top_x_length+offset, y_length, 0);
  glVertex3f(top_x_length+offset, y_length, z_length);
  glVertex3f(offset, y_length, z_length);
  //Bottom face 
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, z_length);
  glVertex3f(bottom_x_length, 0, z_length);
  glVertex3f(bottom_x_length, 0, 0);
  //Left face 
  glVertex3f(0, 0, 0);
  glVertex3f(offset, y_length, 0);
  glVertex3f(offset, y_length, z_length);
  glVertex3f(0, 0, z_length);
  //Right face 
  glVertex3f(bottom_x_length, 0, 0);
  glVertex3f(bottom_x_length, 0, z_length);
  glVertex3f(top_x_length+offset, y_length, z_length);
  glVertex3f(top_x_length+offset, y_length, 0);

  glEnd();

  glPopMatrix();
  
};

double TrapezoidalPrism::get_bottom_x_length(){
  return bottom_x_length; 
};

double TrapezoidalPrism::get_top_x_length(){
  return top_x_length; 
};
double TrapezoidalPrism::get_y_length(){
  return y_length; 
};

double TrapezoidalPrism::get_z_length(){
  return z_length; 
};

double TrapezoidalPrism::get_offset(){
  return offset; 
};

void TrapezoidalPrism::set_bottom_x_length(double new_bottom_x_length){
  bottom_x_length = new_bottom_x_length;
};

void TrapezoidalPrism::set_top_x_length(double new_top_x_length){
  top_x_length = new_top_x_length;
};

void TrapezoidalPrism::set_y_length(double new_y_length){
  y_length = new_y_length;
};

void TrapezoidalPrism::set_z_length(double new_z_length){
  z_length = new_z_length;
};

void TrapezoidalPrism::set_offset(double new_offset){
  offset = new_offset;
};

TrapezoidalPrism::~TrapezoidalPrism(){

};
