#include "Data.h"
#include "Display.h"
#include "Simulation.h"

void main(int argc, char** argv)
{
	// инициализация библиотеки DevIL для загрузки изображений 
	ilInit();
	iluInit();
	ilutInit();

	// инициализация библиотеки GLUT
	glutInit(&argc, argv);

	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// СОЗДАНИЕ ОКНА:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 10);
	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// 3. создаем окно
	glutCreateWindow("Laba_09");

	// инициализация GLEW 
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Error: %s\n", glewGetErrorString(err));
	}
	printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	// проверка поддержки расширения для работы с буфером VBO 
	if (GLEW_ARB_vertex_buffer_object) {
		printf("VBO is supported\n");
	};

	// ПОЛУЧЕНИЕ ИНФОРМАЦИИ ОБ OPENGL 
	printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
	printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
	printf("GL_VERSION = %s\n\n", glGetString(GL_VERSION));

	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(reshape);
	// устанавливаем функцию, которая будет вызваться максимально часто
	glutIdleFunc(simulation);

	// ИНИЦИАЛИЗАЦИЯ ДАННЫХ, НЕОБХОДИМЫХ ДЛЯ РАБОТЫ ПРОГРАММЫ:
	initData();

	// основной цикл обработки сообщений ОС
	glutMainLoop();
};