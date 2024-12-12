#pragma once

#include <windows.h>

#include <vector>
#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Mesh.h"
#include "Material.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"


// ����� ��� ������������� ������ ������������ �������
class GraphicObject
{
public:
	// �����������
	GraphicObject();

	// ��������� � ��������� ������� �������
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();

	// ��������� � ��������� ���� �������� � ��������
	// ������� �������������� � �������������� ��������� 
	// ������ ��� Oy �� ������� �������
	void setAngle(float grad);
	float getAngle();

	// ��������� �������� ����� �������
	void set�olor(glm::vec3 color);
	glm::vec3 getColor();

	void setScale(float scale);

	// ��������� ������������� ���������
	void setMaterial(std::shared_ptr<PhongMaterial> material);

	// ��������� ������������� ����
	void setMesh(std::shared_ptr<Mesh> mesh);

	// ������� ������
	void draw();

private:
	// ������� ������� � ���������� ������� ���������
	glm::vec3 position;
	// ���� �������� � �������������� ��������� (� ��������)
	float angle;
	// ���� ������
	glm::vec3 color;
	// ������� ������ (������������ �������) - ���� �� ��������� ������ ���
	GLfloat modelMatrix[16];
	// ������������ ��������
	std::shared_ptr<PhongMaterial> material;
	// ������������ ���
	std::shared_ptr<Mesh> mesh;
	// ������ ������
	float scale;
private:
	// ������ ������� modelMatrix �� ������ position � angle
	void recalculateModelMatrix();
};