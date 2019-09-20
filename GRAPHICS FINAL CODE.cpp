#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#define M_PI 3.141592654f

unsigned int g_windowWidth = 600;
unsigned int g_windowHeight = 600;
char* g_windowName = "HW2-Rasterization";

GLFWwindow* g_window;

const int g_image_width = g_windowWidth;
const int g_image_height = g_windowHeight;

std::vector<float> g_image;
int counter = 0;

void putPixel(int x, int y)
{
	// clamp
	if (x >= g_image_width || x < 0 || y >= g_image_height || y < 0) return;

	// write
	g_image[y* g_image_width + x] = 1.0f;
}

//-------------------------------------------------------------------------------

// Function that maps Cartesian Coordinate System to Screen Coordinate System for Quadrant 3
void QuadrantThreeRepresentation(int x1, int y1, int scaleX, int scaleY)
{
	int tempX1 = x1;
	int tempY1 = y1;

	x1 = x1 + scaleX;
	y1 = (y1 * -1) + scaleY;
	//std::cout << x1 << ", " << y1 << std::endl;
	putPixel(x1, y1);
}

// Function that maps Cartesian Coordinate System to Screen Coordinate System for Quadrant 4
void QuadrantFourRepresentation(int x1, int y1, int scaleX, int scaleY)
{
	int tempX1 = x1;
	int tempY1 = y1;
	x1 = x1 + scaleX;
	y1 = (y1 * -1) + scaleY;
	//std::cout << x1 << ", " << y1 << std::endl;
	putPixel(x1, y1);
}

// Function that maps Cartesian Coordinate System to Screen Coordinate System for Quadrant 5
void QuadrantFiveRepresentation(int x1, int y1, int scaleX, int scaleY)
{
	int oldTempX1, oldTempY1;
	oldTempX1 = x1;
	oldTempY1 = y1;
	// Reflect Back Over the origin
	x1 = -x1;
	y1 = -y1;

	// Map to Screen Coordinates
	x1 = x1 + scaleX;
	y1 = y1 + scaleY;

	// Swap Coordinates
	int tempX1 = x1;
	x1 = y1;
	y1 = tempX1;
	
	//std::cout << x1 << ", " << y1 << std::endl;

	putPixel(x1, y1);
}

// Function that maps Cartesian Coordinate System to Screen Coordinate System for Quadrant 6
void QuadrantSixRepresentation(int x1, int y1, int scaleX, int scaleY)
{
	int tempX1, tempY1;
	tempX1 = x1;
	tempY1 = y1;

	// Reflect over the origin
	x1 = -x1;
	y1 = -y1;

	// Map to Screen Coordinates
	x1 = x1 + scaleX;
	y1 = y1 + scaleY;

	//std::cout << x1 << ", " << y1 << std::endl;

	putPixel(x1, y1);

}

// Function that maps Cartesian Coordinate System to Screen Coordinate System for Quadrant 7
void QuadrantSevenRepresentation(int x1, int y1, int scaleX, int scaleY)
{
	int tempX1, tempY1;
	tempX1 = x1;
	tempY1 = y1;

	// Reflect Across Y axis
	x1 = -x1;

	// Map to Screen Coordinate System
	x1 = x1 + scaleX;
	y1 = y1 + scaleY;
	std::cout << x1 << ", " << y1 << std::endl;
	putPixel(x1, y1);
}

// Function that maps Cartesian Coordinate System to Screen Coordinate System for Quadrant 8 
void QuadrantEightRepresentation(int x1, int y1, int scaleX, int scaleY)
{
	//int oldTempX1, oldTempY1;
	//oldTempX1 = x1;
	//oldTempY1 = y1;

	//// Reflect across x axis
	//y1 = -y1;

	//// Map to Screen Coordinates
	//x1 = x1 + scaleX;
	//y1 = y1 + scaleY;

	//// Swap Coordinates
	//int tempX1 = x1;
	//x1 = y1;
	//y1 = tempX1;
	//
	//std::cout << x1 << ", " << y1 << std::endl;
	//putPixel(x1, y1);
}

// Function that maps Cartesian Coordinate System to Screen Coordinate System for Vertical Lines (Bottom Up)
void verticalLinesBottomUp(int x1, int y1, int scaleX, int scaleY)
{
}

