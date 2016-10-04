
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#elif defined(WIN32)
	#include <Windows.h>
	#include <tchar.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
	#include <unistd.h>
	#include <sys/time.h>
#endif


#include "Camera.hpp"
#include "Ground.hpp"
#include "KeyManager.hpp"

#include "Shape.hpp"
#include "Vehicle.hpp"

//My includes
#include "RectangularPrism.hpp"
#include "TriangularPrism.hpp"
#include "TrapezoidalPrism.hpp"
#include "Cylinder.hpp"
#include "MyVehicle.hpp"

#include "RemoteDataManager.hpp"
#include "Messages.hpp"
#include "HUD.hpp"
#include "ObstacleManager.hpp"

void display();
void reshape(int width, int height);
void idle();

void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void special_keydown(int keycode, int x, int y);
void special_keyup(int keycode, int x, int y);

void mouse(int button, int state, int x, int y);
void dragged(int x, int y);
void motion(int x, int y);

bool autopilot_on = false;

using namespace std;
using namespace scos;

// Used to store the previous mouse location so we
//   can calculate relative mouse movement.
int prev_mouse_x = -1;
int prev_mouse_y = -1;

// vehicle control related variables
Vehicle * vehicle = NULL;
double speed = 0;
double steering = 0;

//Testing HAX
RectangularPrism * testBox = NULL;
TrapezoidalPrism * testTrapezoid = NULL;
TriangularPrism * testTriangle = NULL;
Cylinder * testCylinder = NULL;


TriangularPrism * tempTri;
Cylinder * tempCyl;
TrapezoidalPrism * tempTrap;
RectangularPrism * tempRect;

// default goal location
std::deque<GoalState> goals;

std::map<int, Vehicle *> otherVehicles;

int frameCounter = 0;

//int _tmain(int argc, _TCHAR* argv[]) {
int main(int argc, char ** argv) {

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	glutInit(&argc, (char**)(argv));
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("MTRN3500 - GL");

	Camera::get()->setWindowDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutSpecialFunc(special_keydown);
	glutSpecialUpFunc(special_keyup);

	glutMouseFunc(mouse);
	glutMotionFunc(dragged);
	glutPassiveMotionFunc(motion);

	// -------------------------------------------------------------------------
	// Please uncomment the following line of code and replace 'MyVehicle'
	//   with the name of the class you want to show as the current 
	//   custom vehicle.
	// -------------------------------------------------------------------------

	vehicle = new MyVehicle();
	// add test obstacles
	ObstacleManager::get()->addObstacle(Obstacle(10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(10,-10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,-10, 1));

        // Test rectangularPrism
        //RectangularPrism testBox();
        testBox = new RectangularPrism(10.0, 10.0, 10.0, 45);
	testBox->setColor(0,0,1);
	testBox->set_x_length(5.0);
        testTrapezoid = new TrapezoidalPrism(0.0, 1.0, 3.0, 120);
	testTrapezoid->setColor(0,1,0);
	testBox->set_x_length(5.0);
        testTriangle = new TriangularPrism(-1.0, 3.0, -2.0, 0);
	testTriangle->setColor(1,0,0);
	testBox->set_y_length(2.0);
        testCylinder = new Cylinder(-2.0, 4.0, 2.0, -45);
	testCylinder->setColor(1,1,0);
	testCylinder->set_radius(4.0);
	
	// add test goal
	GoalState g;
	g.x = 25;
	g.z = 0;
	goals.push_back(g);

	glutMainLoop();

	if (vehicle != NULL) {
		delete vehicle;
	}

	return 0;
}

void drawGoals()
{

	for (int i = 0; i < goals.size(); ++i) {

		GoalState goal = goals[i];

		glPushMatrix();
		glTranslatef(goal.x, 0, goal.z);
		glRotated(90, -1, 0, 0);
		static GLUquadric * quad = gluNewQuadric();

		// make first goal purple
		if (i == 0)
			glColor3f(1, .3, 1);
		else
			glColor3f(1, 1, 1);

		gluCylinder(quad, .5, .5, 10, 5, 1);
		glPopMatrix();
	}
}

void display() {
	frameCounter++;
	// -------------------------------------------------------------------------
	//  This method is the main draw routine. 
	// -------------------------------------------------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(Camera::get()->isPursuitMode() && vehicle != NULL) {
		double x = vehicle->getX(), y = vehicle->getY(), z = vehicle->getZ();
		double dx = cos(vehicle->getRotation() * 3.141592765 / 180.0);
		double dy = sin(vehicle->getRotation() * 3.141592765 / 180.0);
		Camera::get()->setDestPos(x + (-20 * dx), y + 15, z + (-20 * dy));
		Camera::get()->setDestDir(dx, -0.25, dy);
	}
	Camera::get()->updateLocation();
	Camera::get()->setLookAt();

	Ground::draw();
	
	// draw other vehicles
	for(std::map<int, Vehicle *>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) 
		iter->second->draw();

	// draw my vehicle
	if (vehicle != NULL) {
		vehicle->draw();

	}
        
	// draw obstacles
	ObstacleManager::get()->drawAll();

	// draw goals
	drawGoals();
	
	// draw HUD
	HUD::Draw();

	glutSwapBuffers();
};

