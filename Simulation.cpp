#include "Simulation.h"

float timeElapsed = 0;

// функция симуляции - вызывается максимально часто
// через заранее неизвестные промежутки времени
// для чего регистрируется с помощью glutIdleFunc 
void simulation()
{
	// определение времени симуляции
	simulationTime = getSimulationTime();
	timeElapsed += simulationTime;
	if (timeElapsed >= 0.5f)
	{

		timeElapsed -= 0.5f;
	}


	// симуляция всех игровых объектов (их плавное перемещение)
	gameObjectsSimulation(simulationTime);

	// симуляция монстров 
	monstersSimulation(simulationTime);
	
	// перемещение главного героя (распределение сообщений)
	movePlayer();

	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
};

bool isCellOccupied(glm::ivec2 position)
{
	for (int i = 0; i < 3; i++)
	{
		if (monsters[i]->getPosition() == position)
		{
			return true;
		}
	}

	return false;
}

MoveDirection chooseNewMoveDirection(glm::ivec2 position, MoveDirection PrevDirection)
{
	std::vector<MoveDirection> possibleDirs;

	int x = position.x;
	int y = position.y;

	if (y > 0 && passabilityMap[x][y - 1] == 0 && !isCellOccupied(glm::ivec2(x, y - 1)) && PrevDirection != MoveDirection::DOWN)
	{
		possibleDirs.push_back(MoveDirection::UP);
	}

	if (y < 20 && passabilityMap[x][y + 1] == 0 && !isCellOccupied(glm::ivec2(x, y + 1)) && PrevDirection != MoveDirection::UP)
	{
		possibleDirs.push_back(MoveDirection::DOWN);
	}

	if (x > 0 && passabilityMap[x - 1][y] == 0 && !isCellOccupied(glm::ivec2(x - 1, y)) && PrevDirection != MoveDirection::RIGHT)
	{
		possibleDirs.push_back(MoveDirection::LEFT);
	}

	if (x < 20 && passabilityMap[x + 1][y] == 0 && !isCellOccupied(glm::ivec2(x + 1, y)) && PrevDirection != MoveDirection::LEFT)
	{
		possibleDirs.push_back(MoveDirection::RIGHT);
	}

	if (!possibleDirs.empty())
		return possibleDirs[rand() % possibleDirs.size()];

	switch (PrevDirection)
	{
	case MoveDirection::UP: 
		if (!isCellOccupied(glm::ivec2(x, y + 1)) && passabilityMap[x][y + 1] == 0)
			return MoveDirection::DOWN;
		else
			return MoveDirection::STOP;
	case MoveDirection::DOWN: 
		if (!isCellOccupied(glm::ivec2(x, y - 1)) && passabilityMap[x][y - 1] == 0)
			return MoveDirection::UP;
		else
			return MoveDirection::STOP;
	case MoveDirection::LEFT: 
		if (!isCellOccupied(glm::ivec2(x + 1, y)) && passabilityMap[x + 1][y] == 0)
			return MoveDirection::RIGHT;
		else
			return MoveDirection::STOP;
	case MoveDirection::RIGHT:
		if (!isCellOccupied(glm::ivec2(x - 1, y)) && passabilityMap[x - 1][y] == 0)
			return MoveDirection::LEFT;
		else
			return MoveDirection::STOP;
	default: return MoveDirection::STOP;
	}
}

// симуляция монстров 
void monstersSimulation(float simulationTime)
{
	for (int i = 0; i < 3; i++)
	{
		if (!monsters[i]->isMoving())
		{
			MoveDirection newDirection = chooseNewMoveDirection(monsters[i]->getPosition(), monsters[i]->getPrevMoveDirection());
			monsters[i]->move(newDirection);
		}
		if (monsters[i]->getPosition() == player->getPosition())
			player->kill();
		monsters[i]->simulate(simulationTime);
	}
}

