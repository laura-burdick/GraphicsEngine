#include "GameModels.h"
#include "VertexFormat.h"

using namespace Models;

GameModels::~GameModels() {
	map<string,Model>::iterator it;
	for(it=gameModelList.begin(); it!=gameModelList.end(); ++it) {
		//delete VAO and VBOs
		unsigned int* p = &it->second.vao;
		glDeleteVertexArrays(1,p);
		glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
		it->second.vbos.clear();
	}
	gameModelList.clear();
}

void GameModels::createTriangleModel(const GLuint& program, const string& gameModelName) {
	unsigned int vao;
	unsigned int vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(vec3( 0.25, -0.25, 0.0),vec4( 0, 1, 0, 1)));
	vertices.push_back(VertexFormat(vec3(-0.25, -0.25, 0.0),vec4( 0, 1, 0, 1)));
	vertices.push_back(VertexFormat(vec3( 0.25, 0.25, 0.0),vec4( 0, 1, 0, 1)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	GLuint posLocation = glGetAttribLocation(program, "in_position");
	glEnableVertexAttribArray(posLocation);
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	GLuint colLocation = glGetAttribLocation(program, "in_color");
	glEnableVertexAttribArray(colLocation);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)12);

	Model myModel;
	myModel.vao = vao;
	myModel.vbos.push_back(vbo);
	gameModelList[gameModelName] = myModel;
}
	
void GameModels::deleteModel(const string& gameModelName) {
	Model model = gameModelList[gameModelName];
	unsigned int p = model.vao;
	glDeleteVertexArrays(1, &p);
	glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
	model.vbos.clear();
	gameModelList.erase(gameModelName);
}
		
unsigned int GameModels::getModel(const string& gameModelName) {
	return gameModelList[gameModelName].vao;
}