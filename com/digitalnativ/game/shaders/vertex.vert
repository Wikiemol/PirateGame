#version 330

uniform vec2 screenDimensions;
uniform vec2 objectDimensions;
uniform mat2x2 rotation;
uniform vec2 translation;
in vec3 pos;
in vec2 texCoord;
out vec2 TexCoord;
void main() {
    vec3 position = pos;
    position.xy *= objectDimensions;
    position.xy *= rotation;
    position.xy += translation;
    position.xy /= screenDimensions;
    gl_Position.xyz = position;
    gl_Position.w = 1;
    TexCoord = texCoord;
}
