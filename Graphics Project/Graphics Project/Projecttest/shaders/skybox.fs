#version 330 core

in vec3 dir;

uniform samplerCube cubeMap;

layout(location = 0) out vec4 fragcolor;

const float gamma = 2.2;

vec4 texture_gamma(samplerCube tex, vec3 texdir){
	vec4 texcol = texture(tex, texdir);
	return vec4(pow(texcol.rgb, vec3(gamma)), texcol.a);
}

void main(){
	fragcolor = texture_gamma(cubeMap, dir);

}