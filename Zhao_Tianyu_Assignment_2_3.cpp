
using namespace std;
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "GL/freeglut.h"
GLsizei ww = 600, hh = 600;
float theta = 0; // degree for rotate only teapot
float xrot = 0; // 
float yrot = 0;
float scale = 1;
float shapescale = 1;
float px = 0;
float py = 0;

float rotax;
float rotay;
float transx = 0;
float transy = 0;
float transz = 0;

float stopatx = 0;
float stopaty = 0;
float stopattheta = 0;

int mousex; //record prev mouse coordi
int mousey;
bool rotateworld = 0; // if rotateworld selected
bool axes = 0; //if show axes
bool click = 0; // first mouse down
bool rotateaxis = 0; // if rotate axes calculated
bool camera = 1;
bool rotateglobal = 0;
bool press = 0;
bool pressshift = 0;
bool pressalt = 0;
bool pressctrl = 0;
bool stopflag = 0;
bool autorotate = 0;
bool drawtp = 1;
bool smooth = 1;

string filename;
vector<vector<float>> ver;
vector<vector<int>> pol;
int m = -1;
int n = -1;

bool l0 = 1;
bool l1 = 0;
bool l2 = 0;
bool l3 = 0;

GLfloat amb[] = { 0.2,0.2,0.2,1.0 };

GLfloat pos0[] = { 1, 0, 0, 0 };
GLfloat dif0[] = { 0.7, 0.7, 0.7, 1 };
GLfloat spe0[] = { 0.7,0.7,0,32 };

GLfloat pos1[] = { -1, 0, 0, 0 };
GLfloat dif1[] = { 0.75, 0.0, 0.1, 1 };
GLfloat spe1[] = { 0.7,0,0.7,16 };

GLfloat pos2[] = { 0, 1, 0, 0 };
GLfloat dif2[] = { 0.0, 0.8, 0.1, 1 };
GLfloat spe2[] = { 0.0,0.7,0.7,8 };

GLfloat pos3[] = { 0, -1, 0, 0 };
GLfloat dif3[] = { 0.0, 0.0, 0.95, 1 };
GLfloat spe3[] = { 0.7,0.7,0.7,4 };



static void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
	gluPerspective(60 * shapescale, 1, 0.01, 10);
	glTranslatef(0, 0, -2);

	glEnable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	if (l0) {
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, pos0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, dif0);
		glLightfv(GL_LIGHT0, GL_SPECULAR, spe0);
	}
	if (l1) {
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_POSITION, pos1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, dif1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, spe1);
	}
	if (l2) {
		glEnable(GL_LIGHT2);
		glLightfv(GL_LIGHT2, GL_POSITION, pos2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, dif2);
		glLightfv(GL_LIGHT2, GL_SPECULAR, spe2);
	}
	if (l3) {
		glEnable(GL_LIGHT3);
		glLightfv(GL_LIGHT3, GL_POSITION, pos3);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, dif3);
		glLightfv(GL_LIGHT3, GL_SPECULAR, spe3);
	}
	glLightfv(GL_LIGHT2, GL_AMBIENT, amb);

