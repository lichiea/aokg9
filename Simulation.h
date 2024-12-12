#pragma once

#include "Data.h"

// получение времени симул€ции в секундах
float getSimulationTime();

// симул€ци€ камеры
/// void cameraSimulation(float simulationTime);

// симул€ци€ всех игровых объектов
void gameObjectsSimulation(float simulationTime);

// перемещение гг (распределение сообщений)
void movePlayer();



void simulation();

bool isCellOccupied(glm::ivec2 position);

MoveDirection chooseNewMoveDirection(glm::ivec2 position, MoveDirection PrevDirection);

// симул€ци€ монстров 
void monstersSimulation(float simulationTime);