void movePlayer()
{
	if (!player->isMoving() && player->isAlife())
	{
		glm::ivec2 pos = player->getPosition();
		if (GetAsyncKeyState(0x44))
		{
			if (passabilityMap[pos.x][pos.y - 1] == 0)
				player->move(MoveDirection::UP);
			else if (passabilityMap[pos.x][pos.y - 1] == 1 && passabilityMap[pos.x][pos.y - 2] == 0 && !isCellOccupied(glm::ivec2(pos.x, pos.y - 2)))
			{
				passabilityMap[pos.x][pos.y - 2] = 1;
				passabilityMap[pos.x][pos.y - 1] = 0;
				
				mapObjects[pos.x][pos.y - 2] = mapObjects[pos.x][pos.y - 1];
				mapObjects[pos.x][pos.y - 1] = nullptr;

				player->move(MoveDirection::UP);
				mapObjects[pos.x][pos.y - 2]->move(MoveDirection::UP);
			}
		}
		else if (GetAsyncKeyState(0x41))
		{
			if (passabilityMap[pos.x][pos.y + 1] == 0)
				player->move(MoveDirection::DOWN);
			else if (passabilityMap[pos.x][pos.y + 1] == 1 && passabilityMap[pos.x][pos.y + 2] == 0 && !isCellOccupied(glm::ivec2(pos.x, pos.y + 2)))
			{
				passabilityMap[pos.x][pos.y + 1] = 0;
				passabilityMap[pos.x][pos.y + 2] = 1;
				
				mapObjects[pos.x][pos.y + 2] = mapObjects[pos.x][pos.y + 1];
				mapObjects[pos.x][pos.y + 1] = nullptr;
				
				player->move(MoveDirection::DOWN);
				mapObjects[pos.x][pos.y + 2]->move(MoveDirection::DOWN);
			}
		}
		else if (GetAsyncKeyState(0x57))
		{
			if (passabilityMap[pos.x - 1][pos.y] == 0)
				player->move(MoveDirection::LEFT);
			else if (passabilityMap[pos.x - 1][pos.y] == 1 && passabilityMap[pos.x - 2][pos.y] == 0 && !isCellOccupied(glm::ivec2(pos.x - 2, pos.y)))
			{
				passabilityMap[pos.x - 1][pos.y] = 0;
				passabilityMap[pos.x - 2][pos.y] = 1;
				
				mapObjects[pos.x - 2][pos.y] = mapObjects[pos.x - 1][pos.y];
				mapObjects[pos.x - 1][pos.y] = nullptr;
				
				player->move(MoveDirection::LEFT);
				mapObjects[pos.x - 2][pos.y]->move(MoveDirection::LEFT);
			}
		}
		else if (GetAsyncKeyState(0x53))
		{
			if (passabilityMap[pos.x + 1][pos.y] == 0)
				player->move(MoveDirection::RIGHT);
			else if (passabilityMap[pos.x + 1][pos.y] == 1 && passabilityMap[pos.x + 2][pos.y] == 0 && !isCellOccupied(glm::ivec2(pos.x + 2, pos.y)))
			{
				passabilityMap[pos.x + 1][pos.y] = 0;
				passabilityMap[pos.x + 2][pos.y] = 1;
				
				mapObjects[pos.x + 2][pos.y] = mapObjects[pos.x + 1][pos.y];
				mapObjects[pos.x + 1][pos.y] = nullptr;
				
				player->move(MoveDirection::RIGHT);
				mapObjects[pos.x + 2][pos.y]->move(MoveDirection::RIGHT);
			}
		}
	}
}

float getSimulationTime()
{
	LARGE_INTEGER tic;
	LARGE_INTEGER frequency;

	QueryPerformanceCounter(&tic);
	QueryPerformanceFrequency(&frequency);

	static LARGE_INTEGER prevTic = tic;

	prevTic.QuadPart = tic.QuadPart - prevTic.QuadPart;

	float time = (float)prevTic.QuadPart / (float)frequency.QuadPart;

	prevTic = tic;

	return time;
}



void gameObjectsSimulation(float simulationTime)
{
	if (player->isAlife())
		player->simulate(simulationTime);
	
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (mapObjects[i][j] != nullptr && mapObjects[i][j]->isMoving())
			{
				mapObjects[i][j]->simulate(simulationTime);
			}
		}
	}
}