void reshape(int width, int height) {

	Camera::get()->setWindowDimensions(width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};

void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_)
{
	// filter 
	const double kSmoothingFactor = 0.5;
	vehicle->setX(vehicle->getX() * kSmoothingFactor + x * (1 - kSmoothingFactor));
	vehicle->setZ(vehicle->getZ() * kSmoothingFactor + z * (1 - kSmoothingFactor));

	vehicle->setRotation(r);
	vehicle->steering = steering_;
	vehicle->speed = speed_;
}

double getTime()
{
#if defined(WIN32)
	LARGE_INTEGER freqli;
	LARGE_INTEGER li;
	if(QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
		return double(li.QuadPart) / double(freqli.QuadPart);
	}
	else {
		static ULONGLONG start = GetTickCount64();
		return (GetTickCount64() - start) / 1000.0;
	}
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}

void idle() {

	if (KeyManager::get()->isAsciiKeyPressed('a')) {
		Camera::get()->strafeLeft();
	}

	if (KeyManager::get()->isAsciiKeyPressed('c')) {
		Camera::get()->strafeDown();
	}

	if (KeyManager::get()->isAsciiKeyPressed('d')) {
		Camera::get()->strafeRight();
	}

	if (KeyManager::get()->isAsciiKeyPressed('s')) {
		Camera::get()->moveBackward();
	}

	if (KeyManager::get()->isAsciiKeyPressed('w')) {
		Camera::get()->moveForward();
	}

	if (KeyManager::get()->isAsciiKeyPressed(' ')) {
		Camera::get()->strafeUp();
	}

	speed = 0;
	steering = 0;
	if(autopilot_on){
	    update(vehicle);
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * -1;   
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_UP)) {
		speed = Vehicle::MAX_FORWARD_SPEED_MPS;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_DOWN)) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
	}

	// attempt to do data communications every 4 frames if we've created a local vehicle
	if(frameCounter % 4 == 0 && vehicle != NULL) {

		// if not connected, attempt to connect every 2 seconds
		if(!RemoteDataManager::IsConnected()) {
			if(frameCounter % 120 == 0) {
		
				// erase other vehicles
				for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
					delete iter->second;
				}
				otherVehicles.clear();

				// uncomment this line to connect to the robotics server.
				RemoteDataManager::Connect("www.robotics.unsw.edu.au","18081");

				// on connect, let's tell the server what we look like
				if (RemoteDataManager::IsConnected()) {
					ObstacleManager::get()->removeAll();

					VehicleModel vm;
					vm.remoteID = 0;

					//
					// student code goes here
					//
					
					std::vector<Shape *> shapesList = dynamic_cast<MyVehicle*>(vehicle)->returnShapes();
					for(int i = 0; i < shapesList.size(); i++){
					  ShapeInit temp = {};
				          temp.rgb[0] = shapesList[i]->getRed(); 
				          temp.rgb[1] = shapesList[i]->getGreen(); 
				          temp.rgb[2] = shapesList[i]->getBlue(); 
				          temp.xyz[0] = shapesList[i]->getX(); 
				          temp.xyz[1] = shapesList[i]->getY(); 
				          temp.xyz[2] = shapesList[i]->getZ(); 

					  if(dynamic_cast<RectangularPrism*>(shapesList[i])){
					    temp.type = RECTANGULAR_PRISM;
					    temp.params.rect.xlen = (float)dynamic_cast<RectangularPrism*>(shapesList[i])->get_x_length();
					    temp.params.rect.ylen = (float)dynamic_cast<RectangularPrism*>(shapesList[i])->get_y_length();
					    temp.params.rect.zlen = (float)dynamic_cast<RectangularPrism*>(shapesList[i])->get_z_length();
					    vm.shapes.push_back(temp);
					  }else if(dynamic_cast<TriangularPrism*>(shapesList[i])){
					    temp.type = TRIANGULAR_PRISM;
					    temp.params.tri.alen = (float)dynamic_cast<TriangularPrism*>(shapesList[i])->get_x_length();
					    temp.params.tri.blen = (float)dynamic_cast<TriangularPrism*>(shapesList[i])->get_side();
					    temp.params.tri.depth = (float)dynamic_cast<TriangularPrism*>(shapesList[i])->get_z_length();
					    temp.params.tri.angle = (float)dynamic_cast<TriangularPrism*>(shapesList[i])->get_angle()*180/M_PI;
					    vm.shapes.push_back(temp);
					  }else if(dynamic_cast<TrapezoidalPrism*>(shapesList[i])){
					    temp.type = TRAPEZOIDAL_PRISM;
					    temp.params.trap.alen = (float)dynamic_cast<TrapezoidalPrism*>(shapesList[i])->get_bottom_x_length();
					    temp.params.trap.blen = (float)dynamic_cast<TrapezoidalPrism*>(shapesList[i])->get_top_x_length();
					    temp.params.trap.height = (float)dynamic_cast<TrapezoidalPrism*>(shapesList[i])->get_y_length();
					    temp.params.trap.aoff = (float)dynamic_cast<TrapezoidalPrism*>(shapesList[i])->get_offset();
					    temp.params.trap.depth = (float)dynamic_cast<TrapezoidalPrism*>(shapesList[i])->get_z_length();
					    vm.shapes.push_back(temp);
					  }else if(dynamic_cast<Cylinder*>(shapesList[i])){
					    temp.type = CYLINDER;
					    temp.params.cyl.depth = (float)dynamic_cast<Cylinder*>(shapesList[i])->get_y_length();
					    temp.params.cyl.radius = (float)dynamic_cast<Cylinder*>(shapesList[i])->get_radius();
					    temp.params.cyl.isRolling = dynamic_cast<Cylinder*>(shapesList[i])->get_isRolling();
					    temp.params.cyl.isSteering = dynamic_cast<Cylinder*>(shapesList[i])->get_isSteering();
					    vm.shapes.push_back(temp);
					  }

					}

					RemoteDataManager::Write(GetVehicleModelStr(vm));
				}
			}
		}

		// if we're connected, send our vehicle state to the server
		if (RemoteDataManager::IsConnected()) {
			VehicleState vs;
			vs.remoteID = 0;
			vs.x = vehicle->getX();
			vs.z = vehicle->getZ();
			vs.rotation = vehicle->getRotation();
			vs.speed = vehicle->getSpeed();
			vs.steering = vehicle->getSteering();
			RemoteDataManager::Write(GetVehicleStateStr(vs));
		}

		// if we're still connected, receive and handle response messages from the server
		if (RemoteDataManager::IsConnected()) {
			std::vector<RemoteMessage> msgs = RemoteDataManager::Read();
			for(unsigned int i = 0; i < msgs.size(); i++ ) {

				RemoteMessage msg = msgs[i];
				//cout << msg.payload << endl;

				switch(msg.type) {
					// new models
					case 'M':
						{
						  //cout << "Attempting to fetch models..." << endl;
							std::vector<VehicleModel> models = GetVehicleModels(msg.payload);
							for(unsigned int i = 0; i < models.size(); i++) {
							  //cout << "Beginning model sweep " << i << endl;
							  //cout << "Models should go up to " << models.size()-1 << endl;
								VehicleModel vm = models[i];
								//cout << "Model remote ID: " << vm.remoteID << endl;
								otherVehicles[vm.remoteID] = new MyVehicle(false);

								for (int j = 0; j < vm.shapes.size(); j++){

								  //cout << "Iterating over shapes, iteration " << j << endl;
							          //cout << "Shapes should go up to  " << vm.shapes.size()-1 << endl;
								  double x = (double)vm.shapes[j].xyz[0];
								  double y = (double)vm.shapes[j].xyz[1];
								  double z = (double)vm.shapes[j].xyz[2];
								  double rotation = (double)vm.shapes[j].rotation;
								  double red = (double)vm.shapes[j].rgb[0];
								  double blue = (double)vm.shapes[j].rgb[1];
								  double green = (double)vm.shapes[j].rgb[2];

								  switch(vm.shapes[j].type){
								  case RECTANGULAR_PRISM:
								    tempRect = new RectangularPrism(x,y,z,rotation);
								    tempRect->set_x_length(vm.shapes[j].params.rect.xlen);
								    tempRect->set_y_length(vm.shapes[j].params.rect.ylen);
								    tempRect->set_z_length(vm.shapes[j].params.rect.zlen);
								    tempRect->setColor(red, blue, green);
								    otherVehicles[vm.remoteID]->addShape(tempRect);
								    break;
								  case TRIANGULAR_PRISM:
								    tempTri = new TriangularPrism(x,y,z,rotation);
								    tempTri->set_x_length(vm.shapes[j].params.tri.alen);
								    tempTri->set_side(vm.shapes[j].params.tri.blen);
								    tempTri->set_angle(vm.shapes[j].params.tri.angle*M_PI/180);
								    tempTri->set_z_length(vm.shapes[j].params.tri.depth);
								    tempTri->setColor(red, blue, green);
								    otherVehicles[vm.remoteID]->addShape(tempTri);
								    break;
								  case TRAPEZOIDAL_PRISM:
								    tempTrap = new TrapezoidalPrism(x,y,z,rotation);
								    tempTrap->set_bottom_x_length(vm.shapes[j].params.trap.alen);
								    tempTrap->set_top_x_length(vm.shapes[j].params.trap.blen);
								    tempTrap->set_y_length(vm.shapes[j].params.trap.height);
								    tempTrap->set_offset(vm.shapes[j].params.trap.aoff);
								    tempTrap->set_z_length(vm.shapes[j].params.trap.depth);
								    tempTrap->setColor(red, blue, green);
								    otherVehicles[vm.remoteID]->addShape(tempTrap);
								    break;
								  case CYLINDER:
								    tempCyl = new Cylinder(x,y,z,rotation);
								    tempCyl->set_radius(vm.shapes[j].params.cyl.radius);
								    tempCyl->set_y_length(vm.shapes[j].params.cyl.depth);
								    tempCyl->set_isSteering(vm.shapes[j].params.cyl.isSteering);
								    tempCyl->set_isRolling(vm.shapes[j].params.cyl.isRolling);
								    tempCyl->setColor(red, blue, green);
								    otherVehicles[vm.remoteID]->addShape(tempCyl);
								    break;
								  default:
								    //cout << "Switch statement error!" << endl;
								    tempRect = new RectangularPrism(0,0,0);
								    //tempRect->set_x_length(vm.shapes[j].params.rect.xlen);
								    //tempRect->set_y_length(vm.shapes[j].params.rect.ylen);
								    //tempRect->set_z_length(vm.shapes[j].params.rect.zlen);
								    tempRect->setColor(1, 1, 1);
								    otherVehicles[vm.remoteID]->addShape(tempRect);
								    }
								  //cout << "Exited switch successfully" << endl;
								}
								//cout << "ended model sweep" << endl;
							}
							break;
						}

					// vehicle states
					case 'S': 
						{
							std::vector<VehicleState> states = GetVehicleStates(msg.payload);
							for(unsigned int i = 0; i < states.size(); i++) {
								VehicleState vs = states[i];

								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(vs.remoteID);
								if(iter != otherVehicles.end()) {
									Vehicle * veh = iter->second;
									remoteDriver(veh, vs.x, vs.z, vs.rotation, vs.speed, vs.steering);
								}
							}
							break;
						}

					// goal state
					case 'G':
						{
							goals = GetGoals(msg.payload);
							break;
						}

					// obstacle state
					case 'O':
						{
							std::vector<ObstacleState> obs = GetObstacles(msg.payload);
							for(unsigned int i = 0; i < obs.size(); i++) {
								Obstacle o(obs[i].x, obs[i].z, obs[i].radius);
								ObstacleManager::get()->addObstacle(o);
							}
							break;
						}

					// disconnectlist
					case 'D':
						{
							std::vector<int> disconnectedIDs = GetVehicleDisconnects(msg.payload);
							for(unsigned int i = 0; i < disconnectedIDs.size(); i++) {
								int id = disconnectedIDs[i];
								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(id);
								if(iter != otherVehicles.end()) {
									delete iter->second;
									otherVehicles.erase(iter);
								}
							}
							break;
						}

					// error message
					case 'E':
						{
							cerr << "Server error: " << msg.payload << endl;
							break;
						}

				}
			} 
		}
	}


	const float sleep_time_between_frames_in_seconds = 0.025;

	static double previousTime = getTime();
	const double currTime = getTime();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;

	// do a simulation step
	if (vehicle != NULL) {
		vehicle->update(speed, steering, elapsedTime);
	}
	for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
		iter->second->update(elapsedTime);
	}

	display();

