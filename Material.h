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

// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class PhongMaterial
{
public:
	// конструктор по умолчанию
	PhongMaterial();

	// задание параметров материала
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

	// загрузка параметров материала из внешнего текстового файла
	void load(std::string filename);

	// установка всех параметров материала
	void apply();

private:
	// фоновая составляющая 
	glm::vec4 ambient;
	// диффузная составляющая
	glm::vec4 diffuse;
	// зеркальная составляющая
	glm::vec4 specular;
	// самосвечение
	glm::vec4 emission;
	// степень отполированности
	float shininess;
};