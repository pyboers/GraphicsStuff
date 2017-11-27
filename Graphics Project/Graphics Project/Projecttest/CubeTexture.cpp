#include "CubeTexture.h"

#ifdef _WIN32
#include <windows.h>
#include <GL/glew.h>
#endif

#include <iostream>

using namespace std;

static unsigned char * loadImage(char * fileName, BITMAPFILEHEADER *fileHeader, BITMAPINFOHEADER *infoHeader) {
	FILE *bitmapFile = fopen(fileName, "r");
	unsigned char *pixelBuffer;
	// Check file opened
	if (bitmapFile == NULL) {
		printf("Error: Failed to open the file at path %s\n", fileName);
		delete[] bitmapFile;
		return nullptr;	// error
	}
	fread(fileHeader, 14, 1, bitmapFile);

	// Check for valid window bitmap
	if (fileHeader->bfType != 0x4D42) {
		printf("Error: Trying to load %s it is in an invalid bitmap format.\n", fileName);
		fclose(bitmapFile);
		return nullptr;	// error
	}

	// read in file header
	fread(infoHeader, sizeof(BITMAPINFOHEADER), 1, bitmapFile);

	// Check the image is at least RGB ... i.e 24 bits per pixel
	if (infoHeader->biBitCount < 24) {
		printf("Error: Trying to load %s.\nThe file is not in RGB or RGBA format.\nIt may be in grayscale format, open it in an image editor of your choice and change the image mode to RGB or RGBA.\n", fileName);
		fclose(bitmapFile);
		return nullptr;	// error
	}

	// ofset the pointer to the start of the pixel data
	fseek(bitmapFile, fileHeader->bfOffBits, SEEK_SET);

	// Read in the pixel data
	pixelBuffer = new unsigned char[infoHeader->biWidth * infoHeader->biHeight * (infoHeader->biBitCount / 8)];
	fread(pixelBuffer, sizeof(unsigned char), infoHeader->biWidth * infoHeader->biHeight * (infoHeader->biBitCount / 8), bitmapFile);

	// If texture is in ABGR format swizzle it into RGBA for openGL upload
	if (infoHeader->biBitCount == 32) {
		unsigned char c;
		for (int i = 0; i < infoHeader->biWidth * infoHeader->biHeight; i++) {
			c = pixelBuffer[i * 4];
			pixelBuffer[i * 4] = pixelBuffer[i * 4 + 3];
			pixelBuffer[i * 4 + 3] = c;
			c = pixelBuffer[i * 4 + 1];
			pixelBuffer[i * 4 + 1] = pixelBuffer[i * 4 + 2];
			pixelBuffer[i * 4 + 2] = c;
		}
	}
	fclose(bitmapFile);
	return pixelBuffer;
}

// Loads a bitmap into texture memory
int CubeTexture::GetTexture(char * fileName) {
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	GLuint texObject;
	glGenTextures(1, &texObject);
	int i;
	for (i = 0; i < 6; i++) {
		//load textures
		char buf[64];

		sprintf(buf, "%s%d.bmp", fileName, i);
		unsigned char *pixelBuffer = loadImage(buf,  &fileHeader, &infoHeader);

		// Bin to buffer
		glBindTexture(GL_TEXTURE_CUBE_MAP, texObject);

		// Upload texture data
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, static_cast<GLint>(0), infoHeader.biBitCount == 32 ? GL_RGBA : GL_RGB,
			static_cast<GLsizei>(infoHeader.biWidth), static_cast<GLsizei>(infoHeader.biHeight),
			static_cast<GLint>(0), infoHeader.biBitCount == 32 ? GL_RGBA : GL_BGR_EXT, GL_UNSIGNED_BYTE,
			static_cast<GLvoid*>(pixelBuffer));

		// Delete old copy of pixel data
		delete[] pixelBuffer;
	}
	// Set texture parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	

	return static_cast<int>(texObject);
}