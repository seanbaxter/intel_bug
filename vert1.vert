#version 460

layout(binding=0)
uniform Buf1 {
	vec4 pos;
	vec4 another;
};

void main() {
	gl_Position = pos;
}