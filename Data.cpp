#include "Data.h"
using namespace glm;
using namespace std;
//int passabilityMap[21][21] = {
// 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
// 3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
// 3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
// 3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
// 3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
// 3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
// 3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
// 3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
// 3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
// 3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
// 3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
// 3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
// 3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
// 3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
// 3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
// 3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
// 3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
// 3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
// 3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
// 3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
// 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
//};

void makeMap(int** matrix, int rows, int columns) {
	int arr[21][21] = { 0 };

	auto maze = MazeGenerator::generate(20, 20);

	//MazeGenerator::print(maze);

	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 20; i++) {
			arr[i][j] = maze[i][j];
		}
	}

	// Устанавливаем границы
	for (int i = 0; i < 21; ++i) {
		arr[0][i] = 3;
		arr[20][i] = 3;
		arr[i][0] = 3;
		arr[i][20] = 3;
	}
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
			matrix[r][c] = arr[r][c];
}
int passabilityMap[21][21] = { 0 };
float simulationTime;
// фабрика для создания игровых объектов
GameObjectFactory gameObjectFactory;
// все игровые объекты
std::shared_ptr<GameObject> mapObjects[21][21];
std::shared_ptr<GameObject> player;
std::shared_ptr<GameObject> monsters[3];
// графический объект для плоскости (частный случай)
GraphicObject planeGraphicObject;
// используемая камера
Camera camera;
// используемый источник света
Light light;

Texture planeTexture;

// функция для инициализации всех общих данных (камера, объекты и т.д.)
void initData(){

	int** matrix = new int* [21];
	for (int row = 0; row < 21; row++)
		matrix[row] = new int[21];
	makeMap(matrix, 21, 21);
	for (int j = 0; j < 21; j++) {
		for (int i = 0; i < 21; i++) {
			passabilityMap[i][j] = matrix[i][j];
		}
	}

	camera.setPosition(vec3(15, 0, 50));
	light.setPosition(vec4(20.0, 20.0, 15.0, 1.0));
	light.setAmbient(vec4(1.0, 1.0, 1.0, 1.0));
	light.setDiffuse(vec4(1.0, 1.0, 1.0, 1.0));
	light.setSpecular(vec4(1.0, 1.0, 1.0, 1.0));

	// инициализация фабрики (в дальнейшем на основе json-файла)
	gameObjectFactory.init("data\\GameObjectsDescription.json");

	// инициализация объектов сцены
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			switch (passabilityMap[i][j]) {
			case 1:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, i, j);
				break;
			case 2:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, i, j);
				break;
			case 3:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, i, j);
				break;
			default:
				mapObjects[i][j] = nullptr;
				break;
			}
		}
	}
	// инициализация монстров
	monsters[0] = gameObjectFactory.create(GameObjectType::MONSTER, 19, 19);
	monsters[1] = gameObjectFactory.create(GameObjectType::MONSTER, 1, 19);
	monsters[2] = gameObjectFactory.create(GameObjectType::MONSTER, 19, 1);

	// инициализация главного героя
	player = gameObjectFactory.create(GameObjectType::PLAYER, 1, 1);
	// инициализация плоскости
	planeGraphicObject.setPosition(glm::vec3(0, -0.5, 0));
	std::shared_ptr<Mesh> planeMesh = std::make_shared<Mesh>();
	planeMesh->load("data\\meshes\\HighPolyPlane.obj");
	planeGraphicObject.setMesh(planeMesh);
	std::shared_ptr<PhongMaterial> planeMaterial = std::make_shared<PhongMaterial>();
	planeMaterial->load("data\\materials\\PlaneMaterial.txt");
	planeGraphicObject.setMaterial(planeMaterial);

	planeTexture.load("data\\textures\\plane.jpg");


	for (int row = 0; row < 21; row++)
		delete[] matrix[row];
	delete[] matrix;
}