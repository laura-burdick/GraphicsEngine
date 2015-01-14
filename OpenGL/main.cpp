#pragma warning(disable:4996) //so that I can use copy over Microsoft's deprecation

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

const int NUM_POINTS = 100000;

void init();
void renderScene();
static char* readShaderSource(const char* shaderFile);
GLuint InitShader(const char* vShaderFile, const char* fShaderFile);

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

	GLuint program = InitShader("VertexShader.glsl", "FragmentShader.glsl");
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

static char* readShaderSource(const char* shaderFile) {
	ifstream fin(shaderFile);
	if(fin.fail()) {
		cout << "Error opening file " << shaderFile << endl;
		return NULL;
	}

	string shaderText = "";
	char c;
	fin.get(c);
	while(!fin.eof()) {
		shaderText += c;
		fin.get(c);
	}

	fin.close();

	char* ret = new char[shaderText.size() + 1];
	copy(shaderText.begin(),shaderText.end(),ret);
	ret[shaderText.size()] = '\0';

	return ret;
}

GLuint InitShader(const char* vShaderFile, const char* fShaderFile) {
	struct Shader {
		const char* filename;
		GLenum type;
		GLchar* source;
	} shaders[2] = {
		{ vShaderFile, GL_VERTEX_SHADER, NULL },
		{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
	};

	GLuint program = glCreateProgram();

	for(int i=0; i<2; ++i) {
		Shader& s = shaders[i];
		s.source = readShaderSource(s.filename);
		if(shaders[i].source == NULL) {
			cout << "Failed to read " << s.filename << endl;
			return 0;
			//exit(EXIT_FAILURE);
		}

		GLuint shader = glCreateShader(s.type);
		glShaderSource(shader, 1, (const GLchar**) &s.source, NULL);
		glCompileShader(shader);

		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if(!compiled) {
			cout << s.filename << " failed to compile: " << endl;
			GLint logSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetShaderInfoLog(shader, logSize, NULL, logMsg);
			cout << logMsg << endl;
			delete [] logMsg;
			return 0;
			//exit(EXIT_FAILURE);
		}

		delete [] s.source;

		glAttachShader(program, shader);
	}

	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if(!linked) {
		cout << "Shader program failed to link" << endl;
		GLint logSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		cout << logMsg << endl;
		delete [] logMsg;
		return 0;
		//exit(EXIT_FAILURE);
	}

	glUseProgram(program);
	return program;
}