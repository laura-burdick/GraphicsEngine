#pragma warning(disable:4996) //so that I can use the function copy despite Microsoft's deprecation

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "glm/glm.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using std::copy;
using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using glm::vec2;

#include "ShaderLoader.h"

const int NUM_POINTS = 100000;

void init();
void renderScene();

int main(int argc, char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512,512);

	glutCreateWindow("OpenGL Window");
	glewInit();
	init();
	
	//register callbacks
	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}

void init() {
	vec2 points[NUM_POINTS];

	vec2 vertices[3] = {vec2(-1.0,-1.0), vec2(0.0,1.0), vec2(1.0,-1.0)};

	points[0] = vec2(0.25,0.50);

	for(int i=1; i<NUM_POINTS; ++i) {
		int j=rand() % 3;
		points[i] = (points[i-1]+vertices[j])/2.0f;
	}

	ShaderLoader shaderLoader;
	GLuint program = shaderLoader.createProgram("VertexShader.glsl", "FragmentShader.glsl");
	glUseProgram(program);

	unsigned int vao;
	unsigned int vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint posLocation = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(posLocation);
	glVertexAttribPointer(posLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	/*GLuint colLocation = glGetAttribLocation(program, "in_color");
	glEnableVertexAttribArray(colLocation);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)12);*/

	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_POINTS, 0, NUM_POINTS);
	glFlush();
}