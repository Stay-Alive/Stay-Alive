#version 330 core

// IN variables
layout(location=0) in vec4 position;
layout(location=1) in vec2 uv;

// Matricies
uniform mat4 matrix;

out vec2 fragment_uv;

void main() {
    fragment_uv = uv;
	// Get the final position
	gl_Position = matrix * position;
}
