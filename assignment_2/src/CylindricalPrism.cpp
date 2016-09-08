
#include "CylindricalPrism.hpp"
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

CylindricalPrism::CylindricalPrism(): Shape(){
  y_length = 1;
  radius = 1;
  slices = 10;
};

CylindricalPrism::CylindricalPrism(double x_, double y_, double z_): Shape(x_, y_, z_){
  y_length = 1;
  radius = 1;
  slices = 10;
};

CylindricalPrism::CylindricalPrism(double x_, double y_, double z_, double rotation_):
  Shape(x_, y_, z_, rotation_){
  y_length = 1;
  radius = 1;
  slices = 100;
};
void CylindricalPrism::draw(){

  double groundOffset = y_length/2;
  
  glPushMatrix();
  glTranslated(x,y+groundOffset,z);
  //glRotated(rotation,0,1,0);

  for(int i=0; i<slices; i++){
  double theta = ((float)i)*2.0*M_PI/slices;
  double nextTheta = ((float)i+1)*2.0*M_PI/slices;
  glBegin(GL_TRIANGLE_STRIP);
  /*vertex at middle of end */
  glVertex3f(0.0, 0, 0.0);
  /*vertices at edges of circle*/
  glVertex3f(radius*cos(theta), 0, radius*sin(theta));
  glVertex3f(radius*cos(nextTheta), 0, radius*sin(nextTheta));
  /* the same vertices at the bottom of the cylinder*/
  glVertex3f(radius*cos(nextTheta), y_length, radius*sin(nextTheta));
  glVertex3f(radius*cos(theta), y_length, radius*sin(theta));
  glVertex3f(0.0, y_length, 0.0);
  glEnd();
 }

  glPopMatrix();
  
};

double CylindricalPrism::get_radius(){
  return radius; 
};
double CylindricalPrism::get_y_length(){
  return y_length; 
};


void CylindricalPrism::set_radius(double new_radius){
  radius = new_radius;
};

void CylindricalPrism::set_y_length(double new_y_length){
  y_length = new_y_length;
};

CylindricalPrism::~CylindricalPrism(){

};
