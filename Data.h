#pragma once

#include <windows.h>

#include <memory>
#include <vector>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "GameObject.h"
#include "GraphicObject.h"
#include "Light.h"
#include "Material.h"
#include "GameObjectFactory.h"
#include "Maze.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

extern float simulationTime;

// карта проходимости
extern int passabilityMap[21][21];

// список игровых объектов расположенных на карте
extern std::shared_ptr<GameObject> mapObjects[21][21];

// графический объект для плоскости (частный случай)
extern GraphicObject planeGraphicObject;

// игрок
extern std::shared_ptr<GameObject> player;

// Монстры
extern std::shared_ptr<GameObject> monsters[3];

// используемая камера
extern Camera camera;

// используемый источник света
extern Light light;

// используемые материалы
extern std::vector<std::shared_ptr<PhongMaterial>> materials;

// используемые меши
extern std::vector<std::shared_ptr<Mesh>> meshes;

extern Texture planeTexture;

// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData();