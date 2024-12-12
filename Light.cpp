#include "Light.h"


Light::~Light() {};

void Light::setPosition(vec4 positionk) { this->position = positionk; }
void Light::setAmbient(vec4 color) { this->ambient = color; }
void Light::setDiffuse(vec4 color) { this->diffuse = color; }
void Light::setSpecular(vec4 color) { this->specular = color; }

void Light::apply(GLenum LightNumber) {

    GLfloat globalAmbientColor[] = { 0.2, 0.2, 0.2, 1.0 };

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);

    glEnable(LightNumber);
    glLightfv(LightNumber, GL_AMBIENT, glm::value_ptr(this->ambient));
    glLightfv(LightNumber, GL_DIFFUSE, glm::value_ptr(this->diffuse));
    glLightfv(LightNumber, GL_SPECULAR, glm::value_ptr(this->specular));
    glLightfv(LightNumber, GL_POSITION, glm::value_ptr(this->position));
}