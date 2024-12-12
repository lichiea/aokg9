#pragma once

#include <windows.h>

#include <glew.h>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <string>
#include <vector>
#include <iostream>

// ПЕРЕЧИСЛЕНИЕ ДЛЯ ОПРЕДЕЛЕНИЯ РЕЖИМА ФИЛЬТРАЦИИ 
enum class TextureFilter {
	POINT,
	// ТОЧЕЧНАЯ 
	BILINEAR,
	TRILINEAR,
	ANISOTROPIC
};

// КЛАСС ДЛЯ РАБОТЫ С ТЕКСТУРОЙ 
class Texture
{
public:
	// загрузка текстуры из внешнего файла 
	void load(std::string filename);
	// применение текстуры (привзяка к текстурному блоку и установка параметров) 
	void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);
	// отключение текстурирования для всех текстурных блоков 
	static void disableAll();
private:
	// идентификатор (индекс) текстурного объекта 
	GLuint texIndex;
};