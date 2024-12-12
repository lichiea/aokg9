#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <fstream>

#include "GameObject.h"

// ОПРЕДЕЛЕНИЕ ТИПОВ ИГРОВЫХ ОБЪЕКТОВ 
enum class GameObjectType {
	LIGHT_OBJECT,	// легкий игровой объект
	HEAVY_OBJECT,	// тяжелый игровой объект
	BORDER_OBJECT,	// граничный игровой объект
	PLAYER,			// игровой объект для представления игрока
	BOMB,			// игровой объект для представления бомбы
	MONSTER			// игровой объект для представления монстров
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

// КЛАСС ДЛЯ СОЗДАНИЯ ИГРОВЫХ ОБЪЕКТОВ
class GameObjectFactory
{
public:
	// инициализация фабрики:
	// загрузка мешей и установка параметров материала
	bool init(std::string filename);
	// создание нового объекта заданного типа
	std::shared_ptr<GameObject> create(GameObjectType type, int x, int y);
private:
	// меши для каждого типа объекта
	std::vector<std::shared_ptr<Mesh>> meshes;
	// материалы для каждого типа объекта
	std::vector<std::shared_ptr<PhongMaterial>> materials;
};