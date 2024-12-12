#include "Display.h"
using namespace glm;
bool isOrthographic = false;
float Sscale = 0.3;


void zoomOrt(float distance) {
	Sscale += distance * 0.05;
	if (Sscale < 0.3) Sscale = 0.3;
	if (Sscale > 2.3) Sscale = 2.3;
	reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}


void setProjection(int width, int height) {
	if (isOrthographic) {
		float aspect = (float)width / height;
		float orthoHeight = 10.0 * Sscale; 
		float orthoWidth = 10.0 * Sscale;
		if (aspect >= 1.0) { glOrtho(-aspect * orthoWidth, aspect * orthoWidth, -orthoHeight, orthoHeight, 0.2, 70.0); }
		else { glOrtho(-orthoWidth, orthoWidth, -orthoHeight / aspect, orthoHeight / aspect, 0.2, 70.0); }

	}
	else {
		gluPerspective(25.0, (float)width / height, 0.2, 70.0);
	}

}
void display()
{
	// отчищаем буфер цвета и буфер глубины
	if (isOrthographic == true) glClearColor(0.00, 0.00, 0.00, 1.0);
	else glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// включаем режим расчета освещения
	glEnable(GL_LIGHTING);

	// устанавливаем камеру
	camera.apply();

	// устанавливаем источник света
	light.apply(GL_LIGHT0);

	// выводим все игровые объекты
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (passabilityMap[i][j] != 0)
				mapObjects[i][j]->draw();
		}
	}

	for (int i = 0; i < 3; i++)
		monsters[i]->draw();

	if (player->isAlife())
		player->draw();

	drawPlane();
	
	// смена переднего и заднего буферов
	glutSwapBuffers();
	processInput(simulationTime);
	// выводим заголовок окна
	char windowTitle[128];
	int FPS = getFPS();
	sprintf_s(windowTitle, 128, "Laba_09 [%i FPS]", FPS);
	glutSetWindowTitle(windowTitle);
};

int getFPS()
{
	static int FPS = 0;
	static int frameCnt = 0;
	frameCnt++;

	static float elapsedTime = 0;

	LARGE_INTEGER tic;
	LARGE_INTEGER frequency;

	QueryPerformanceCounter(&tic);
	QueryPerformanceFrequency(&frequency);

	static LARGE_INTEGER prevTic = tic;

	prevTic.QuadPart = tic.QuadPart - prevTic.QuadPart;

	elapsedTime += (float)prevTic.QuadPart / (float)frequency.QuadPart;

	prevTic = tic;

	if (elapsedTime >= 0.5f)
	{
		FPS = (float)frameCnt / elapsedTime;
		elapsedTime = 0.0f;
		frameCnt = 0;
	}

	return FPS;
}

// вывод горизонтальной плоскости (основание уровня) 
void drawPlane()
{
	// выбираем активный текстурный блок 
	glActiveTexture(GL_TEXTURE0);
	// разрешаем текстурирование в выбранном текстурном блоке 
	glEnable(GL_TEXTURE_2D);
	// привязываем текстуру к ранее выбранному текстурному блоку 
	planeTexture.apply();
	// указываем режим наложения текстуры (GL_MODULATE) 
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// выводим плоскость 
	planeGraphicObject.draw();
	// отключаем текстурирование (чтобы все остальные объекты выводились без текстур) 
	Texture::disableAll();
}


void keyboard(unsigned char key, int x, int y) {
	switch (static_cast<char>(key)) {
	case 'w':
		player->move(MoveDirection::UP);

		break;
	case 's':

		player->move(MoveDirection::DOWN);
		break;
	case 'a':
		player->move(MoveDirection::RIGHT);
		break;
	case 'd':
		player->move(MoveDirection::LEFT);
		break;

	}
};

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//setProjection(width, height);
	gluPerspective(25.0, (float)width / height, 0.2, 70.0);
	glMatrixMode(GL_MODELVIEW);
}

void processInput(float sTime) {
	if (GetAsyncKeyState(VK_UP)) {
		camera.rotateUpDown(sTime * 50);
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		camera.rotateUpDown(-50 * sTime);
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		camera.rotateLeftRight(sTime * 50);
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		camera.rotateLeftRight(-50 * sTime);
	}
	if (GetAsyncKeyState(0xBB)) {
		if (isOrthographic) zoomOrt(-50 * sTime);
		else camera.zoomInOut(-50 * sTime);
	}
	if (GetAsyncKeyState(0xBD)) {
		if (isOrthographic) zoomOrt(sTime * 50);
		else camera.zoomInOut(sTime * 50);
	}
	if (GetAsyncKeyState(VK_RBUTTON)) {
		isOrthographic = !isOrthographic; //
		if (isOrthographic == true) cout << "or ";
		else cout << "per ";
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);
		//setProjection(width, height); // 
		reshape(width, height); // 
	}
}
