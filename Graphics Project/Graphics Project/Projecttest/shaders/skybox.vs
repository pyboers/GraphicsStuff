#version 330 core

uniform mat4 vp;

//out vec2 texel;
out vec3 dir;

void main() {
	vec2 pos = vec2((gl_VertexID & 2) >> 1, 1 - (gl_VertexID & 1)) * 2.0 - 1.0;
	vec4 front = inverse(vp) * vec4(pos, -1.0, 1.0);
	vec4 back = inverse(vp) * vec4(pos,  1.0, 1.0);

	dir = back.xyz / back.w - front.xyz / front.w;
	gl_Position = vec4(pos,0.0,1.0);
}