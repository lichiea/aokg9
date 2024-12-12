#include "GraphicObject.h"

GraphicObject::GraphicObject()
{
	position = glm::vec3(0, 0, 0);
	angle = 0;
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	material = nullptr;
	scale = 1.0f;
}

void GraphicObject::setPosition(glm::vec3 position)
{
	this->position = position;

	recalculateModelMatrix();
}

glm::vec3 GraphicObject::getPosition()
{
	return position;
}

void GraphicObject::setAngle(float grad)
{
	this->angle = grad;

	recalculateModelMatrix();
}

float GraphicObject::getAngle()
{
	return angle;
}

void GraphicObject::setСolor(glm::vec3 color)
{
	this->color = color;
}

glm::vec3 GraphicObject::getColor()
{
	return color;
}

void GraphicObject::setMaterial(std::shared_ptr<PhongMaterial> material)
{
	this->material = material;
}

void GraphicObject::setMesh(std::shared_ptr<Mesh> mesh)
{
	this->mesh = mesh;
}

void GraphicObject::setScale(float scale)
{
	this->scale = scale;
	recalculateModelMatrix();
}

// расчет матрицы modelMatrix на основе position и angle
void GraphicObject::recalculateModelMatrix()
{
	modelMatrix[0] = cos(glm::radians(angle)) * scale;
	modelMatrix[1] = 0;
	modelMatrix[2] = sin(glm::radians(angle));
	modelMatrix[3] = 0;

	modelMatrix[4] = 0;
	modelMatrix[5] = scale;
	modelMatrix[6] = 0;
	modelMatrix[7] = 0;

	modelMatrix[8] = -sin(glm::radians(angle));
	modelMatrix[9] = 0;
	modelMatrix[10] = -cos(glm::radians(angle)) * scale;
	modelMatrix[11] = 0;

	modelMatrix[12] = position[0];
	modelMatrix[13] = position[1];
	modelMatrix[14] = position[2];
	modelMatrix[15] = 1;
}

// вывести объект
void GraphicObject::draw()
{
	glColor3f(color.r, color.g, color.b);

	if (material != nullptr) {
		material->apply();
	}

	glPushMatrix();
	glMultMatrixf(modelMatrix);
	
	if (mesh != nullptr)
	{
		mesh->draw();
	}

	glPopMatrix();
}