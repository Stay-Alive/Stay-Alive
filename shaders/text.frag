// https://github.com/fogleman/Craft
#version 330 core

in vec2 fragment_uv;

uniform sampler2D textureSampler;

out vec4 fragColor;

void main() {
    vec4 color = texture(textureSampler, fragment_uv);
    color.a = max(color.a, 0.4);
    fragColor = color;
}
