#pragma once

#include <windows.h>

#include <glew.h>

#include <map>
#include <vector>
#include <string>
#include <fstream>

#include "rapidjson/document.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

// Структура, описывающая одну вершину полигональной сетки 
// каждая вершина имеет геометрические координаты, 
// вектор нормали и текстурные координаты
struct Vertex
{
	Vertex(glm::vec3 v, glm::vec2 vt, glm::vec3 vn);
	// геометрические координаты
	GLfloat coord[3];
	// вектор нормали
	GLfloat normal[3];
	// текстурные координаты нулевого текстурного блока 
	GLfloat texCoord[2];
};

// КЛАСС ДЛЯ РАБОТЫ C МЕШЕМ
class Mesh
{
public:
	// конструктор
	Mesh();
	// загрузка меша из файла с указанным именем
	void load(std::string filename);
	// вывод меша (передача всех вершин в OpenGL)
	void draw();

	void clear();
private:
	// количество индексов  
	int indexCount;
	// индексы (идентификаторы) буферов OpenGL 
	GLuint bufferIds[2];
};
