#ifndef __VERTEX_FORMAT_H
#define __VERTEX_FORMAT_H

#include "glm/glm.hpp"
using glm::vec3;
using glm::vec4;

struct VertexFormat {
	vec3 position;
	vec4 color;

	VertexFormat(const vec3 &pos, const vec4 &color) {
		position = pos;
		this->color = color;
	}
};

#endif