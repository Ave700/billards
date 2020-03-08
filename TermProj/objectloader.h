#pragma once

#include <string>
#include <vector>
#include "glm/glm/vec3.hpp"
#include "glm/glm/vec2.hpp"


bool loadObject(const char* filename, float* vertexArray, float* normalArray, float* uvArray, int numVerts);