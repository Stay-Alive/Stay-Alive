#version 330 core

in vec2 fragment_uv;

uniform sampler2D textureSampler;

void main() {
    vec4 color = texture2D(sampler, fragment_uv);
    color.a = max(color.a, 0.4);
    gl_FragColor = color;
}
