#pragma once

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <map>
#include <string>

/**
* Class for loading bitmap files into texture buffer and handling texture IDs
*/
class CubeTexture {
public:
	/** Loads a texture into memory and returns the id of the texture object created */
	static int GetTexture(char * fileName);
};