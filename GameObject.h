#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GraphicObject.h"

// �����-������������ ��� �������� ����������� ����������� 
enum class MoveDirection { STOP, LEFT, RIGHT, UP, DOWN };

// ����� ��� ������������� �������� ������� 
class GameObject
{
public:
	// ����������� 
	GameObject();

	GameObject(GraphicObject& graphObj);

	// ��������� ������������� ������������ ������� 
	// ���������� ����������� ����������� ������� ��� ������������ ������������� 
	void setGraphicObject(const GraphicObject& graphicObject);

	// ��������� ���������� ��������� (��� ������������� ������ ��� ��������) 
	void setPosition(int x, int y);
	void setPosition(glm::ivec2 position);

	// ��������� ������� ���������� ��������� 
	glm::ivec2 getPosition();

	// ������ �������� � ��������� ����������� � ��������� ���������  
	// �������� ������������ ������������ ����������� ������ � ������� 
	void move(MoveDirection direction, float speed = 3.0f);
	// �������� �� ��, ��� ������ � ��������� ������ �������� 
	bool isMoving();
	// ��������� �������� ������� (������� ����������� �������) 
	// ����� ���������� ���������� � ������� simulation 
	void simulate(float sec);

	// ����� �������� ������� �� ����� 
	void draw(void);

	void kill();

	bool isAlife();

	MoveDirection getPrevMoveDirection();

private:
	// ����������� ������ (��� ������ �� �����) 
	GraphicObject graphicObject;
	// ���������� ���������� �������� ������� 
	glm::ivec2 position;
	// ��������� ������� (�������� ����������� �����������) 
	MoveDirection sost;
	MoveDirection prevSost;
	// �������� � ����������� (�� 0.0 �� 1.0) 
	float progress;
	// �������� ����������� 
	float speed;

	bool alife;
};