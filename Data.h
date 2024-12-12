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

// ����� ������������
extern int passabilityMap[21][21];

// ������ ������� �������� ������������� �� �����
extern std::shared_ptr<GameObject> mapObjects[21][21];

// ����������� ������ ��� ��������� (������� ������)
extern GraphicObject planeGraphicObject;

// �����
extern std::shared_ptr<GameObject> player;

// �������
extern std::shared_ptr<GameObject> monsters[3];

// ������������ ������
extern Camera camera;

// ������������ �������� �����
extern Light light;

// ������������ ���������
extern std::vector<std::shared_ptr<PhongMaterial>> materials;

// ������������ ����
extern std::vector<std::shared_ptr<Mesh>> meshes;

extern Texture planeTexture;

// ������� ��� ������������� ���� ����� ������ (������, ������� � �.�.)
void initData();