#ifdef _WIN32 
	Sleep(sleep_time_between_frames_in_seconds * 1000);
#else
	usleep(sleep_time_between_frames_in_seconds * 1e6);
#endif
};

void keydown(unsigned char key, int x, int y) {

	// keys that will be held down for extended periods of time will be handled
	//   in the idle function
	KeyManager::get()->asciiKeyPressed(key);

	// keys that react ocne when pressed rather than need to be held down
	//   can be handles normally, like this...
	switch (key) {
	case 27: // ESC key
		exit(0);
		break;      
	case '0':
		Camera::get()->jumpToOrigin();
		break;
	case 'p':
		Camera::get()->togglePursuitMode();
		break;
	case 'z':
	        autopilot_on = !autopilot_on;
		break;
	}

};

void keyup(unsigned char key, int x, int y) {
	KeyManager::get()->asciiKeyReleased(key);
};

void special_keydown(int keycode, int x, int y) {

	KeyManager::get()->specialKeyPressed(keycode);

};

void special_keyup(int keycode, int x, int y) {  
	KeyManager::get()->specialKeyReleased(keycode);  
};

void mouse(int button, int state, int x, int y) {

};

void dragged(int x, int y) {

	if (prev_mouse_x >= 0) {

		int dx = x - prev_mouse_x;
		int dy = y - prev_mouse_y;

		Camera::get()->mouseRotateCamera(dx, dy);
	}

	prev_mouse_x = x;
	prev_mouse_y = y;
};

