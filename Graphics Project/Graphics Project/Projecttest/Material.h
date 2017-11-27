#pragma once
#ifndef ___Material__
#define ___Material__
#include "GL/glew.h"
#include "Vector3f.h"
#include "Shader.h"
class Material {
	int texId;
	float shininess;
	Vector3f diffuseCoefficient;
	Vector3f specularCoefficient;
public:
	Material(int texId, float shininess, 
		Vector3f diffuseCoefficient, Vector3f specularCoefficient);

	void bind(Shader *s);

};
#endif 
