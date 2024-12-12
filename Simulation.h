#pragma once

#include "Data.h"

// ��������� ������� ��������� � ��������
float getSimulationTime();

// ��������� ������
/// void cameraSimulation(float simulationTime);

// ��������� ���� ������� ��������
void gameObjectsSimulation(float simulationTime);

// ����������� �� (������������� ���������)
void movePlayer();



void simulation();

bool isCellOccupied(glm::ivec2 position);

MoveDirection chooseNewMoveDirection(glm::ivec2 position, MoveDirection PrevDirection);

// ��������� �������� 
void monstersSimulation(float simulationTime);