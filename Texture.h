#pragma once

#include <windows.h>

#include <glew.h>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <string>
#include <vector>
#include <iostream>

// ������������ ��� ����������� ������ ���������� 
enum class TextureFilter {
	POINT,
	// �������� 
	BILINEAR,
	TRILINEAR,
	ANISOTROPIC
};

// ����� ��� ������ � ��������� 
class Texture
{
public:
	// �������� �������� �� �������� ����� 
	void load(std::string filename);
	// ���������� �������� (�������� � ����������� ����� � ��������� ����������) 
	void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);
	// ���������� ��������������� ��� ���� ���������� ������ 
	static void disableAll();
private:
	// ������������� (������) ����������� ������� 
	GLuint texIndex;
};