//	glRotatef(xrot, 0.0, 1.0, 0.0);
//	glRotatef(yrot, 1.0, 0.0, 0.0);
	if (rotateglobal == 1) {
		if (theta > 360) theta -= 360;
		glRotatef(theta, rotax, rotay, 0.0);
		stopattheta = theta;
		stopatx = rotax;
		stopaty = rotay;
		stopflag = 0;
	}
	else {
		stopflag = 1;
	}
	
	if (smooth == 1) {
		glShadeModel(GL_SMOOTH);
	}
	else {
		glShadeModel(GL_FLAT);
	}
	/*if (rotateglobal == 1) {
		glTranslatef(transx, transy, transz);
	}*/
	if (axes == 1) {
		if (stopflag == 1) {
			glRotatef(stopattheta, stopatx, stopaty, 0.0);
		}
		glBegin(GL_LINES);
		// draw line for x axis
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		// draw line for y axis
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		// draw line for Z axis
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
	}

	/*if (rotateworld == 1) {
		glRotatef(-stopattheta, stopatx, stopaty, 0.0);
		glRotatef(theta, rotax, rotay, 0.0);
	}*/
	//if (rotateglobal == 0) {
		//glTranslatef(transx, transy, transz);
	//}
	if (rotateworld == 1) {
		glTranslatef(transx, transy, transz);
		glRotatef(-stopattheta, stopatx, stopaty, 0.0);
		glRotatef(theta, rotax, rotay, 0.0);
		if (rotateaxis == 1) {
			glBegin(GL_LINES);
			glColor3f(1.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(rotax * 20, rotay * 20, 0.0);
			glEnd();
			glColor3f(1.0, 1.0, 1.0);
		}
	}
	else {
		if (rotateaxis == 1) {
			glBegin(GL_LINES);
			glColor3f(1.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(rotax * 20, rotay * 20, 0.0);
			glEnd();
			glColor3f(1.0, 1.0, 1.0);
		}
		glTranslatef(transx, transy, transz);
	}

	if (drawtp == 1) {
		glCullFace(GL_BACK);
		glutSolidTeapot(0.3);
	}
	else {
		float ax = 0, ay = 0, az = 0, bx = 0, by = 0, bz = 0, nx = 0, ny = 0, nz = 0;
		for (int i = 0; i < n; i++) {
			ax = ver[pol[i][0] - 1][0] - ver[pol[i][1] - 1][0];
			ay = ver[pol[i][0] - 1][1] - ver[pol[i][1] - 1][1];
			az = ver[pol[i][0] - 1][2] - ver[pol[i][1] - 1][2];
			bx = ver[pol[i][1] - 1][0] - ver[pol[i][2] - 1][0];
			by = ver[pol[i][1] - 1][1] - ver[pol[i][2] - 1][1];
			bz = ver[pol[i][1] - 1][2] - ver[pol[i][2] - 1][2];
			nx = ay * bz - az * by;
			ny = az * bx - ax * bz;
			nz = ax * by - ay * bx;
			float m = sqrt(nx * nx + ny * ny + nz * nz);
			float n[3] = { nx / m,ny / m,nz / m };
			glNormal3f(n[0], n[1], n[2]);
			glBegin(GL_POLYGON);
			for (int j = 0; j < pol[i].size(); j++) {
				glVertex3f(ver[pol[i][j] - 1][0], ver[pol[i][j] - 1][1], ver[pol[i][j] - 1][2]);
			}
			glEnd();
		}
	}
	glFlush();
}



static void myreshape(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w < h) {

		glOrtho(-1.0 * scale, 1.0  * scale, -1.0 * scale, 1.0* scale, -1.0* scale, 1.0* scale);
		//glOrtho(-1.0 * scale, 1.0* scale, -1.0 * h / w * scale, 1.0 * h / w * scale, -1.0* scale, 1.0* scale);
	}
	else {
		glOrtho(-1.0 * scale, 1.0  * scale, -1.0 * scale, 1.0* scale, -1.0* scale, 1.0* scale);
		//glOrtho(-1.0 * w / h * scale, 1.0 * w / h * scale,-1.0* scale, 1.0* scale, -1.0* scale, 1.0* scale);
	}
	glMatrixMode(GL_MODELVIEW);
	if (w < h) {
		glViewport(0, (h - w) / 2, w, w);
	}
	else {
		glViewport((w - h) / 2, 0, h, h);
		//glViewport(0, 0, h, h);
	}
	ww = w;
	hh = h;
}

