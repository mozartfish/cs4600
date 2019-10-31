#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <map>

#define M_PI 3.141592654f

unsigned int g_windowWidth = 800;
unsigned int g_windowHeight = 600;
char* g_windowName = "HW3-3D-Basics";

GLFWwindow* g_window;

// Model data
std::vector<float> g_meshVertices; // the vertices of the triangle
std::vector<float> g_meshNormals; // the vector containing the list of normal vectors
std::vector<unsigned int> g_meshIndices; // the vector containing the indices of te mesh
std::map<unsigned int, int> countMap; // map for storing the frequency of vertices used in the mesh
GLfloat g_modelViewMatrix[16];

// Default options
bool enablePersp = true;
bool teapotSpin = false;
bool enableDolly = false;
bool showCheckerboard = false;

// Dolly zoom options 
float fov = M_PI / 4.f;
float distance = 4.5f;
float halfWidth = distance * tan(fov / 2);

// Auxiliary math functions
float dotProduct(const float* a, const float* b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

void crossProduct(const float* a, const float* b, float* r)
{
	r[0] = a[1] * b[2] - a[2] * b[1];
	r[1] = a[2] * b[0] - a[0] * b[2];
	r[2] = a[0] * b[1] - a[1] * b[0];
}

float radianToDegree(float angleInRadian) {
	return angleInRadian * 180.f / M_PI;
}

void normalize(float* a)
{
	const float len = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);

	a[0] /= len;
	a[1] /= len;
	a[2] /= len;
}


std::vector<float>generateVector(int vertex)
{
	// store the resultant vector
	std::vector<float> vectorResult;

	//std::cout << "The vertex selected is " << vertex << std::endl;
	
	// get the coordinates of the point
	float pX = g_meshVertices[3 * vertex + 0];
	float pY = g_meshVertices[3 * vertex + 1];
	float pZ = g_meshVertices[3 * vertex + 2];

	//std::cout << "The x coordinate is " << pX << std::endl;
	//std::cout << "The y coordinate is " << pY << std::endl;
	//std::cout << "The z coordinate is " << pZ << std::endl;

	// check if the vertex is already stored in the map
	if (countMap.count(vertex) == 0)
	{
		//std::cout << "The vertex is not located in the table" << std::endl;
		int counter = 1;
		countMap[vertex] = counter;
	}
	else
	{
		//std::cout << "The vertex is located in the table" << std::endl;
		int counter = countMap[vertex];
		counter = counter + 1;
		countMap[vertex] = counter;
	}

	// push the values
	vectorResult.push_back(pX);
	vectorResult.push_back(pY);
	vectorResult.push_back(pZ);

	//std::cout << "X value is " << vectorResult[0] << std::endl;
	//std::cout << "Y value is " << vectorResult[1] << std::endl;
	//std::cout << "Z value is " << vectorResult[2] << std::endl;
	return vectorResult;
}


