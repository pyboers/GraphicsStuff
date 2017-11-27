#include "Material.h"

Material::Material(int texId, float shininess, Vector3f diffuseCoefficient, Vector3f specularCoefficient) : texId(texId), shininess(shininess), diffuseCoefficient(diffuseCoefficient), specularCoefficient(specularCoefficient){

}

void Material::bind(Shader *s) {
	s->uniformVec3("material_specularCoefficient", &specularCoefficient);
	s->uniformVec3("material_diffuseCoefficient", &diffuseCoefficient);
	s->uniformf("material_shininess", shininess);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texId);
	s->uniformi("texture0", 0);
}
