#include "Data.h"
#include "Display.h"
#include "Simulation.h"

void main(int argc, char** argv)
{
	// ������������� ���������� DevIL ��� �������� ����������� 
	ilInit();
	iluInit();
	ilutInit();

	// ������������� ���������� GLUT
	glutInit(&argc, argv);

	// ������������� ������� (������ ������)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// �������� ����:
	// 1. ������������� ������� ����� ���� ����
	glutInitWindowPosition(200, 10);
	// 2. ������������� ������ ����
	glutInitWindowSize(800, 600);
	// 3. ������� ����
	glutCreateWindow("Laba_09");

	// ������������� GLEW 
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Error: %s\n", glewGetErrorString(err));
	}
	printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	// �������� ��������� ���������� ��� ������ � ������� VBO 
	if (GLEW_ARB_vertex_buffer_object) {
		printf("VBO is supported\n");
	};

	// ��������� ���������� �� OPENGL 
	printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
	printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
	printf("GL_VERSION = %s\n\n", glGetString(GL_VERSION));

	// ��������� ������� ��������� ������
	// ������������� �������, ������� ����� ���������� ��� ����������� ����
	glutDisplayFunc(display);
	// ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
	glutReshapeFunc(reshape);
	// ������������� �������, ������� ����� ��������� ����������� �����
	glutIdleFunc(simulation);

	// ������������� ������, ����������� ��� ������ ���������:
	initData();

	// �������� ���� ��������� ��������� ��
	glutMainLoop();
};