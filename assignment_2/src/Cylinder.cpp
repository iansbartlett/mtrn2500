
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

Cylinder::Cylinder(): Shape(){
  y_length = 1;
  radius = 1;
  slices = DEFAULT_SLICES;
};

Cylinder::Cylinder(double x_, double y_, double z_): Shape(x_, y_, z_){
  y_length = 1;
  radius = 1;
  slices = DEFAULT_SLICES; 
};

Cylinder::Cylinder(double x_, double y_, double z_, double rotation_):
  Shape(x_, y_, z_, rotation_){
  y_length = 1;
  radius = 1;
  slices = DEFAULT_SLICES;
};
void Cylinder::draw(){

  double groundOffset = y_length/2;
  
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(-90, 1, 0, 0);
  glTranslated(0,0,radius);
  glRotated(rotation,0,1,0);

  glColor3f(red, green, blue);
  
  for(int i=0; i<slices; i++){
     double theta = ((float)i)*2.0*M_PI/slices;
     double nextTheta = ((float)i+1)*2.0*M_PI/slices;
     glBegin(GL_TRIANGLE_STRIP);
     glVertex3f(0.0, y_length/2, 0.0);
     glVertex3f(radius*cos(nextTheta), y_length/2, radius*sin(nextTheta));
     glVertex3f(radius*cos(theta), y_length/2, radius*sin(theta));
     glVertex3f(radius*cos(nextTheta), -y_length/2, radius*sin(nextTheta));
     glVertex3f(radius*cos(theta), -y_length/2, radius*sin(theta));
     glVertex3f(0.0, -y_length/2, 0.0);
     glEnd();
 }

  glPopMatrix();
  
};

double Cylinder::get_radius(){
  return radius; 
};
double Cylinder::get_y_length(){
  return y_length; 
};


void Cylinder::set_radius(double new_radius){
  radius = new_radius;
};

void Cylinder::set_y_length(double new_y_length){
  y_length = new_y_length;
};

Cylinder::~Cylinder(){

};