// Function that maps Cartesian Coordinate System to Screen Coordinate System for Vertical Lines (Top Down)
void verticalLinesTopDown(int x1, int y1, int scaleX, int scaleY)
{
}

// Functon that Maps Cartesian Coordinate System to Screen Coordinate System for Horizontal Lines (Left Right)
void horizontalLinesLeftRight(int x1, int y1, int scaleX, int scaleY)
{
}

// Function that Maps Cartesian Coordinate System to Screen Coordinate System for Horizontal Lines (Right Left)
void horizontalLinesRightLeft(int x1, int y1, int scaleX, int scaleY)
{
}





void drawLine(int x1, int y1, int x2, int y2)
{
	// TODO: part of Homework Task 1
	// This function should draw a line from pixel (x1, y1) to pixel (x2, y2)

	// Quadrant 1 Case
	if (x1 <= x2 && y1 < y2 && std::abs(y2 - y1) > std::abs(x2 - x1))
	{
		std::cout << "Quadrant 1 Case" << std::endl;

		int tempX1, tempY1, tempX2, tempY2;

		tempX1 = x1;
		tempY1 = y1;
		tempX2 = x2;
		tempY2 = y2;

		x1 = y1;
		y1 = tempX1;
		x2 = y2;
		y2 = tempX2;

		int dx, dy, D, inc0, inc1;

		dx = x2 - x1;
		dy = y2 - y1;
		D = 2 * dy - dx;
		inc0 = 2 * dy;
		inc1 = 2 * (dy - dx);
		putPixel(x1, y1);

		while (x1 < x2)
		{
			if (D <= 0)
			{
				D = D + inc0;
			}
			else
			{
				D = D + inc1;
				y1 = y1 + 1;
			}

			x1 = x1 + 1;
			putPixel(y1, x1);
		}


	}

	// Quadrant 2
	if (x1 < x2 && std::abs(y2 - y1) < std::abs(x2 - x1) && y1 <= y2)
	{
		std::cout << "Quadrant 2 Case" << std::endl;
		int dx, dy, D, inc0, inc1;

		dx = x2 - x1;
		dy = y2 - y1;
		D = 2 * dy - dx;
		inc0 = 2 * dy;
		inc1 = 2 * (dy - dx);
		putPixel(x1, y1);

		while (x1 < x2)
		{
			if (D <= 0)
			{
				D = D + inc0;
			}
			else
			{
				D = D + inc1;
				y1 = y1 + 1;
			}
			x1 = x1 + 1;
			putPixel(x1, y1);
		}
	}


	// Quadrant 3
	if (x2 > x1 && y2 < y1 && std::abs(y1 - y2) < std::abs(x2 - x1))
	{
		std::cout << "Quadrant 3 Case" << std::endl;

		int tempX1, tempY1, tempX2, tempY2, scaleX, scaleY;
		tempX1 = x1;
		tempX2 = x2;
		tempY1 = y1;
		tempY2 = y2;

		scaleX = x1;
		scaleY = y1;

		// Map to Cartesian Coordinate System
		x1 = x1 - scaleX;
		y1 = y1 - scaleY;
		x2 = x2 - scaleX;
		y2 = y2 - scaleY;

		// Reflect to Positive Coordinates
		y2 = -y2;

		int dx, dy, D, inc0, inc1;

		dx = x2 - x1;
		dy = y2 - y1;
		D = 2 * dy - dx;
		inc0 = 2 * dy;
		inc1 = 2 * (dy - dx);
		putPixel(tempX1, tempY1);

		while (x1 < x2)
		{
			if (D <= 0)
			{
				D = D + inc0;
			}
			else
			{
				D = D + inc1;
				y1 = y1 + 1;
			}
			x1 = x1 + 1;
			QuadrantThreeRepresentation(x1, y1, scaleX, scaleY);
		}
	}

	// Quadrant 4
	if (x2 > x1 && y2 < y1 && std::abs(y2 - y1) > std::abs(x2 - x1))
	{
		std::cout << "Quadrant 4 Case" << std::endl;

		int tempX1, tempY1, tempX2, tempY2, scaleX, scaleY;
		// Determine the scale and scale coordinates accordingly
		scaleX = x1;
		scaleY = y1;
		tempX1 = x1;
		tempY1 = y1;
		tempX2 = x2;
		tempY2 = y2;
		x1 = x1 - scaleX;
		y1 = y1 - scaleY;
		x2 = x2 - scaleX;
		y2 = y2 - scaleY;

		// Reflect across the y axis
		y2 = -y2;

		int dx, dy, D, inc0, inc1;

		dx = x2 - x1;
		dy = y2 - y1;
		D = 2 * dy - dx;
		inc0 = 2 * dy;
		inc1 = 2 * (dy - dx);
		putPixel(tempX1, tempY1);

		while (x1 < x2)
		{
			if (D <= 0)
			{
				D = D + inc0;
			}
			else
			{
				D = D + inc1;
				y1 = y1 + 1;
			}
			x1 = x1 + 1;
			QuadrantFourRepresentation(x1, y1, scaleX, scaleY);
		}
	}

	// Quadrant 5 Case
	if (x2 < x1 && y2 < y1 && std::abs(y2 - y1) > std::abs(x2 - x1))
	{
		std::cout << "Quadrant 5 Case" << std::endl;

		// Map coordinates to Cartesian Coordinates
		int tempX1, tempY1, tempX2, tempY2, scaleX, scaleY;
		tempX1 = x1;
		tempY1 = y1;
		tempX2 = x2;
		tempY2 = y2;

		// Swap Coordinates
		x1 = y1;
		y1 = tempX1;
		x2 = y2;
		y2 = tempX2;

		scaleX = x1;
		scaleY = y1;

		x1 = x1 - scaleX;
		y1 = y1 - scaleY;
		x2 = x2 - scaleX;
		y2 = y2 - scaleY;

		// Reflect Coordinates about the Origin for drawing
		x2 = -x2;
		y2 = -y2;

		int dx, dy, D, inc0, inc1;

		dx = x2 - x1;
		dy = y2 - y1;
		D = 2 * dy - dx;
		inc0 = 2 * dy;
		inc1 = 2 * (dy - dx);
		putPixel(tempX1, tempY1);

		while (x1 < x2)
		{
			if (D <= 0)
			{
				D = D + inc0;
			}
			else
			{
				D = D + inc1;
				y1 = y1 + 1;
			}
			x1 = x1 + 1;
			QuadrantFiveRepresentation(x1, y1, scaleX, scaleY);
		}



	}

	// Quadrant 6 Case
	if (x2 < x1 && y2 < y1 && std::abs(y2 - y1) < std::abs(x2 - x1))
	{
		std::cout << "Quadrant 6 Case" << std::endl;

		// Map Coordinates to Cartesian Coordinates
		int tempX1, tempY1, tempX2, tempY2, scaleX, scaleY;

		tempX1 = x1;
		tempY1 = y1;
		tempX2 = x2;
		tempY2 = y2;

		scaleX = x1;
		scaleY = y1;

		x1 = x1 - scaleX;
		y1 = y1 - scaleY;
		x2 = x2 - scaleX;
		y2 = y2 - scaleY;

		// Reflect over origin
		x2 = -x2;
		y2 = -y2;

		int dx, dy, D, inc0, inc1;

		dx = x2 - x1;
		dy = y2 - y1;
		D = 2 * dy - dx;
		inc0 = 2 * dy;
		inc1 = 2 * (dy - dx);
		putPixel(tempX1, tempY1);

		while (x1 < x2)
		{
			if (D <= 0)
			{
				D = D + inc0;
			}
			else
			{
				D = D + inc1;
				y1 = y1 + 1;
			}
			x1 = x1 + 1;
			QuadrantSixRepresentation(x1, y1, scaleX, scaleY);
		}

	}

	// Quadrant 7 Case
	if (x2 < x1 && y2 > y1 && std::abs(y2 - y1) < std::abs(x2 - x1))
	{
		std::cout << "Quadrant 7 Case" << std::endl;

		int tempX1, tempY1, tempX2, tempY2, scaleX, scaleY;

		// Map coordinates to Cartesian Coordinates
		tempX1 = x1;
		tempY1 = y1;
		tempX2 = x2;
		tempY2 = y2;

		scaleX = x1;
		scaleY = y1;
		
		x1 = x1 - scaleX;
		y1 = y1 - scaleY;
		x2 = x2 - scaleX;
		y2 = y2 - scaleY;

		// Reflect Across Y axis
		x2 = -x2;

		int dx, dy, D, inc0, inc1;

		dx = x2 - x1;
		dy = y2 - y1;
		D = 2 * dy - dx;
		inc0 = 2 * dy;
		inc1 = 2 * (dy - dx);
		putPixel(tempX1, tempY1);

		while (x1 < x2)
		{
			if (D <= 0)
			{
				D = D + inc0;
			}
			else
			{
				D = D + inc1;
				y1 = y1 + 1;
			}
			x1 = x1 + 1;
			QuadrantSevenRepresentation(x1, y1, scaleX, scaleY);
		}


	}

	// Quadrant 8 Case
	if (x2 < x1 && y2 > y1 && std::abs(y2 - y1) > std::abs(x2 - x1))
	{
		std::cout << "Quadrant 8 Case" << std::endl;

		// Map Screen Coordinates to Cartesian Coordinates
		int tempX1, tempY1, tempX2, tempY2, scaleX, scaleY;
		tempX1 = x1;
		tempY1 = y1;
		tempX2 = x2;
		tempY2 = y2;

		x1 = y1;
		y1 = tempX1;
		x2 = y2;
		y2 = tempX2;

		x1 = x1 - scaleX;
		y1 = y1 - scaleY;
		x2 = x2 - scaleX;
		y2 = y2 - scaleY;

		// Reflect Across X-Axis
		y2 = -y2;

		int dx, dy, D, inc0, inc1;

		//dx = x2 - x1;
		//dy = y2 - y1;
		//D = 2 * dy - dx;
		//inc0 = 2 * dy;
		//inc1 = 2 * (dy - dx);
		//putPixel(tempX1, tempY1);

		//while (x1 < x2)
		//{
		//	if (D <= 0)
		//	{
		//		D = D + inc0;
		//	}
		//	else
		//	{
		//		D = D + inc1;
		//		y1 = y1 + 1;
		//	}
		//	x1 = x1 + 1;
		//	QuadrantEightRepresentation(x1, y1, scaleX, scaleY);
		//}
	}


}

