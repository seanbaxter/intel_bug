#version 460

layout(binding=0)
uniform Buf2 {
	ivec4 pos;
};

void main() {
	gl_Position = vec4(pos);
}