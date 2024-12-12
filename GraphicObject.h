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


// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ОДНОГО ГРАФИЧЕСКОГО ОБЪЕКТА
class GraphicObject
{
public:
	// Конструктор
	GraphicObject();

	// Установка и получение позиции объекта
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();

	// Установка и получения угла поворота в градусах
	// поворот осуществляется в горизонтальной плоскости 
	// вокруг оси Oy по часовой стрелке
	void setAngle(float grad);
	float getAngle();

	// Установка текущего цвета объекта
	void setСolor(glm::vec3 color);
	glm::vec3 getColor();

	void setScale(float scale);

	// Установка используемого материала
	void setMaterial(std::shared_ptr<PhongMaterial> material);

	// Установка используемого меша
	void setMesh(std::shared_ptr<Mesh> mesh);

	// Вывести объект
	void draw();

private:
	// Позиция объекта в глобальной системе координат
	glm::vec3 position;
	// Угол поворота в горизонтальной плоскости (в градусах)
	float angle;
	// Цвет модели
	glm::vec3 color;
	// Матрица модели (расположение объекта) - чтоб не вычислять каждый раз
	GLfloat modelMatrix[16];
	// Используемый материал
	std::shared_ptr<PhongMaterial> material;
	// Используемый меш
	std::shared_ptr<Mesh> mesh;
	// Размер модели
	float scale;
private:
	// расчет матрицы modelMatrix на основе position и angle
	void recalculateModelMatrix();
};