void CirclePoints(int xCoord, int yCoord)
{
	putPixel(xCoord, yCoord);
	putPixel(yCoord, xCoord);
	putPixel(xCoord, -yCoord);
	putPixel(yCoord, -xCoord);
	putPixel(-xCoord, yCoord);
	putPixel(-yCoord, xCoord);
	putPixel(-xCoord, -yCoord);
	putPixel(-yCoord, -xCoord);
}

void drawCircle(int x0, int y0, int R)
{
	// TODO: part of Homework Task 2
	// This function should draw a circle,
	// where pixel (x0, y0) is the center of the circle and R is the radius

	int x, y, D;

	x = 0;
	y = R;
	D = 1 - R;

	CirclePoints(0, R);

	while (y > x)
	{
		if (D < 0)
		{
			D = D + 2 * x + 3;
		}
		else
		{
			D = D + 2 * (x - y) + 5;
			y = y - 1;
		}
		x = x + 1;
		CirclePoints(x, y);

	}
}

struct line
{
	int x1, x2, y1, y2;
	// TODO: part of Homework Task 3
	// This function should initialize the variables of struct line
	void init() { }
	// This function should update the values of member variables and draw a line when 2 points are clicked. 
	void AddPoint(int x, int y) { }
};

struct circle
{
	int x0, y0, R;
	// TODO: part of Homework Task 3
	// This function should initialize the variables of struct circle
	void init() { }
	// This function should update the values of member variables and draw a circle when 2 points are clicked
	// The first clicked point should be the center of the circle
	// The second clicked point should be a point on the circle
	void AddPoint(int x, int y) { }
};

void glfwErrorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error " << error << ": " << description << std::endl;
	exit(1);
}

void glfwKeyCallback(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
{
	if (p_key == GLFW_KEY_ESCAPE && p_action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(g_window, GL_TRUE);
	}
	else if (p_key == GLFW_KEY_L && p_action == GLFW_PRESS)
	{
		std::cout << "Line mode" << std::endl;
		// TODO: part of Homework Task 3
		// This part switch on the line mode
	}
	else if (p_key == GLFW_KEY_C && p_action == GLFW_PRESS)
	{
		std::cout << "Circle mode" << std::endl;
		// TODO: part of Homework Task 3
		// This part should switch on the circle mode
	}
}

//!GLFW mouse callback
int xCoord1, yCoord1, xCoord2, yCoord2;

void glfwMouseButtonCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods)
{
	double xpos, ypos;
	glfwGetCursorPos(p_window, &xpos, &ypos);
	ypos = g_windowHeight - ypos;
	if (p_button == GLFW_MOUSE_BUTTON_LEFT && p_action == GLFW_PRESS) 
	{
		std::cout << "You clicked pixel: " << xpos << ", " << ypos << std::endl;
		// TODO: part of Homework Task 3
		std::cout << counter << std::endl;
		if (counter == 0)
		{
			//std::cout << "hit the counter" << std::endl;
			xCoord1 = xpos;
			yCoord1 = ypos;
			counter = counter + 1;
		}
		else
		{
			xCoord2 = xpos;
			yCoord2 = ypos;
			drawLine(xCoord1, yCoord1, xCoord2, yCoord2);
			counter = 0;
		}

		



	}
}

