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

// ���������, ����������� ���� ������� ������������� ����� 
// ������ ������� ����� �������������� ����������, 
// ������ ������� � ���������� ����������
struct Vertex
{
	Vertex(glm::vec3 v, glm::vec2 vt, glm::vec3 vn);
	// �������������� ����������
	GLfloat coord[3];
	// ������ �������
	GLfloat normal[3];
	// ���������� ���������� �������� ����������� ����� 
	GLfloat texCoord[2];
};

// ����� ��� ������ C �����
class Mesh
{
public:
	// �����������
	Mesh();
	// �������� ���� �� ����� � ��������� ������
	void load(std::string filename);
	// ����� ���� (�������� ���� ������ � OpenGL)
	void draw();

	void clear();
private:
	// ���������� ��������  
	int indexCount;
	// ������� (��������������) ������� OpenGL 
	GLuint bufferIds[2];
};
