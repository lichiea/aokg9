#pragma once

#include <windows.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
using namespace glm;
// КЛАСС ДЛЯ РАБОТЫ С КАМЕРОЙ
class Camera
{
public:
	// êîíñòðóêòîðû
	Camera();
	// óñòàíîâêà è ïîëó÷åíèå ïîçèöèè êàìåðû
	void setPosition(vec3 position);
	vec3 getPosition();
	float getAngleX();
	float getAngleY();
	float getR();
	void rotateLeftRight(float degree);
	void rotateUpDown(float degree);
	void zoomInOut(float distance);
	//void zoomOrt(float distance);

	void apply();
	~Camera() {};
private:

	void recalculatePosition();
private:

	float r;
	float angleX;
	float angleY;
	vec3 position;
};