#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>
using std::cout;
using std::endl;

#include "ShaderLoader.h"
#include "GameModels.h"
using namespace Models;
using namespace Core;

void init();
void renderScene();
void closeCallback();

GLuint program;
GameModels* gameModels;

int main(int argc, char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("OpenGL Window");
	glewInit();
	init();
	
	//register callbacks
	glutDisplayFunc(renderScene);
	glutCloseFunc(closeCallback);

	glutMainLoop();

	delete gameModels;
	glDeleteProgram(program);

	return 0;
}

void init() {
	glEnable(GL_DEPTH_TEST);

	//load and compile shaders
	ShaderLoader shaderLoader;
	program = shaderLoader.createProgram("VertexShader.glsl","FragmentShader.glsl");

	gameModels = new GameModels();
	gameModels->createTriangleModel(program,"triangle1");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,0.0,0.0,1.0);

	glBindVertexArray(gameModels->getModel("triangle1"));
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void closeCallback() {
	cout << "GLUT: Finished" << endl;
	glutLeaveMainLoop();
}