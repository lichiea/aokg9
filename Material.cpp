#include "Material.h"

PhongMaterial::PhongMaterial()
{
	ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	specular = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	emission = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	shininess = 0.0f;
}

void PhongMaterial::setAmbient(glm::vec4 color)
{
	ambient = color;
}

void PhongMaterial::setDiffuse(glm::vec4 color)
{
	diffuse = color;
}

void PhongMaterial::setSpecular(glm::vec4 color)
{
	specular = color;
}

void PhongMaterial::setEmission(glm::vec4 color)
{
	emission = color;
}

void PhongMaterial::setShininess(float p)
{
	shininess = p;
}

glm::vec4 PhongMaterial::getAmbient()
{
	return ambient;
}

glm::vec4 PhongMaterial::getDiffuse()
{
	return diffuse;
}

glm::vec4 PhongMaterial::getSpecular()
{
	return specular;
}

glm::vec4 PhongMaterial::getEmission()
{
	return emission;
}

float PhongMaterial::getShininess()
{
	return shininess;
}

void PhongMaterial::load(std::string filename)
{
	std::ifstream in;
	in.open(filename);
	std::string Name;
	glm::vec4 color;

	if (in.is_open())
	{
		while (!in.eof())
		{
			in >> Name;
			if (Name != "shininess:")
			{
				in >> color.r >> color.g >> color.b >> color.a;
				if (Name == "diffuse:")
					setDiffuse(color);
				else if (Name == "ambient:")
					setAmbient(color);
				else if (Name == "specular:")
					setSpecular(color);
				else if (Name == "emission:")
					setEmission(color);
			}
			else
			{
				float tmp;
				in >> tmp;
				setShininess(tmp);
			}
		}
		in.close();
	}
}

void PhongMaterial::apply()
{
	GLfloat tmp[] = { ambient.r, ambient.g, ambient.b, ambient.a };
	glMaterialfv(GL_FRONT, GL_AMBIENT, tmp);

	for (int i = 0; i < 4; i++)
		tmp[i] = diffuse[i];
	glMaterialfv(GL_FRONT, GL_DIFFUSE, tmp);

	for (int i = 0; i < 4; i++)
		tmp[i] = specular[i];
	glMaterialfv(GL_FRONT, GL_SPECULAR, tmp);

	for (int i = 0; i < 4; i++)
		tmp[i] = emission[i];
	glMaterialfv(GL_FRONT, GL_EMISSION, tmp);

	glMaterialf(GL_FRONT, GL_SHININESS, GLfloat(shininess));
}