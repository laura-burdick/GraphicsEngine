#ifndef __GAME_MODELS_H
#define __GAME_MODELS_H

#include "Dependencies\glew\glew.h"
#include <vector>
#include <string>
#include <map>
using std::map;
using std::string;
using std::vector;

namespace Models {
	struct Model {
		unsigned int vao;
		vector<unsigned int> vbos;
	};

	class GameModels {
	private:
		map<string,Model> gameModelList;
	public:
		~GameModels();
		void createTriangleModel(const GLuint& program, const string& gameModelName);
		void deleteModel(const string& gameModelName);
		unsigned int getModel(const string& gameModelName);
	};
}

#endif