//-------------------------------------------------------------------------------

struct color
{
	unsigned char r, g, b;
};

int ReadLine(FILE *fp, int size, char *buffer)
{
	int i;
	for (i = 0; i < size; i++) {
		buffer[i] = fgetc(fp);
		if (feof(fp) || buffer[i] == '\n' || buffer[i] == '\r') {
			buffer[i] = '\0';
			return i + 1;
		}
	}
	return i;
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
	glfwSetMouseButtonCallback(g_window, glfwMouseButtonCallback);

	// Make the window's context current
	glfwMakeContextCurrent(g_window);

	// turn on VSYNC
	glfwSwapInterval(1);
}

void initGL()
{
	glClearColor(1.f, 1.f, 1.f, 1.0f);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawPixels(g_image_width, g_image_height, GL_LUMINANCE, GL_FLOAT, &g_image[0]);
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

void initImage()
{
	g_image.resize(g_image_width * g_image_height);
}

bool writeImage()
{
	std::vector<color> tmpData;
	tmpData.resize(g_image_width * g_image_height);

	for (int i = 0; i < g_image_height; i++)
	{
		for (int j = 0; j < g_image_width; j++)
		{
			// make sure the value will not be larger than 1 or smaller than 0, which might cause problem when converting to unsigned char
			float tmp = g_image[i* g_image_width + j];
			if (tmp < 0.0f)	tmp = 0.0f;
			if (tmp > 1.0f)	tmp = 1.0f;

			tmpData[(g_image_height - i - 1)* g_image_width + j].r = unsigned char(tmp * 255.0);
			tmpData[(g_image_height - i - 1)* g_image_width + j].g = unsigned char(tmp * 255.0);
			tmpData[(g_image_height - i - 1)* g_image_width + j].b = unsigned char(tmp * 255.0);
		}
	}

	FILE *fp = fopen("data/out.ppm", "wb");
	if (!fp) return false;

	fprintf(fp, "P6\r");
	fprintf(fp, "%d %d\r", g_image_width, g_image_height);
	fprintf(fp, "255\r");
	fwrite(tmpData.data(), sizeof(color), g_image_width * g_image_height, fp);
	fclose(fp);

	return true;
}

void drawImage()
{	
	
	//drawLine(150, 10, 450, 10); // horizontal line
	//drawLine(150, 310, 450, 310); // horizontal line
	//drawLine(150, 10, 150, 310); // vertical line
	//drawLine(450, 10, 450, 310); // vertical line
	//drawLine(150, 310, 300, 410); // positive line
	//drawLine(300, 410, 450, 310); // negative line


	//drawLine(0, 200, 600, 200);

	// New Test Cases
	//drawLine(300, 200, 400, 500); // Quadrant 1 Test Case
	//drawLine(300, 200, 500, 300); // Quadrant 2 Test Case
	//drawLine(300, 200, 600, 100); // Quadrant 3 Test Case
	//drawLine(300, 500, 500, 200); // Quadrant 4 Test Case
	//drawLine(200, 400, 100, 50); // Quadrant 5 Test Case
	//drawLine(300, 200, 100, 50); // Quadrant 6 Test Case
	//drawLine(500, 100, 300, 200); // Quadrant 7 Test Case
	//drawLine(200, 200, 100, 500); // Quadrant 8 Test Case

	//drawLine(300, 600, 300, 100); // STILL HAVE YET TO FIGURE OUT THIS TEST CASE


	//drawCircle(500, 500, 50);
}

int main()
{
	initImage();
	drawImage();
	writeImage();

	// render loop
	initWindow();
	initGL();
	renderLoop();

	return 0;
}
