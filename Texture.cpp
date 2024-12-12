#include "Texture.h"

void Texture::load(std::string filename)
{
	// создаем новое "изображение" 
	ILuint imageId; 
	ilGenImages(1, &imageId);

	// задаем текущее "изображение" 
	ilBindImage(imageId);

	// загружаем изображение 
	wchar_t unicodeString[256];
	wsprintf(unicodeString, L"%S", filename.c_str());
	bool result = ilLoadImage(unicodeString);

	// получение параметров загруженной текстуры 
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	int depth = ilGetInteger(IL_IMAGE_DEPTH);
	int format = ilGetInteger(IL_IMAGE_FORMAT);
	int type = ilGetInteger(IL_IMAGE_TYPE);

	int size = width * height * depth;

	if (format == format == IL_RGBA || format == IL_BGRA)
		size *= 4;
	else if (format == IL_RGB || format == IL_BGR)
		size *= 3;

	if (type == IL_FLOAT)
		size *= 4;

	void* copyPixels = new unsigned char[size];

	ilCopyPixels(0, 0, 0, width, height, depth, format, type, copyPixels);

	// определяем модель памяти (параметры распаковки) 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glActiveTexture(GL_TEXTURE0);

	glGenTextures(1, &texIndex);
	glBindTexture(GL_TEXTURE_2D, texIndex);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, copyPixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// удаляем "изображение" 
	ilDeleteImage(imageId);
	delete[] copyPixels;
}

void Texture::apply(TextureFilter texFilter)
{
	glBindTexture(GL_TEXTURE_2D, texIndex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(texFilter));
}

void Texture::disableAll()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
