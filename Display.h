#pragma once

#include "Data.h"

void display(void);

int getFPS();

void drawPlane();
void display(void);
void processInput(float);

void reshape(int width, int height);
void setProjection(int width, int height);
void zoomOrt(float distance);
void keyboard(unsigned char key, int x, int y);