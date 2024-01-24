#version 450 core

layout(location = 0) in vec2 pos;
out vec2 uv;

uniform mat4 transform;

void main() {
    uv = (pos + 1.0) / 2.0;
    gl_Position = transform * vec4(pos.x, pos.y, 0.0, 1.0);
}
