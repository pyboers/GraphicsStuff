#include "Light.h"
Light::Light(int Id, float intensity, Vector3f pos, Vector3f diffuseCoefficient, Vector3f specularCoefficient, Vector3f attenuation)  : Id(Id), intensity(intensity), pos(pos), diffuseCoefficient(diffuseCoefficient), specularCoefficient(specularCoefficient), attenuation(attenuation){
	if (Id > MAX_LIGHTS) {
		printf("Error Light Id: %d is more than MAX_LIGHTS: %d", Id, MAX_LIGHTS);
	}
}

void Light::updateShader(Shader * s) {
	s->bind();
	s->uniformi("light_amt", Id+1);
	char * buf = (char *)malloc(sizeof(char) * 32);
	sprintf(buf, "lights[%d].", Id);
	char * var = (char *)malloc(sizeof(char) * 128);
	strcpy(var, buf);
	strcat(var, "diffuseCoefficient");
	s->uniformVec3(var, &diffuseCoefficient);
	strcpy(var, buf);
	strcat(var, "intensity");
	s->uniformf(var, intensity);
	strcpy(var, buf);
	strcat(var, "specularCoefficient");
	s->uniformVec3(var, &specularCoefficient);
	strcpy(var, buf);
	strcat(var, "att");
	s->uniformVec3(var, &attenuation);
	strcpy(var, buf);
	strcat(var, "pos");
	s->uniformVec3(var, &pos);

}

void Light::updateAmbient(Shader * s, Vector3f *ambient) {
	s->bind();
	s->uniformVec3("ambientLighting", ambient);
}