static void drawpoly() {
	ifstream infile(filename);
	if (infile.is_open()) {
		string line;
		string s = "";
		while (getline(infile, line)) {
			if (line[0] == '/' || line[1] == '/') {
				continue;
			}
			else {
				for (int i = 0; i < line.length(); i++) {
					if (line[i] >= 48 && line[i] <= 57) {
						s.push_back(line[i]);
					}
					else {
						if (s != "") {
							if (m == -1) {
								m = stoi(s);
								s = "";
							}
						}
					}
				}
				break;
			}
		}
		if (s != "") {
			if (n == -1) {
				n = stoi(s);
			}
		}
		s = "";
		//cout << m << ' ' << n << endl;
		//vector<vector<float>> ver;
		//vector<vector<int>> pol;
		for (int i = 0; i < m; i++) {
			getline(infile, line);
			if (line[0] == '/' || line[1] == '/') {
				i--;
				continue;
			}
			line.append(" ");
			vector<float> a;
			ver.push_back(a);
			for (int j = 0; j < line.length(); j++) {
				if (line[j] != ' ') {
					s.push_back(line[j]);
				}
				else {
					if (s != "") {
						ver[i].push_back(atof(s.c_str()));
						s = "";
					}
				}
			}
		}
		for (int i = 0; i < n; i++) {
			getline(infile, line);
			if (line[0] == '/' || line[1] == '/') {
				i--;
				continue;
			}
			vector<int> a;
			pol.push_back(a);
			line.append(" ");
			for (int j = 0; j < line.length(); j++) {
				if (line[j] != ' ') {
					s.push_back(line[j]);
				}
				else {
					if (s != "") {
						pol[i].push_back(stoi(s.c_str()));
						s = "";
					}
				}
			}
		}/*
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < ver[i].size(); j++) {
				cout << ver[i][j] << ' ';
			}
			cout << endl;
		}*/
	}
	else {
		cout << "Fail to open the file. Selected show file object again." << endl;
		drawtp = 1;
	}

}

