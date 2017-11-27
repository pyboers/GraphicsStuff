#version 330 core

in vec2 texel;

layout(location = 0) out vec4 fragcolor;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
	float ran = rand(texel);
	if(ran < 0.85){
		ran = 1;
	}else{
		ran = 0;
	}
	fragcolor = vec4(ran,ran,ran,ran);

}