void computeNormals()
{
	g_meshNormals.resize(g_meshVertices.size());
	// TASK 1
	// The code below sets all normals to point in the z-axis, so we get a boring constant gray color
	// The following should be replaced with your code for normal computation

	// the size of the different vectors
	//std::cout << "The size of the vertices vector is " << g_meshVertices.size() << std::endl;
	//std::cout << "The size of the indices vector is " << g_meshIndices.size() << std::endl;
	//std::cout << "The size of the normals vector is " << g_meshNormals.size() << std::endl;
	//std::cout << "The size of mesh indices / 3 is " << g_meshIndices.size() / 3 << std::endl;
	for (int v = 0; v < g_meshIndices.size() / 3; ++v)
	{
		/*g_meshNormals[3 * v + 2] = 1.0;*/

		// get three vertices
		int point1 = g_meshIndices[3 * v + 0];
		int point2 = g_meshIndices[3 * v + 1];
		int point3 = g_meshIndices[3 * v + 2];

		//std::cout << "The value of point1 is " << point1 << std::endl;
		//std::cout << "The value of point2 is " << point2 << std::endl;
		//std::cout << "The value of point3 is " << point3 << std::endl;

		// make vectors
		std::vector<float> vectorP = generateVector(point1);
		std::vector<float> vectorQ = generateVector(point2);
		std::vector<float> vectorR = generateVector(point3);

		// compute vector PQ
		float pQX = vectorQ[0] - vectorP[0];
		float pQY = vectorQ[1] - vectorP[1];
		float pQZ = vectorQ[2] - vectorP[2];

		/*std::cout << "The value of the pQ x coordinate is " << pQX << std::endl;
		std::cout << "The value of the pQ y coordinate is " << pQY << std::endl;
		std::cout << "The value of the pQ z coordinate is " << pQZ << std::endl;*/

		// compute the vector PR
		float pRX = vectorR[0] - vectorP[0];
		float pRY = vectorR[1] - vectorP[1];
		float pRZ = vectorR[2] - vectorP[2];

		/*std::cout << "The value of the pR x coordinate is " << pRX << std::endl;
		std::cout << "The value of the pR y coordinate is " << pRY << std::endl;
		std::cout << "The value of the pR z coordinate is " << pRZ << std::endl;*/

		// compute the cross product ||PQ x PR||
		float i = (pQY * pRZ) - (pQZ * pRY);
		float j = (pQZ * pRX) - (pQX * pRZ);
		float k = (pQX * pRY) - (pQY * pRX);

	/*	std::cout << "The value of i is " << i << std::endl;
		std::cout << "The value of j is " << j << std::endl;
		std::cout << "The value of k is " << k << std::endl;*/

		// compute the 2 norm
		float twoNorm = std::sqrt(std::pow(i, 2) + std::pow(j, 2) + std::pow(k, 2));
	/*	std::cout << "The two norm is " << twoNorm << std::endl;*/

		// normalize the vector
		float normalX = i / twoNorm;
		float normalY = j / twoNorm;
		float normalZ = k / twoNorm;

		//std::cout << "The value of normalX is " << normalX << std::endl;
		//std::cout << "The value of normalY is " << normalY << std::endl;
		//std::cout << "The value of normalZ is " << normalZ << std::endl;


		// allocate 9 spots at a time for the normal coordinates
		// the normal vector is perpendicular to point 1, point 2, and point 3
		// each point has x, y, z value so we allocate a spot for each x, y, and z values
		g_meshNormals[3 * point1 + 0] += normalX;
		g_meshNormals[3 * point1 + 1] += normalY;
		g_meshNormals[3 * point1 + 2] += normalZ;
		g_meshNormals[3 * point2 + 0] += normalX;
		g_meshNormals[3 * point2 + 1] += normalY;
		g_meshNormals[3 * point2 + 2] += normalZ;
		g_meshNormals[3 * point3 + 0] += normalX;
		g_meshNormals[3 * point3 + 1] += normalY;
		g_meshNormals[3 * point3 + 2] += normalZ;
	}

	for (int j = 0; j < g_meshNormals.size() / 3; ++j)
	{
		g_meshNormals[3 * j + 0] = g_meshNormals[3 * j + 0] / countMap[j];
		g_meshNormals[3 * j + 1] = g_meshNormals[3 * j + 1] / countMap[j];
		g_meshNormals[3 * j + 2] = g_meshNormals[3 * j + 2] / countMap[j];
	}

}

void loadObj(std::string p_path)
{
	std::ifstream nfile;
	nfile.open(p_path);
	std::string s;

	while (nfile >> s)
	{
		if (s.compare("v") == 0)
		{
			float x, y, z;
			nfile >> x >> y >> z;
			g_meshVertices.push_back(x);
			g_meshVertices.push_back(y);
			g_meshVertices.push_back(z);
		}		
		else if (s.compare("f") == 0)
		{
			std::string sa, sb, sc;
			unsigned int a, b, c;
			nfile >> sa >> sb >> sc;

			a = std::stoi(sa);
			b = std::stoi(sb);
			c = std::stoi(sc);

			g_meshIndices.push_back(a - 1);
			g_meshIndices.push_back(b - 1);
			g_meshIndices.push_back(c - 1);
		}
		else
		{
			std::getline(nfile, s);
		}
	}

	computeNormals();

	std::cout << p_path << " loaded. Vertices: " << g_meshVertices.size() / 3 << " Triangles: " << g_meshIndices.size() / 3 << std::endl;
}

double getTime()
{
	return glfwGetTime();
}

void glfwErrorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error " << error << ": " << description << std::endl;
	exit(1);
}

