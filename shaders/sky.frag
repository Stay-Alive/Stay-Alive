#version 330 core

in vec2 fragment_uv;

uniform sampler2D textureSampler;
uniform float timer;

out vec4 fragColor;

void main() {
    vec2 uv = vec2(timer, fragment_uv.t);
    vec4 color = texture(textureSampler, uv);
    color.a = max(color.a, 0.4);
    fragColor = color;
}
