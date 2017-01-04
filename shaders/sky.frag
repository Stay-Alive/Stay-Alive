#version 330 core

in vec2 fragment_uv;

uniform float timer;
uniform sampler2D textureSampler;

out vec4 fragColor;

void main() {
    vec2 uv = vec2(timer, fragment_uv.t);
    fragColor = texture(textureSampler, uv);
}
