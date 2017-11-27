#pragma once
#ifndef ___LIGHT__
#define ___LIGHT__
#define _CRT_SECURE_NO_WARNINGS
#include "Vector3f.h"
#include "Shader.h"
#define MAX_LIGHTS 0
class Light{
private:
	Vector3f diffuseCoefficient;
	Vector3f specularCoefficient;
	Vector3f attenuation;
	Vector3f pos;
	int Id;
public:
	float intensity;
	Light(int Id, float intensity, Vector3f pos, Vector3f diffuseCoefficient, Vector3f specularCoefficient, Vector3f attenuation);
	void updateShader(Shader *s);

	static void updateAmbient(Shader *s, Vector3f *ambient);

};
#endif