void motion(int x, int y) {

	prev_mouse_x = x;
	prev_mouse_y = y;
};

void update(Vehicle * car){
    //Find forces due to obstacles
    double F_x = 0;
    double F_z = 0;
    //double vehicle_x = vehicle.getX;
    //double vehicle_y = vehicle.getY;
    double vehicle_v_x;
    double vehicle_v_z;
    GoalState nextGoal;
    double goal_dx;
    double goal_dz;
    double goal_dist;
    double angle;
    double angle_cos;

    std::list<Obstacle> obstacles = ObstacleManager::get()->getObstacles(car->x, car->z, 10);
    for (std::list<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++) {
		    double dx = (it->getX() - car->x);
		    double dz = -(it->getZ() - car->z);
		    F_x = F_x + 0.0*dx/pow(dx,3);
		    F_z = F_z + 0.0*dz/pow(dz,3);
		    //cout << "Checked obstacle " << endl;
		    //cout << "Distances: " << dx << " " << dz << endl;
    }

    //Pop goal, check distance, if less than 10 move on to next goal
    do{
    nextGoal = goals.front();
    goals.pop_front();
    goal_dx = (nextGoal.x-car->x);
    goal_dz = -(nextGoal.z-car->z);
    goal_dist = sqrt(pow(goal_dx,2)+pow(goal_dz,2));
    //cout << "Goal distance: " << goal_dist << endl;
    }while(goal_dist < 10.0);
    goals.push_front(nextGoal);

    //Find forces due to goals
    //cout << "Goal dx :" << goal_dx << endl;
    //cout << "Goal dz :" << goal_dz << endl;
    if(goal_dx != 0.0){
      F_x = F_x - goal_dx*abs(1/pow(goal_dx,3));
    }else{
      F_x = 0;
    }

    //cout << "F_z before update: " << F_z << endl;
    //cout << "Goal dz :" << goal_dz << endl;
    if(goal_dz != 0.0){
      F_z = F_z - goal_dz*abs(1/pow(goal_dz,3));
    }else{
      F_z = 0;
    }
    //cout << "F_z after update: " << F_z << endl;

    //Attempt to align vehicle vector with force vector 
    vehicle_v_x = -car->speed * cos(car->rotation * M_PI/180.0);
    vehicle_v_z = car->speed * sin(car->rotation * M_PI/180.0);

    //cout << "ANGLE DEBUG........................." << endl;
    //cout << "Car rotation value: " << vehicle->getRotation() << endl;
    //cout << "Car angle: " << (180-car->rotation) << endl;
    //cout << "Force angle: " << atan(F_z/F_x)*180/M_PI << endl;
    //angle = (atan(F_z/F_x)*180/M_PI)+(180-car->rotation);
    if(car->speed > 0){
      angle_cos = ((F_x*vehicle_v_x)+(F_z*vehicle_v_z))/abs((sqrt(pow(F_x,2)+pow(F_z,2))*car->speed));
    }else{
      angle_cos = 1;
    }
    //cout << "Angle error: " << angle <<  endl;
    //cout << "........................." << endl;

    //Debug outputs
    cout << "Goal coords: " << nextGoal.x << " " << nextGoal.z << endl;
    //cout << "Vehicle coords: " << car->x << " " << car->z << endl;
    cout << "Force vector: " << F_x << " " << F_z << endl;
    cout << "Velocity vector" << vehicle_v_x << " " << vehicle_v_z << endl;

    //steering
    /*
    if(angle*180/M_PI < 15){ 
    cout << "Steering angle: " << -sin(angle)*15 << endl;
    car->steering = -sin(angle)*15;
    }else{
    cout << "Steering angle maxed" << endl;
    car->steering = 15;
    }
    */
    cout << "Angle cos: " << angle_cos << endl;
    if(angle_cos+1 < 0.95 ){
       car->steering = 15;
    }else if(angle_cos+1 > 1.05 ){
       car->steering = -15;
    }else{
       car->steering = 0;
    }
    cout << "Steering" << car->steering << endl;
    cout << "Drive: " << abs(angle_cos*10.0) << endl;
    car->speed = abs(6.0)+4;
}

