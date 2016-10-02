#version 330
uniform sampler2D tex;
uniform vec4 color;
in vec2 TexCoord;
out vec4 fragcolor;
void main() {
    fragcolor = color;
}