void togglePerspective() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Perspective Projection
	if (enablePersp)
	{
		// Dolly zoom computation
		if (enableDolly) {
			// TASK 3
			// Your code for dolly zoom computation goes here
			// You can use getTime() to change fov over time
			// distance should be recalculated here using the Equation 2 in the description file
			fov = std::abs(std::sin(getTime()));
			std::cout << "The value of the distance is " << distance << std::endl;
			distance = (halfWidth / std::tan(fov / 2));
		}

		float fovInDegree = radianToDegree(fov);
		// field of view degree is angle
		// parameter 2 : aspect ratio (the box)
		// parameter 3: how far we clamp
		gluPerspective(fovInDegree, (GLfloat)g_windowWidth / (GLfloat)g_windowHeight, 0.1f, distance + 500);
		//gluPerspective(fovInDegree, (GLfloat)g_windowWidth / (GLfloat)g_windowHeight, 1.0f, 40.f); // the second coordinate is for the distance
	}
	// Othogonal Projection
	else
	{
	
			// Scale down the object for a better view in orthographic projection
			glScalef(0.5, 0.5, 0.5);

			// TASK 3
			// Your code for orthogonal projection goes here
			// (Hint: you can use glOrtho() function in OpenGL
			// left, right,  bottom, top, near, far
			glOrtho(-1, 1, -0.75, 0.75, 0.1f, 1000.0f);
	}
}

void glfwKeyCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
{
	if (p_key == GLFW_KEY_ESCAPE && p_action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(g_window, GL_TRUE);
	}
	if (p_key == GLFW_KEY_P && p_action == GLFW_PRESS) {

		// Perspective Projection
		enablePersp = true;
		togglePerspective();
		std::cout << "Perspective activated\n";

	}
	if (p_key == GLFW_KEY_O && p_action == GLFW_PRESS) {

		// Orthographic Projection
		enablePersp = false;
		togglePerspective();
		std::cout << "Orthogonal activated\n";

	}
	if (p_key == GLFW_KEY_S && p_action == GLFW_PRESS) {

		// Toggle Spinning
		if (!teapotSpin) {
			std::cout << "Teapot spinning on\n";
		}
		else {
			std::cout << "Teapot spinning off\n";
		}
		teapotSpin = !teapotSpin;
	}
	if (p_key == GLFW_KEY_D && p_action == GLFW_PRESS) {

		// Toggle dolly zoom
		if (!enableDolly)
		{
			std::cout << "Dolly zoom on\n";
		}
		else {
			std::cout << "Dolly zoom off\n";
		}
		enableDolly = !enableDolly;
	}
	if (p_key == GLFW_KEY_C && p_action == GLFW_PRESS) {

		// Show/hide Checkerboard
		if (!showCheckerboard)
		{
			std::cout << "Show checkerboard\n";
		}
		else {
			std::cout << "Hide checkerboard\n";
		}
		showCheckerboard = !showCheckerboard;
	}
}

void initWindow()
{
	// initialize GLFW
	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit())
	{
		std::cerr << "GLFW Error: Could not initialize GLFW library" << std::endl;
		exit(1);
	}

	g_window = glfwCreateWindow(g_windowWidth, g_windowHeight, g_windowName, NULL, NULL);
	if (!g_window)
	{
		glfwTerminate();
		std::cerr << "GLFW Error: Could not initialize window" << std::endl;
		exit(1);
	}

	// callbacks
	glfwSetKeyCallback(g_window, glfwKeyCallback);

	// Make the window's context current
	glfwMakeContextCurrent(g_window);

	// turn on VSYNC
	glfwSwapInterval(1);
}

void initGL()
{
	glClearColor(1.f, 1.f, 1.f, 1.0f);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void printHotKeys() {
	std::cout << "\nHot Keys..\n"
		<< "Orthogonal Projection:  O\n"
		<< "Perspective Projection: P\n"
		<< "Toggle Spinning:        S\n"
		<< "Toggle Dolly Zoom:      D\n"
		<< "Show/hide Checkerboard: C\n"
		<< "Exit:                   Esc\n\n";
}

void clearModelViewMatrix()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			g_modelViewMatrix[4 * i + j] = 0.0f;
		}
	}
}

