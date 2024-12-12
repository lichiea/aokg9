#pragma once

#include <windows.h>

#include <string>
#include <fstream>

#include "rapidjson/document.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

// ����� ��� ������ � ����������
class PhongMaterial
{
public:
	// ����������� �� ���������
	PhongMaterial();

	// ������� ���������� ���������
	void setAmbient(glm::vec4 color);
	void setDiffuse(glm::vec4 color);
	void setSpecular(glm::vec4 color);
	void setEmission(glm::vec4 color);
	void setShininess(float p);

	glm::vec4 getAmbient();
	glm::vec4 getDiffuse();
	glm::vec4 getSpecular();
	glm::vec4 getEmission();
	float getShininess();

	// �������� ���������� ��������� �� �������� ���������� �����
	void load(std::string filename);

	// ��������� ���� ���������� ���������
	void apply();

private:
	// ������� ������������ 
	glm::vec4 ambient;
	// ��������� ������������
	glm::vec4 diffuse;
	// ���������� ������������
	glm::vec4 specular;
	// ������������
	glm::vec4 emission;
	// ������� ����������������
	float shininess;
};