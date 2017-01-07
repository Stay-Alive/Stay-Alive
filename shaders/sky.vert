#version 330 core

// IN variables
layout(location=0) in vec4 position;
layout(location=1) in vec2 uv;
layout(location=2) in vec3 normal;

// Matricies
uniform mat4 matrix;

out vec2 frag_uv;

void main() {
    frag_uv = uv;
	// Get the final position
	gl_Position = matrix * position;
}