static void left_actived(int x, int y) {
	if (click == 0) {
		mousex = x;
		mousey = y;
		click = 1;
	}
	else {
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
			if (pressshift == 1) {
				if (ww < hh) {
					transx += (x - mousex) / (float)ww * 2.0;
					transy += -(y - mousey) / (float)ww * 2.0;
				}
				else {
					transx += (x - mousex) / (float)hh * 2.0;
					transy += -(y - mousey) / (float)hh * 2.0;
				}
			}

			mousex = x;
			mousey = y;
			pressshift = 1;
		}
		else if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
			if (pressctrl == 1) {
				if (ww < hh) {
					//transz += (x - mousex) / (float)ww * 2.0;
					shapescale += -(y - mousey) / (float)ww * 2.0;
				}
				else {
					//transz += (x - mousex) / (float)hh * 2.0;
					shapescale += -(y - mousey) / (float)hh * 2.0;
				}
			}
			if (shapescale < 0) {
				shapescale = 0;
			}
			mousex = x;
			mousey = y;
			pressctrl = 1;
		}
		else if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
			if (pressalt == 1) {
				if (ww < hh) {
					transz += (x - mousex) / (float)ww * 2.0;
					//transy += -(y - mousey) / (float)ww * 2.0;
				}
				else {
					transz += (x - mousex) / (float)hh * 2.0;
					//transy += -(y - mousey) / (float)hh * 2.0;
				}
			}

			mousex = x;
			mousey = y;
			pressalt = 1;
		}
		else if (rotateworld == 1 || rotateglobal == 1) {

			float x1, y1;
			if (ww < hh) {
				x1 = x / (float)ww * 2.0 - 1;
				y1 = -(y / (hh - ((float)hh - ww) / 2.0) * 2.0 - 1);
			}
			else {
				x1 = x / (ww - ((float)ww - hh) / 2.0) * 2.0 - 1;
				y1 = -(y / (float)hh * 2.0 - 1);
			}
			float diff = x1 - rotax / rotay * y1;
			if (diff < 0) {
				diff = -1 * diff;
			}
			float speed = diff;
			if (x - mousex > 0) {
				theta += 5 * speed;
			}
			else if (x - mousex < 0) {
				theta -= 5 * speed;
			}
			mousex = x;
			mousey = y;
		}
		else {
			/*float x1, y1;
			if (ww < hh) {
				x1 = x / (float)ww * 2.0 - 1;
				y1 = -(y / (hh - ((float)hh - ww) / 2.0) * 2.0 - 1);
			}
			else {
				x1 = x / (ww - ((float)ww - hh) / 2.0) * 2.0 - 1;
				y1 = -(y / (float)hh * 2.0 - 1);
			}
			*/
			float diff = ((float)x - (float)ww / 2) * ((float)y - (float)hh / 2);
			if (diff < 0) {
				diff = -1 * diff;
			}
			float speed = (diff + 15000) / 25000;
			if (x - mousex > 0) {
				xrot += 5 * speed;
			}
			else if (x - mousex < 0) {
				xrot -= 5 * speed;
			}
			if (y - mousey > 0) {
				yrot += 5 * speed;
			}
			else if (y - mousey < 0) {
				yrot -= 5 * speed;
			}
			mousex = x;
			mousey = y;

		}
	}
	display();
}
static void mouse_press(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		if (rotateaxis == 0 && (rotateworld == 1 || rotateglobal == 1)) {
			float x1, y1;
			if (ww < hh) {
				x1 = x / (float)ww * 2.0 - 1;
				y1 = -(y / (hh - ((float)hh - ww) / 2.0) * 2.0 - 1);
			}
			else {
				x1 = x / (ww - ((float)ww - hh) / 2.0) * 2.0 - 1;
				y1 = -(y / (float)hh * 2.0 - 1);
			}
			rotax = -y1;
			rotay = x1;
			px = x1;
			py = y1;
			rotateaxis = 1;
		}
		glutMotionFunc(left_actived);
		press = 0;

		pressalt = 0;
		pressctrl = 0;
		pressshift = 0;
	}
}
static void mainmenu(int selected) {

}

static void othermenu(int selected) {
	switch (selected) {
	case 0:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		theta = 0; // degree for rotate only teapot
		xrot = 0; // 
		yrot = 0;
		transx = 0;// reset translation
		transy = 0;
		transz = 0;
		px = 0;
		py = 0;
		rotateworld = 0; // if rotateworld selected
		rotateglobal = 0;
		axes = 0; //if show axes
		click = 0; // first mouse down
		rotateaxis = 0; // if rotate axes calculated
		pressalt = 0;
		pressctrl = 0;
		pressshift = 0;
		stopatx = 0;
		stopaty = 0;
		stopattheta = 0;
		//camera = 0;
		stopflag = 0;
		shapescale = 1;
		autorotate = 0;
		smooth = 0;
		drawtp = 1;
		l0 = 1;
		l1 = 0;
		l2 = 0;
		l3 = 0;
		ver.clear();
		pol.clear();
		m = -1;
		n = -1;
		display();
		break;
	case 1:
		glutSwapBuffers();
		break;
	case 2:
		exit(EXIT_SUCCESS);
	}
}

void myfunc() {
	float diff = (float)px - (float)rotax / (float)rotay * (float)py;
	theta += diff;
	display();
}

static void rotmenu(int selected) {
	switch (selected) {
	case 0:
		rotateworld = 1;
		rotateglobal = 0;
		break;
	case 1:
		rotateglobal = 1;
		rotateworld = 0;
		break;
	case 2:
		xrot = 0; // 
		yrot = 0;
		transx = 0;// reset translation
		transy = 0;
		transz = 0;
		stopatx = 0;
		stopaty = 0;
		theta = 0;
		stopattheta = 0;
		shapescale = 1;
		display();
		break;
	}
}