void updateModelViewMatrix()
{	
	clearModelViewMatrix();

	g_modelViewMatrix[0] = 1.0f;
	g_modelViewMatrix[5] = 1.0f;
	g_modelViewMatrix[10] = 1.0f;

	g_modelViewMatrix[14] = -distance;
	g_modelViewMatrix[15] = 1.0f;

	// TASK 2
	// The following code sets a static modelView matrix
	// This should be replaced with code implementing Task 2
	// You can use getTime() to change rotation over time


	float a = g_modelViewMatrix[0];
	float b = g_modelViewMatrix[1];
	float c = g_modelViewMatrix[2];
	float d = g_modelViewMatrix[4];
	float e = g_modelViewMatrix[5];
	float f = g_modelViewMatrix[6];
	float g = g_modelViewMatrix[8];
	float h = g_modelViewMatrix[9];
	float i = g_modelViewMatrix[10];

	// Matrix Multiplication with the y rotation matrix where theta is represented by getTime()

	if (teapotSpin == true)
	{
		g_modelViewMatrix[0] = (a * std::cos(getTime())) + 0 + (c * -std::sin(getTime()));
		g_modelViewMatrix[1] = b;
		g_modelViewMatrix[2] = (a * std::sin(getTime())) + 0 + (c * std::cos(getTime()));
		g_modelViewMatrix[4] = (d * std::cos(getTime())) + 0 - (f * std::sin(getTime()));
		g_modelViewMatrix[5] = e;
		g_modelViewMatrix[6] = (d * std::sin(getTime())) + 0 + (f * std::cos(getTime()));
		g_modelViewMatrix[8] = (g * std::cos(getTime())) + 0 - (i * std::sin(getTime()));
		g_modelViewMatrix[9] = h;
		g_modelViewMatrix[10] = (g * std::sin(getTime())) + 0 + (i * std::cos(getTime()));
	}
}

void setModelViewMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	updateModelViewMatrix();
	glLoadMatrixf(g_modelViewMatrix);
}

void drawTeapot() {
	glBegin(GL_TRIANGLES);
	for (size_t f = 0; f < g_meshIndices.size(); ++f)
	{
		const float scale = 0.1f;
		const unsigned int idx = g_meshIndices[f];
		const float x = scale * g_meshVertices[3 * idx + 0];
		const float y = scale * g_meshVertices[3 * idx + 1];
		const float z = scale * g_meshVertices[3 * idx + 2];

		const float nx = g_meshNormals[3 * idx + 0];
		const float ny = g_meshNormals[3 * idx + 1];
		const float nz = g_meshNormals[3 * idx + 2];

		glNormal3f(nx, ny, nz);
		glVertex3f(x, y, z);
	}
	glEnd();
}
void renderTeapot() {
	drawTeapot();
}

void drawCheckerBoard() {
	int checkerCount = g_windowWidth;
	int checkerSize = (g_windowWidth) / checkerCount;

	glBegin(GL_QUADS);
	for (int i = 0; i < checkerCount; ++i) {
		for (int j = 0; j < checkerCount; ++j) {
			if ((i + j) % 2 == 0)
				glColor3f(0.0, 0.1, 1.0);
			else
				glColor3f(1.0, 0.0, 1.0);

			float x = i - checkerCount / 2; // to be between -1 and 1
			float z = j - checkerCount / 2;
			x *= checkerSize;
			z *= checkerSize;
			float y = -1.0f;
			glVertex3f(x, y, z);
			glVertex3f(x, y, z - checkerSize);
			glVertex3f(x + checkerSize, y, z - checkerSize);
			glVertex3f(x + checkerSize, y, z);
		}
	}
	glEnd();
}
void renderCheckerBoard() {

	/*
	/* If you want to keep checkerboard still while rotating the
	/* the teapot, you need to change the transformation for the
	/* checkerboard plane
	*/
	glMatrixMode(GL_MODELVIEW);
	clearModelViewMatrix();

	g_modelViewMatrix[0] = 1;
	g_modelViewMatrix[2] = 0;
	g_modelViewMatrix[5] = 1;
	g_modelViewMatrix[8] = 0;
	g_modelViewMatrix[10] = 1;
	g_modelViewMatrix[14] = -distance;
	g_modelViewMatrix[15] = 1.0f;
	
	glLoadMatrixf(g_modelViewMatrix);

	// Disable shading for the checkerboard
	glDisable(GL_LIGHTING);
	drawCheckerBoard();
	glEnable(GL_LIGHTING);
}

void render()
{
	togglePerspective();
	setModelViewMatrix();
	renderTeapot();
	if (showCheckerboard)
		renderCheckerBoard();
}

void renderLoop()
{
	while (!glfwWindowShouldClose(g_window))
	{
		// clear buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		render();

		// Swap front and back buffers
		glfwSwapBuffers(g_window);

		// Poll for and process events
		glfwPollEvents();
	}
}

int main()
{
	initWindow();
	initGL();
	loadObj("data/teapot.obj");
	printHotKeys();
	renderLoop();
}
