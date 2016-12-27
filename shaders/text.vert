#version 330 core

// IN variables
layout(location=0) in vec3 position;
layout(location=1) in vec2 texCoords;

// Matricies
uniform mat4 matrix;

out vec2 fragment_uv;

void main() {
    fragment_uv = textureCoords;
	// Get the final position
	gl_Position = matrix * vec4(position, 1.0);
}
