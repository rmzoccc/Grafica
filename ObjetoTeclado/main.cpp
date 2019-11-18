#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

using namespace std;

double x = 0;
double y = 0;
double amountMoveH = 0;
double amountMoveV = 0;

bool moveObject = false;

void controls(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(action == GLFW_PRESS){
		if(key == GLFW_KEY_ESCAPE){
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		else if(key == GLFW_KEY_RIGHT){
			amountMoveH = 0.1;
			moveObject = true;
		}
		else if(key == GLFW_KEY_LEFT){
			amountMoveH = -0.1;
			moveObject = true;
		}
		else if(key == GLFW_KEY_UP){
			amountMoveV = 0.1;
			moveObject = true;
		}
		else if(key == GLFW_KEY_DOWN){
			amountMoveV = -0.1;
			moveObject = true;
		}
	}
	else if(action == GLFW_RELEASE){
		if(key == GLFW_KEY_RIGHT){
			amountMoveH = 0;
			moveObject = false;
		}
		else if(key == GLFW_KEY_LEFT){
			amountMoveH = 0;
			moveObject = false;
		}
		else if(key == GLFW_KEY_UP){
			amountMoveV = 0;
			moveObject = false;
		}
		else if(key == GLFW_KEY_DOWN){
			amountMoveV = 0;
			moveObject = false;
		}
	}
}

void drawCube() {
	GLfloat vertices[] = {
		-1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
		1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
		-1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
		-1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
	};

	GLfloat colors[] = {
		0, 0, 0,   0, 0, 0,   0, 0, 0,   0, 0, 0,
		1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,
		0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,
		0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,
		1, 1, 0,   1, 1, 0,   1, 1, 0,   1, 1, 0,
		1, 0, 1,   1, 0, 1,   1, 0, 1,   1, 0, 1
	};

	static float alpha = 0;
	glRotatef(alpha, 0.5, 1, 0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	alpha += 1;
}

void display( GLFWwindow* window ) {
	int i = 0;
	while(!glfwWindowShouldClose(window)) {

		GLint windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);

		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
		gluPerspective( 60, (double)windowWidth / (double)windowHeight, 0.1, 100 );


		if(moveObject){
			x += amountMoveH;
			y += amountMoveV;
		}
		glTranslatef(x, y, -5);
		drawCube();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main(int argc, char** argv) {
	if(!glfwInit()){
		cout<<"Cannot initialize GLFW\n";
	}
	
	GLFWwindow* window = glfwCreateWindow(1024, 620, "Move Object", NULL, NULL);

	if(window == NULL){
		cout<<"Cannot open GLFW window.\n";
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, controls);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	if( window != NULL ) {
		display( window );
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}