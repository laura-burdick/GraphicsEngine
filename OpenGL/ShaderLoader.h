#ifndef __SHADER_LOADER
#define __SHADER_LOADER

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <string>
using std::string;

namespace Core {

	class ShaderLoader {
	private:
		//reads and returns the contents of a file
		string readShader(char *filename);

		//creates and compiles a shader (vertex or fragment)
		GLuint createShader(GLenum shaderType, string source, char* shaderName);
	public:
		//extracts the shader contents, creates both shaders,
		//loads them into the program which is returned in the rendering loop
		GLuint createProgram(char* vertexShaderFilename, char* fragmentShaderFilename);
	};

}

#endif