static void dismenu(int selected) {
	switch (selected) {
	case 0:
		axes = 1;
		display();
		break;
	case 1:
		axes = 0;
		display();
		break;
	case 2:
		if (autorotate == 0) {
			autorotate = 1;
			glutIdleFunc(myfunc);
			//display();
		}
		else {
			autorotate = 0;
			glutIdleFunc(NULL);
		}
		break;
	case 3:
		drawtp = 1;
		display();
		break;
	case 4:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		theta = 0; // degree for rotate only teapot
		xrot = 0; // 
		yrot = 0;
		transx = 0;// reset translation
		transy = 0;
		transz = 0;
		px = 0;
		py = 0;
		rotateworld = 0; // if rotateworld selected
		rotateglobal = 0;
		axes = 0; //if show axes
		click = 0; // first mouse down
		rotateaxis = 0; // if rotate axes calculated
		pressalt = 0;
		pressctrl = 0;
		pressshift = 0;
		stopatx = 0;
		stopaty = 0;
		stopattheta = 0;
		//camera = 0;
		stopflag = 0;
		shapescale = 1;
		autorotate = 0;
		smooth = 0;
		drawtp = 1;
		l0 = 1;
		l1 = 0;
		l2 = 0;
		l3 = 0;
		ver.clear();
		pol.clear();
		m = -1;
		n = -1;
		drawtp = 0;
		cout << "Please input the file name:";
		cin >> filename;
		drawpoly();
		display();
		break;
	}
}

void lightmenu(int selected) {
	switch (selected) {
	case 0:
		if (l0 == 1) { l0 = 0; }
		else l0 = 1;
		display();
		break;
	case 1:
		if (l1 == 1) { l1 = 0; }
		else l1 = 1;
		display();
		break;
	case 2:
		if (l2 == 1) { l2 = 0; }
		else l2 = 1;
		display();
		break;
	case 3:
		if (l3 == 1) { l3 = 0; }
		else l3 = 1;
		display();
		break;
	case 4:
		if (smooth == 1) { smooth = 0; }
		else smooth = 1;
		display();
	}
}

// Zhao_Tianyu_Assignment_2_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

int main(int argc, char **argv) {

	// window initialization
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(30, 30);


	// create window
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Assignment 2: Teapot Rotation");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// set empty display function
	glutDisplayFunc(display);
	glutReshapeFunc(myreshape);
	glutMouseFunc(mouse_press);


	int other = glutCreateMenu(othermenu);
	glutAddMenuEntry("Clear", 0);
	glutAddMenuEntry("Refresh", 1);
	//glutAddMenuEntry("Camera on", 3);
	//glutAddMenuEntry("Camera off", 4);
	glutAddMenuEntry("Exit", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	int rotate = glutCreateMenu(rotmenu);
	glutAddMenuEntry("Reset View", 2);
	glutAddMenuEntry("Rotate World", 1);
	glutAddMenuEntry("Rotate Teapot", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	int display = glutCreateMenu(dismenu);
	glutAddMenuEntry("Show axes", 0);
	glutAddMenuEntry("Hide axes", 1);
	glutAddMenuEntry("Auto-Rotate on/off", 2);
	glutAddMenuEntry("Show Teapot", 3);
	glutAddMenuEntry("Show File Object(s)", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int light = glutCreateMenu(lightmenu);
	glutAddMenuEntry("Light 0 Toggle", 0);
	glutAddMenuEntry("Light 1 Toggle", 1);
	glutAddMenuEntry("Light 2 Toggle", 2);
	glutAddMenuEntry("Light 3 Toggle", 3);
	glutAddMenuEntry("Smooth Shade on/off", 4);

	// create menu
	int root = glutCreateMenu(mainmenu);
	glutAddSubMenu("Other Action", other);
	glutAddSubMenu("Rotate", rotate);
	glutAddSubMenu("Display", display);
	glutAddSubMenu("Light", light);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	


	// start glut loop
	glutMainLoop();

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
