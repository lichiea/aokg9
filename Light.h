#pragma once

#include <windows.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
using namespace glm;

using namespace std;
//  À¿—— ƒÀﬂ –¿¡Œ“€ — »—“Œ◊Õ» ŒÃ —¬≈“¿
class Light
{
public:

	Light() :position(vec4(20.0, 20.0, 15.0, 1.0)), ambient(vec4(0.4, 0.0, 0.0, 1.0)), diffuse(vec4(1.0, 0.0, 0.0, 1.0)), specular(vec4(1.0, 1.0, 1.0, 1.0)) {};

	void setPosition(vec4 position);
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);

	void apply(GLenum LightNumber = GL_LIGHT0);
	~Light();
private:

	vec4 position;

	vec4 ambient;

	vec4 diffuse;

	vec4 specular;
};