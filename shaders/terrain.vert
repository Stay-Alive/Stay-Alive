// reference: https://github.com/iZastic/OpenGL_3D_Game_Tutorial
#version 330 core

// IN variables
layout(location=0) in vec3 position;
layout(location=1) in vec2 texCoords;
layout(location=2) in vec3 normal;

// OUT variables
out vec2 textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

// Matricies
uniform mat4 transformMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform float terrainSize;

uniform vec3 lightPosition;

float randSO(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float TerrainHeight(vec3 vCoordPos)
{
    float fNoiseCoordScale = 1.0;
	float heightScale = 1.0;

    float fValueHeight = randSO(vec2(vCoordPos.x / terrainSize * fNoiseCoordScale, vCoordPos.z / terrainSize * fNoiseCoordScale));;

     return heightScale * (fValueHeight - vCoordPos.y);
}

void main()
{
	// Calculate the position of the object in the world
	//vec4 worldPosition = transformMatrix * vec4(position.x, TerrainHeight(position), position.z, 1.0);
    vec4 worldPosition = transformMatrix * vec4(position.x, position.y, position.z, 1.0);

	// Multiply the normal by transformation matrix (fixes normal if object is rotated)
	surfaceNormal = (transformMatrix * vec4(normal, 0.0)).xyz;
	// Get the vector of the light from the position the object is in the world
	toLightVector = lightPosition - worldPosition.xyz;
	// Get the vector to the camera from the position of the object
	toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

	// Pass the texture coords to the next shader with tile ammount
	textureCoords = texCoords * 40.0;

	// Get the final position
	gl_Position = projectionMatrix * viewMatrix * worldPosition;
}
