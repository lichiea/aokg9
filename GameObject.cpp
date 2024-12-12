#include "GameObject.h"

GameObject::GameObject()
{
	sost = MoveDirection::STOP;
	progress = 0.0f;
	speed = 0.0f;
	alife = 1;
}

GameObject::GameObject(GraphicObject& graphObj)
{
	graphicObject = graphObj;
	position = glm::vec2(0.0f, 0.0f);
	sost = MoveDirection::STOP;
	progress = 0.0f;
	speed = 0.0f;
}

void GameObject::setGraphicObject(const GraphicObject& graphicObject)
{
	this->graphicObject = graphicObject;
}

void GameObject::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

void GameObject::setPosition(glm::ivec2 position)
{
	this->position = position;
}

glm::ivec2 GameObject::getPosition()
{
	return position;
}

void GameObject::move(MoveDirection direction, float speed)
{
	this->speed = speed;
	progress = 0;
	sost = direction;
	switch (direction)
	{
	case MoveDirection::UP:
		this->setPosition(position.x, position.y - 1);
		break;
	case MoveDirection::DOWN:
		this->setPosition(position.x, position.y + 1);
		break;
	case MoveDirection::LEFT:
		this->setPosition(position.x - 1, position.y);
		break;
	case MoveDirection::RIGHT:
		this->setPosition(position.x + 1, position.y);
		break;
	}
}

bool GameObject::isMoving()
{
	return sost != MoveDirection::STOP && progress < 1.0f;
}

void GameObject::simulate(float sec)
{
	glm::vec3 pos = graphicObject.getPosition();
	float displacement = progress - 1;
	switch (sost)
	{
	case MoveDirection::UP:
		graphicObject.setPosition(glm::vec3(pos.x, pos.y, position.y - 10 - displacement));
		break;
	case MoveDirection::DOWN:
		graphicObject.setPosition(glm::vec3(pos.x, pos.y, position.y - 10 + displacement));
		break;
	case MoveDirection::LEFT:
		graphicObject.setPosition(glm::vec3(position.x - 10 - displacement, pos.y, pos.z));
		break;
	case MoveDirection::RIGHT:
		graphicObject.setPosition(glm::vec3(position.x - 10 + displacement, pos.y, pos.z));
		break;
	}
	progress += speed * sec;
	if (progress >= 1.0f)
	{
		prevSost = sost;
		sost = MoveDirection::STOP;
		graphicObject.setPosition(glm::vec3(position.x - 10, pos.y, position.y - 10));
	}
}

void GameObject::draw(void)
{
	graphicObject.draw();
}

void GameObject::kill()
{
	alife = 0;
}

bool GameObject::isAlife()
{
	return alife;
}

MoveDirection GameObject::getPrevMoveDirection()
{
	return prevSost;
}
