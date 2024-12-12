#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <fstream>

#include "GameObject.h"

// ����������� ����� ������� �������� 
enum class GameObjectType {
	LIGHT_OBJECT,	// ������ ������� ������
	HEAVY_OBJECT,	// ������� ������� ������
	BORDER_OBJECT,	// ��������� ������� ������
	PLAYER,			// ������� ������ ��� ������������� ������
	BOMB,			// ������� ������ ��� ������������� �����
	MONSTER			// ������� ������ ��� ������������� ��������
};

//std::map<std::string, GameObjectType> gameObjectType
//{
//	{"LightObject", GameObjectType::LIGHT_OBJECT}, {"HeavyObject", GameObjectType::HEAVY_OBJECT}, {"BorderObject", GameObjectType::BORDER_OBJECT},
//	{"Player", GameObjectType::PLAYER}, {"Bomb", GameObjectType::BOMB}, {"Monter", GameObjectType::MONSTER}
//};

enum MaterialType
{
	diffuse, ambient, specular, emission, shininess
};

// ����� ��� �������� ������� ��������
class GameObjectFactory
{
public:
	// ������������� �������:
	// �������� ����� � ��������� ���������� ���������
	bool init(std::string filename);
	// �������� ������ ������� ��������� ����
	std::shared_ptr<GameObject> create(GameObjectType type, int x, int y);
private:
	// ���� ��� ������� ���� �������
	std::vector<std::shared_ptr<Mesh>> meshes;
	// ��������� ��� ������� ���� �������
	std::vector<std::shared_ptr<PhongMaterial>> materials;
};