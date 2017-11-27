#version 330 core

in vec2 texel;

uniform sampler2D lastframe;
uniform vec2 dimensions;

layout(location = 0) out vec4 fragcolor;

int countNeighbors(vec2 pos){
	float distx = 1/dimensions.x;
	float disty = 1/dimensions.y;
	int count = 0;
	if(texture(lastframe, pos + vec2(-distx, -disty)).r > 0.5){
		count++;
	}
	
	if(texture(lastframe, pos + vec2(-distx, 0)).r > 0.5){
		count++;
	}
	
	if(texture(lastframe, pos + vec2(-distx, disty)).r > 0.5){
		count++;
	}
	
	if(texture(lastframe, pos + vec2(0, disty)).r > 0.5){
		count++;
	}
	
	if(texture(lastframe, pos + vec2(distx, disty)).r > 0.5){
		count++;
	}
	
	if(texture(lastframe, pos + vec2(distx, 0)).r > 0.5){
		count++;
	}
	
	if(texture(lastframe, pos + vec2(distx, -disty)).r > 0.5){
		count++;
	}
	
	if(texture(lastframe, pos + vec2(0, -disty)).r > 0.5){
		count++;
	}
	
	return count;
}

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

//Dayand night
//const int rules[18] = int[18](/*0*/0, /*1*/0, /*2*/ 0, /*3*/1, /*4*/0, /*5*/0, /*6*/1, /*7*/1, /*8*/1,/*Live*/ /*0*/0, /*1*/0, /*2*/ 0, /*3*/1, /*4*/1, /*5*/0, /*6*/1, /*7*/1, /*8*/1);
//GameOfLife
//const int rules[18] = int[18](/*0*/0, /*1*/0, /*2*/ 0, /*3*/1, /*4*/0, /*5*/0, /*6*/0, /*7*/0, /*8*/0,/*Live*/ /*0*/0, /*1*/0, /*2*/ 1, /*3*/1, /*4*/0, /*5*/0, /*6*/0, /*7*/0, /*8*/0);
//HighLife
//const int rules[18] = int[18](/*0*/0, /*1*/0, /*2*/ 0, /*3*/1, /*4*/0, /*5*/0, /*6*/1, /*7*/0, /*8*/0,/*Live*/ /*0*/0, /*1*/0, /*2*/ 1, /*3*/1, /*4*/0, /*5*/0, /*6*/0, /*7*/0, /*8*/0);
//Seeds
const int rules[18] = int[18](/*0*/0, /*1*/0, /*2*/ 1, /*3*/0, /*4*/0, /*5*/0, /*6*/0, /*7*/0, /*8*/0,/*Live*/ /*0*/0, /*1*/0, /*2*/ 0, /*3*/0, /*4*/0, /*5*/0, /*6*/0, /*7*/0, /*8*/0);
void main(){
	int count = countNeighbors(texel);
	float r = texture(lastframe, texel).r;
	if(r > 0.5){
		r = 1;
	}else{
		r = 0;
	}
	highp int curralive = int(r);
	int alive = rules[count + (curralive*9)];
	fragcolor = vec4(alive,alive,alive,1);

}